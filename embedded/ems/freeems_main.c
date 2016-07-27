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
 * @file freeems_main.c
 * @brief The main function!
 *
 * The function main is traditionally an applications starting point. For us
 * it has two jobs. The first is to call init() which initialises everything
 * before any normal code runs. After that main() is simply an infinite loop
 * from which low priority non-realtime code runs. The most important units of
 * code that runs under the main loop umbrella are the injection, ignition and
 * scheduling calculations.
 * <h> original author</h> Fred Cooke
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

#include <hal/ems/freeems_hal.h>
#include <hal/log.h>
#include "inc/main.h"

#ifdef __PERF__
void performBaseMeasurements();
#endif // __PERF__

/** @brief The main function!
 *
 * The centre of the application is here. From here all non-ISR code is called
 * directly or indirectly. The two coarse blocks are init and the main loop.
 * Init is called first to set everything up and then the main loop is entered
 * where the flow of control continues until the device is switched off or
 * reset (excluding asynchronous ISR code). Currently the main loop only runs
 * the fuel, ignition and scheduling calculation code, and only when actually
 * required. The intention is to maintain a very low latency for calculations
 * such that the behaviour of the device more closely reflects the attached
 * engines rapidly changing requirements. When accessory code is added a new
 * scheduling algorithm will be required to keep the latency low without
 * starving any particular blocks of CPU time.
 *
 * @author Fred Cooke
 */
