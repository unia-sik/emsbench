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
 * @file staticInit.c
 * @brief Static initialisation of non-zero variables
 *
 * This file contains static initialisations for fields that require a non-zero
 * initial value after reset. Zero fields are taken care of by GCC and doing
 * this here means less init time and init code, both good things. Variables
 * initialised here are placed together by the compiler in flash and copied up
 * to RAM as a linear block before the main method runs. This is significantly
 * more efficient than doing them one-by-one in an init routine.
 *
 * <h> original author</h> Fred Cooke
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

#include "inc/freeEMS.h"


//unsigned char asyncDatalogType = asyncDatalogBasic;
unsigned char asyncDatalogType = asyncDatalogBasic;

unsigned short tachoPeriod = 65535;	/* Lowest RPM at start up time. */

// Values for testing
unsigned short masterPulseWidth = 10;
unsigned short totalAngleAfterReferenceIgnition = 540;
unsigned short totalAngleAfterReferenceInjection = 180;

/* Setup the pointers to the registers for fueling use, this does NOT work if
 * done in global.c, I still don't know why. */

// TODO perhaps read from the ds1302 once at start up and init the values or
//      different ones with the actual time and date then update them in RTI

/* Setup so that the tacho reads low when the engine isn't running */
unsigned long engineCyclePeriod = ticksPerCycleAtOneRPM;
