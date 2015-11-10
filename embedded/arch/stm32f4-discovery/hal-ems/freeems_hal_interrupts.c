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

#include "hal_freeems_interface.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencmsis/core_cm3.h>

#include <liboutput/output.h>

/*
 * This is the callback function for the interrupts of timer 2.
 */
void TIM2_IRQHandler(void) {
  /*
   * When the timer overflow interrupt occures, call the FreeEMS function to
   * handle it.
   */
  IRQ_HANDLE(TIM2, TIM_SR_UIF, TIM2_CNT, {
    TimerOverflow();
  });

  /*
   * When the primary RPM input channel changes state, call the FreeEMS function
   * PrimaryRPMISR() to handle it.
   */
  IRQ_HANDLE(TIM2, TIM_SR_CC2IF, TIM2_CCR2, {
    PrimaryRPMISR();
  });

  /*
  * When the timer that handles the ignition dwell events elapses, the function
  * IgnitionDwellISR() is called. This function generates the outputsignal and
  * sets the timer intervall for the next ignition dwell time.
  *
  * @see The already calculated times for ignition dwell are queued in the
  *      fields dwellQueueLength, nextDwellChannel, queuedDwellOffsets
  */
  IRQ_HANDLE(TIM2, TIM_SR_CC3IF, TIM2_CCR3, {
    PIT_IRQ_WRAPPER(TIM2, 3);
    IgnitionDwellISR();

  });

  /*
   * When the timer that handles the ignition fire events elapses, the function
   * IgnitionFireISR() is called. This function generates the outputsignal and
   * sets the timer intervall for the next ignition fire time.
   *
   * @see The already calculated times for ignition fire are queued in the
   *      fields ignitionQueueLength, nextIgnitionChannel, queuedIgnitionOffsets
   */
  IRQ_HANDLE(TIM2, TIM_SR_CC4IF, TIM2_CCR4, {
    PIT_IRQ_WRAPPER(TIM2, 4);
    IgnitionFireISR();
  });

  /*
   * The trigger interrupt is disabled for this timer. If the interrupt occures
   * anyways, the flag is cleared and a debug messages is logged.
   */
  IRQ_INVALID(TIM2, TIM_SR_TIF);
}

/*
 * This is the callback function for interrupts of timer 3. Timer 3 is connected
 * to the GPIO channels for the first four injectors.
 */
void TIM3_IRQHandler(void) {

  /*
   * If the scheduled time when the first injector is to be
   * activated/deactivated is reached, call the function Injector1ISR().
   *
   * @see The function Injector1ISR() then decides if it has to schedule the
   *      dactivation time (if injector was just activated), the next activation
   *      time (if the injector was just deactivated) or if there is nothing to
   *      do for a longer period just to disable this channel. The channels
   *      themselves are OC, so the corresponding pins are pulled high or low
   *      at the scheduled time.
   *      This channel can be only activated by PrimaryRPMISR(), which
   *      calculates ALL injection start times. Injector1ISR() can only
   *      reset the timer if a next injection time is in the queue, or
   *      deactivate the channel if not.
   */
  IRQ_HANDLE(TIM3, TIM_SR_CC1IF, TIM3_CCR1, {
    Injector1ISR();
  });

  /*
     * If the scheduled time when the second injector is to be
     * activated/deactivated is reached, call the function Injector2ISR().
     *
     * @see The function Injector2ISR() then decides if it has to schedule the
     *      dactivation time (if injector was just activated), the next
     *      activation time (if the injector was just deactivated) or if there
     *      is nothing to do for a longer period just to disable this channel.
     *      The channels themselves are OC, so the corresponding pins are pulled
     *      high or low at the scheduled time. This channel can be only
     *      activated by PrimaryRPMISR(), which calculates ALL injection start
     *      times. Injector2ISR() can only reset the timer if a next injection
     *      time is in the queue, or deactivate the channel if not.
     */
  IRQ_HANDLE(TIM3, TIM_SR_CC2IF, TIM3_CCR2, {
    Injector2ISR();
  });

  /*
     * If the scheduled time when the third injector is to be
     * activated/deactivated is reached, call the function Injector3ISR().
     *
     * @see The function Injector3ISR() then decides if it has to schedule the
     *      dactivation time (if injector was just activated), the next
     *      activation time (if the injector was just deactivated) or if there
     *      is nothing to do for a longer period just to disable this channel.
     *      The channels themselves are OC, so the corresponding pins are pulled
     *      high or low at the scheduled time. This channel can be only
     *      activated by PrimaryRPMISR(), which calculates ALL injection start
     *      times. Injector3ISR() can only reset the timer if a next injection
     *      time is in the queue, or deactivate the channel if not.
     */
  IRQ_HANDLE(TIM3, TIM_SR_CC3IF, TIM3_CCR3, {
    Injector3ISR();
  });

  /*
     * If the scheduled time when the fourth injector is to be
     * activated/deactivated is reached, call the function Injector4ISR().
     *
     * @see The function Injector4ISR() then decides if it has to schedule the
     *      dactivation time (if injector was just activated), the next
     *      activation time (if the injector was just deactivated) or if there
     *      is nothing to do for a longer period just to disable this channel.
     *      The channels themselves are OC, so the corresponding pins are pulled
     *      high or low at the scheduled time. This channel can be only
     *      activated by PrimaryRPMISR(), which calculates ALL injection start
     *      times. Injector4ISR() can only reset the timer if a next injection
     *      time is in the queue, or deactivate the channel if not.
     */
  IRQ_HANDLE(TIM3, TIM_SR_CC4IF, TIM3_CCR4, {
    Injector4ISR();
  });
}

