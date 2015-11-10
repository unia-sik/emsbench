/*
 * This file is part of EmsBench.
 *
 * Copyright 2015 University of Augsburg
 *
 * EmsBench is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EmsBench is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EmsBench.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * $Id: header-ems.c 480 2015-10-27 12:42:40Z klugeflo $
 * @file init.c
 * @brief Initialise the devices state
 *
 * Setup, configure and initialise all aspects of the devices state including
 * but not limited to:
 *
 * - Setup the bus clock speed
 * - Configuration based variable initialisation
 * - I/O register behaviour and initial state
 * - Configure and enable interrupts
 * - Copy tunable data up to RAM from flash
 * - Configure peripheral module behaviour
 *
 * <h> original author</h> Fred Cooke
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

#define INIT_C
#include "hal/ems/freeems_hal.h"
#include "inc/freeEMS.h"
#include "inc/flashWrite.h"
#include "inc/interrupts.h"
#include "inc/utils.h"
#include "inc/commsISRs.h"
#include "inc/pagedLocationBuffers.h"
#include "inc/init.h"
#include "inc/DecoderInterface.h"
#include "inc/xgateVectors.h"
#include <string.h>

#include <hal/ems/freeems_hal.h>

/** @brief The main top level init
 *
 * The main init function to be called from main.c before entering the main
 * loop. This function is simply a delegator to the finer grained special
 * purpose init functions.
 *
 * @author Fred Cooke
 */
void init() {
  /* Disable ALL interrupts while we configure the board ready for use */
  ATOMIC_START();
  /* Copy table and config blocks of data from flash to the paged ram blocks for
   * fast data lookup */
  initAllPagedRAM();
  /* Initialise the rest of the running variables etc */
  initVariables();
  /* TODO, finalise this */
  initFlash();
  /* TODO Set user/feature/config up here! */
  initConfiguration();
  /* Re-enable any configured interrupts */
  ATOMIC_END();
}




/** @brief Set the PLL clock frequency
 *
 * Set the Phase Locked Loop to our desired frequency (80MHz) and switch to
 * using it for clock (40MHz bus speed).
 *
 * @note This function is not used any more, but will be kept, because some of
 *       the comments may be usefull in the future.
 * @author Fred Cooke
 */
void initPLL() {
  /* Switches to base external OSCCLK to ensure PLL is not being used (off out
   * of reset, but not sure if the monitor turns it on before passing control or
   * not)
   */
  CLKSEL &= PLLSELOFF;
  /* Turn the PLL device off to adjust its speed (on by default out of reset) */
  PLLCTL &= PLLOFF;
  /* 16MHz / (3 + 1) = 4MHz Bus frequency */
  REFDV = PLLDIVISOR;
  /* 4MHz * (9 + 1) = 40MHz Bus frequency */
  SYNR = PLLMULTIPLIER;
  /* Turn the PLL device back on again at 80MHz */
  PLLCTL |= PLLON;

  while (!(CRGFLG & PLLLOCK)) {
    /* Do nothing while we wait till the PLL loop locks onto the target
     * frequency. Target frequency is given by
     * (2 * (crystal frequency / (REFDV + 1)) * (SYNR + 1))
     * Bus frequency is half PLL frequency and given by
     * ((crystal frequency / (REFDV + 1)) * (SYNR + 1))
     */
  }

  /* Switches to PLL clock for internal bus frequency	*/
  CLKSEL = PLLSELON;
  /* from MC9S12XDP512V2.pdf Section 2.4.1.1.2 page 101 Third paragraph	*/
  /* "This takes a MAXIMUM of 4 OSCCLK clock cylces PLUS 4 PLL clock cycles"*/
  /* "During this time ALL clocks freeze, and CPU activity ceases"	*/
  /* Therefore there is no point waiting for this to occur, we already are...*/
}


/**
 *  Configure all the I/O to default values to keep power use down etc
 *  @note This function is not used any more, but will be kept, because some of
 *        the comments may be usefull in the future.
 * */
