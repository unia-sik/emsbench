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
 * @file setup.c
 * @brief Setup functions for FreeEMS.
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */

#include "freeems.h"
#include <hal/ems/freeems_hal.h>
#include <hal/log.h>

/**** Setup functions */


void setup_emulation(void) {
  log_printf("setting up emulation\r\n");
  /*
   * masterPulseWidth and totalAngleAfterReferenceInjection are
   * set in **freeems/fuelAndIgnitionCalcs.c** in function:
   * **calculateFuelAndIgnition()** which is called in the freeems_main
   */
  masterPulseWidth = 123;
  totalAngleAfterReferenceInjection = 123;
}
