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
 * @file globalDefines.h
 * @ingroup allHeaders
 * @ingroup globalHeaders
 *
 * @brief Global hash define literal replacements
 *
 * Currently this holds most hash defined constants and literals.
 *
 * <h> original author</h> Fred Cooke
 * @todo TODO Some investigation as to whether it is best to use consts or
 *            defines is required
 * @todo TODO Break this up into smaller chunks that are included into this file
 *
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

/* Header file multiple inclusion protection courtesy eclipse Header Template */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual */
#ifndef FILE_GLOBALDEFINES_H_SEEN
#define FILE_GLOBALDEFINES_H_SEEN


/* TODO perhaps configure various ports and pins etc to have names such that the
 * code can stay untouched when being ported and just the header changed to suit?
 * definitely a good idea, but we'll see what karsten says before putting time
 * into it. something like : #define RPM_IN_MAIN IC0 etc etc
 */


/* Definitions for functions used across the project */
/* http://www.seattlerobotics.org/encoder/200109/encoder.htm section Assembly */
#define INLINE_ASSEMBLY(code) __asm__ __volatile__ (code)
#define ALWAYS_INLINE __attribute__((always_inline))

/* Common macro definitions across the project */
/* Boolean */
#define FALSE 0
#define TRUE !FALSE /* http://c2.com/cgi/wiki?CeePreprocessorStatements */
//#include <osek/ostypes.h>


/* 8 bit values */
#define ZEROS 0x00
#define ONES 0xFF

/* 16 bit values */
#define ZEROS16 0x0000
#define ONES16 0xFFFF

/* Halves and Maxes */
#define LONGHALF 0x80000000	/* 2147483648 */
#define LONGMAX 0xFFFFFFFF	/* 4294967295*/
#define SHORTHALF 0x8000	/* 32768 */
#define SHORTMAX 0xFFFF		/* 65535 */

/* Individual bits WARNING, do not not these for notted versions, use the notted
 * ones below instead :
 * http://supp.iar.com/Support/?note=12582&from=search+result */

/* 1st bit = 1*/
#define BIT0		0x01
/* 2nd bit = 2 */
#define BIT1		0x02
/* 3rd bit = 4 */
#define BIT2		0x04
/* 4th bit = 8 */
#define BIT3		0x08
/* 5th bit = 16	*/
#define BIT4		0x10
/* 6th bit = 32	*/
#define BIT5		0x20
/* 7th bit = 64	*/
#define BIT6		0x40
/* 8th bit = 128 */
#define BIT7		0x80

/* 1st bit = 1 */
#define BIT0_16		0x0001
/* 2nd bit = 2	*/
#define BIT1_16		0x0002
/* 3rd bit = 4	*/
#define BIT2_16		0x0004
/* 4th bit = 8	*/
#define BIT3_16		0x0008
/* 5th bit = 16	*/
#define BIT4_16		0x0010
/* 6th bit = 32	*/
#define BIT5_16		0x0020
/* 7th bit = 64	*/
#define BIT6_16		0x0040
/* 8th bit = 128 */
#define BIT7_16		0x0080
/* 9th bit = 256 */
#define BIT8_16		0x0100
/* 10th bit = 512 */
#define BIT9_16		0x0200
/* 11th bit = 1024 */
#define BIT10_16	0x0400
/* 12th bit = 2048 */
#define BIT11_16	0x0800
/* 13th bit = 4096 */
#define BIT12_16	0x1000
/* 14th bit = 8192 */
#define BIT13_16	0x2000
/* 15th bit = 16384 */
#define BIT14_16	0x4000
/* 16th bit = 32768 */
#define BIT15_16	0x8000

/* Individual bits NOTTED : http://supp.iar.com/Support/?note=12582&from=search+result */
/* 1st bit = 1 */
#define NBIT0		0xFE
/* 2nd bit = 2 */
#define NBIT1		0xFD
/* 3rd bit = 4	*/
#define NBIT2		0xFB
/* 4th bit = 8	*/
#define NBIT3		0xF7
/* 5th bit = 16	*/
#define NBIT4		0xEF
/* 6th bit = 32	*/
#define NBIT5		0xDF
/* 7th bit = 64	*/
#define NBIT6		0xBF
/* 8th bit = 128 */
#define NBIT7		0x7F
/* 1st bit = 1	*/
#define NBIT0_16	0xFFFE
/* 2nd bit = 2	*/
#define NBIT1_16	0xFFFD
/* 3rd bit = 4	*/
#define NBIT2_16	0xFFFB
/* 4th bit = 8	*/
#define NBIT3_16	0xFFF7
/* 5th bit = 16	*/
#define NBIT4_16	0xFFEF
/* 6th bit = 32	*/
#define NBIT5_16	0xFFDF
/* 7th bit = 64	*/
#define NBIT6_16	0xFFBF
/* 8th bit = 128 */
#define NBIT7_16	0xFF7F
/* 9th bit = 256 */
#define NBIT8_16	0xFEFF
/* 10th bit = 512 */
#define NBIT9_16	0xFDFF
/* 11th bit = 1024 */
#define NBIT10_16	0xFBFF
/* 12th bit = 2048 */
#define NBIT11_16	0xF7FF
/* 13th bit = 4096 */
#define NBIT12_16	0xEFFF
/* 14th bit = 8192 */
#define NBIT13_16	0xDFFF
/* 15th bit = 16384 */
#define NBIT14_16	0xBFFF
/* 16th bit = 32768 */
#define NBIT15_16	0x7FFF


