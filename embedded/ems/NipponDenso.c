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
 * @file NipponDenso.c
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief Reads Nippon Denso 24/2 sensors
 *
 * This file contains the two interrupt service routines for handling engine
 * position and RPM signals from mainly Toyota engines using this sensor style.
 *
 * One ISR handles the 24 evenly spaced teeth and the other handles the two
 * adjacent teeth. This signal style provides enough information for wasted
 * spark ignition and semi sequential fuel injection.
 *
 * Supported engines include:
 * - 4A-GE
 * - 7A-FE
 * - 3S-GE
 * - 1UZ-FE
 * - Mazda F2T
 *
 * <h> original author</h> Fred Cooke
 * @note Pseudo code that does not compile with zero warnings and errors MUST be
 *       commented out.
 *
 * @todo TODO make this generic for evenly spaced teeth with a pulse per
 *       revolution from the second input.
 *
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

#include "inc/freeEMS.h"
#include "inc/interrupts.h"
#include "inc/DecoderInterface.h"
#include "inc/utils.h"
#include <hal/ems/freeems_hal.h>
#include <hal/log.h>

/** Primary RPM ISR
 *
 * Summary of intended engine position capture scheme (out of date as at 3/1/09)
 *
 * Position/RPM signal interpretation :
 * Discard edges that have arrived too soon (lose sync here?)
 * Check to ensure we haven't lost sync (pulse arrives too late)
 * Compare time stamps of successive edges and calculate RPM
 * Store RPM and position in globals
 *
 * Schedule events :
 * loop through all events (spark and fuel), schedule those that fall
 * sufficiently after this tooth and before the next one we expect.
 *
 * Sample ADCs :
 * Grab a unified set of ADC readings at one time in a consistent crank location
 * to eliminate engine cycle dependent noise. Set flag stating that New pulse,
 * advance, etc should be calculated.
 *
 * @author Fred Cooke
 *
 * @warning These are for testing and demonstration only, not suitable for
 *          driving with just yet.
 *
 * @todo TODO bring the above docs up to date with reality
 * @todo TODO finish this off to a usable standard
 */