/*
 * This is the callback function for interrupts of timer 4. Timer 4 is connected
 * to the GPIO channels for the fifth and sixth injector.
 * @remark FreeEMS can theoretically handle up to eight injectors. The channels
 *         for injector seven and eight would then also be handled by this
 *         timer.
 */
void TIM4_IRQHandler(void) {
  /*
   * If the scheduled time when the fifth injector is to be
   * activated/deactivated is reached, call the function Injector5ISR().
   *
   * @see The function Injector5ISR() then decides if it has to schedule the
   *      dactivation time (if injector was just activated), the next activation
   *      time (if the injector was just deactivated) or if there is nothing to
   *      do for a longer period just to disable this channel.The channels
   *      themselves are OC, so the corresponding pins are pulled high or low
   *      at the scheduled time. This channel can be only activated by
   *      PrimaryRPMISR(), which calculates ALL injection start times.
   *      Injector5ISR() can only reset the timer if a next injection time is in
   *       the queue, or deactivate the channel if not.
   */
  IRQ_HANDLE(TIM4, TIM_SR_CC1IF, TIM4_CCR1, {
    Injector5ISR();
  });

  /*
   * If the scheduled time when the sixth injector is to be
   * activated/deactivated is reached, call the function Injector6ISR().
   *
   * @see The function Injector6ISR() then decides if it has to schedule the
   *      dactivation time (if injector was just activated), the next activation
   *      time (if the injector was just deactivated) or if there is nothing to
   *      do for a longer period just to disable this channel.The channels
   *      themselves are OC, so the corresponding pins are pulled high or low
   *      at the scheduled time. This channel can be only activated by
   *      PrimaryRPMISR(), which calculates ALL injection start times.
   *      Injector6ISR() can only reset the timer if a next injection time is in
   *       the queue, or deactivate the channel if not.
   */
  IRQ_HANDLE(TIM4, TIM_SR_CC2IF, TIM4_CCR2, {
    Injector6ISR();
  });

  /*
   * When the secondyry RPM input channel changes state, call the FreeEMS
   * function SecondaryRPMISR() to handle it.
   */

  IRQ_HANDLE(TIM4, TIM_SR_CC3IF, TIM4_CCR3, {
    SecondaryRPMISR();
  });
}

/*
 * This is the callback for timer 5. Timer 5 should not trigger any interrupts.
 * Its only purpose is that its counter value is used to measure the runtime of
 * different code (e.g.  PrimaryRPMISR(), SecondaryRPMISR(), ...)
 */
void TIM5_IRQHandler(void) {
}

/*
 * This is the callback for timer 7. Timer 7 is the realtime clock.
 */
void TIM7_IRQHandler(void) {
  /*
   * The update event (= overflow) of timer 6 is used as the trigger for the
   * internal realtime clock. This interrupt has to occor exactly with the
   * desired frequency of the RTC. Usually this is 8 kHz.
   *
   * When the trigger occures, call the function RTIISR() to update the internal
   * RTC.
   */
  IRQ_HANDLE(TIM7, TIM_SR_UIF, TIM7_CNT, {
    RTIISR();
  });

  /*
   * All of the following interrups are deactivated, if any of those occures
   * anyways a debug message is pput in the log.
   * - trigger interrupt
   * - capture/compare interrupt for channels 1 -4
   */
  IRQ_INVALID(TIM7, TIM_SR_CC1IF | TIM_SR_CC2IF |
              TIM_SR_CC3IF | TIM_SR_CC4IF |
              TIM_SR_TIF);

}