void initIO() {
  /* for now, hard code all stuff to be outputs as per Freescale documentation,
  * later what to do will be pulled from flash configuration such that all
  * things are setup at once, and not messed with thereafter. when the port
  * something uses is changed via the tuning interface, the confuration will be
  * done on the fly, and the value burned to flash such that next boot happens
  * correctly and current running devices are used in that way.

   */

  /* Turn off and on and configure all the modules in an explicit way */
  // TODO set up and turn off all modules (CAN,SCI,SPI,IIC,etc)


  /* And configure them all for analog input */
  /* Turns on the ADC block and sets auto flag clear */
  ATD0CTL2 = 0xC0;
  /* Set sequence length = 8 */
  ATD0CTL3 = 0x40;
  /* Set the ADC clock and sample period for best accuracy */
  ATD0CTL4 = 0x73;
  /* Sets justification to right, multiplex and scan all channels. Writing to
   * this causes conversions to begin */
  ATD0CTL5 = 0xB0;

  /* And configure them all for analog input */
  /* TODO bring this out of config based on chip variant variable. Sets wrap on
   * 8th ADC because we can't use the other 8 on 112 pin version */
  ATD1CTL0 = 0x07;
  /* Turns on the ADC block and sets auto flag clear */
  ATD1CTL2 = 0xC0;
  /* Set sequence length = 8 */
  ATD1CTL3 = 0x40;
  /* Set the ADC clock and sample period for best accuracy */
  ATD0CTL4 = 0x73;
  /* Sets justification to right, multiplex and scan all channels. Writing to
   * this causes conversions to begin */
  ATD0CTL5 = 0xB0;

#ifndef NO_INIT
  /* Set up the PWM component and initialise its values to off */
  /* Turn on PWM 0 - 6 (7 is user LED on main board) */
  PWME = 0x7F;
  /* The fastest we can go for all channels */
  PWMCLK = ZEROS;
  /* The fastest prescaler we can go for all channels */
  PWMPRCLK = ZEROS;
  /* The fastest we can go */
  PWMSCLA = ZEROS;
  /* The fastest we can go */
  PWMSCLB = ZEROS;
  /* TODO PWM channel concatenation for high resolution */
  // join channel pairs together here (needs 16 bit regs enabled too)
  /*TODO Initialise pwm channels with frequency, and initial duty for real use*/
  // initial PWM settings for testing
  /* PWM periods */
  PWMPER0 = 0xFF; // 255 for ADC0 testing
  PWMPER1 = 0xFF; // 255 for ADC1 testing
  PWMPER2 = 0xFF; // 255 for ADC1 testing
  PWMPER3 = 0xFF; // 255 for ADC1 testing
  PWMPER4 = 0xFF; // 255 for ADC1 testing
  PWMPER5 = 0xFF; // 255 for ADC1 testing
  PWMPER6 = 0xFF; // 255 for ADC1 testing
  PWMPER7 = 0xFF; // 255 for ADC1 testing
  /* PWM duties */
  PWMDTY0 = 0;
  PWMDTY1 = 0;
  PWMDTY2 = 0;
  PWMDTY3 = 0;
  PWMDTY4 = 0;
  PWMDTY5 = 0;
  PWMDTY6 = 0;
  PWMDTY7 = 0;


  /* Initialise the state of pins configured as output */
  /* Initialise to low such that transistor grounded things are all turned off
   * by default. */
  /* The serial monitor pin is on 0x40, and could cause problems if capacitance
   * at the output is large when a reset occurs. */
  PORTA = ZEROS;
  /* Init the rest of the spark outputs as off */
  PORTB = ZEROS;
  /* 0b_0001_1111 : when not in use 0b_1001_1111 PE7 should be high PE5 and PE6
   * should be low, the rest high */
  PORTE = 0x1F;
  PORTK = ZEROS;
  PORTS = ZEROS;
  /* All pins in off state at boot up (only matters for 2 - 7) */
  PORTT = ZEROS;
  PORTM = ZEROS;
  // TODO hook these up to the adc channels such that you can vary the
  //      brightness of an led with a pot.
  PORTP = ZEROS;
  PORTH = ZEROS;
  PORTJ = ZEROS;
  /* AD0PT1 You are out of your mind if you waste this on digital Inputs */
  /* AD1PT1 You are out of your mind if you waste this on digital Inputs */

  /* Initialise the Data Direction Registers */
  /* To outputs based on the note at the end of chapter
   * 1.2.2 of MC9S12XDP512V2.pdf */

  /* GPIO (8) */
  DDRA = ONES;
  /* GPIO (8) */
  DDRB = ONES;
  /* 0b_1111_1100 : Clock and mode pins PE0,PE1 are input only pins, the rest
   * are GPIO */
  DDRE = 0xFC;
  /* Only 0,1,2,3,4,5,7, NOT 6 (7) */
  DDRK = ONES;
  /* SCI0, SCI1, SPI0 (8) */
  DDRS = ONES;
  /* 0b_1111_1100 set ECT pins 0,1 to IC and 2:7 to OC (8) */
  DDRT = 0xFC;
  /* CAN 0 - 3 (8) */
  DDRM = ONES;
  /* PWM pins (8) */
  DDRP = ONES;
  /* All pins configured as input for misc isrs (SPI1, SPI2) (8) */
  DDRH = ZEROS;
  /* Only 0,1,6,7 are brought out on the 112 pin chip (4) */
  DDRJ = ONES;
  /* Configure the non bonded pins to output to avoid current drain
   * (112 pin package) */
  /* NON-bonded external data bus pins */
  DDRC = ONES;
  /* NON-bonded external data bus pins */
  DDRD = ONES;
  /* AD0DDR1 You are out of your mind if you waste this on digital Inputs */
  /* AD1DDR1 You are out of your mind if you waste this on digital Inputs */
#endif
}


