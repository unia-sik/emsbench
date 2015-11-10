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
 * @file injectorISR.c
 * @brief Prototype implementation of the incection callback function.
 * <h> original author</h> Fred Cooke
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

#include <hal/ems/freeems_hal.h>

/**	@file injectorISR.c
 *
 * @brief Injector ISR shared code
 *
 * This code is identical between all 6 channels, and thus we only want one
 * copy of it. The X in each macro will be replaced with the number that is
 * appropriate for the channel it is being used for at the time.
 *
 * Each channel performs the following actions
 *
 * - 1	Clear its interrupt flag
 * - 2	Record its start time
 * - 3	Measure and record its latency
 * - 4	Check to see if its just turned on
 *   - 4.1	Copy the channels pulse width to a local variable
 *   - 4.2	Determine the minimum pulse width based on code run time const
 *               and latency
 *   - 4.3	Clamp used pulsewidth inside min and max
 *   - 4.4	If used pulse width is larger than the current period of the
 *               engines cycle flag as always on
 *   - 4.5	Set the action to turn off
 *   - 4.6	Increment the time by pulse width
 *   - 4.7	If staging required, either, switch them on and sched to turn
 *               off, or sched to turn on
 * - 5	Else it has just turned off
 *   - 5.1	If staged channel is still on, turn it off
 *   - 5.2	If(self schedule flagged) schedule the next start
 *   - 5.3	Else disable itself
 * - 6	Calculate and record code run time
 * - 7	Return
 *
 * @author Fred Cooke
 */


void InjectorXISR() {

  /* Record the current time as start time */
  unsigned short TCNTStart = hal_timer_time_get();

  /* Record the edge time stamp from the IC register */
  unsigned short edgeTimeStamp = hal_timer_oc_compare_get(INJECTIONX_OUTPUT(INJECTOR_CHANNEL_NUMBER));

  /* Calculate and store the latency based on compare time and start time */
  injectorCodeLatencies[INJECTOR_CHANNEL_NUMBER] = TCNTStart - edgeTimeStamp;

  /* If rising edge triggered this */
  if(hal_timer_oc_pin_get(INJECTIONX_OUTPUT(INJECTOR_CHANNEL_NUMBER)) == HIGH) {

    /* Find out what max and min for pulse width are */
    unsigned short localPulseWidth = injectorMainPulseWidthsRealtime[INJECTOR_CHANNEL_NUMBER];
    unsigned short localMinimumPulseWidth = injectorSwitchOnCodeTime + injectorCodeLatencies[INJECTOR_CHANNEL_NUMBER];
    /** @todo TODO *maybe* instead of checking min and increasing pulse, just
     * force it straight off if diff between start and now+const is greater than
     * desired pulsewidth */

    /* Ensure we dont go under minimum pulsewidth */
    if(localPulseWidth < localMinimumPulseWidth) {
      localPulseWidth = localMinimumPulseWidth;
    }/* else{ just use the value } */

    LongTime timeStamp;

    /* Install the low word */
    timeStamp.timeShorts[0] = edgeTimeStamp;

    /* Find out what our timer value means and put it in the high word */
    if(hal_timer_overflow_get()) {
      timeStamp.timeShorts[1] = timerExtensionClock + 1;
    }
    else {
      timeStamp.timeShorts[1] = timerExtensionClock;
    }

    // store the end time for use in the scheduler
    injectorMainEndTimes[INJECTOR_CHANNEL_NUMBER] = timeStamp.timeLong + localPulseWidth;

    /* Set the action for compare to switch off FIRST or it might inadvertently
     * PWM the injector during opening... */
    hal_timer_oc_output_set(INJECTIONX_OUTPUT(INJECTOR_CHANNEL_NUMBER), OC_MODE_TO_LOW);

    /* Set the time to turn off again */
    hal_timer_oc_compare_set(INJECTIONX_OUTPUT(INJECTOR_CHANNEL_NUMBER), edgeTimeStamp + localPulseWidth);

    log_printf("Nh%u@%u: Nl@%u (%u)\r\n", INJECTOR_CHANNEL_NUMBER, edgeTimeStamp, edgeTimeStamp + localPulseWidth, localPulseWidth);

    /* This is the point we actually want the time to, but because the code is
     * so simple, it can't help but be a nice short time */

    /* If staged injection is required, switch on or schedule corresponding
     * staged injector and remember that we did. */
    if (coreStatusA & STAGED_REQUIRED) {
      if (fixedConfigs1.coreSettingsA & STAGED_START) {
        /* Switch that channel on NOW */
        STAGEDPORT |= STAGEDXON;
        stagedOn |= STAGEDXON;
      }
      else {
        /* Schedule the start at a later time */
        /// @todo TODO PIT scheduling of staged start
      }
    }
    /* Calculate and store code run time */
    injectorCodeOpenRuntimes[INJECTOR_CHANNEL_NUMBER] = hal_timer_time_get() - TCNTStart;
  }
  else { // Stuff for switch off time
    log_printf("Nl%u@%u\r\n", INJECTOR_CHANNEL_NUMBER, edgeTimeStamp);
    /* If we switched the staged injector on and it's still on, turn it off now.*/
    if (stagedOn & STAGEDXON) {
      STAGEDPORT &= STAGEDXOFF;
      stagedOn &= STAGEDXOFF;
    }

    /* Set the action for compare to switch on and the time to next start time,
     * clear the self timer flag */
    if (selfSetTimer & injectorMainOnMasks[INJECTOR_CHANNEL_NUMBER]) {
      hal_timer_oc_compare_set(INJECTIONX_OUTPUT(INJECTOR_CHANNEL_NUMBER), injectorMainStartTimesHolding[INJECTOR_CHANNEL_NUMBER]);
      hal_timer_oc_output_set(INJECTIONX_OUTPUT(INJECTOR_CHANNEL_NUMBER), OC_MODE_TO_HIGH);
      selfSetTimer &= injectorMainOffMasks[INJECTOR_CHANNEL_NUMBER];
      log_printf("Nlur@%u\r\n", injectorMainStartTimesHolding[INJECTOR_CHANNEL_NUMBER]);
    }
    else {
      // Disable interrupts and actions incase the period from this end to the
      // next start is long (saves cpu)
      hal_timer_oc_output_set(INJECTIONX_OUTPUT(INJECTOR_CHANNEL_NUMBER), OC_MODE_TO_LOW);
      hal_timer_oc_active_set(INJECTIONX_OUTPUT(INJECTOR_CHANNEL_NUMBER), FALSE);
    }
    /* Calculate and store code run time */
    injectorCodeCloseRuntimes[INJECTOR_CHANNEL_NUMBER] = hal_timer_time_get() - TCNTStart;
  }
}