void PrimaryRPMISR() {

  /* Save all relevant available data here */
  /* Save the current timer count */
  unsigned short codeStartTimeStamp = hal_timer_time_get();

  /* Save the edge time stamp */
  unsigned short edgeTimeStamp = hal_timer_ic_capture_get(PRIMARY_RPM_INPUT);
  /* Save the values on port T regardless of the state of DDRT */
  unsigned char PTITCurrentState = hal_timer_ic_pin_get(PRIMARY_RPM_INPUT);

  /* Calculate the latency in ticks */
  ISRLatencyVars.primaryInputLatency = codeStartTimeStamp - edgeTimeStamp;

  /** @todo TODO discard narrow ones! test for tooth width and tooth period
   * the width should be based on how the hardware is setup. IE the LM1815
   * is adjusted to have a pulse output of a particular width. This noise
   * filter should be matched to that width as should the hardware filter.
   */

  /* The LM1815 variable reluctance sensor amplifier allows the output to be
   * pulled high starting at the center of a tooth. So, what we see as the
   * start of a tooth is actually the centre of a physical tooth. Because
   * tooth shape, profile and spacing may vary this is the only reliable edge
   * for us to schedule from, hence the trailing edge code is very simple.
   */
  if (PTITCurrentState) {

    // increment crank pulses TODO this needs to be wrapped in tooth period and
    // width checking
    primaryPulsesPerSecondaryPulse++;

    // calculate rough rpm (this will be wrong when the var is used correctly)
    /* 0.8us ticks, 150mil = 2 x 60 seconds, times rpm scale factor of 2 */
    *RPMRecord = ticksPerCycleAtOneRPMx2 / engineCyclePeriod;

    // don't run until the second trigger has come in and the period is correct
    // (VERY temporary)
    if (!(coreStatusA & PRIMARY_SYNC)) {
      log_printf("EP s1\r\n");
      primaryTeethDroppedFromLackOfSync++;
      return;
    }

    LongTime timeStamp;

    /* Install the low word */
    timeStamp.timeShorts[0] = edgeTimeStamp;
    /* Find out what our timer value means and put it in the high word */
    if (hal_timer_overflow_get() && !(edgeTimeStamp & 0x8000)) {
      timeStamp.timeShorts[1] = timerExtensionClock + 1;
    }
    else {
      timeStamp.timeShorts[1] = timerExtensionClock;
    }

    // temporary data from inputs
    primaryLeadingEdgeTimeStamp = timeStamp.timeLong;
    timeBetweenSuccessivePrimaryPulses = primaryLeadingEdgeTimeStamp
                                         - lastPrimaryPulseTimeStamp;
    lastPrimaryPulseTimeStamp = primaryLeadingEdgeTimeStamp;


    // TODO make scheduling either fixed from boot with a limited range, OR
    //      preferrably if its practical scheduled on the fly to allow arbitrary
    //      advance and retard of both fuel and ignition.

    /* Check for loss of sync by too high a count */
    if (primaryPulsesPerSecondaryPulse > 12) {
      log_printf("EP s2\r\n");
      /* Increment the lost sync count */
      Counters.crankSyncLosses++;

      /* Reset the count of teeth */
      primaryPulsesPerSecondaryPulse = 0;
      /* Get the hell out of here before we do something bad */
      return;
    }

    // CAUTION came to me lying in bed half asleep idea :

    // TODO move tooth selection to the calc loop in main such that this routine
    //      just iterates through an array of events and schedules those that
    //      are destined for this tooth.

    // if ign enabled
    // iterate through ignition first, schedule all of those
    // iterate through dwell next, schedule all of those
    // if fuel enabled
    // iterate through main fuel next, schedule all of those
    // if staging enabled and required
    // iterate through staged fuel last,

    // TODO should make for a clean compact scheduling implementation. the fuel
    //      code doesn't care when/how it has started in the past, and hopefully
    //      ign will be the same.

    // this will be done with an array and per tooth check in future
    if ((primaryPulsesPerSecondaryPulse % 2) == 0) {
      // TODO sample ADCs on teeth other than that used by the scheduler in
      //      order to minimise peak run time and get clean signals
      sampleEachADC(ADCArrays);
      Counters.syncedADCreadings++;
      *mathSampleTimeStampRecord = hal_timer_time_get();

      /* Set flag to say calc required */
      coreStatusA |= CALC_FUEL_IGN;

      /* Reset the clock for reading timeout */
      Clocks.timeoutADCreadingClock = 0;

      if (masterPulseWidth > injectorMinimumPulseWidth) {
	// use reference PW to decide. spark needs moving outside this area
	// though TODO
        /* Determine if half the cycle is bigger than short-max */
        unsigned short maxAngleAfter;
        if ((engineCyclePeriod >> 1) > 0xFFFF) {
          maxAngleAfter = 0xFFFF;
        }
        else {
          maxAngleAfter = (unsigned short) (engineCyclePeriod >> 1);
        }

        /* Check advance to ensure it is less than 1/2 of the previous engine
         * cycle and more than codetime away */
        unsigned short advance;
        if (totalAngleAfterReferenceInjection > maxAngleAfter) {
          // if too big, make it max
          advance = maxAngleAfter;
        }
        else
          if (totalAngleAfterReferenceInjection
              < trailingEdgeSecondaryRPMInputCodeTime) {
            // if too small, make it min
            advance = trailingEdgeSecondaryRPMInputCodeTime;
          }
          else {   // else use it as is
            advance = totalAngleAfterReferenceInjection;
          }

        // determine the long and short start times
        unsigned short startTime = primaryLeadingEdgeTimeStamp
                                   + advance;
        unsigned long startTimeLong = timeStamp.timeLong + advance;

        /* Determine the channels to schedule */
        unsigned char fuelChannel = (primaryPulsesPerSecondaryPulse / 2)
                                    - 1;
        unsigned char ignitionChannel = (primaryPulsesPerSecondaryPulse
                                         / 2) - 1;
        if (fuelChannel > 5 || ignitionChannel > 5) {
          return;
        }

        // FAK: FIXME: channel 0 gets fired before injection!?!?
        // determine whether or not to reschedule
        unsigned char reschedule = 0;
        unsigned long diff = startTimeLong
                             - (injectorMainEndTimes[fuelChannel]
                                + injectorSwitchOffCodeTime);
        if (diff > LONGHALF) {
          // http://www.diyefi.org/forum/viewtopic.php?f=8&t=57&p=861#p861
          reschedule = 1;
        }

        // schedule the appropriate channel
        if (!hal_timer_oc_active_get(INJECTIONX_OUTPUT(fuelChannel)) || reschedule) {
          hal_timer_oc_active_set(INJECTIONX_OUTPUT(fuelChannel), TRUE);
          hal_timer_oc_output_set(INJECTIONX_OUTPUT(fuelChannel), OC_MODE_TO_HIGH);
          hal_timer_oc_compare_set(INJECTIONX_OUTPUT(fuelChannel), startTime);
        }
        else {
          injectorMainStartTimesHolding[fuelChannel] = startTime;
          // setup a bit to let the timer interrupt know to set its own new start from a var
          selfSetTimer |= injectorMainOnMasks[fuelChannel];
          log_printf("P@%u: Nq%u@%u (%u)\r\n", edgeTimeStamp, fuelChannel, startTime, advance);
        }

        // TODO advance/retard/dwell numbers all need range checking etc done.
        //      some of this should be done in the calculator section, and some
        //      here. currently none is done at all and for that reason, this
        //     will not work in a real system yet, if it works at all.
        // as do array indexs here and in the ISRs...

        // TODO implement mechanism for dropping a cylinder in event of over
        //      queueing or spark cut/round robin important as ignition sequence
        //      disrupted when this occurs as it stands.

        // TODO check queue length checks to ensure we dont count up to
        //      somewhere we can never count down from. This could be causing
        //      the hanging long phenomina

        // DWELL

        // If dwell is not currently enabled, set it all up
        if (!hal_timer_pit_active_get(IGNITION_DWELL_PIT)) {
          /* Schedule Dwell event (do this first because it comes earliest. */
          // set the channel to fire
          nextDwellChannel = ignitionChannel;

          // set the time
          hal_timer_pit_interval_set(IGNITION_DWELL_PIT, advance);
          // turn on the ints
          hal_timer_pit_active_set(IGNITION_DWELL_PIT, TRUE);
          log_printf("P@%u: IDa%u@%u\r\n", edgeTimeStamp, nextDwellChannel, advance);
        }
        else
          if (dwellQueueLength == 0) {
            // load time offset such that next period is correct
            hal_timer_pit_interval_set(IGNITION_DWELL_PIT,
                                       advance
                                       - hal_timer_pit_current_get(
                                         IGNITION_DWELL_PIT));
            // increment queue length
            dwellQueueLength++;
            log_printf("P@%u: IDd%u@%u\r\n", edgeTimeStamp, nextDwellChannel, advance - hal_timer_pit_current_get(IGNITION_DWELL_PIT));
          }
          else
            if (dwellQueueLength
                > fixedConfigs1.engineSettings.combustionEventsPerEngineCycle) {
              //TODO sensible figures here for array index OOBE
              // do nothing, or increment a counter or something similar.
            }
            else {
              //unsigned short sumOfDwells = PITLD0;
              unsigned short sumOfDwells = hal_timer_pit_interval_get(
                                             IGNITION_DWELL_PIT);
              // add up the prequeued time periods

              // queue = 1 pitld is all
              // queue = 2 one from 0 index of array AND pitld

              unsigned char index = 0;
              while (index < (dwellQueueLength - 1)) {
                sumOfDwells += queuedDwellOffsets[index];
                index++;
              }

              // store time offset in appropriate array location
              //queuedDwellOffsets[dwellQueueLength - 1] = advance - (PITCNT0 + sumOfDwells);
              queuedDwellOffsets[dwellQueueLength - 1] = advance
                  - (hal_timer_pit_current_get(IGNITION_DWELL_PIT)
                     + sumOfDwells);
              // increment queue length from one or more
              dwellQueueLength++;
              log_printf("P@%u: IDq%u@%u\r\n", edgeTimeStamp, nextDwellChannel, advance - (hal_timer_pit_current_get(IGNITION_DWELL_PIT) + sumOfDwells));
            }

        // IGNITION experimental stuff

        // If ignition is not currently enabled, set it all up
        if (!hal_timer_pit_active_get(IGNITION_FIRE_PIT)) {
          /* Schedule Ignition event (do this first because it comes earliest. */
          // set the channel to fire
          nextIgnitionChannel = ignitionChannel;

          // figure out the time to set the delay reg to
          hal_timer_pit_interval_set(IGNITION_FIRE_PIT,
                                     advance
                                     + injectorMainPulseWidthsRealtime[fuelChannel]);
        //PITLD1 = ignitionAdvances[ignitionChannel + outputBankIgnitionOffset];
          hal_timer_pit_active_set(IGNITION_FIRE_PIT, TRUE);
          log_printf("P@%u: IFa%u@%u\r\n", edgeTimeStamp, nextIgnitionChannel, advance + injectorMainPulseWidthsRealtime[fuelChannel]);
        }
        else
          if (ignitionQueueLength == 0) {
            // load timer register
            hal_timer_pit_interval_set(IGNITION_FIRE_PIT,
                                       advance
                                       + injectorMainPulseWidthsRealtime[fuelChannel]
                                       - hal_timer_pit_current_get(
                                         IGNITION_FIRE_PIT));
            // increment to 1
            ignitionQueueLength++;
            log_printf("P@%u: IFd%u@%u\r\n", edgeTimeStamp, nextIgnitionChannel, advance + injectorMainPulseWidthsRealtime[fuelChannel] - hal_timer_pit_current_get(IGNITION_FIRE_PIT));
          }
          else
            if (ignitionQueueLength
                > fixedConfigs1.engineSettings.combustionEventsPerEngineCycle) {
              //TODO sensible figures here for array index OOBE
              // do nothing, or increment a counter or something similar.
            }
            else {
              //unsigned short sumOfIgnitions = PITLD1;
              unsigned short sumOfIgnitions = hal_timer_pit_interval_get(
                                                IGNITION_FIRE_PIT);
              // add up the prequeued time periods

              // queue = 1 pitld is all
              // queue = 2 one from 0 index of array AND pitld

              unsigned char index = 0;
              while (index < (ignitionQueueLength - 1)) {
                sumOfIgnitions += queuedIgnitionOffsets[index];
                index++;
              }

              // store time offset in appropriate array location
              //queuedIgnitionOffsets[ignitionQueueLength - 1] = advance - (PITCNT1 + sumOfIgnitions);
              queuedIgnitionOffsets[ignitionQueueLength - 1] = advance
                  - (hal_timer_pit_current_get(IGNITION_FIRE_PIT)
                     + sumOfIgnitions);

              // increment from 1 or more
              ignitionQueueLength++;

              log_printf("P@%u: IFq%u@%u\r\n", edgeTimeStamp, nextIgnitionChannel, advance - (hal_timer_pit_current_get(IGNITION_FIRE_PIT) + sumOfIgnitions));
            }
      }
    }
    else {
      RuntimeVars.primaryInputLeadingRuntime = hal_timer_time_get()
          - codeStartTimeStamp;
    }
  }
  else {
    hal_io_set(DEBUG_OUTPUT_1, HIGH);
    hal_io_set(DEBUG_OUTPUT_2, HIGH);
    hal_io_set(DEBUG_OUTPUT_3, HIGH);
    hal_io_set(DEBUG_OUTPUT_4, HIGH);
    hal_io_set(DEBUG_OUTPUT_5, HIGH);
    hal_io_set(DEBUG_OUTPUT_6, HIGH);
    hal_io_set(DEBUG_OUTPUT_7, HIGH);
    RuntimeVars.primaryInputTrailingRuntime = hal_timer_time_get()
        - codeStartTimeStamp;
  }

  Counters.primaryTeethSeen++;
  // suss out rpm and accurate TDC reference

  // if you say it quick, it doesn't sound like much :
  // schedule fuel and ign based on spark cut and fuel cut and timing vars and
  // status vars config vars
}

