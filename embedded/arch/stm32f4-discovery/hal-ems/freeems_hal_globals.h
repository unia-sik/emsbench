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
 * $Id: freeems_hal_globals.h 502 2015-11-05 14:18:19Z klugeflo $
 * @brief Various globally accessable fields.
 * @file freeems_hal_globals.h
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#ifndef FILE_FREEEMS_HAL_GLOBALS_H_SEEN
#define FILE_FREEEMS_HAL_GLOBALS_H_SEEN

#include <stdint.h>
#include <stdbool.h>

/*
 * Used for periodic timers:
 * TIMx_CCRx_LAST : timer value when the interrupt was triggerd last
 *                  time
 * TIMx_CCRx_NEXT : timer value when the interrupt should be triggered
 *                  next time
 * TIMx_CCRx_SET  : true if TIMx_CCRx_NEXT was set to a value and has to
 *                  be applied on next periodic interrupt
 */
extern volatile uint16_t TIM2_CCR3_LAST;
extern volatile uint16_t TIM2_CCR3_NEXT;
extern volatile bool TIM2_CCR3_SET;

extern volatile uint16_t TIM2_CCR4_LAST;
extern volatile uint16_t TIM2_CCR4_NEXT;
extern volatile bool TIM2_CCR4_SET;


#endif /* FILE_FREEEMS_HAL_GLOBALS_H_SEEN */
