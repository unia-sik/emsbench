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
 * $Id: hal_timer.h 502 2015-11-05 14:18:19Z klugeflo $
 * @ingroup halInterface
 * @brief Functions to use general purpose timers.
 * @file hal_timer.h
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#ifndef HAL_TIMER_H_
#define HAL_TIMER_H_

/**
 * @author Andreas Meixner
 * @brief Returns the current value of the reference clock.
 * The reference timer is the one which all other timers except for the RTC are
 * synchronized with.
 * @return The current value of the reference timer.
 */
extern uint16_t hal_timer_time_get(void);

/**
 * @author Andreas Meixner
 * Returns if an overflow has occured on the reference timer.
 * The reference timer is the one which all other timers except for the RTC are
 * synchronized with.
 * @return true if an overflow occured, false otherwise.
 */
extern bool hal_timer_overflow_get(void);

/**
 * @author Andreas Meixner
 * Clears the overflow flag of the reference timer.
 * The reference timer is the one which all other timers except for the RTC are
 * synchronized with.
 */
extern void hal_timer_overflow_clear(void);

#endif /* HAL_TIMER_H_ */
