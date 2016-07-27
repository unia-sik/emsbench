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
 * $Id: freeems_hal_globals.h 546 2016-07-15 06:51:19Z klugeflo $
 * @brief Various globally accessable fields.
 * @file freeems_hal_globals.h
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#ifndef FILE_FREEEMS_HAL_GLOBALS_H_SEEN
#define FILE_FREEEMS_HAL_GLOBALS_H_SEEN

#include <stdint.h>
#include <stdbool.h>

volatile uint16_t TIM2_CCR3_LAST;
volatile uint16_t TIM2_CCR3_NEXT;
volatile bool TIM2_CCR3_SET;

volatile uint16_t TIM2_CCR4_LAST;
volatile uint16_t TIM2_CCR4_NEXT;
volatile bool TIM2_CCR4_SET;

//channelid_t injectionOutputChannels[] = {INJECTION1_OUTPUT,INJECTION2_OUTPUT,INJECTION3_OUTPUT,INJECTION4_OUTPUT,INJECTION5_OUTPUT,INJECTION6_OUTPUT,INJECTION7_OUTPUT,INJECTION8_OUTPUT};
//channelid_t ignitionChannels[] = {IGNITION1_OUTPUT,IGNITION2_OUTPUT,IGNITION3_OUTPUT,IGNITION4_OUTPUT,IGNITION5_OUTPUT,IGNITION6_OUTPUT,IGNITION7_OUTPUT,IGNITION8_OUTPUT};


#endif /* FILE_FREEEMS_HAL_GLOBALS_H_SEEN */
