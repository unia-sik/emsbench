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
 * $Id: tg.h 502 2015-11-05 14:18:19Z klugeflo $
 * @brief HAL interface for trace generator
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */

#ifndef HAL_TG_TG_H
#define HAL_TG_TG_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief How many counter ticks stand for one second.
 * The timer is set up to run at a frequency of 1,25MHz, that means one second
 * is equal to 1250000 ticks.
 * @seealso Timer setupt in tim_setup(void) and clock configuration values
 *          SPEED, TCPERIOD and TCPRESCALER.
 */
#define TICKS_PER_SECOND 1250000 // Testing was @ 65536


/**
 * @brief How long (timer counter ticks) should the level be kept high?
 * @todo Check how long shortest interval between two primaries can be!
 * @note This is very strange - setting a small value will slow down trace
 * generation (using 5 approximately doubles simulation time).
 */
#define TG_HIGH_TIME 100

typedef uint16_t timctr_t;

/**
 * Modes for output compare channels
 * OC_MODE_NONE   : No output change
 * OC_MODE_ON     : High output
 * OC_MODE_OFF    : Low output
 * OC_MODE_TOGGLE : Toggle output
 */
typedef enum status_enum_t {
  OC_MODE_NONE, ///< No output change
  OC_MODE_ON, ///< Set output pin to high
  OC_MODE_OFF, ///< Set output pin to low
  OC_MODE_TOGGLE, ///< Toggle output pin level
} oc_mode_t;


/**
 * @brief Initialise trace generator HAL.
 * This function should setup all timers etc.
 */
void hal_tg_setup();

/**
 * @brief Start trace generation.
 * For embedded platforms, the implementation of this function may be left
 * empty. Its aim is to provide some hook for x86-pc implementations
 * to allow executing the trace generator without interrupts.
 */
void hal_tg_run();

/**
 * @brief Notify HAL that trace generation is finished.
 */
void hal_tg_notify_finished();

/**
 * @brief Set timer for primary signal.
 * @param time absolute time stamp
 * @param mode output action
 */
void hal_tg_set_primary_time(timctr_t time, oc_mode_t mode);

/**
 * @brief Set timer for secondary signal.
 * @param time absolute time stamp
 * @param mode output action
 */
void hal_tg_set_secondary_time(timctr_t time, oc_mode_t mode);

/**
 * @brief Advance timer for primary signal
 * @param adv offset relative to last signal
 * @param mode output action
 */
void hal_tg_advance_primary_time(timctr_t adv, oc_mode_t mode);

/**
 * @brief Advance timer for secondary signal
 * @param adv offset relative to last signal
 * @param mode output action
 */
void hal_tg_advance_secondary_time(timctr_t adv, oc_mode_t mode);

/**
 * @return Current value of primary time
 */
timctr_t hal_tg_get_primary_time();

/**
 * @return Current value of secondary time
 */
timctr_t hal_tg_get_secondary_time();

/**
 * @return Current time
 */
timctr_t hal_tg_get_time();



/**
 * @name External functions defined by actual trace generation
 * @{
 */

/**
 * @brief Callback for primary ISR
 * @param cur_mode current mode of OC channel (action executed for this IRQ)
 */
extern void handle_primary(bool state);

/**
 * @brief Callback for secondary ISR
 * @param cur_mode current mode of OC channel (action executed for this IRQ)
 */
extern void handle_secondary(bool state);


/**
 * @}
 */

#endif // !HAL_TG_TG_H
