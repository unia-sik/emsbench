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
#include <hal/log.h>
#include <hal/ems/freeems_hal.h>
#include <driver/pcc.h>
#include <arch/nios2/io.h>
#include "freeems_hal_globals.h"

/**
 * This array is used to store the current interval times of the ignition timers.
 * The original FreeEMS wrote theses times directly into registers and if needed
 * read them directly from those registers.
 *
 * This does not work any more, because the nios is set up to use the TIMER_1
 * and TIMER_2 for the ignition timers. These timers change the value written to
 *  the period register, so it will be lost unless it is saved elsewhere.
 **/
// TODO AM: find a better solution for this problem
// possible solutions are
// - alter FreeEMS so it no longer needs to get the interval time from the
//   hardware/hal
uint16_t ignitionIntervalls[2] = { 0, 0 };
#define DWELL_INTERVALL 0
#define FIRE_INTERVALL 1

uint16_t hal_timer_time_get(void) {
  // read the lower two bytes of the timer value
  return IORD16(A_SCCT, SCCT_CTR);
  return 0;
}

bool hal_timer_overflow_get(void) {
  // see freeems_hal_globals.h for documentation of lastTickHighWord
  return (lastTickHighWord != IORD16(A_TIMER, NIOS2_TIMER_SNAPH));
}

void hal_timer_overflow_clear(void) {
  //nothing has to be done here, because the overflow interrupt is generated by
  //software
  // see freeems_hal_interrupts.c and freeems_hal_globals.h for more information.
}

uint16_t hal_timer_ic_capture_get(channelid_t channel_id) {
  switch (channel_id) {
  case PRIMARY_RPM_INPUT:
    // return the cc-value of channel 0
    return IORD16(A_SCCT, SCCT_CH_CCR0);
  case SECONDARY_RPM_INPUT:
    // return the cc-value of channel 1
    return IORD16(A_SCCT, SCCT_CH_CCR1);
  default:
    log_printf(
      "ERROR: invalid channel ID (%d) for hal_timer_ic_capture_get\r\n",
      channel_id);
    break;
  }
  return 0;
}

pinstate_t hal_timer_ic_pin_get(channelid_t channel_id) {
  switch (channel_id) {
  case PRIMARY_RPM_INPUT:
    // check if the pin state of SCCT channel 0 is high (1) or low (0) and
    // return the state
    if (IORD16(A_SCCT, SCCT_CH_INP) & SCCT_CH_BITS_1(0, 1)) {
      return HIGH;
    }
    else {
      return LOW;
    }
  case SECONDARY_RPM_INPUT:
    // check if the pin state of SCCT channel 1 is high (1) or low (0) and
    // return the state
    if (IORD16(A_SCCT, SCCT_CH_INP) & SCCT_CH_BITS_1(1, 1)) {
      return HIGH;
    }
    else {
      return LOW;
    }
  default:
    log_printf(
      "ERROR: invalid channel ID (%d) for hal_timer_ic_pin_get\r\n",
      channel_id);
    break;
  }
  return LOW;
}

pinstate_t hal_timer_oc_pin_get(channelid_t channel_id) {
  switch (channel_id) {
  case INJECTION1_OUTPUT:
    if (IORD32(A_SCCT, SCCT_CH_OUT) & SCCT_CH_BITS_1(2, 1)) {
      return HIGH;
    }
    else {
      return LOW;
    }
  case INJECTION2_OUTPUT:
    if (IORD32(A_SCCT, SCCT_CH_OUT) & SCCT_CH_BITS_1(3, 1)) {
      return HIGH;
    }
    else {
      return LOW;
    }
  case INJECTION3_OUTPUT:
    if (IORD32(A_SCCT, SCCT_CH_OUT) & SCCT_CH_BITS_1(4, 1)) {
      return HIGH;
    }
    else {
      return LOW;
    }
  case INJECTION4_OUTPUT:
    if (IORD32(A_SCCT, SCCT_CH_OUT) & SCCT_CH_BITS_1(5, 1)) {
      return HIGH;
    }
    else {
      return LOW;
    }
  case INJECTION5_OUTPUT:
    if (IORD32(A_SCCT, SCCT_CH_OUT) & SCCT_CH_BITS_1(6, 1)) {
      return HIGH;
    }
    else {
      return LOW;
    }
  case INJECTION6_OUTPUT:
    if (IORD32(A_SCCT, SCCT_CH_OUT) & SCCT_CH_BITS_1(7, 1)) {
      return HIGH;
    }
    else {
      return LOW;
    }
  default:
    log_printf(
      "ERROR: invalid channel ID (%d) for hal_timer_oc_pin_get\r\n",
      channel_id);
    break;
  }
  return LOW;
}

