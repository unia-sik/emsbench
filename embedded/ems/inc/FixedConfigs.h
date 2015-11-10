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
 * @file FixedConfigs.h
 * @ingroup allHeaders
 * @ingroup globalHeaders
 *
 * @brief Struct typedefs for fixed configuration
 *
 * This file contains the struct data type definitions for fixed configuration items.
 *
 * Fixed, in this context means that it typically is not tuned in a live way
 * and therefore should not be cached in RAM while running. Usually these are
 * values that do not change such as cylinder volume, injector size, cylinder
 * count and other constants related to physical aspects of the engine setup.
 * When adding configuration values, please consider adding them here first.
 * If a value doesn't need to be live tunable definitely put it here instead.
 *
 * <h> original author</h> Fred Cooke
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

/* Header file multiple inclusion protection courtesy eclipse Header Template*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual*/
#ifndef FILE_FIXED_CONFIGS_H_SEEN
#define FILE_FIXED_CONFIGS_H_SEEN



/** @brief Preset values for inputs
 *
 * In some cases you may want to ignore input readings and just use some
 * configured value for a particular sensor. These are the values used when you
 * choose to use a fixed reading instead of the real thing.
 *
 * @author Fred Cooke
 */
typedef struct {
  /* Pre configured value settings for the sensor inputs */
  unsigned short presetIAT;
  unsigned short presetCHT;
  unsigned short presetTPS;
  unsigned short presetEGO;
  unsigned short presetBRV;
  unsigned short presetMAP;
  unsigned short presetAAP;
  unsigned short presetMAT;
  unsigned short presetEGO2;
  unsigned short presetIAP;
  unsigned short presetBPW; /* Base Pulse Width */
  unsigned short presetAF; /* Air Flow */
} sensorPreset;

#define SENSOR_PRESETS_SIZE sizeof(sensorPreset)


typedef struct {
  /* Sensor related settings */
  unsigned short TPSClosedMAP;
  unsigned short TPSOpenMAP;

  /* Sensor input conditioning settings */
  /* These are used to calculate MAP, EGO and TPS from ADC readings. */

  /* For MAP, default to MPX4250A 260kPa - 8kPa = 252kPa See the link for the
   * transfer function*/

  /* 0 kPa usually. */
  unsigned short MAPMinimum;
  /* 10000, 11500, 25000, 30000, 40000 etc (/100 for kPa) */
  unsigned short MAPRange;

  /* For AAP, default to MPX4100A 107.5kPa - 14kPa = 93.5kPa See the link for
   * the transfer function */

  /* 0 kPa usually. */
  unsigned short AAPMinimum;
  /* 10000, 11500, 25000, 30000, 40000 etc (/100 for kPa) */
  unsigned short AAPRange;

  /* Default to Innovate LC-1 on lambda 0.5 - 1.5 for 0-5V range
   * (lambda range = 1.0) */

  /* 0.5 lambda ? (0.5 x 32768 = 16384) */
  unsigned short EGOMinimum;
  /* 1.5 lambda ? ((1.5 - 0.5) x 32768 = 32768 (max 49152)) */
  unsigned short EGORange;

  /* 0 - 24.5 Volt measurement with 10k and 39k resistors */
  /* http://www.google.com/search?hl=en&safe=off&q=5+*+(39000+%2B+10000)+%2F+10000&btnG=Search */

  /* 0 Volts usually. */
  unsigned short BRVMinimum;
  /* 24.5 Volts for 10k and 39k resistors on a 12v vehicle */
  unsigned short BRVRange;

  /* Default to 25% of voltage = closed (0%) */
  /* 75% of voltage = open (100%) */

  /* *should* be zero, but often isn't, this value corresponds to 0% TPS */
  unsigned short TPSMinimumADC;
  /*  */
  unsigned short TPSMaximumADC;
// unsigned short TPSADCRange;	// ?? 100% = how many ADCs ?
  /*efine TPS_MINIMUM 0	** = 0.00% For clarity ONLY, always zero.*/

  /* = 100.00% */
#define TPS_RANGE_MAX 64000
} sensorRange;

#define SENSOR_RANGES_SIZE sizeof(sensorRange)