/* Serial Comms Stuff */
#define ESCAPE_BYTE	0xBB
#define START_BYTE	0xAA
#define STOP_BYTE	0xCC
#define ESCAPED_ESCAPE_BYTE		0x44
#define ESCAPED_START_BYTE		0x55
#define ESCAPED_STOP_BYTE		0x33
#define flashSectorSize			1024
/* 512 words to a 1k flash sector */
#define flashSectorSizeInWords	 512


#define RPM_FACTOR 2
#define MAP_FACTOR 100
#define TPS_FACTOR 640
#define BRV_FACTOR 1000
#define TEMP_FACTOR 100
#define EGO_FACTOR 32768


/* 30 kPa */
#define idleManifoldPressure		 3000
/* 100 kPa */
#define seaLevelKPa					10000
/* 300 kPa */
#define maxExpectedBoost			30000
/* 0 Celcius */
#define freezingPoint				27315
/* 20 Celcius */
#define roomTemperature				29315
/* 85 Celcius */
#define runningTemperature			35815

/* 50% throttle */
#define halfThrottle				32768
/* 14.4 Volts */
#define runningVoltage				14400
/* ~1.5ms */
#define idlePulseWidth				 2000
/* guessed */
#define idleAirFlow 				 1500
/* 500cc per cylinder */
#define typicalCylinderSize			16384
/* 550cc per minute */
#define typicalInjectorSize			 9387
/* 703 grams per litre */
#define densityOfOctane				22496
/* Lambda = 1.0 */
#define stoichiometricLambda		32768

/* Generated with http://www.diyefi.org/calculators.htm#stoich */
#define stoichiometricAFRMethane	17245		/* 17.245 AFR */
#define stoichiometricAFRPropane	15685		/* 15.685 AFR */
#define stoichiometricAFRLPG		15599		/* 15.599 AFR */
#define stoichiometricAFRButane		15469		/* 15.469 AFR */
#define stoichiometricAFROctane		15137		/* 15.137 AFR */
#define stoichiometricAFRGasoline	14700		/* 14.700 AFR */
#define stoichiometricAFRXylene		13681		/* 13.681 AFR */
#define stoichiometricAFRToluene	13512		/* 13.512 AFR */
#define stoichiometricAFRBenzene	13282		/* 13.282 AFR */
#define stoichiometricAFRE85		 9862		/*  9.862 AFR */
#define stoichiometricAFREthanol	 9008		/*  9.008 AFR */
#define stoichiometricAFRMethanol	 6475		/*  6.475 AFR */

/* Voltage read at lowest ADC reading */
#define batteryVoltageMin			    0
/* Voltage difference between lowest and highest ADC reading */
#define batteryVoltageRange			24500
/* Lambda read at lowest ADC reading */
#define LC1LambdaMin				16384
/* Lambda read at highest ADC reading */
#define LC1LambdaMax				49152
/* Lambda difference between lowest and highest ADC reading */
#define LC1LambdaRange				32768
/* Lambda read at lowest ADC reading */
#define AFR1020LambdaMin			16384
/* Lambda read at highest ADC reading */
#define AFR1020LambdaMax			49152
/* Lambda difference between lowest and highest ADC reading */
#define AFR1020LambdaRange			32768


/* MAP Sensor Data Explanation
 *
 * Motorola/Freescale pressure sensor data obtained from the
 * data sheets by extrapolation of the "typical" line to the
 * borders of the transfer function chart. This gives us the
 * correct values in the middle despite not being able to
 * reach the ends of the scale.
 *
 * By min and max I mean the OV and 5V pressures that aren't
 * attainable, but that give the correct function in between.
 */


/* www.freescale.com/files/sensors/doc/data_sheet/MPX4100A.pdf */

/* Pressure read at lowest ADC reading */
#define MPX4100AMin				1400
/* Pressure read at highest ADC reading */
#define MPX4100AMax				10750
/* Pressure difference between lowest and highest ADC readings */
#define MPX4100ARange			9350