bool hal_timer_oc_active_get(channelid_t channel_id) {
  switch (channel_id) {
  case INJECTION1_OUTPUT:
    return IORD32(A_SCCT, SCCT_CH_IE) & SCCT_CH_BITS_1(2, 1);
    break;
  case INJECTION2_OUTPUT:
    return IORD32(A_SCCT, SCCT_CH_IE) & SCCT_CH_BITS_1(3, 1);
    break;
  case INJECTION3_OUTPUT:
    return IORD32(A_SCCT, SCCT_CH_IE) & SCCT_CH_BITS_1(4, 1);
    break;
  case INJECTION4_OUTPUT:
    return IORD32(A_SCCT, SCCT_CH_IE) & SCCT_CH_BITS_1(5, 1);
    break;
  case INJECTION5_OUTPUT:
    return IORD32(A_SCCT, SCCT_CH_IE) & SCCT_CH_BITS_1(6, 1);
    break;
  case INJECTION6_OUTPUT:
    return IORD32(A_SCCT, SCCT_CH_IE) & SCCT_CH_BITS_1(7, 1);
    break;
  default:
    log_printf(
      "ERROR: invalid channel ID (%d) for hal_timer_oc_active_get\r\n",
      channel_id);
    break;
  }
  return false;
}

void hal_timer_oc_active_set(channelid_t channel_id, bool active) {
  int32_t interruptEnableFlags = IORD32(A_SCCT, SCCT_CH_IE);
  int32_t newFlags = 0;
  switch (channel_id) {
  case INJECTION1_OUTPUT:
    newFlags =
      active ?
      interruptEnableFlags | SCCT_CH_BITS_1(2, 1) :
      interruptEnableFlags & ~SCCT_CH_BITS_1(2, 1);
    break;
  case INJECTION2_OUTPUT:
    newFlags =
      active ?
      interruptEnableFlags | SCCT_CH_BITS_1(3, 1) :
      interruptEnableFlags & ~SCCT_CH_BITS_1(3, 1);
    break;
  case INJECTION3_OUTPUT:
    newFlags =
      active ?
      interruptEnableFlags | SCCT_CH_BITS_1(4, 1) :
      interruptEnableFlags & ~SCCT_CH_BITS_1(4, 1);
    break;
  case INJECTION4_OUTPUT:
    newFlags =
      active ?
      interruptEnableFlags | SCCT_CH_BITS_1(5, 1) :
      interruptEnableFlags & ~SCCT_CH_BITS_1(5, 1);
    break;
  case INJECTION5_OUTPUT:
    newFlags =
      active ?
      interruptEnableFlags | SCCT_CH_BITS_1(6, 1) :
      interruptEnableFlags & ~SCCT_CH_BITS_1(6, 1);
    break;
  case INJECTION6_OUTPUT:
    newFlags =
      active ?
      interruptEnableFlags | SCCT_CH_BITS_1(7, 1) :
      interruptEnableFlags & ~SCCT_CH_BITS_1(7, 1);
    break;
  default:
    log_printf(
      "ERROR: invalid channel ID (%d) for hal_timer_oc_active_set\r\n",
      channel_id);
    break;
  }
  IOWR32(A_SCCT, SCCT_CH_IE, newFlags);
}

