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

/**
 * The hal has to generate the following interrupt calls to the FreeEMS code.
 *
 * 1. Every 125us call RTIISR() to update the internal clock
 * 2. Whenever the real time clock counter reaches a multiple of 2¹⁶ = 65536
 *    call TimerOverflow()
 * 3. When the pin state of the RPM meter changes call PrimaryRPMISR() or
 *    SecondaryRPMISR()
 * 4. When the ignition dwell timer elapses call IgnitionDwellISR()
 * 5. When the ignition fire timer elapses call IgnitionFireISR()
 * 6. When one of the injection timers elapses call the respective
 *    Injector1ISR(), Injector2ISR(), Injector3ISR(), ...
 *
 */

/**
 * @author Andreas Meixner
 * @brief The one ISR NIOS calls
 * Whenever an interrupt is pending, NIOS2 will call this ISR.
 * This function will check which interrupts are pending and will call the
 * appropriate handler functions of FreeEMS.
 */
void do_irq() {

  uint32_t pending = __rdctl_ipending();

  // if the flag for a pending timer event ist set
  if(pending & 0x40) {
    // see if timer 0 (RTC) is the interrupt source
    uint32_t timerFlag = IORD16(A_TIMER_0, NIOS2_TIMER_STATUS);
    //log_printf("t0F: %X\r\n", timerFlag);
    if((timerFlag & NIOS2_TIMER_STATUS_TO)) {
      // FreeEMS internaly keeps track of time. For this purpose it assumes the
      // hardware has a 16bit clock running at 1.25MHz, which generates a tick
      // interrupt on every tick, and an overflow interrupt everytime the 16bit
      // counter overflows (every 65536 ticks) NIOS2 has a 32 bit counter, so
      // the overflow has to be simulated, by generating the interrupt in the
      // software. check if the high word of the counter value has changed since
      // the last tick, if so call TimerOverfolw()
      uint16_t currentTickHighWord = IORD16(A_TIMER_0, NIOS2_TIMER_SNAPH);
      if(currentTickHighWord != lastTickHighWord) {
        lastTickHighWord = currentTickHighWord;
        TimerOverflow();
      }
      // advance the internal RTC
      RTIISR();

      // clear the flag
      IOWR16(A_TIMER_0, NIOS2_TIMER_STATUS, timerFlag & ~NIOS2_TIMER_STATUS_TO);
    }

    // see if Timer_1 (ignition dwell) is the interrupt source
    timerFlag = IORD16(A_TIMER_1, NIOS2_TIMER_STATUS);
    if((timerFlag & NIOS2_TIMER_STATUS_TO)) {
      IgnitionDwellISR();
      // clear the flag
      IOWR16(A_TIMER_1, NIOS2_TIMER_STATUS, timerFlag & ~(NIOS2_TIMER_STATUS_TO));
    }

    // see if Timer_2 (ignition fire) is the interrupt source
    timerFlag = IORD16(A_TIMER_2, NIOS2_TIMER_STATUS);
    if((timerFlag & NIOS2_TIMER_STATUS_TO)) {
      IgnitionFireISR();
      IOWR16(A_TIMER_2, NIOS2_TIMER_STATUS, timerFlag & ~(NIOS2_TIMER_STATUS_TO));
    }
  }
  // if the flag for a pending SCCT timer event is set
  if(pending & 0x400) {
    // external interrupt (SCCT)
    // see if the oc channel 0 (scct) was the interrupt source
    uint32_t isFlags = IORD32(A_SCCT, SCCT_CH_IS);
    // if IC channel 0 has a pending interrupt, call PrimaryRPMISR
    if(isFlags & SCCT_CH_BITS_1(0,1)) {
      // clear interrupt flags
      IOWR32(A_SCCT, SCCT_CH_IS, SCCT_CH_BITS_1(0,1));
      PrimaryRPMISR();
    }
    // if IC channel 1 has a pending interrupt, call SecondaryRPMISR
    if(isFlags & SCCT_CH_BITS_1(1,1)) {
      // clear interrupt flags
      IOWR32(A_SCCT, SCCT_CH_IS, SCCT_CH_BITS_1(1,1));
      SecondaryRPMISR();
    }
    // if OC channel 2 has a pending interrupt, call Injector1ISR
    if(isFlags & SCCT_CH_BITS_1(2,1)) {
      // clear interrupt flags
      IOWR32(A_SCCT, SCCT_CH_IS, SCCT_CH_BITS_1(2,1));
      Injector1ISR();
    }
    // if OC channel 3 has a pending interrupt, call Injector2ISR
    if(isFlags & SCCT_CH_BITS_1(3,1)) {
      // clear interrupt flags
      IOWR32(A_SCCT, SCCT_CH_IS, SCCT_CH_BITS_1(3,1));
      Injector2ISR();
    }
    // if OC channel 4 has a pending interrupt, call Injector3ISR
    if(isFlags & SCCT_CH_BITS_1(4,1)) {
      // clear interrupt flags
      IOWR32(A_SCCT, SCCT_CH_IS, SCCT_CH_BITS_1(4,1));
      Injector3ISR();
    }
    // if OC channel 5 has a pending interrupt, call Injector4ISR
    if(isFlags & SCCT_CH_BITS_1(5,1)) {
      // clear interrupt flags
      IOWR32(A_SCCT, SCCT_CH_IS, SCCT_CH_BITS_1(5,1));
      Injector4ISR();
    }
    // if OC channel 6 has a pending interrupt, call Injector5ISR
    if(isFlags & SCCT_CH_BITS_1(6,1)) {
      // clear interrupt flags
      IOWR32(A_SCCT, SCCT_CH_IS, SCCT_CH_BITS_1(6,1));
      Injector5ISR();
    }
    // if OC channel 7 has a pending interrupt, call Injector6ISR
    if(isFlags & SCCT_CH_BITS_1(7,1)) {
      // clear interrupt flags
      IOWR32(A_SCCT, SCCT_CH_IS, SCCT_CH_BITS_1(7,1));
      Injector6ISR();
    }
  }
}

void exception_handle() {
}
