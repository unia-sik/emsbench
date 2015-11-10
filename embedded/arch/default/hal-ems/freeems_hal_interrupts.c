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
 * $Id: freeems_hal_interrupts.c 502 2015-11-05 14:18:19Z klugeflo $
 * @brief All interrupt service routines of the hal.
 * @file freeems_hal_interrupts.c
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#include <hal/ems/freeems_hal.h>

#include "freeems_hal_globals.h"
#include "freeems_hal_macros.h"

//#include "freeems.h"

/**
 * @author Andreas Meixner
 *
 * The hal has to generate the following interrupt calls to the FreeEMS code.
 *
 * 1. Every 125us call RTIISR() to update the internal clock
 * 2. Whenever the real time clock counter reaches a multiple of 2¹⁶ = 65536
 *    call TimerOverflow()
 * 3. When the pin state of the RPM meter changes call PrimaryRPMISR()
 *    or SecondaryRPMISR()
 * 4. When the ignition dwell timer elapses call IgnitionDwellISR()
 * 5. When the ignition fire timer elapses call IgnitionFireISR()
 * 6. When one of the injection timers elapses call the respective
 *    Injector1ISR(), Injector2ISR(), Injector3ISR(), ...
 *
 */


