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
 * $Id: log.h 502 2015-11-05 14:18:19Z klugeflo $
 * @brief Defines macros for logging
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */

#ifndef HAL_LOG_H
#define HAL_LOG_H

#include <liboutput/usbuart.h>
#include <libbasic/gprintf.h>

#define usbuart_printf(args...) gprintf(NULL, 0, usbuart_putchar, args)

/**
 * @author Andreas Meixner
 * @biref initialize logging
 * This macro initializes everythich needed for logging. After calling this
 * calls to log_printf, debug_printf and perf_printf have to work properly.
 */
#define log_init() { usbuart_init(); usbuart_wait(); }

#ifdef __LOG__
#define log_printf usbuart_printf
#define log_puts usbuart_puts
/**
 * @author Andreas Meixner
 * @brief Defines a variable codeStartTimeStamp and stores the current time
 *        (hal_timer_get_time() in it.
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
#define debug_printf usbuart_printf
#define debug_puts usbuart_puts
#else
#define debug_printf(args...) ((void)0)
#define debug_puts(args...) ((void)0)
#endif

#ifdef __PERF__
#define perf_printf usbuart_printf
#else
#define perf_printf(args...) ((void)0)
#endif

#define output_performance_log() ((void)0)

#endif // !HAL_LOG_H
