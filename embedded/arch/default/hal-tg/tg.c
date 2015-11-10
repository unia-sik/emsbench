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
 * $Id: tg.c 502 2015-11-05 14:18:19Z klugeflo $
 * @file tg.c
 * @brief Implementation of trace generation HAL
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#include <hal/tg/tg.h>
#include <hal/log.h>

#include <stdbool.h>
#include <stdio.h>

static timctr_t time_current = 0;
static timctr_t time_primary = 0;
static timctr_t time_secondary = 0;

static oc_mode_t mode_primary = OC_MODE_ON;
static oc_mode_t mode_secondary = OC_MODE_ON;

static bool state_primary = false;
static bool state_secondary = false;

static bool finished = false;


static void set_state(bool *state, oc_mode_t mode) {
  switch (mode) {
  case OC_MODE_NONE: ///< No output change
    break;
  case OC_MODE_ON: ///< Set output pin to high
    *state = true;
    break;
  case OC_MODE_OFF: ///< Set output pin to low
    *state = false;
    break;
  case OC_MODE_TOGGLE: ///< Toggle output pin level
    *state = !(*state);
    break;
  }
}


void hal_tg_setup() {
  printf("HAL-TG setup\n");
}


void hal_tg_run() {
  printf("HAL-TG run\n");
  //int ctr = 0;
  while (!finished) {
    debug_printf("time_ cur = %u prim = %u sec = %u\n",
                 time_current, time_primary, time_secondary);
    if ( time_primary >= time_current &&
         ( time_secondary <= time_current || time_primary <= time_secondary) ) {
      time_current = time_primary;
      set_state(&state_primary, mode_primary);
      handle_primary(state_primary);
    }
    else
      if (time_secondary >= time_current &&
          time_secondary < time_primary ) { // 2nd condition should be true anyway if we come here
        time_current = time_secondary;
        set_state(&state_secondary, mode_secondary);
        handle_secondary(state_secondary);
      }
      else {
        // nothing found, seems we are running into an overflow, so reset time
        time_current = 0;
      }
    //if (++ctr > 40) return;
  }

}


void hal_tg_notify_finished() {
  printf("HAL-TG finished\n");
  finished = true;
}


void hal_tg_set_primary_time(timctr_t time, oc_mode_t mode) {
  time_primary = time;
  mode_primary = mode;
  debug_printf("T1 set to %u, mode %d\n", time, mode);
}


void hal_tg_set_secondary_time(timctr_t time, oc_mode_t mode) {
  time_secondary = time;
  mode_secondary = mode;
  debug_printf("T2 set to %u, mode %d\n", time, mode);
}


void hal_tg_advance_primary_time(timctr_t adv, oc_mode_t mode) {
  time_primary += adv;
  mode_primary = mode;
  debug_printf("T1 advance by %u to %u, mode %d\n", adv, time_primary, mode);
}


void hal_tg_advance_secondary_time(timctr_t adv, oc_mode_t mode) {
  time_secondary += adv;
  mode_secondary = mode;
  debug_printf("T2 advanced by %u to %u, mode %d\n", adv, time_secondary, mode);
}


timctr_t hal_tg_get_primary_time() {
  return time_primary;
}


timctr_t hal_tg_get_secondary_time() {
  return time_secondary;
}


timctr_t hal_tg_get_time() {
  return time_current;
}
