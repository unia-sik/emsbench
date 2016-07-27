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
 * $Id: freeems_hal_functions.c 561 2016-07-24 15:24:52Z meixnean $
 * @brief Implementation of nearly all HAL functions.
 * @file freeems_hal_functions.c
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#include <hal/ems/freeems_hal.h>

#include "freeems_hal_globals.h"
#include "freeems_hal_macros.h"

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

#include <liboutput/output.h>

/**
 * This array is used to store the current interval times of the ignition timers.
 * The original FreeEMS wrote theses times directly into registers and if needed
 * read them directly from those registers.
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

uint16_t hal_timer_time_get(void) {
  return TIM_CNT(TIM2);
}

bool hal_timer_overflow_get(void) {
  return (TIM_SR(TIM2) & TIM_SR_UIF) != 0;
}

void hal_timer_overflow_clear(void) {
  TIM_SR(TIM2) &= ~TIM_SR_UIF;
}

uint16_t hal_timer_ic_capture_get(channelid_t channel_id) {
  switch (channel_id) {
  case PRIMARY_RPM_INPUT:
    return TIM_CCR2(TIM2);
  case SECONDARY_RPM_INPUT:
    return TIM_CCR3(TIM4);
  default:
    return 0;
  }
}

pinstate_t hal_timer_ic_pin_get(channelid_t channel_id) {
  switch (channel_id) {
  case PRIMARY_RPM_INPUT:
    return (GPIO_IDR(GPIOA) & GPIO1) != 0;
  case SECONDARY_RPM_INPUT:
    return (GPIO_IDR(GPIOB) & GPIO8) != 0;
  default:
    return false;
  }
}

pinstate_t hal_timer_oc_pin_get(channelid_t channel_id) {
  pinstate_t retVal = LOW;
  switch (channel_id) {
  case INJECTION1_OUTPUT:
    retVal = gpio_get(GPIOB, GPIO4) & GPIO4 ? HIGH : LOW;
    break;
  case INJECTION2_OUTPUT:
    retVal = gpio_get(GPIOB, GPIO5) & GPIO5 ? HIGH : LOW;
    break;
  case INJECTION3_OUTPUT:
    retVal = gpio_get(GPIOB, GPIO0) & GPIO0 ? HIGH : LOW;
    break;
  case INJECTION4_OUTPUT:
    retVal = gpio_get(GPIOB, GPIO1) & GPIO1 ? HIGH : LOW;
    break;
  case INJECTION5_OUTPUT:
    retVal = gpio_get(GPIOB, GPIO6) & GPIO6 ? HIGH : LOW;
    break;
  case INJECTION6_OUTPUT:
    retVal = gpio_get(GPIOB, GPIO7) & GPIO7 ? HIGH : LOW;
    break;
  default:
    retVal = LOW;
    debug_printf("hal_timer_oc_pin_get unknown channel id %d\r\n",
                 channel_id);
    break;
  }
  return retVal;
}

bool hal_timer_oc_active_get(channelid_t channel_id) {
  switch (channel_id) {
  case INJECTION1_OUTPUT:
    return (TIM_DIER(TIM3) & TIM_DIER_CC1IE) != 0;
  case INJECTION2_OUTPUT:
    return (TIM_DIER(TIM3) & TIM_DIER_CC2IE) != 0;
  case INJECTION3_OUTPUT:
    return (TIM_DIER(TIM3) & TIM_DIER_CC3IE) != 0;
  case INJECTION4_OUTPUT:
    return (TIM_DIER(TIM3) & TIM_DIER_CC4IE) != 0;
  case INJECTION5_OUTPUT:
    return (TIM_DIER(TIM4) & TIM_DIER_CC1IE) != 0;
  case INJECTION6_OUTPUT:
    return (TIM_DIER(TIM4) & TIM_DIER_CC2IE) != 0;
  default:
    return false;
  }
}

void hal_timer_oc_active_set(channelid_t channel_id, bool active) {
  switch (channel_id) {
  case INJECTION1_OUTPUT:
    OC_ACTIVE_SET(TIM3, 1, active)
    ;
    break;
  case INJECTION2_OUTPUT:
    OC_ACTIVE_SET(TIM3, 2, active)
    ;
    break;
  case INJECTION3_OUTPUT:
    OC_ACTIVE_SET(TIM3, 3, active)
    ;
    break;
  case INJECTION4_OUTPUT:
    OC_ACTIVE_SET(TIM3, 4, active)
    ;
    break;
  case INJECTION5_OUTPUT:
    OC_ACTIVE_SET(TIM4, 1, active)
    ;
    break;
  case INJECTION6_OUTPUT:
    OC_ACTIVE_SET(TIM4, 2, active)
    ;
    break;
  default:
    debug_printf("hal_timer_oc_output_set: channel id '%d' unknown.",
                 channel_id);
  }
}

uint16_t hal_timer_oc_compare_get(channelid_t channel_id) {
  switch (channel_id) {
  case INJECTION1_OUTPUT:
    return TIM_CCR1(TIM3);
  case INJECTION2_OUTPUT:
    return TIM_CCR2(TIM3);
  case INJECTION3_OUTPUT:
    return TIM_CCR3(TIM3);
  case INJECTION4_OUTPUT:
    return TIM_CCR4(TIM3);
  case INJECTION5_OUTPUT:
    return TIM_CCR1(TIM4);
  case INJECTION6_OUTPUT:
    return TIM_CCR2(TIM4);
  default:
    debug_printf("hal_timer_oc_output_set: channel id '%d' unknown.",
                 channel_id);
  }
  return 0;
}

void hal_timer_oc_compare_set(channelid_t channel_id, uint16_t value) {
  switch (channel_id) {
  case INJECTION1_OUTPUT:
    TIM_CCR1 (TIM3) = value;
    break;
  case INJECTION2_OUTPUT:
    TIM_CCR2 (TIM3) = value;
    break;
  case INJECTION3_OUTPUT:
    TIM_CCR3 (TIM3) = value;
    break;
  case INJECTION4_OUTPUT:
    TIM_CCR4 (TIM3) = value;
    break;
  case INJECTION5_OUTPUT:
    TIM_CCR1 (TIM4) = value;
    break;
  case INJECTION6_OUTPUT:
    TIM_CCR2 (TIM4) = value;
    break;
  default:
    debug_printf("hal_timer_oc_output_set: channel id '%d' unknown.",
                 channel_id);
  }
}

void hal_timer_oc_output_set(channelid_t channel_id, ocmode_t mode) {
  switch (channel_id) {
  case INJECTION1_OUTPUT:
    OC_MODE_SET(TIM3, 1, 1, mode)
    ;
    break;
  case INJECTION2_OUTPUT:
    OC_MODE_SET(TIM3, 1, 2, mode)
    ;
    break;
  case INJECTION3_OUTPUT:
    OC_MODE_SET(TIM3, 2, 3, mode)
    ;
    break;
  case INJECTION4_OUTPUT:
    OC_MODE_SET(TIM3, 2, 4, mode)
    ;
    break;
  case INJECTION5_OUTPUT:
    OC_MODE_SET(TIM4, 1, 1, mode)
    ;
    break;
  case INJECTION6_OUTPUT:
    OC_MODE_SET(TIM4, 1, 2, mode)
    ;
    break;
  default:
    debug_printf("hal_timer_oc_output_set: channel id '%d' unknown.",
                 channel_id);
  }
}

void hal_timer_pit_interval_set(pitid_t pit_id, uint16_t value) {
  switch (pit_id) {
  case IGNITION_DWELL_PIT:
    ignitionIntervalls[DWELL_INTERVALL] = value;
    PIT_INTERVAL_SET(TIM2, 3, value)
    ;
    break;
  case IGNITION_FIRE_PIT:
    ignitionIntervalls[FIRE_INTERVALL] = value;
    PIT_INTERVAL_SET(TIM2, 4, value)
    ;
    break;
  }
}

uint16_t hal_timer_pit_interval_get(pitid_t pit_id) {
  switch (pit_id) {
  case IGNITION_FIRE_PIT:
    return ignitionIntervalls[FIRE_INTERVALL];
  case IGNITION_DWELL_PIT:
    return ignitionIntervalls[DWELL_INTERVALL];
  default:
    return 0;
  }
}

bool hal_timer_pit_active_get(pitid_t pit_id) {
  switch (pit_id) {
  case IGNITION_DWELL_PIT:
    return (TIM2_DIER & TIM_DIER_CC3IE) != 0;
  case IGNITION_FIRE_PIT:
    return (TIM2_DIER & TIM_DIER_CC4IE) != 0;
  default:
    return false;
  }
}

void hal_timer_pit_active_set(pitid_t pit_id, bool active) {
  switch (pit_id) {
  case IGNITION_DWELL_PIT:
    PIT_ACTIVE_SET(TIM2, 3, active)
    ;
    break;
  case IGNITION_FIRE_PIT:
    PIT_ACTIVE_SET(TIM2, 4, active)
    ;
    break;
  }
}

uint16_t hal_timer_pit_current_get(pitid_t pit_id) {
  switch (pit_id) {
  case IGNITION_FIRE_PIT:
    // get TIM2 channle 4
    return TIM2_CCR4 - TIM2_CNT;
  case IGNITION_DWELL_PIT:
    // get TIM2 channle 3
    return TIM2_CCR3 - TIM2_CNT;
  }
  return 0;
}

pinstate_t hal_io_get(channelid_t channel_id) {
  pinstate_t retVal = LOW;
  switch (channel_id) {
  case IGNITION1_OUTPUT:
    retVal = gpio_get(GPIOC, GPIO1) ? HIGH : LOW;
    break;
  case IGNITION2_OUTPUT:
    retVal = gpio_get(GPIOC, GPIO2) ? HIGH : LOW;
    break;
  case IGNITION3_OUTPUT:
    retVal = gpio_get(GPIOC, GPIO3) ? HIGH : LOW;
    break;
  case IGNITION4_OUTPUT:
    retVal = gpio_get(GPIOC, GPIO4) ? HIGH : LOW;
    break;
  case IGNITION5_OUTPUT:
    retVal = gpio_get(GPIOC, GPIO5) ? HIGH : LOW;
    break;
  case IGNITION6_OUTPUT:
    retVal = gpio_get(GPIOC, GPIO6) ? HIGH : LOW;
    break;
  case DEBUG_OUTPUT_1:
    retVal = gpio_get(GPIOC, GPIO9) ? HIGH : LOW;
    break;
  case DEBUG_OUTPUT_2:
    retVal = gpio_get(GPIOC, GPIO10) ? HIGH : LOW;
    break;
  case DEBUG_OUTPUT_3:
    retVal = gpio_get(GPIOC, GPIO11) ? HIGH : LOW;
    break;
  case DEBUG_OUTPUT_4:
    retVal = gpio_get(GPIOC, GPIO12) ? HIGH : LOW;
    break;
  case DEBUG_OUTPUT_5:
    retVal = gpio_get(GPIOC, GPIO13) ? HIGH : LOW;
    break;
  case DEBUG_OUTPUT_6:
    retVal = gpio_get(GPIOC, GPIO14) ? HIGH : LOW;
    break;
  case DEBUG_OUTPUT_7:
    retVal = gpio_get(GPIOC, GPIO15) ? HIGH : LOW;
    break;
  case DEBUG_OUTPUT_8:
    retVal = gpio_get(GPIOC, GPIO0) ? HIGH : LOW;
    break;
  default:
    log_printf("ERROR: invalid channel ID (%d) for hal_io_get\r\n",
               channel_id);
    break;
  }
  return retVal;
}

void hal_io_set(channelid_t channel_id, pinstate_t value) {
  switch (channel_id) {
  case IGNITION1_OUTPUT:
    if (value == HIGH) {
      gpio_set(GPIOC, GPIO1);
    }
    else {
      gpio_clear(GPIOC, GPIO1);
    }
    break;
  case IGNITION2_OUTPUT:
    if (value == HIGH) {
      gpio_set(GPIOC, GPIO2);
    }
    else {
      gpio_clear(GPIOC, GPIO2);
    }
    break;
  case IGNITION3_OUTPUT:
    if (value == HIGH) {
      gpio_set(GPIOC, GPIO3);
    }
    else {
      gpio_clear(GPIOC, GPIO3);
    }
    break;
  case IGNITION4_OUTPUT:
    if (value == HIGH) {
      gpio_set(GPIOC, GPIO4);
    }
    else {
      gpio_clear(GPIOC, GPIO4);
    }
    break;
  case IGNITION5_OUTPUT:
    if (value == HIGH) {
      gpio_set(GPIOC, GPIO5);
    }
    else {
      gpio_clear(GPIOC, GPIO5);
    }
    break;
  case IGNITION6_OUTPUT:
    if (value == HIGH) {
      gpio_set(GPIOC, GPIO6);
    }
    else {
      gpio_clear(GPIOC, GPIO6);
    }
    break;
  case DEBUG_OUTPUT_1:
    if (value == HIGH) {
      gpio_set(GPIOC, GPIO9);
    }
    else {
      gpio_clear(GPIOC, GPIO9);
    }
    break;
  case DEBUG_OUTPUT_2:
    if (value == HIGH) {
      gpio_set(GPIOC, GPIO10);
    }
    else {
      gpio_clear(GPIOC, GPIO10);
    }
    break;
  case DEBUG_OUTPUT_3:
    if (value == HIGH) {
      gpio_set(GPIOC, GPIO11);
    }
    else {
      gpio_clear(GPIOC, GPIO11);
    }
    break;
  case DEBUG_OUTPUT_4:
    if (value == HIGH) {
      gpio_set(GPIOC, GPIO12);
    }
    else {
      gpio_clear(GPIOC, GPIO12);
    }
    break;
  case DEBUG_OUTPUT_5:
    if (value == HIGH) {
      gpio_set(GPIOC, GPIO13);
    }
    else {
      gpio_clear(GPIOC, GPIO13);
    }
    break;
  case DEBUG_OUTPUT_6:
    if (value == HIGH) {
      gpio_set(GPIOC, GPIO14);
    }
    else {
      gpio_clear(GPIOC, GPIO14);
    }
    break;
  case DEBUG_OUTPUT_7:
    if (value == HIGH) {
      gpio_set(GPIOC, GPIO15);
    }
    else {
      gpio_clear(GPIOC, GPIO15);
    }
    break;
  case DEBUG_OUTPUT_8:
    if (value == HIGH) {
      gpio_set(GPIOC, GPIO0);
    }
    else {
      gpio_clear(GPIOC, GPIO0);
    }
    break;
  default:
    log_printf("ERROR: invalid channel ID (%d) for hal_io_set\r\n",
               channel_id);
    break;
  }
}

void hal_performance_startCounter() {
  timer_reset(TIM5);
  timer_enable_counter(TIM5);
}

unsigned int hal_performance_stopCounter() {
  unsigned int ret = TIM5_CNT;
  timer_disable_counter(TIM5);
  return ret;
}
