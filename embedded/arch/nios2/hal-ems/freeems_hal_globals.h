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
 * $Id: freeems_hal_globals.h 512 2015-11-10 15:29:05Z meixnean $
 * @brief Various globally accessable fields.
 * @file freeems_hal_globals.h
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#ifndef FILE_FREEEMS_HAL_GLOBALS_H_SEEN
#define FILE_FREEEMS_HAL_GLOBALS_H_SEEN

#include <stdint.h>
#include <stdbool.h>

/**
 * @author Andreas Meixner
 * @brief Stores the high word of the Timer_0 counter value.
 * This value is needed because NIOS2 has a 32 bit timer counter but FreeEMS
 * works with 16 bit timer values. So whenever the RTC ticks, the high word of
 * the counter value will be stored, and each tick this value changes
 * TimerOverflow() has to be called.
 */
uint16_t lastTickHighWord;

#define	SPEED_NORMAL 1
#define SPEED_SLOW   2

#if defined(__SPEED__fast)
#define SPEED SPEED_NORMAL
#elif defined (__SPEED__slow)
#define SPEED SPEED_SLOW
#else
#define SPEED = SPEED_NORMAL
#endif


#if SPEED == SPEED_NORMAL
#define TIMER_0_PERIOD 40
#define RTC_PRESCALER_LOW 6250
#define RTC_PRESCALER_HIGH 0
#elif SPEED == SPEED_SLOW
/*
 * The simplest way to change this speed is to use a multiple of the normal
 * speed.
 * e.g. set TIMER_0_PERIOD to 30*NORMAL = 30*40 = 1200
 * and set RTC_PRESCALER to 30*NORMAL = 30*6250 = 187500
 * CAUTION the value for RTC_PRESCALER has to be represented as two 16bit values
 * in this example that means RTC_PRESCALER_LOW = 56428 and
 * RTC_PRESCALER_HIGH = 2
 */
//#define TIMER_0_PERIOD 800
//#define RTC_PRESCALER_LOW 59464
//#define RTC_PRESCALER_HIGH 1
//#define TIMER_0_PERIOD 1200
//#define RTC_PRESCALER_LOW 56428
//#define RTC_PRESCALER_HIGH 2
#define TIMER_0_PERIOD 4000
#define RTC_PRESCALER_LOW 35176
#define RTC_PRESCALER_HIGH 9
#else
#error "SPEED" defined in config.h was set neither SPEED_NORMAL nor SPEED_SLOW
#endif

#endif /* FILE_FREEEMS_HAL_GLOBALS_H_SEEN */