typedef struct {
  /* Fuel injection settings TODO duplication from original temp code below!! */

  /* 500cc = 0.5l 0.5 * 32768 = pcv, so divide by 32768 go get litres */
  unsigned short perCylinderVolume;
  /* 34 for hydrogen, all others less, figure is 14.7 * 1024, divide by 1024 to
   * get AFR */
  unsigned short stoichiometricAFR;
  /* Injector flow of 240cc/min / 60 is 4ml/second is multiplied by 1024, so
   * divide by 1024 for ml/second, divide by 1000 for litres/second */
  unsigned short injectorFlow;
  /* 703gm/litre for Octane. 32 * fuel density = number, divide by 32 for the
   * real figure */
  unsigned short densityOfFuelAtSTP;
  /* Setting variables (must be inited with useful values) */

  /* How much air it swallows per power producing event	*/
  unsigned short capacityOfAirPerCombustionEvent;
  /* How much fuel flows per minute per channel	*/
  unsigned short perPrimaryInjectorChannelFlowRate;
  /* How much fuel flows per minute per channel	*/
  unsigned short perSecondaryInjectorChannelFlowRate;
  /* How many groups of injectors we are firing	*/
  unsigned char ports;
  /* How many coils we are firing */
  unsigned char coils;
  /* How many power producing events per engine cycle */
  unsigned char combustionEventsPerEngineCycle;
  /* Rotary = 1, 2 Stroke = 1, 4 Stroke = 2 */
  unsigned char revolutionsPerEngineCycle;
  /* How many teeth are on the crank signal including the missing ones if any
   * (eg. 36-1 primary = 36 not 35) */
  unsigned char primaryTeeth;
  /* Number sequentially removed from primary teeth (eg. 36-1 missing = 1) */
  unsigned char missingTeeth;
} engineSetting;

#define ENGINE_SETTINGS_SIZE sizeof(engineSetting)


typedef struct {
  /* Serial settings */

  /* 22 = (40MHz / (16*115.2kHz)) = 21.7013889 */
  unsigned short baudDivisor;
  /* Default = 1, Default for PC = 10 */
  unsigned char networkAddress;
} serialSetting;

#define SERIAL_SETTINGS_SIZE sizeof(serialSetting)


typedef struct {
  /* Tacho settings */
  unsigned char tachoTickFactor;
  unsigned short tachoTotalFactor;
} tachoSetting;

#define TACHO_SETTINGS_SIZE sizeof(tachoSetting)


typedef struct {
  /* How often an ADC reading MUST occur */
  unsigned short readingTimeout;
} sensorSetting;

#define SENSOR_SETTINGS_SIZE sizeof(sensorSetting)


#define userTextFieldArrayLength1 1024 - (ENGINE_SETTINGS_SIZE + SERIAL_SETTINGS_SIZE + TACHO_SETTINGS_SIZE + 2)

/**
 * One of two structs of fixed configuration data such as physical parameters
 * etc.
 * If you add something here, please ensure you update all of the following :
 * - Default values in the initial definitions in FixedConfig1.c and
 *   FixedConfig2.c
 * - The lookupBlockDetails() function in blockDetailsLookup.c
 * - The JSON data map and other related firmware interface definition files
 *
 * @todo TODO add doxy comments for each element of the struct
 */
typedef struct {

  engineSetting engineSettings;

  serialSetting serialSettings;

  tachoSetting tachoSettings;

  /* Settings variables : 0 = false */

  /* Each bit represents the state of some core setting, masks below and above
   * where the same one is used */
  unsigned short coreSettingsA;
  /* Bit masks for coreSettingsA */ // TODO needs a rename, as does coreStatusA
  //#define COREA1			BIT1_16		/*  1 */

/*  2 1 = high teeth 0 = low teeth */
#define PRIMARY_POLARITY	BIT2_16
/*  3 1 = high teeth 0 = low teeth */
#define SECONDARY_POLARITY	BIT3_16

  //#define COREA4 			BIT4_16		/*  4 */
  //#define FUEL_CUT			BIT5_16		/*  5 Remove injection completely */
  //#define HARD_SPARK_CUT	BIT6_16		/*  6 Remove ignition completely */
  //#define SOFT_SPARK_CUT	BIT7_16		/*  7 Remove ignition events round robin style */
  //#define SPARK_RETARD		BIT8_16		/*  8 Retard ignition in RPM dependent way */

  /*  9 Whether we are firing the staged injectors */
#define STAGED_ON			BIT9_16
  /* 10 1 = Fixed start 0 = Scheduled start */
#define STAGED_START		BIT10_16
  /* 11 1 = Fixed end 0 = Scheduled end */
#define STAGED_END			BIT11_16
  //#define COREA12			BIT12_16	/* 12 */
  //#define COREA13			BIT13_16	/* 13 */
  //#define COREA14			BIT14_16	/* 14 */
  //#define COREA15			BIT15_16	/* 15 */
  //#define COREA16			BIT16_16	/* 16 */

  unsigned char userTextField[userTextFieldArrayLength1]; /* "Place your personal notes here!!" */
} fixedConfig1;

#define FIXED_CONFIG1_SIZE sizeof(fixedConfig1)


#define userTextFieldArrayLength2 1024 - (SENSOR_RANGES_SIZE + SENSOR_PRESETS_SIZE + SENSOR_SETTINGS_SIZE)

/** @copydoc fixedConfig1 */
typedef struct {

  sensorPreset sensorPresets;

  sensorRange sensorRanges;

  sensorSetting sensorSettings;

  /* User text field for noting which installation the unit is from etc. */
  /* "Place your personal notes here!!" */
  unsigned char userTextField2[userTextFieldArrayLength2];
} fixedConfig2;

#define FIXED_CONFIG2_SIZE sizeof(fixedConfig2)


#else
/* let us know if we are being untidy with headers */
#warning "Header file FIXED_CONFIGS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
