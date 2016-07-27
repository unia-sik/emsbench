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
 * @file main.c
 * @brief main file of emsbench software.
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

#include <hal/ems/freeems_hal.h>
#include <hal/log.h>
#include "inc/main.h"
#include "setup.h"

int main(void) {
  hal_system_clock();

  // FIXME: this is platform-specific, add start-wait hooks to HAL
  log_init();

  debug_puts("Initializing stuff!\r\n");
  hal_system_init();

  hal_system_info();

  debug_puts("Starting Timers!\r\n");
  hal_system_start();

  debug_puts("Entering FreeEMS!\r\n");

  setup_emulation();

  main_freeems();

  while(1) {
    debug_puts("STUCK IN MEANINGLESS INFINITE LOOP! (main.c 43)");
  }

  debug_puts("Everything is over :-(");
  return 0;
}