/** @brief Buffer lookup tables addresses
 *
 * Save pointers to the lookup tables which live in paged flash.
 *
 * @note Many thanks to Jean Bélanger for the inspiration/idea to do this!
 * @note This function is not used any more, but will be kept, because some of
 *       the comments may be usefull in the future.
 * @author Fred Cooke
 */
void initLookupAddresses() {
  IATTransferTableLocation = (void*)&IATTransferTable;
  CHTTransferTableLocation = (void*)&CHTTransferTable;
  MAFTransferTableLocation = (void*)&MAFTransferTable;
  TestTransferTableLocation = (void*)&TestTransferTable;
}


/** @brief Buffer fuel tables addresses
 *
 * Save pointers to the fuel tables which live in paged flash.
 *
 * @note Many thanks to Jean Bélanger for the inspiration/idea to do this!
 * @note This function is not used any more, but will be kept, because some of
 *       the comments may be usefull in the future.
 * @author Fred Cooke
 */
void initFuelAddresses() {
  /* Setup addresses within the page to avoid warnings */
  VETableMainFlashLocation		= (void*)&VETableMainFlash;
  VETableSecondaryFlashLocation	= (void*)&VETableSecondaryFlash;
  VETableTertiaryFlashLocation	= (void*)&VETableTertiaryFlash;
  LambdaTableFlashLocation		= (void*)&LambdaTableFlash;
  VETableMainFlash2Location		= (void*)&VETableMainFlash2;
  VETableSecondaryFlash2Location	= (void*)&VETableSecondaryFlash2;
  VETableTertiaryFlash2Location	= (void*)&VETableTertiaryFlash2;
  LambdaTableFlash2Location		= (void*)&LambdaTableFlash2;
}


/** @brief Copy fuel tables to RAM
 *
 * Initialises the fuel tables in RAM by copying them up from flash.
 * @note This function is not used any more, but will be kept, because some of
 *       the comments may be usefull in the future.
 * @author Fred Cooke
 */
void initPagedRAMFuel(void) {
  /* Copy the tables from flash to RAM */
  RPAGE = RPAGE_FUEL_ONE;
  memcpy((void*)&TablesA,	VETableMainFlashLocation,		MAINTABLE_SIZE);
  memcpy((void*)&TablesB,	VETableSecondaryFlashLocation,	MAINTABLE_SIZE);
  memcpy((void*)&TablesC,	VETableTertiaryFlashLocation,	MAINTABLE_SIZE);
  memcpy((void*)&TablesD,	LambdaTableFlashLocation,		MAINTABLE_SIZE);
  RPAGE = RPAGE_FUEL_TWO;
  memcpy((void*)&TablesA,	VETableMainFlash2Location,		MAINTABLE_SIZE);
  memcpy((void*)&TablesB,	VETableSecondaryFlash2Location,	MAINTABLE_SIZE);
  memcpy((void*)&TablesC,	VETableTertiaryFlash2Location,	MAINTABLE_SIZE);
  memcpy((void*)&TablesD,	LambdaTableFlash2Location,		MAINTABLE_SIZE);
}


/** @brief Buffer timing tables addresses
 *
 * Save pointers to the timing tables which live in paged flash.
 *
 * @note Many thanks to Jean Bélanger for the inspiration/idea to do this!
 * @note This function is not used any more, but will be kept, because some of
 *       the comments may be usefull in the future.
 * @author Fred Cooke
 */
void initTimingAddresses() {
  /* Setup addresses within the page to avoid warnings */
  IgnitionAdvanceTableMainFlashLocation			= (void*)&IgnitionAdvanceTableMainFlash;
  IgnitionAdvanceTableSecondaryFlashLocation		= (void*)&IgnitionAdvanceTableSecondaryFlash;
  InjectionAdvanceTableMainFlashLocation			= (void*)&InjectionAdvanceTableMainFlash;
  InjectionAdvanceTableSecondaryFlashLocation		= (void*)&InjectionAdvanceTableSecondaryFlash;
  IgnitionAdvanceTableMainFlash2Location			= (void*)&IgnitionAdvanceTableMainFlash2;
  IgnitionAdvanceTableSecondaryFlash2Location		= (void*)&IgnitionAdvanceTableSecondaryFlash2;
  InjectionAdvanceTableMainFlash2Location			= (void*)&InjectionAdvanceTableMainFlash2;
  InjectionAdvanceTableSecondaryFlash2Location	= (void*)&InjectionAdvanceTableSecondaryFlash2;
}


/** @brief Copy timing tables to RAM
 *
 * Initialises the timing tables in RAM by copying them up from flash.
 * @note This function is not used any more, but will be kept, because some of
 *       the comments may be usefull in the future.
 * @author Fred Cooke
 */
