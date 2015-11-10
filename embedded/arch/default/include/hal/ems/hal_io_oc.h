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
 * $Id: hal_io_oc.h 502 2015-11-05 14:18:19Z klugeflo $
 * @ingroup halInterface
 * @brief Functions to use outpuc compare channels
 * @file hal_io_oc.h
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#ifndef HAL_IO_OC_H_
#define HAL_IO_OC_H_

/**
 * @author Andreas Meixner
 * @brief All possible modes for a OC channel.
 * The mode defines what state the OC channel will change to when the counter
 * value (see hal_timer_oc_compare_set(channelid_t, uint16_t))
 * matches the timer value.
 */
typedef enum oc_modes {
  /**
   * The channel will be disabled. This means the pin state will remain as it is
   * and nothing will happen to the pin state the next time the counter and
   * timer values match.
   */
  OC_MODE_DISABLE = 0,
  /**
   * The next time the counter matches the timer value the pin will be set to
   * high, or will remain high if it already is.
   */
  OC_MODE_TO_HIGH = 3,
  /**
   * The next time the counter matches the timer value the pin will be set to
   * low, or it will remain low if it already is.
   */
  OC_MODE_TO_LOW = 2,
  /**
   * The next time the counter matches the timer value the pin will toggle its
   * state. If the pin is low it will be set high, if it is high it will be set
   * low.
   */
  OC_MODE_TOGGLE = 1,
} ocmode_t;

/**
 * @author Andreas Meixner
 * Returns the pin state of the output compare channel.
 * @param channel_id The output compare channel id.
 * @return The pin state of the output compare channel.
 */
extern pinstate_t hal_timer_oc_pin_get(channelid_t channel_id);

/**
 * @author Andreas Meixner
 * Returns if the output compare channel is active.
 * @param channel_id The output compare channel id.
 * @return The channel active state
 */
extern bool hal_timer_oc_active_get(channelid_t channel_id);

/**
 * @author Andreas Meixner
 * Changes the state of the output compare channel.
 * @param channel_id The output compare channel id.
 * @param active The state of the output compare channel to change to.
 */
extern void hal_timer_oc_active_set(channelid_t channel_id, bool active);

/**
 * @author Andreas Meixner
 * Returns the output compare time value of a channel.
 * @param channel_id The output compare channel id.
 * @return The time value of the OC channel.
 */
extern uint16_t hal_timer_oc_compare_get(channelid_t channel_id);

/**
 * @author Andreas Meixner
 * Changes the output compare value of a channel.
 * @param channel_id The output compare channel id.
 * @param value The output compare value, time for next interrupt.
 */
extern void hal_timer_oc_compare_set(channelid_t channel_id, uint16_t value);

/**
 * @author Andreas Meixner
 * Changes the output mode of the output compare channel.
 * @param channel_id The output compare channel id.
 * @param mode The output compare mode.
 */
extern void hal_timer_oc_output_set(channelid_t channel_id, ocmode_t mode);

#endif /* HAL_IO_OC_H_ */
