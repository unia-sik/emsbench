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
 * @file ignitionISRs.c
 * @ingroup interruptHandlers
 *
 * @brief Turn ignition channels on and off
 *
 * This currently semi-working but broken code is intended to one day provide
 * multi-channel ignition capabilities. The basic method will be to turn a pin
 * or set of pins on or another pin or set of pins off during each run of the
 * appropriate handler. Each run will be triggered either by the scheduler and
 * possibly this code itself as well. Currently it does not work correctly and
 * isn't suitable for actual use as an ignition control solution.
 *
 * <h> original author</h> Fred Cooke
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

#define IGNITIONISRS_C
#include "inc/freeEMS.h"
#include "inc/interrupts.h"
#include "hal/ems/freeems_hal.h"
#include <hal/log.h>


/* Summary of intended ignition timing scheme
 *
 * Set TWO PIT timers based on a reference point (probably single cam trigger or
 * optionally toggle bit based on missing tooth on crank)
 * Arm one PIT timer interrupt to trigger when we need to start dwelling
 * Arm the other PIT timer interrupt to trigger when we need to fire
 * Configure a variable to point to the next pin to turn on for dwell
 * Configure a variable to point to the next pin to turn off to fire
 * On PIT interrupt for dwell check to see that spark should have finished
 * If so, turn on coil to dwell
 * If not, reset dwell timer interrupt for end of spark event
 * On PIT interrupt for spark, turn off coil (amything else?)
 * Repeat for each cylinder.
 */

/* Further consideration to spark duration and dwell starting possibly needs to
 * be done. */

/* further reading: ftp://ftp-sop.inria.fr/esterel/pub/papers/FDL99-camready.pdf
 * section 4.1 has a nice diagram */


/**	@brief Ignition dwell control
 *
 * This function turns ignition pins on to dwell when required.
 *
 * @author Fred Cooke
 *
 * @todo TODO make this actually work.
 */
void IgnitionDwellISR(void) {

  CAPTURE_START_TIME();

  log_printf("ID%u@%u %u\r\n", nextDwellChannel, hal_timer_pit_interval_get(IGNITION_DWELL_PIT), GET_START_TIME());
  // start dwelling asap
  hal_io_set(IGNITIONX_OUTPUT(nextDwellChannel), HIGH);
  if(dwellQueueLength == 0) {
    // turn off the int
    hal_timer_pit_active_set(IGNITION_DWELL_PIT, FALSE);

  }
  else {
    // reduce queue length by one
    dwellQueueLength--;

    // increment channel counter to next channel
    if(nextDwellChannel < (fixedConfigs1.engineSettings.combustionEventsPerEngineCycle - 1)) {
      nextDwellChannel++; // if not the last channel, increment
    }
    else {
      nextDwellChannel = 0; // if the last channel, reset to zero
    }

    // if the queue length after decrement is greater than 0 then we need to
    // load the timer, if it is zero and we decremented, the timer was already
    // loaded.
    if(dwellQueueLength > 0) {
      if(dwellQueueLength > 8) {
	// TODO ???? why 8 ???? 12 or combustion events per... or ?
        // throw a nasty error of some sort for index out of range issue that
	// should never occur (for now just light a LED)
      }
      else {
        // load the timer if the index is good
        // FIXME: Use IGNITION_DWELL_PIT instead of channel stuff!
        hal_timer_pit_interval_set(IGNITION_DWELL_PIT, queuedDwellOffsets[dwellQueueLength - 1]);
        log_printf("IDr%u@%u\r\n", nextDwellChannel, queuedDwellOffsets[dwellQueueLength - 1]);
      }
    }
  }
}


/**	@brief Ignition discharge control
 *
 * This function turns ignition pins off to discharge when required.
 *
 * @author Fred Cooke
 *
 * @todo TODO make this actually work.
 */
void IgnitionFireISR(void) {
  CAPTURE_START_TIME();

  log_printf("IF%u@%u %u\r\n", nextIgnitionChannel, hal_timer_pit_interval_get(IGNITION_FIRE_PIT), GET_START_TIME());
  // fire the coil asap
  hal_io_set(IGNITIONX_OUTPUT(nextIgnitionChannel), LOW);

  if(ignitionQueueLength == 0) {
    // turn off the int
    hal_timer_pit_active_set(IGNITION_FIRE_PIT, FALSE);
  }
  else {
    // reduce queue length by one
    ignitionQueueLength--;

    // increment channel counter to next channel
    if(nextIgnitionChannel < (fixedConfigs1.engineSettings.combustionEventsPerEngineCycle - 1)) {
      nextIgnitionChannel++; // if not the last channel, increment
    }
    else {
      nextIgnitionChannel = 0; // if the last channel, reset to zero
    }

    // if the queue length after decrement is greater than 0 then we need to
    // load the timer, if it is zero and we decremented, the timer was already
    // loaded.
    if(ignitionQueueLength > 0) {
      if(ignitionQueueLength > fixedConfigs1.engineSettings.combustionEventsPerEngineCycle) {
	// TODO as above!!!!!!!!!!
        // throw a nasty error of some sort for index out of range issue that
	// should never occur (for now just light a LED)
      }
      else {
        // load the timer if the index is good
        // FIXME: Use IGNITION_FIRE_PIT instead of channel stuff!
        hal_timer_pit_interval_set(IGNITION_FIRE_PIT, queuedIgnitionOffsets[ignitionQueueLength - 1]);
        log_printf("IFr%u@%u\r\n", nextIgnitionChannel, queuedIgnitionOffsets[ignitionQueueLength - 1]);
      }
    }
  }
}