void initPagedRAMTime() {
  /* Copy the tables from flash to RAM */
  RPAGE = RPAGE_TIME_ONE;
  memcpy((void*)&TablesA,	IgnitionAdvanceTableMainFlashLocation,			MAINTABLE_SIZE);
  memcpy((void*)&TablesB,	IgnitionAdvanceTableSecondaryFlashLocation,		MAINTABLE_SIZE);
  memcpy((void*)&TablesC,	InjectionAdvanceTableMainFlashLocation,			MAINTABLE_SIZE);
  memcpy((void*)&TablesD,	InjectionAdvanceTableSecondaryFlashLocation,	MAINTABLE_SIZE);
  RPAGE = RPAGE_TIME_TWO;
  memcpy((void*)&TablesA,	IgnitionAdvanceTableMainFlash2Location,			MAINTABLE_SIZE);
  memcpy((void*)&TablesB,	IgnitionAdvanceTableSecondaryFlash2Location,	MAINTABLE_SIZE);
  memcpy((void*)&TablesC,	InjectionAdvanceTableMainFlash2Location,		MAINTABLE_SIZE);
  memcpy((void*)&TablesD,	InjectionAdvanceTableSecondaryFlash2Location,	MAINTABLE_SIZE);
}


/** @brief Buffer tunable tables addresses
 *
 * Save pointers to the tunable tables which live in paged flash and their
 * sub-sections too.
 *
 * @note Many thanks to Jean Bélanger for the inspiration/idea to do this!
 * @note This function is not used any more, but will be kept, because some of
 *       the comments may be usefull in the future.
 * @author Fred Cooke
 */
void initTunableAddresses() {
  /* Setup addresses within the page to avoid warnings */
  SmallTablesAFlashLocation 	= (void*)&SmallTablesAFlash;
  SmallTablesBFlashLocation 	= (void*)&SmallTablesBFlash;
  SmallTablesCFlashLocation 	= (void*)&SmallTablesCFlash;
  SmallTablesDFlashLocation 	= (void*)&SmallTablesDFlash;
  SmallTablesAFlash2Location	= (void*)&SmallTablesAFlash2;
  SmallTablesBFlash2Location	= (void*)&SmallTablesBFlash2;
  SmallTablesCFlash2Location	= (void*)&SmallTablesCFlash2;
  SmallTablesDFlash2Location	= (void*)&SmallTablesDFlash2;

  /* TablesA */
  dwellDesiredVersusVoltageTableLocation    = (void*)&SmallTablesAFlash.dwellDesiredVersusVoltageTable;
  dwellDesiredVersusVoltageTable2Location   = (void*)&SmallTablesAFlash2.dwellDesiredVersusVoltageTable;
  injectorDeadTimeTableLocation             = (void*)&SmallTablesAFlash.injectorDeadTimeTable;
  injectorDeadTimeTable2Location            = (void*)&SmallTablesAFlash2.injectorDeadTimeTable;
  postStartEnrichmentTableLocation          = (void*)&SmallTablesAFlash.postStartEnrichmentTable;
  postStartEnrichmentTable2Location         = (void*)&SmallTablesAFlash2.postStartEnrichmentTable;
  engineTempEnrichmentTableFixedLocation    = (void*)&SmallTablesAFlash.engineTempEnrichmentTableFixed;
  engineTempEnrichmentTableFixed2Location   = (void*)&SmallTablesAFlash2.engineTempEnrichmentTableFixed;
  primingVolumeTableLocation                = (void*)&SmallTablesAFlash.primingVolumeTable;
  primingVolumeTable2Location               = (void*)&SmallTablesAFlash2.primingVolumeTable;
  engineTempEnrichmentTablePercentLocation  = (void*)&SmallTablesAFlash.engineTempEnrichmentTablePercent;
  engineTempEnrichmentTablePercent2Location = (void*)&SmallTablesAFlash2.engineTempEnrichmentTablePercent;
  dwellMaxVersusRPMTableLocation            = (void*)&SmallTablesAFlash.dwellMaxVersusRPMTable;
  dwellMaxVersusRPMTable2Location           = (void*)&SmallTablesAFlash2.dwellMaxVersusRPMTable;

  /* TablesB */
  perCylinderFuelTrimsLocation  = (void*)&SmallTablesBFlash.perCylinderFuelTrims;
  perCylinderFuelTrims2Location = (void*)&SmallTablesBFlash2.perCylinderFuelTrims;

  /* TablesC */
  // TODO

  /* TablesD */
  // TODO

  /* filler defs */
  fillerALocation  = (void*)&SmallTablesAFlash.filler;
  fillerA2Location = (void*)&SmallTablesAFlash2.filler;
  fillerBLocation  = (void*)&SmallTablesBFlash.filler;
  fillerB2Location = (void*)&SmallTablesBFlash2.filler;
  fillerCLocation  = (void*)&SmallTablesCFlash.filler;
  fillerC2Location = (void*)&SmallTablesCFlash2.filler;
  fillerDLocation  = (void*)&SmallTablesDFlash.filler;
  fillerD2Location = (void*)&SmallTablesDFlash2.filler;
}


/**
 * @note This function is not used any more, but will be kept, because some of
 *       the comments may be usefull in the future.
 */
