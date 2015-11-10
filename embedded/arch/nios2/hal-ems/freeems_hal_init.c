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
 * $Id: freeems_hal_init.c 512 2015-11-10 15:29:05Z meixnean $
 * @brief Implementation of initialization functions.
 * @file freeems_hal_init.c
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#include <hal/ems/freeems_hal.h>
#include "freeems_hal_globals.h"
/**** Setup functions */

/*
 * Setup timers
 */
static void hal_priv_timer_setup() {
  // init the two timers for dwell and fire
  // enable interrupt for three timers
  // timer 0 will be the rtc, timer 1 will be for ignition dwell and timer 2
  // will be ignition fire
  uint32_t ienable_register = __rdctl_ienable();
  ienable_register |= A_TIMER_0 | A_TIMER_1 | A_TIMER_2;
  __wrctl_ienable(ienable_register);
  // set interval of TIMER_0 so the interrupt will be called every 125µs (RTC)
  IOWR16(A_TIMER_0, NIOS2_TIMER_PERIODL, RTC_PRESCALER_LOW);
  IOWR16(A_TIMER_0, NIOS2_TIMER_PERIODH, RTC_PRESCALER_HIGH);

  IOWR16(A_TIMER_1, NIOS2_TIMER_PERIODL, 0x0);
  IOWR16(A_TIMER_1, NIOS2_TIMER_PERIODH, 0x0);

  IOWR16(A_TIMER_2, NIOS2_TIMER_PERIODL, 0x0);
  IOWR16(A_TIMER_2, NIOS2_TIMER_PERIODH, 0x0);

  IOWR16(A_TIMER_0, NIOS2_TIMER_CONTROL, NIOS2_TIMER_CONTROL_START | NIOS2_TIMER_CONTROL_CONT | NIOS2_TIMER_CONTROL_ITO);
  IOWR16(A_TIMER_1, NIOS2_TIMER_CONTROL, NIOS2_TIMER_CONTROL_ITO);
  IOWR16(A_TIMER_2, NIOS2_TIMER_CONTROL, NIOS2_TIMER_CONTROL_ITO);

  // init the SCCT timer
  // This timer is used to read the input signal of the RPM meter, and controll
  // the output for injection
  ienable_register = __rdctl_ienable();
  ienable_register |= IRQ_SCCT_BIT;
  __wrctl_ienable(ienable_register);

  // set frequency to the same as TIMER_0
  // the prescaler will allways be the value in the SCCT_PSC + 1, so we have to
  // subtract one from TIMER_0_PERIOD
  IOWR32(A_SCCT, SCCT_PSC, TIMER_0_PERIOD -1);
  // enable interrupt of the SCCT
  IOWR32(A_SCCT, SCCT_CTR_IE, 0x1);
  // set mode of the first two channels to IC (RPM) and set the mode of the next
  // six channels to OC (injection)
  int32_t channelModeFlagMask = SCCT_CH_MS_IC | (SCCT_CH_MS_IC<<1) | (SCCT_CH_MS_OC<<2) | (SCCT_CH_MS_OC<<3) | (SCCT_CH_MS_OC<<4) | (SCCT_CH_MS_OC<<5) | (SCCT_CH_MS_OC<<6) | (SCCT_CH_MS_OC<<7);
  IOWR32(A_SCCT, SCCT_CH_MS, channelModeFlagMask);
  // set channels to generate interrupt on rising edge
  IOWR32(A_SCCT, SCCT_CH_AS, SCCT_IC_POSEDGE | (SCCT_IC_POSEDGE<<2));
  // enable interrupt for IC event on both channels
  IOWR32(A_SCCT, SCCT_CH_IE, 0x3);
  // interrupt and period of the OC channels will be set during runtime, so
  // nothing has to be done here.
}

static void hal_priv_gpio_setup() {
}

static void hal_priv_isr_setup() {

}

void hal_system_clock(void) {

}

void hal_system_init(void) {
  hal_priv_timer_setup();
  hal_priv_gpio_setup();
  hal_priv_isr_setup();
}

void hal_system_start(void) {
  // start the interrupt system of nios2
  uint32_t sr = __rdctl_status();
  sr |= SPR_SR_PIE;
  __wrctl_status(sr);
}