/** Secondary RPM ISR
 *
 * Similar to the primary one.
 *
 * @todo TODO bring this documentation up to date.
 * @todo TODO finish this off to a usable standard.
 */
void SecondaryRPMISR() {

  /* Save all relevant available data here */
  /* Save the current timer count */
  unsigned short codeStartTimeStamp = hal_timer_time_get();
  /* Save the timestamp */
  unsigned short edgeTimeStamp = hal_timer_ic_capture_get(SECONDARY_RPM_INPUT);

  log_printf("s%d\r\n", codeStartTimeStamp);

  /* Calculate the latency in ticks */
  ISRLatencyVars.secondaryInputLatency = codeStartTimeStamp - edgeTimeStamp;

  /** @todo TODO discard narrow ones! test for tooth width and tooth period
   * the width should be based on how the hardware is setup. IE the LM1815
   * is adjusted to have a pulse output of a particular width. This noise
   * filter should be matched to that width as should the hardware filter.
   */

  /* The LM1815 variable reluctance sensor amplifier allows the output to be
   * pulled high starting at the center of a tooth. So, what we see as the
   * start of a tooth is actually the centre of a physical tooth. Because
   * tooth shape, profile and spacing may vary this is the only reliable edge
   * for us to schedule from, hence the trailing edge code is very simple.
   */
  if (hal_timer_ic_pin_get(SECONDARY_RPM_INPUT)) {

// was this code like this because of a good reason?
// primaryPulsesPerSecondaryPulseBuffer = primaryPulsesPerSecondaryPulse;
    primaryPulsesPerSecondaryPulse = 0;

    // if we didn't get the right number of pulses drop sync and start over
    if ((primaryPulsesPerSecondaryPulse != 12)
        && (coreStatusA & PRIMARY_SYNC)) {
      coreStatusA &= CLEAR_PRIMARY_SYNC;
      Counters.crankSyncLosses++;
    }

    LongTime timeStamp;

    /* Install the low word */
    timeStamp.timeShorts[0] = edgeTimeStamp;
    /* Find out what our timer value means and put it in the high word */
    //TODO AM: see same code in PrimaryRPMISR
    if (hal_timer_overflow_get()) {
      timeStamp.timeShorts[1] = timerExtensionClock + 1;
    }
    else {
      timeStamp.timeShorts[1] = timerExtensionClock;
    }

    // get the data we actually want
    // save the engine cycle period
    engineCyclePeriod = 2 * (timeStamp.timeLong - lastSecondaryOddTimeStamp);
    // save this stamp for next time round
    lastSecondaryOddTimeStamp = timeStamp.timeLong;

    // Because this is our only reference, each time we get this pulse, we know
    // where we are at (simple mode so far)
    coreStatusA |= PRIMARY_SYNC;
    RuntimeVars.secondaryInputLeadingRuntime = hal_timer_time_get()
        - codeStartTimeStamp;
  }
  else {
    RuntimeVars.secondaryInputTrailingRuntime = hal_timer_time_get()
        - codeStartTimeStamp;
  }

  Counters.secondaryTeethSeen++;
  // suss out phase/engine cycle reference showing which bank we are on

  /* If the flag is not cleared at the beginning then the interrupt gets
   * rescheduled while it is running, hence it can't be done at the end of the
   * ISR */
}