void initPagedRAMTune() {
  /* Copy the tables from flash to RAM */
  RPAGE = RPAGE_TUNE_ONE;
  memcpy((void*)&TablesA,	SmallTablesAFlashLocation,	MAINTABLE_SIZE);
  memcpy((void*)&TablesB,	SmallTablesBFlashLocation,	MAINTABLE_SIZE);
  memcpy((void*)&TablesC,	SmallTablesCFlashLocation,	MAINTABLE_SIZE);
  memcpy((void*)&TablesD,	SmallTablesDFlashLocation,	MAINTABLE_SIZE);
  RPAGE = RPAGE_TUNE_TWO;
  memcpy((void*)&TablesA,	SmallTablesAFlash2Location,	MAINTABLE_SIZE);
  memcpy((void*)&TablesB,	SmallTablesBFlash2Location,	MAINTABLE_SIZE);
  memcpy((void*)&TablesC,	SmallTablesCFlash2Location,	MAINTABLE_SIZE);
  memcpy((void*)&TablesD,	SmallTablesDFlash2Location,	MAINTABLE_SIZE);
}


/** @brief Buffer addresses of paged data
 *
 * Save the paged memory addresses to variables such that we can access them
 * from another paged block with no warnings.
 *
 * If you try to access paged data from the wrong place you get nasty warnings.
 * These calls to functions that live in the same page that they are addressing
 * prevent those warnings.
 *
 * @note Many thanks to Jean Bélanger for the inspiration/idea to do this!
 * @note This function is not used any more, but will be kept, because some of
 *       the comments may be usefull in the future.
 * @author Fred Cooke
 */
void initAllPagedAddresses() {
  /* Setup pointers to lookup tables */
  initLookupAddresses();
  /* Setup pointers to the main tables */
  initFuelAddresses();
  initTimingAddresses();
  initTunableAddresses();
}


/** @brief Copies paged flash to RAM
 *
 * Take the tables and config from flash up to RAM to allow live tuning.
 *
 * For the main tables and other paged config we need to adjust
 * the RPAGE value to the appropriate one before copying up.
 *
 * This function is simply a delegator to the ones for each flash page. Each
 * one lives in the same paged space as the data it is copying up.
 *
 * @author Fred Cooke
 */
void initAllPagedRAM() {
  /* Setup the flash block pointers before copying flash to RAM using them */
  initAllPagedAddresses();

  /*Copy the tables up to their paged RAM blocks through the window from flash*/
  initPagedRAMFuel();
  initPagedRAMTime();
  initPagedRAMTune();

  /* Default to page one for now, perhaps read the configured port straight out
   * of reset in future? TODO */
  setupPagedRAM(TRUE); // probably something like (PORTA & TableSwitchingMask)
}


/* Initialise and set up all running variables that require a non-zero start
 * value here */
/* All other variables are initialised to zero by the premain built in code*/
void initVariables() {
  /* And the opposite for the other halves */
  CoreVars = &CoreVars0;
  DerivedVars = &DerivedVars0;
  ADCArrays = &ADCArrays0;
  ADCArraysRecord = &ADCArrays1;
  asyncADCArrays = &asyncADCArrays0;
  asyncADCArraysRecord = &asyncADCArrays1;
  currentDwellMath = &currentDwell0;
  currentDwellRealtime = &currentDwell1;

  injectorMainPulseWidthsMath = injectorMainPulseWidths0;
  injectorMainPulseWidthsRealtime = injectorMainPulseWidths1;
  injectorStagedPulseWidthsMath = injectorStagedPulseWidths0;
  injectorStagedPulseWidthsRealtime = injectorStagedPulseWidths1;

  // TODO temp, remove
  mathSampleTimeStamp = &ISRLatencyVars.mathSampleTimeStamp0;
  // TODO temp, remove
  mathSampleTimeStampRecord = &ISRLatencyVars.mathSampleTimeStamp1;
  // TODO temp, remove
  RPM = &RPM0;
  // TODO temp, remove
  RPMRecord = &RPM1;

  /* Setup the pointers to the registers for fueling use, this does NOT work if
   * done in global.c, I still don't know why. */
  injectorMainTimeRegisters[0] = TC2_ADDR;
  injectorMainTimeRegisters[1] = TC3_ADDR;
  injectorMainTimeRegisters[2] = TC4_ADDR;
  injectorMainTimeRegisters[3] = TC5_ADDR;
  injectorMainTimeRegisters[4] = TC6_ADDR;
  injectorMainTimeRegisters[5] = TC7_ADDR;
  injectorMainControlRegisters[0] = TCTL2_ADDR;
  injectorMainControlRegisters[1] = TCTL2_ADDR;
  injectorMainControlRegisters[2] = TCTL1_ADDR;
  injectorMainControlRegisters[3] = TCTL1_ADDR;
  injectorMainControlRegisters[4] = TCTL1_ADDR;
  injectorMainControlRegisters[5] = TCTL1_ADDR;

  configuredBasicDatalogLength = maxBasicDatalogLength;

  // TODO perhaps read from the ds1302 once at start up and init the values or
  //      different ones with the actual time and date then update them in RTI
}


