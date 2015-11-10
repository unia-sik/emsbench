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
 * $Id: hal_timer_pit.h 502 2015-11-05 14:18:19Z klugeflo $
 * @ingroup halInterface
 * @brief Functions to control programmable interrupt timers.
 * @file hal_timer_pit.h
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#ifndef HAL_TIMER_PIT_H_
#define HAL_TIMER_PIT_H_

/**
 * @brief Defines IDs for all the programmable inetrrupt timers FreeEMS uses.
 *
 * @seealso hal_timer_pit_interval_set(channelid_t, uint16_t)
 * @seealso hal_timer_pit_active_get(channelid_t)
 * @seealso hal_timer_pit_active_set(channelid_t, bool)
 */
typedef enum pits {
  /**
   * The ID of the timer that controlls the ignition fire event.
   */
  IGNITION_FIRE_PIT,
  /**
   * The ID of the timer that controlls the ignition dwell event.
   */
  IGNITION_DWELL_PIT
} pitid_t;

/**
 * @author Andreas Meixner
 * Sets the interrupt interval value of the periodic interrupt timer
 * channel. Interval is valid after the next interrupt if timer is
 * already active.
 * @param pit_id The periodic interrupt timer channel id.
 * @param value The interval value.
 */
extern void hal_timer_pit_interval_set(pitid_t pit_id, uint16_t value);

/**
 * @author Andreas Meixner
 * Returns true if the interrupt of the given timer channel is enabled,
 * otherwise false.
 * @param pit_id The periodic interrupt timer channel id.
 * @return The state of the periodic interrupt timer channel, true if the
 *         inetrrupt is enabled, otherwise false.
 */
extern bool hal_timer_pit_active_get(pitid_t pit_id);

/**
 * @author Andreas Meixner
 * Enables/disables the interrupt of the given timer channel.
 * @param pit_id The channel id of the timer whose interrupt si to be
 *        enabled/disabled.
 * @param active true if the interrupt is to be enabled, otherwise false.
 */
extern void hal_timer_pit_active_set(pitid_t pit_id, bool active);

/**
 * @author Andreas Meixner
 * @brief Returns the current counter value of the pit.
 * The current counter value is the amount of timer ticks left before the next
 * interrupt will be generated.
 * @param pit_id The Id of the pit from which to obtain the counter value.
 * @return The current counter value.
 */
extern uint16_t hal_timer_pit_current_get(pitid_t pit_id);

/**
 * @author Andreas Meixner
 * @brief Returns the current interval value of the the periodic interrupt timer.
 * The intervall is the time, measured in ticks if the given timer, between two
 * interrupts.
 * @param pit_id The tinterrupt timer id
 * @return The current interval length of this timer.
 */
extern uint16_t hal_timer_pit_interval_get(pitid_t pit_id);

#endif /* HAL_TIMER_PIT_H_ */
