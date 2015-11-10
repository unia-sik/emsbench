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
 * $Id: freeems_hal_functions.c 502 2015-11-05 14:18:19Z klugeflo $
 * @brief Implementation of nearly all HAL functions.
 * @file freeems_hal_functions.c
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#include <hal/ems/freeems_hal.h>
#include "freeems_hal_globals.h"
#include "freeems_hal_macros.h"

/**
 * This array is used to store the current interval times of the ignition
 * timers. The original FreeEMS wrote theses times directly into registers and
 * if needed read them directly from those registers.
 *
 * This does nor work any more, because the stm32f4 is set up to use the
 * channels 3 and 4 of TIM2 for the ignition timers. This timer has only one
 * count register. To set when the next ignition interrupt has to occure the
 * compare register of channel 3 (or 4) is set to
 * [current_timer_count] + [next interval time]. That means the actual interval
 * time is no longer obtainable from a register.
 **/
// TODO AM: find a better solution for this problem
// possible solutions are
// - alter FreeEMS so it no longer needs to get the interval time from the
//   hardware/hal
// - use a different timers for each interrupt (probably not possible because
//   there are not enough timers)
uint16_t ignitionIntervalls[2] = { 0, 0 };
#define DWELL_INTERVALL 0
#define FIRE_INTERVALL 1

uint16_t
hal_timer_time_get (void) {
  return 0;
}

bool
hal_timer_overflow_get (void) {
  return 0;
}

void
hal_timer_overflow_clear (void) {
}

uint16_t
hal_timer_ic_capture_get (channelid_t channel_id) {
  return 0;
}

pinstate_t
hal_timer_ic_pin_get (channelid_t channel_id) {
  return false;
}

pinstate_t
hal_timer_oc_pin_get (channelid_t channel_id) {
  return 0;
}

bool
hal_timer_oc_active_get (channelid_t channel_id) {
  return false;
}

void
hal_timer_oc_active_set (channelid_t channel_id, bool active) {
}

void
hal_timer_oc_compare_set (channelid_t channel_id, uint16_t value) {
}

uint16_t
hal_timer_oc_compare_get (channelid_t channel_id) {
  return 0;
}

void
hal_timer_oc_output_set (channelid_t channel_id, ocmode_t mode) {
}

void
hal_timer_pit_interval_set (pitid_t pit_id, uint16_t value) {
}

uint16_t
hal_timer_pit_interval_get (pitid_t pit_id) {
  return 0;
}

bool
hal_timer_pit_active_get (pitid_t pit_id) {
  return false;
}

void
hal_timer_pit_active_set (pitid_t pit_id, bool active) {
}

uint16_t
hal_timer_pit_current_get (pitid_t pit_id) {
  return 0;
}

pinstate_t
hal_io_get (channelid_t channel_id) {
  return false;
}

void
hal_io_set (channelid_t channel_id, pinstate_t value) {
}

void
hal_performance_startCounter () {
}

unsigned int
hal_performance_stopCounter () {
  return 0;
}

