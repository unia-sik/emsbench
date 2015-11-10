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
 * @file FixedConfig2.c
 * @ingroup dataInitialisers
 *
 * @brief Second fixed config block
 *
 * This file contains the definition of the second fixed configuration block.
 * The declaration can be found in the global constants header file.
 *
 * Please ensure that all variables added here have good default values.
 *
 * <h> original author</h> Fred Cooke
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

#include "inc/freeEMS.h"


/// @todo TODO divide fixedConfig2 into useful chunks
/// @todo TODO create engine hardware config chunk
/// @todo TODO create random stuff chunk
/// @todo TODO add the userTextField2 to the dictionary/address lookup


/** @copydoc fixedConfig1 */
const volatile fixedConfig2 fixedConfigs2 FIXEDCONF2 = {
  {
    /* presetIAT */
    roomTemperature,
    /* presetCHT */
    runningTemperature,
    /* presetTPS */
    halfThrottle,
    /* presetEGO */
    stoichiometricLambda,
    /* presetBRV */
    runningVoltage,
    /* presetMAP */
    idleManifoldPressure,
    /* presetAAP */
    seaLevelKPa,
    /* presetMAT */
    roomTemperature,
    /* presetEGO2 */
    stoichiometricLambda,
    /* presetIAP */
    maxExpectedBoost,
    /* presetBPW */
    idlePulseWidth,
    /* presetAF */
    idleAirFlow
  },

  {
    /* TPSClosedMAP */
    offIdleMAP,
    /* TPSOpenMAP */
    nearlyWOTMAP,
    /* MAPMinimum */
    MPX4250AMin,
    /* MAPRange */
    MPX4250ARange,
    /* AAPMinimum */
    MPX4100AMin,
    /* AAPRange */
    MPX4100ARange,
    /* EGOMinimum */
    LC1LambdaMin,
    /* EGORange */
    LC1LambdaRange,
    /* BRVMinimum */
    batteryVoltageMin,
    /* BRVRange */
    batteryVoltageRange,
    /* TPSMinimumADC */
    TPSDefaultMin,
    /* TPSMaximumADC */
    TPSDefaultMax
  },

  {
      /* readingTimeout */
      /** Default to half a second 60rpm for a 4 cylinder
       * @todo TODO new method of ADC sampling, Always sample ADC async, If no
       *       sync, use async ADC readings, otherwise use synced. Do this with
       *       pointer to array set at beginning of math
       */
    500,
  },

  {"Place your personal notes about whatever you like in here! Don't hesitate to tell us a story about something interesting. Do keep in mind though that when you upload your settings file to the forum this message WILL be visible to all and sundry, so don't be putting too many personal details, bank account numbers, passwords, PIN numbers, license plates, national insurance numbers, IRD numbers, social security numbers, phone numbers, email addresses, love stories and other private information in this field. In fact it is probably best if you keep the information stored here purely related to the vehicle that this system is installed on and relevant to the state of tune and configuration of settings. Lastly, please remember that this field WILL be shrinking in length from it's currently large size to something more reasonable in future. I would like to attempt to keep it at least thirty two characters long though, so writing that much is a non issue, but not more"}
};
