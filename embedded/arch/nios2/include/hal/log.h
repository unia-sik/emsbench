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
 * $Id: log.h 512 2015-11-10 15:29:05Z meixnean $
 * @brief Defines macros for logging
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#ifndef HAL_LOG_H
#define HAL_LOG_H

#include <stdint.h>
#include <output.h>
#include <hal/ems/freeems_hal_circular_buffer.h>
extern circularbuffer_t performance_log_buffer;

/**
 * @author Andreas Meixner
 * @brief initialize logging
 * This macro initializes everythich needed for logging. After calling this
 * calls to log_printf, debug_printf and perf_printf have to work properly.
 */
#define log_init() {\
		performance_log_buffer.head = 0;\
		performance_log_buffer.tail = 0;\
	}\
 
static inline int32_t write_buffer_gprintf(int32_t value) {
  return (int32_t) circular_buffer_write(&performance_log_buffer, (uint8_t)(value & 0xff));
}

#ifdef __LOG__
#define log_printf uart_printf
#define log_puts uart_puts
/**
 * @author Andreas Meixner
 * @brief Defines a variable codeStartTimeStamp and stores the current time
 *       (hal_timer_get_time() in it.
 * This macro is used in combination with GET_START_TIME, for logging purposes.
 */
#define CAPTURE_START_TIME() unsigned short codeStartTimeStamp = hal_timer_time_get()
/**
 * @author Andreas Meixner
 * @brief returns the captured start time.
 * @returns The time stamp captured by calling the macro CAPTURE_START_TIME()
 */
#define GET_START_TIME() codeStartTimeStamp
#else
#define log_printf(args...) ((void)0)
#define log_puts(args...) ((void)0)
#define CAPTURE_START_TIME()
#define GET_START_TIME()
#endif

#ifdef __DEBUG__
#define debug_printf uart_printf
#define debug_puts uart_puts
#else
#define debug_printf(args...) ((void)0)
#define debug_puts(args...) ((void)0)
#endif

#ifdef __PERF__
#define perf_printf(args...) gprintf(NULL, 0, write_buffer_gprintf, args)
#else
#define perf_printf(args...) ((void)0)
#endif

#ifdef __PERF__
#define output_performance_log() output_next_from_buffer(&performance_log_buffer)
#else
#define output_performance_log() ((void)0)
#endif

#endif // !HAL_LOG_H