/* www.freescale.com/files/sensors/doc/data_sheet/MPX4250A.pdf */

/* Pressure read at lowest ADC reading */
#define MPX4250AMin				800
/* Pressure read at highest ADC reading */
#define MPX4250AMax				26000
/* Pressure difference between lowest and highest ADC readings */
#define MPX4250ARange			25200
/* Pressure read at lowest ADC reading */
#define MPXH6300AMin			1200
/* Pressure read at highest ADC reading */
#define MPXH6300AMax			32000
/* Pressure difference between lowest and highest ADC readings */
#define MPXH6300ARange			30800
/* Pressure read at lowest ADC reading */
#define MPXH6400AMin			1200
/* Pressure read at highest ADC reading */
#define MPXH6400AMax			42000
/* Pressure difference between lowest and highest ADC readings */
#define MPXH6400ARange			40800
/* ADC reading at lowest throttle position */
#define TPSDefaultMin			255
/* ADC reading at highest throttle position */
#define TPSDefaultMax			767
/* 30kPa just above where MAP would be with closed throttle at idle */
#define offIdleMAP				3000
/* 95kPa just below where MAP would be at WOT */
#define nearlyWOTMAP			9500
/* twice how many 0.8us ticks there are in between engine cycles at 1 RPM */
#define ticksPerCycleAtOneRPMx2	300000000
/* how many 0.8us ticks there are in between engine cycles at 1 RPM */
#define ticksPerCycleAtOneRPM	150000000
/* Provides for a 4 cylinder down to 50 RPM  */
#define tachoTickFactor4at50	6
/*  8 events per cycle for a typical 4 cylinder tacho, 4 on, 4 off */
/*efine tachoEdgesPerCycle4at50	8
 http://www.google.com/search?hl=en&safe=off&q=((150000000+%2F+6)+%2F++8+)+%2F+50&btnG=Search */
#define tachoTotalFactor4at50	48

/* ticksPerCycleAtOneRPM / 50 */
//#define ticksForFiftyRPM		3000000

//#define lookedUpVEDivisor 512
//#define VEpercentageDivisor 100
#define oneHundredPercentVE 51200

//#define densityOfFuelDivisor 32
//#define densityOfFuelUnitDivisor 1000
#define densityOfFuelTotalDivisor 32000

/* (40MHz / (16*115.2kHz)) = 21.7013889 */
#define divisorFor115200bps 22
/* http://www.google.com/search?hl=en&safe=off&q=22%2F%28%2840000000%2F16%29%2F115200%29&btnG=Search 1.376% error in speed */
/* http://www.google.com/search?hl=en&safe=off&q=40MHz%2F%2816*22%29&btnG=Search 113.636 kHz */

/* Not 1024, the number of gaps between them */
#define ADC_DIVISIONS 1023

/* How many ignition channels the code should support */
#define IGNITION_CHANNELS 12
/* How many injection channels the code should support */
#define INJECTION_CHANNELS 6

/* Ignition defines */
#define DWELL_ENABLE BIT0
#define DWELL_DISABLE NBIT0
#define IGNITION_ENABLE BIT1
#define IGNITION_DISABLE NBIT1

/* Valid RPAGE values :
 *	0xFF - linear
 *	0xFE - linear
 *	0xFD - default
 *	0xFC
 *	0xFB
 *	0xFA
 *	0xF9
 *	0xF8
 */
/* The reset value of RPAGE is 0xFD			*/
/* The other 8k of linear RAM space is accessible	*/
/* through the RPAGE window with 0xFE and 0xFF		*/
/* 0xFE refers to the 0x2000 to 0x3000 region		*/
/* 0xFF refers to the 0x3000 to 0x4000 region		*/
#define RPAGE_TUNE_ONE	0xF8
#define RPAGE_TUNE_TWO	0xF9
#define RPAGE_FUEL_ONE	0xFA
#define RPAGE_FUEL_TWO	0xFB
#define RPAGE_TIME_ONE	0xFC
#define RPAGE_TIME_TWO	0xFD
#define RPAGE_MIN     	0xF8
#define PPAGE_MIN     	0xE0
#define EPAGE_MIN     	0x?? // TODO

/* The TX and RX buffers are slightly larger than 2k because the RX buffer */
/* needs to also receive a header, checksum and attributes for the data    */
/* involved and the TX buffer needs to handle all of those two fold.       */
#define TX_BUFFER_SIZE      0x0820
#define RX_BUFFER_SIZE      0x0810
#define TransferTableSize   2048
#define TX_MAX_PAYLOAD_SIZE 2048


#else
/* let us know if we are being untidy with headers */
#warning "Header file GLOBALDEFINES_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