#define hal_internal_set_oc_compare(adressOffset, newCompareValue){\
  /* set time as new OC time\
  * the new time is given as 16 bit value, so to set the time correctly the \
  * following calculation has to be done\
  * case 1: if the new time (16 bit value) is bigger than the two low bytes of\
  *         the current counter value\
  *         the new 32 bit timer value has to be calculated\
  * case 2: if the new time is smaller than the two low bytes of the current\
  *         counter value then the new time must be\
  *         the two high bytes of the current counter value plus one, followed\
  *         by the new time\
  *NOTE: THE NEW TIME IS AN ABSOLUTE VALUE, NOT AN INCREMENT TO CURRENT TIME. */\
  uint32_t counterValue = IORD32(A_SCCT, SCCT_CTR);\
  /* new time is upper two bytes of current time followed by the two bytes \
   * representing the new time*/\
  uint32_t newTimeValue = (counterValue & 0xFFFF0000) | newCompareValue;\
  /* in case the new time is smaller than the lower two bytes of our 32 bit \
   * counter value we have to add 1 to the upper two bytes of the new 32 bit\
   * OC time. this can be seen as simulating the timer overflow of a 16 bit\
   * timer.*/\
  if((counterValue & 0x0000FFFF) > newCompareValue)\
  {\
    newTimeValue += 0x00010000;\
  }\
  IOWR32(A_SCCT, adressOffset, newTimeValue);\
  /*debug_printf("occs %X %X\r\n", IORD32(A_SCCT, adressOffset), \
   * IORD32(A_SCCT, SCCT_CTR));*/\
}

void hal_timer_oc_compare_set(channelid_t channel_id, uint16_t value) {
  switch (channel_id) {
  case INJECTION1_OUTPUT:
    hal_internal_set_oc_compare(SCCT_CH_CCR2, value)
    ;
    break;
  case INJECTION2_OUTPUT:
    hal_internal_set_oc_compare(SCCT_CH_CCR3, value)
    ;
    break;
  case INJECTION3_OUTPUT:
    hal_internal_set_oc_compare(SCCT_CH_CCR4, value)
    ;
    break;
  case INJECTION4_OUTPUT:
    hal_internal_set_oc_compare(SCCT_CH_CCR5, value)
    ;
    break;
  case INJECTION5_OUTPUT:
    hal_internal_set_oc_compare(SCCT_CH_CCR6, value)
    ;
    break;
  case INJECTION6_OUTPUT:
    hal_internal_set_oc_compare(SCCT_CH_CCR7, value)
    ;
    break;
  default:
    log_printf(
      "ERROR: invalid channel ID (%d) for hal_timer_oc_compare_set\r\n",
      channel_id);
    break;
  }
}

uint16_t hal_timer_oc_compare_get(channelid_t channel_id) {
  switch (channel_id) {
  case INJECTION1_OUTPUT:
    return IORD16(A_SCCT, SCCT_CH_CCR2);
  case INJECTION2_OUTPUT:
    return IORD16(A_SCCT, SCCT_CH_CCR3);
  case INJECTION3_OUTPUT:
    return IORD16(A_SCCT, SCCT_CH_CCR4);
  case INJECTION4_OUTPUT:
    return IORD16(A_SCCT, SCCT_CH_CCR5);
  case INJECTION5_OUTPUT:
    return IORD16(A_SCCT, SCCT_CH_CCR6);
  case INJECTION6_OUTPUT:
    return IORD16(A_SCCT, SCCT_CH_CCR7);
  default:
    log_printf(
      "ERROR: invalid channel ID (%d) for hal_timer_oc_compare_get\r\n",
      channel_id);
    return 0;
  }
}

/**
 * @author Andreas Meixner
 * @brief Set the mode flags for the given channel according to the value of
 *        mode.
 * First set the two bits where the mode ist selected to 00, then set them
 * according to the value of mode.
 **/
#define hal_internal_calculate_mode_flags(channelNumber, mode, modeFlags)\
	          {modeFlags = (modeFlags & ~SCCT_CH_BITS_2(channelNumber, 3));\
               if(mode == OC_MODE_DISABLE){ modeFlags |= SCCT_CH_BITS_2(channelNumber, SCCT_OC_NONE); }\
               else if (mode == OC_MODE_TO_HIGH){ modeFlags |= SCCT_CH_BITS_2(channelNumber, SCCT_OC_HIGH); }\
               else if (mode == OC_MODE_TO_LOW){ modeFlags |= SCCT_CH_BITS_2(channelNumber, SCCT_OC_LOW); }\
               else if (mode == OC_MODE_TOGGLE){ modeFlags |= SCCT_CH_BITS_2(channelNumber, SCCT_OC_TOGGLE); }\
               else {log_printf("ERROR: invalid mode ID (%d) for hal_timer_oc_output_set\r\n", mode);}}