/** @brief Flash module setup
 *
 * Initialise configuration registers for the flash module to allow burning of
 * non-volatile flash memory from within the firmware.
 *
 * The FCLKDIV register can be written once only after reset, thus the lower
 * seven bits and the PRDIV8 bit must be set at the same time.
 *
 * We want to put the flash clock as high as possible between 150kHz and 200kHz
 *
 * The oscillator clock is 16MHz and because that is above 12.8MHz we will set
 * the PRDIV8 bit to further divide by 8 bits as per the manual.
 *
 * 16MHz = 16000KHz which pre-divided by 8 is 2000kHz
 *
 * 2000kHz / 200kHz = 10 thus we want to set the divide register to 10 or 0x0A
 *
 * Combining 0x0A with PRDIV8 gives us 0x4A (0x0A | 0x40 = 0x4A) so we use that
 *
 * @author Sean Keys
 *
 * @note If you use a different crystal lower than 12.8MHz PRDIV8 should not be
 *       set.
 *
 * @warning If the frequency you end up with is outside 150kHz - 200kHz you may
 *          damage your flash module or get corrupt data written to it.
 */
void initFlash() {
  /* Set the flash clock frequency	*/
  FCLKDIV = 0x4A;
  /* Disable all flash protection 	*/
  FPROT = 0xFF;
  /* Clear any errors             	*/
  FSTAT = FSTAT | (PVIOL | ACCERR);
}

/** @brief Xgate module setup
 *
 * Configure XGATE setup registers and prepare XGATE code to be run by copying
 * it from flash hcs12mem can write to to flash XGATE can read from.
 *
 * @author Sean Keys and Fred Cooke
 *
 * @note A thanks goes out to Edward Karpicz for helping me get xgate configured
 * properly.
 *
 * @note This function is not used any more, but will be kept, because some of
 *       the comments may be usefull in the future.
 *
 * @warning If executing from RAM you must copy the code from Flash to RAM
 * before starting Xgate
 *
 */
void initXgate() {
  /* route interrupt to xgate */
  INT_CFADDR = (0x72 & 0xF0);	/* vector address = channel_id * 2 */
  INT_CFDATA0 = 0x01; 		/* RQST = 1 */
  INT_CFDATA1 = 0x81;		/* PRIO = 1 */

  /* HCS12mem currently limits us to half of the available flash, hence this
   * copy code. */
  /* XGATE sees flash starting at paged address 0xE0, 0x8800 */

  // Reuse variables across multiple blocks of unreachable code copying code
  unsigned short * xgateDataDestination;
  unsigned char destinationPage;
  // Save old flash page value
  unsigned char OldPPAGE = PPAGE;

  // Copy the XGATE vector table into the visible region only if it differs from
  // what is already there (save on flash burns for now)
  xgateDataDestination = (unsigned short *)0x8800;
  destinationPage = 0xE0;
  // Copy to ram first as only one paged flash block at a time is visible
  memcpy((void*)&TXBuffer, (void*)&xgateIntVectorTable, sizeof(xgateIntVectorTable));
  // Switch to destination page for comparison
  PPAGE = destinationPage;
  // Do the check, from the copy in RAM to the destination.
  if(compare((unsigned char*)&TXBuffer, (unsigned char*)xgateDataDestination, sizeof(xgateIntVectorTable))) {
    eraseSector(destinationPage, xgateDataDestination);
    writeSector(RPAGE, (unsigned short*)&TXBuffer, destinationPage, xgateDataDestination);
  }

  // Copy xgatethread0 code into the visible region only if it differs from what
  // is already there (save on flash burns for now)
  xgateDataDestination = (unsigned short *)0x9000;
  destinationPage = 0xE1;
  unsigned short xgateThread0Size = (void*)&xgateThread0End - (void*)&xgateThread0;
  // Copy to ram first as only one paged flash block at a time is visible
  // Switch to destination page for comparison
  PPAGE = destinationPage;
  // Do the check, from the copy in RAM to the destination.
  if(compare((unsigned char*)&TXBuffer, (unsigned char*)xgateDataDestination, xgateThread0Size)) {
    eraseSector(destinationPage, xgateDataDestination);
    writeSector(RPAGE, (unsigned short*)&TXBuffer, destinationPage, xgateDataDestination);
  }

  // Switch the page back to how it was
  PPAGE = OldPPAGE;

  // XGATE threads execute from flash at the moment

  // Set the XGVBR register to its start address in flash (page 0xE0 after 2K
  // register space)
  XGVBR = (unsigned short )0x0800;

  // Enable XGate and XGate interrupts
  XGMCTL= (unsigned short)0x8181;
}

/**
 *  Set up the timer module and its various interrupts
 *  @note This function is not used any more, but will be kept, because some of
 *        the comments may be usefull in the future.
 */
