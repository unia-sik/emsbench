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
 * $Id: freeems_hal_init.c 502 2015-11-05 14:18:19Z klugeflo $
 * @brief Implementation of initialization functions.
 * @file freeems_hal_init.c
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#include <hal/ems/freeems_hal.h>

/**** Setup functions */

/*
 * Setup timers
 */
static void hal_priv_timer_setup() {
}

static void hal_priv_gpio_setup() {
}

static void hal_priv_isr_setup() {
}

void hal_system_clock(void) {
}

void hal_system_init(void) {
}

void hal_system_start(void) {
  hal_priv_timer_setup();
  hal_priv_gpio_setup();
  hal_priv_isr_setup();
}