void hal_timer_oc_output_set(channelid_t channel_id, ocmode_t mode) {
  uint32_t modeFlags = IORD32(A_SCCT, SCCT_CH_AS);
  switch (channel_id) {
  case INJECTION1_OUTPUT:
    hal_internal_calculate_mode_flags(2, mode, modeFlags)
    ;
    break;
  case INJECTION2_OUTPUT:
    hal_internal_calculate_mode_flags(3, mode, modeFlags)
    ;
    break;
  case INJECTION3_OUTPUT:
    hal_internal_calculate_mode_flags(4, mode, modeFlags)
    ;
    break;
  case INJECTION4_OUTPUT:
    hal_internal_calculate_mode_flags(5, mode, modeFlags)
    ;
    break;
  case INJECTION5_OUTPUT:
    hal_internal_calculate_mode_flags(6, mode, modeFlags)
    ;
    break;
  case INJECTION6_OUTPUT:
    hal_internal_calculate_mode_flags(7, mode, modeFlags)
    ;
    break;
  default:
    log_printf(
      "ERROR: invalid channel ID (%d) for hal_timer_oc_active_set\r\n",
      channel_id);
    break;
  }
  IOWR32(A_SCCT, SCCT_CH_AS, modeFlags);
}

#define hal_internal_set_pit_interval(timer, newCompareValue){\
  uint32_t newInterval = newCompareValue * TIMER_0_PERIOD;\
  uint16_t high = (newInterval >> 16);\
  uint16_t low = newInterval & 0xFFFF;\
  IOWR16(timer, NIOS2_TIMER_PERIODL, low);\
  IOWR16(timer, NIOS2_TIMER_PERIODH, high);\
}

void hal_timer_pit_interval_set(pitid_t pit_id, uint16_t value) {
  /**
   * The NIOS2 PITs do not have a prescaler. The EMS code assumes all timers to
   * run at 1.25MHz, so
   * all scaling has to be done in software.
   */

  // remember the last interval, because the value that gets written in the
  // register will be altered while the timer runns.
  switch (pit_id) {
  case IGNITION_DWELL_PIT:
    hal_internal_set_pit_interval(A_TIMER_1, value)
    ;
    ignitionIntervalls[DWELL_INTERVALL] = value;
    break;
  case IGNITION_FIRE_PIT:
    hal_internal_set_pit_interval(A_TIMER_2, value)
    ;
    ignitionIntervalls[FIRE_INTERVALL] = value;
    break;
  default:
    log_printf(
      "ERROR: invalid pit ID (%d) for hal_timer_pit_interval_set\r\n",
      pit_id);
    break;
  }
}

uint16_t hal_timer_pit_interval_get(pitid_t pit_id) {
  switch (pit_id) {
  case IGNITION_DWELL_PIT:
    return ignitionIntervalls[DWELL_INTERVALL];
    break;
  case IGNITION_FIRE_PIT:
    return ignitionIntervalls[FIRE_INTERVALL];
    break;
  default:
    log_printf(
      "ERROR: invalid pit ID (%d) for hal_timer_pit_interval_get\r\n",
      pit_id);
    break;
  }
  return -1;
}

bool hal_timer_pit_active_get(pitid_t pit_id) {
  // if bit two in the status register of the timer is 1, the timer is running
  switch (pit_id) {
  case IGNITION_DWELL_PIT:
    return (IORD32(A_TIMER_1, NIOS2_TIMER_STATUS) & 0x2) == 0x2;
  case IGNITION_FIRE_PIT:
    return (IORD32(A_TIMER_2, NIOS2_TIMER_STATUS) & 0x2) == 0x2;
  default:
    log_printf(
      "ERROR: invalid pit ID (%d) for hal_timer_pit_active_get\r\n",
      pit_id);
    break;
  }
  return false;
}

void hal_timer_pit_active_set(pitid_t pit_id, bool active) {
  // set bit two of the control register of the timer to start it, or
  // set bit three to stop it
  uint32_t bitToSet = active ? 0x4 : 0x8;
  switch (pit_id) {
  case IGNITION_DWELL_PIT:
    IOWR32(A_TIMER_1, NIOS2_TIMER_CONTROL,
           ((IORD32(A_TIMER_1, NIOS2_TIMER_CONTROL) & 0x3) | bitToSet));
    break;
  case IGNITION_FIRE_PIT:
    IOWR32(A_TIMER_2, NIOS2_TIMER_CONTROL,
           ((IORD32(A_TIMER_2, NIOS2_TIMER_CONTROL) & 0x3) | bitToSet));
    break;
  default:
    log_printf(
      "ERROR: invalid pit ID (%d) for hal_timer_pit_active_set\r\n",
      pit_id);
    break;
  }
}