void initECTTimer() {

  // TODO rearrange the order of this stuff and pull enable and interrupt enable
  //      out to the last function call of init.


#ifndef NO_INIT
  /* Timer channel interrupts */
  /* 0,1 IC interrupts enabled for reading engine position and RPM, 6 OC
   * channels disabled such that no injector switching happens till scheduled */
  TIE = 0x03;
  /* Clear all the flags such that we are up and running before they first
   * occur */
  TFLG = ONES;
  /* Clear all the flags such that we are up and running before they first
   * occur */
  TFLGOF = ONES;

  /* TODO Turn the timer on and set the rate and overflow interrupt */
  /* max noise filtering as experiment for volvo this will come from flash
   * config */
  // just hiding a wiring/circuit issue...
  //DLYCT = 0xFF;
  /* 0b_1000_1000 Timer enabled, and precision timer turned on */
  TSCR1 = 0x88;
  /* 0b_1000_0111 Overflow interrupt enable, divide by 256 if precision turned
   * off */
  TSCR2 = 0x87;

  /* 4 prescaler gives .1uS resolution and max period of 7ms measured */
//	PTPSR = 0x03;

  /* 32 prescaler gives 0.8uS resolution and max period of 52.4288ms measured */
  PTPSR = 0x1F;

  /* 64 prescaler gives 1.6uS resolution and max period of 105ms measured */
//	PTPSR = 0x3F;
  /* 256 prescaler gives 6.4uS resolution and max period of 400ms measured */
//	PTPSR = 0xFF;
  /* 128 prescaler gives 3.2uS resolution and max period of 200ms measured */
//	PTPSR = 0x7F;
  /* http://www.google.com/search?hl=en&safe=off&q=1+%2F+%2840MHz+%2F+32+%29&btnG=Search */
  /* http://www.google.com/search?hl=en&safe=off&q=1+%2F+%2840MHz+%2F+32+%29+*+2%5E16&btnG=Search */
  /* www.mecheng.adelaide.edu.au/robotics_novell/WWW_Devs/Dragon12/LM4_Timer.pdf */

  /* Initial actions */
  /* 0b_1111_1100 0 and 1 are input capture, 2 through 7 are output compare */
  TIOS = 0xFC;
  /* Set disabled at startup time, use these and other flags to switch fueling
   * on and off inside the decoder */
  TCTL1 = ZEROS;
  /* 0,1 have compare turned off regardless as they are in IC mode. */
  TCTL2 = ZEROS;
  /* Capture off for 4 - 7 */
  TCTL3 = ZEROS;
  /* Capture on both edges of two pins for IC (0,1), capture off for 2,3 */
  TCTL4 = 0x0F;

  // TODO setup delay counters on 0 and 1 to filter noise (nice feature!)
  //DLYCT = ??; built in noise filter

  /* Configurable tachometer output */
  // Precision prescaler - fastest is 1 represented by 0,
  // slowest/longest possible is 256 represented by 255 or 0xFF
  PTMCPSR = fixedConfigs1.tachoSettings.tachoTickFactor - 1;
  // init to slowest possible, first
  MCCNT = ONES16;
  // turn on and setup the mod down counter
  MCCTL = 0xC4;
  // clear the flag up front
  MCFLG = 0x80;
#endif
}


/**
 *  Configure the PIT timers for their various uses.
 *  @note This function is not used any more, but will be kept, because some of
 *        the comments may be usefull in the future.
 */
void initPITTimer() {
#ifndef NO_INIT
  /*  */
  // set micro periods
  /* 32 prescaler gives 0.8uS resolution and max period of 52.4288ms measured */
  PITMTLD0 = 0x1F;
  /* ditto */
  PITMTLD1 = 0x1F;
  /* http://www.google.com/search?hl=en&safe=off&q=1+%2F+%2840MHz+%2F+32+%29
   * Exactly the same as for ECT */

  // set timers running
//	PITLD0 = dwellPeriod;
  // enable module
  PITCFLMT = 0x80;
  // enable channels
  //PITCE = 0x03;
  // enable interrupt
//	PITINTE = 0x01;
  // clear flags
  //PITFLT = ONES;
#endif
}

/**
 *  Setup the sci module(s) that we need to use.
 *  @note This function is not used any more, but will be kept, because some of
 *        the comments may be usefull in the future.
 */
void initSCIStuff() {
  /* The alternative register set selector defaults to zero */

  // set the baud/data speed
  SCI0BD = fixedConfigs1.serialSettings.baudDivisor;

  // etc

  /* Switch to alternative register set? */

  // etc

  /* Switch back again? */

  /*
   * 0 = LOOPS (normal two wire operation)
   * 0 = SCISWAI (Wait mode on)
   * 0 = RSRC (if loops=1, int/ext wiring)
   * 1 = M MODE (9 bit operation)
   * 0 = WAKE (idle line wakeup)
   * 0 = ILT (idle line type count start pos)
   * 1 = PE (parity on)
   * 1 = PT (odd parity) (minicom defaults to no parity)
   *
   * 00010011 = 0x13
   */
  SCI0CR1 = 0x13;

  /*
   * 0 = TIE (tx data empty isr disabled)
   * 0 = TCIE (tx complete isr disabled)
   * 1 = RIE (rx full isr enabled)
   * 0 = ILIE (idle line isr disabled)
   * 1 = TE (transmit enabled)
   * 1 = RE (receive enabled)
   * 0 = RWU (rx wake up normal)
   * 0 = SBK (send break off)
   *
   * 00101100 = 0x2C
   */
  SCI0CR2 = 0x2C;
}