int main_freeems() { // TODO maybe move this to paged flash ?
  debug_printf("freeems_main() started\r\n");
  // Set everything up.
  init();
  coreStatusA |= PRIMARY_SYNC;

#ifdef __PERF__
  performBaseMeasurements();
  unsigned int duration;// = 200000;
#endif

  // Run forever repeating.
  while (TRUE) {
    /* If ADCs require forced sampling, sample now */
    if (coreStatusA & FORCE_READING) {
      ATOMIC_START()
      ; /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
      /* Atomic block to ensure a full set of readings are taken together */
#ifdef __PERF__
      hal_performance_startCounter();
#endif
      /* Check to ensure that a reading wasn't take before we entered a non
       * interruptable state */
      if (coreStatusA & FORCE_READING) {
	// do we still need to do this TODO ?

	// TODO still need to do a pair of loops and clock these two functions
	//      for performance.
        sampleEachADC(ADCArraysRecord);
        Counters.timeoutADCreadings++;

        /* Set flag to say calc required */
        coreStatusA |= CALC_FUEL_IGN;

        /* Clear force reading flag */
        coreStatusA &= CLEAR_FORCE_READING;
      }
#ifdef __PERF__
      duration = hal_performance_stopCounter();
      perf_printf("*r%u\r\n", duration);
#endif
      ATOMIC_END(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
    }

    /* If required, do main fuel and ignition calcs first */
    if (coreStatusA & CALC_FUEL_IGN) {
      ATOMIC_START()
      ; /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
      /* Atomic block to ensure that we don't clear the flag for the next data
       * set when things are tight */
#ifdef __PERF__
      hal_performance_startCounter();
#endif

      /* Switch input bank so that we have a stable set of the latest data */
      if (ADCArrays == &ADCArrays1) {
        RPM = &RPM0; // TODO temp, remove
        RPMRecord = &RPM1; // TODO temp, remove
        ADCArrays = &ADCArrays0;
        ADCArraysRecord = &ADCArrays1;
        // TODO temp, remove
        mathSampleTimeStamp = &ISRLatencyVars.mathSampleTimeStamp0;
        // TODO temp, remove
        mathSampleTimeStampRecord =
          &ISRLatencyVars.mathSampleTimeStamp1;
      }
      else {
        RPM = &RPM1; // TODO temp, remove
        RPMRecord = &RPM0; // TODO temp, remove
        ADCArrays = &ADCArrays1;
        ADCArraysRecord = &ADCArrays0;
        // TODO temp, remove
        mathSampleTimeStamp = &ISRLatencyVars.mathSampleTimeStamp1;
        // TODO temp, remove
        mathSampleTimeStampRecord =
          &ISRLatencyVars.mathSampleTimeStamp0;
      }

      /* Clear the calc required flag */
      coreStatusA &= CLEAR_CALC_FUEL_IGN;
#ifdef __PERF__
      duration = hal_performance_stopCounter();
      perf_printf("*sr%u\r\n", duration);
#endif

      ATOMIC_END(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/

      /* Store the latency from sample time to runtime */
      ISRLatencyVars.mathLatency = hal_timer_time_get()
                                   - *mathSampleTimeStamp;
      /* Keep track of how many calcs we are managing per second... */
      Counters.calculationsPerformed++;
      /* ...and how long they take each */
      unsigned short mathStartTime = hal_timer_time_get();

      /* Generate the core variables from sensor input and recorded tooth
       * timings */
      generateCoreVars();

      RuntimeVars.genCoreVarsRuntime = hal_timer_time_get()
                                       - mathStartTime;
      unsigned short derivedStartTime = hal_timer_time_get();

      /* Generate the derived variables from the core variables based on
       * settings */
      generateDerivedVars();

      RuntimeVars.genDerivedVarsRuntime = hal_timer_time_get()
                                          - derivedStartTime;
      unsigned short calcsStartTime = hal_timer_time_get();
      /* Perform the calculations TODO possibly move this to the software
       * interrupt if it makes sense to do so */
      calculateFuelAndIgnition();

      RuntimeVars.calcsRuntime = hal_timer_time_get() - calcsStartTime;
      /* Record the runtime of all the math total */
      RuntimeVars.mathTotalRuntime = hal_timer_time_get() - mathStartTime;

      RuntimeVars.mathSumRuntime = RuntimeVars.calcsRuntime
                                   + RuntimeVars.genCoreVarsRuntime
                                   + RuntimeVars.genDerivedVarsRuntime;

      ATOMIC_START()
      ; /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
      /* Atomic block to ensure that outputBank and outputBank Offsets match */
#ifdef __PERF__
      hal_performance_startCounter();
#endif
      /* Switch banks to the latest data */
      if (injectorMainPulseWidthsMath == injectorMainPulseWidths1) {
        currentDwellMath = &currentDwell0;
        currentDwellRealtime = &currentDwell1;
        injectorMainPulseWidthsMath = injectorMainPulseWidths0;
        injectorMainPulseWidthsRealtime = injectorMainPulseWidths1;
        injectorStagedPulseWidthsMath = injectorStagedPulseWidths0;
        injectorStagedPulseWidthsRealtime = injectorStagedPulseWidths1;
      }
      else {
        currentDwellMath = &currentDwell1;
        currentDwellRealtime = &currentDwell0;
        injectorMainPulseWidthsMath = injectorMainPulseWidths1;
        injectorMainPulseWidthsRealtime = injectorMainPulseWidths0;
        injectorStagedPulseWidthsMath = injectorStagedPulseWidths1;
        injectorStagedPulseWidthsRealtime = injectorStagedPulseWidths0;
      }
#ifdef __PERF__
      duration = hal_performance_stopCounter();
      perf_printf("*sii%u\r\n", duration);
#endif

      ATOMIC_END(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
    }
    else {
      /* In the event that no calcs are required, sleep a little before
       * returning to retry. */
      // not doing this will cause the ISR lockouts to run for too high a
      // proportion of the time
      sleepMicro(RuntimeVars.mathTotalRuntime);
      /* Using 0.8 ticks as micros so it will run for a little longer than the
       * math did */
    }

    if (!(TXBufferInUseFlags)) {
      //	unsigned short logTimeBuffer = Clocks.realTimeClockTenths;
      /* If the flag for com packet processing is set and the TX buffer is
       * available process the data! */
      if (RXStateFlags & RX_READY_TO_PROCESS) {
        /* Clear the flag */
        RXStateFlags &= RX_CLEAR_READY_TO_PROCESS;

        /* Handle the incoming packet */
        decodePacketAndRespond();
      }
      else
        if (ShouldSendLog) {
          /* send asynchronous data log if required */
          if (asyncDatalogType != asyncDatalogOff) {
            switch (asyncDatalogType) {
            case asyncDatalogBasic: {
              /* Flag that we are transmitting! */
              TXBufferInUseFlags |= COM_SET_SCI0_INTERFACE_ID;
              // SCI0 only for now...

              // headers including length...
              // *length = configuredBasicDatalogLength;
              TXBufferCurrentPositionHandler =
                (unsigned char*) &TXBuffer;

              /* Initialised here such that override is possible */
              TXBufferCurrentPositionSCI0 =
                (unsigned char*) &TXBuffer;
              TXBufferCurrentPositionCAN0 =
                (unsigned char*) &TXBuffer;

              /* Set the flags : firmware, no ack, no addrs, has length */
              *TXBufferCurrentPositionHandler = HEADER_HAS_LENGTH;
              TXBufferCurrentPositionHandler++;

              /* Set the payload ID */
              *((unsigned short*) TXBufferCurrentPositionHandler) =
                responseBasicDatalog;
              TXBufferCurrentPositionHandler += 2;

              /* Set the length */
              *((unsigned short*) TXBufferCurrentPositionHandler) =
                configuredBasicDatalogLength;
              TXBufferCurrentPositionHandler += 2;
              /* populate data log */
              populateBasicDatalog();
              checksumAndSend();
              break;
            }
            case asyncDatalogConfig: {
              // TODO
              break;
            }
            case asyncDatalogTrigger: {
              // TODO
              break;
            }
            case asyncDatalogADC: {
              // TODO
              break;
            }
            case asyncDatalogCircBuf: {
              // TODO
              break;
            }
            case asyncDatalogCircCAS: {
              // TODO
              break;
            }
            case asyncDatalogLogic: {
              // TODO
              break;
            }
            }
          }
        }
    }
    // on once per cycle for main loop heart beat (J0)
    PORTJ ^= 0x01;

    // debug...
    if (SCI0CR2 & SCICR2_RX_ENABLE) {
      PORTK |= BIT2;
    }
    else {
      PORTK &= NBIT2;
    }

    if (SCI0CR2 & SCICR2_RX_ISR_ENABLE) {
      PORTK |= BIT3;
    }
    else {
      PORTK &= NBIT3;
    }
    // PWM experimentation
    adjustPWM();

    output_performance_log();
  }
}


#ifdef __PERF__

void performBaseMeasurements() {
  ATOMIC_START();
  debug_printf("debug performBaseMeasurements\n");
  perf_printf("perf performBaseMeasurements\n");
  unsigned int executionDuration;
  // Each measurement is performed twice to eliminat cache effects
  // 1) Performanc counting
  hal_performance_startCounter();
  executionDuration = hal_performance_stopCounter();
  perf_printf("**MeasB 1: %u\r\n", executionDuration);
  // performe twice do get difference
  hal_performance_startCounter();
  executionDuration = hal_performance_stopCounter();
  perf_printf("**MeasB 2: %u\r\n", executionDuration);
  ATOMIC_END();
}

#endif // __PERF__