uint16_t hal_timer_pit_current_get(pitid_t pit_id) {
  /**
   * The NIOS2 PITs do not have a prescaler. The EMS code assumes all timers to
   * runn at 1.25MHz, so all scaling has to be done in software.
   */
  switch (pit_id) {
  case IGNITION_DWELL_PIT:
    return (IORD32(A_TIMER_1, NIOS2_TIMER_SNAPL) / TIMER_0_PERIOD);
  case IGNITION_FIRE_PIT:
    return (IORD32(A_TIMER_2, NIOS2_TIMER_SNAPL) / TIMER_0_PERIOD);
  default:
    log_printf(
      "ERROR: invalid pit ID (%d) for hal_timer_pit_current_get\r\n",
      pit_id);
    break;
  }
  return -1;
}

pinstate_t hal_io_get(channelid_t channel_id) {
  pinstate_t retVal = LOW;
  switch (channel_id) {
  case IGNITION1_OUTPUT:
    retVal = (IORD32(A_PIO_IGN, 0) & 0x1) ? HIGH : LOW;
    break;
  case IGNITION2_OUTPUT:
    retVal = (IORD32(A_PIO_IGN, 0) & 0x2) ? HIGH : LOW;
    break;
  case IGNITION3_OUTPUT:
    retVal = (IORD32(A_PIO_IGN, 0) & 0x4) ? HIGH : LOW;
    break;
  case IGNITION4_OUTPUT:
    retVal = (IORD32(A_PIO_IGN, 0) & 0x8) ? HIGH : LOW;
    break;
  case IGNITION5_OUTPUT:
    retVal = (IORD32(A_PIO_IGN, 0) & 0x10) ? HIGH : LOW;
    break;
  case IGNITION6_OUTPUT:
    retVal = (IORD32(A_PIO_IGN, 0) & 0x20) ? HIGH : LOW;
    break;
  default:
    log_printf("ERROR: invalid channel ID (%d) for hal_io_get\r\n",
               channel_id);
    break;
  }
  return false;
}

void hal_io_set(channelid_t channel_id, pinstate_t value) {

  uint32_t registerValue = IORD32(A_PIO_IGN, 0);
  switch (channel_id) {
  case IGNITION1_OUTPUT:
    if (value == HIGH) {
      registerValue = registerValue | 0x1;
    }
    else {
      registerValue = registerValue & (~0x1);
    }
    break;
  case IGNITION2_OUTPUT:
    if (value == HIGH) {
      registerValue = registerValue | 0x2;
    }
    else {
      registerValue = registerValue & (~0x2);
    }
    break;
  case IGNITION3_OUTPUT:
    if (value == HIGH) {
      registerValue = registerValue | 0x4;
    }
    else {
      registerValue = registerValue & (~0x4);
    }
    break;
  case IGNITION4_OUTPUT:
    if (value == HIGH) {
      registerValue = registerValue | 0x8;
    }
    else {
      registerValue = registerValue & (~0x8);
    }
    break;
  case IGNITION5_OUTPUT:
    if (value == HIGH) {
      registerValue = registerValue | 0x10;
    }
    else {
      registerValue = registerValue & (~0x10);
    }
    break;
  case IGNITION6_OUTPUT:
    if (value == HIGH) {
      registerValue = registerValue | 0x20;
    }
    else {
      registerValue = registerValue & (~0x20);
    }
    break;
  default:
    log_printf("ERROR: invalid channel ID (%d) for hal_io_set\r\n",
               channel_id);
    break;
  }
}

void hal_irq_atomic_start() {
  // start the interrupt system of nios2
  uint32_t sr = __rdctl_status();
  sr &= ~SPR_SR_PIE;
  __wrctl_status(sr);
}

void hal_irq_atomic_end() {
  // stop the interrupt system of nios2
  uint32_t sr = __rdctl_status();
  sr |= SPR_SR_PIE;
  __wrctl_status(sr);
}

void hal_performance_startCounter() {
  PCC_RESET();
  PCC_START(PCC_GLOBAL);
}

unsigned int hal_performance_stopCounter() {
  PCC_STOP(PCC_GLOBAL);
  unsigned int retVal = PCC_GET_LOW(PCC_GLOBAL);
  return retVal;
}