/* TODO Load and calculate all configuration data required to run */
void initConfiguration() {
  // TODO Calc TPS ADC range on startup or every time? this depends on whether
  //      we ensure that things work without a re init or reset or not.


  /* Add in tunable physical parameters at boot time TODO move to init.c
   * TODO duplicate for secondary fuel? or split somehow?
   *nstant = ((masterConst * perCylinderVolume) / (stoichiometricAFR * injectorFlow));
   *nstant = ((139371764 * 16384) / (15053 * 4096 ));
   * OR
   *nstant = ((masterConst / injectorFlow) * perCylinderVolume) / stoichiometricAFR;
   *nstant = ((139371764 / 4096	) * 16384) / 15053 ;
   * http://www.google.com/search?hl=en&safe=off&q=((139371764++%2F+4096+++++)+*+16384+++)+%2F+15053++++&btnG=Search */
  bootFuelConst = ((unsigned long)(masterFuelConstant / fixedConfigs1.engineSettings.injectorFlow) * fixedConfigs1.engineSettings.perCylinderVolume) / fixedConfigs1.engineSettings.stoichiometricAFR;

  /* The MAP range used to convert fake TPS from MAP and vice versa */
  TPSMAPRange = fixedConfigs2.sensorRanges.TPSOpenMAP - fixedConfigs2.sensorRanges.TPSClosedMAP;

  /* The ADC range used to generate TPS percentage */
  TPSADCRange = fixedConfigs2.sensorRanges.TPSMaximumADC - fixedConfigs2.sensorRanges.TPSMinimumADC;


  /* Use like flags for now, just add one for each later */
  unsigned char cumulativeConfigErrors = 0;

  /* Check various aspects of config which will cause problems */

  /* BRV max bigger than variable that holds it */
  if(((unsigned long)fixedConfigs2.sensorRanges.BRVMinimum + fixedConfigs2.sensorRanges.BRVRange) > 65535) {
    //sendError(BRV_MAX_TOO_LARGE);
    cumulativeConfigErrors++;
  }

  // TODO check all critical variables here!

  /*
   * check ignition settings for range etc, possibly check some of those on the
   *       fly too
   * check fuel settings for being reasonable
   * check all variable tables for correct sizing
   * etc
   */

  while(cumulativeConfigErrors > 0) {
    sleep(1000);
    PORTS_BA ^= ONES16; // flash leds
    //send("There were ");
    //sendUC(cumulativeConfigErrors);
    //send(" config errors, init aborted!");
  }
  // TODO ensure that we can recieve config and settings via serial while this
  // is occuring! If not a bad config will lock us out all together.
}


/**
 *  Set up all the remaining interrupts
 *  @note This function is not used any more, but will be kept, because some of
 *        the comments may be usefull in the future.
 */
void initInterrupts() {
  /* IMPORTANT : Set the s12x vector base register (Thanks Karsten!!) */
  IVBR = 0xF7; /* Without this the interrupts will never find your code! */

  /* Set up the Real Time Interrupt */
  /* 0b_1000_0001 0.125ms/125us period
   * http://www.google.com/search?hl=en&safe=off&q=1+%2F+%2816MHz+%2F+%282+*+10%5E3%29+%29&btnG=Search */
  RTICTL = 0x81;

  /* 0b_1111_1001 0.125s/125ms period
   * http://www.google.com/search?hl=en&safe=off&q=1+%2F+%2816MHz+%2F+%282*10%5E6%29+%29&btnG=Search */
//	RTICTL = 0xF9;

  /* Enable the RTI */
  CRGINT |= 0x80;
  /* Clear the RTI flag */
  CRGFLG = 0x80;

#ifndef NO_INIT
  // set up port H for testing
  // falling edge/pull up for all
  PPSH = ZEROS;
  // enable all pins interrupts
  PIEH = ONES;
  // clear all port H interrupt flags
  PIFH = ONES;
#endif

  // TODO set up irq and xirq for testing
  // IRQCR for IRQ
  //

  /* VReg API setup (only for wait mode? i think so) */
//	VREGAPIR = 0x09C3; /* For 500ms period : (500ms - 0.2ms) / 0.2ms = 0b100111000011 = 2499 */
//	VREGAPICL = 0x02; /* Enable the interrupt */
//	VREGAPICL = 0x04; /* Start the counter running */
  /* Writing a one to the flag will set it if it is unset, so best not to mess
   * with it here as it probably starts off unset */

  /* LVI Low Voltage Interrupt enable */
  VREGCTRL = 0x02; // Counts bad power events for diagnosis reasons
}
