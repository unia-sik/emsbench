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
 * $Id: hal_freeems_interface.h 502 2015-11-05 14:18:19Z klugeflo $
 * @brief This file contains definitions for all funktions of FreeEMS that HAL
 * has to call.
 * @file freeems_hal_interface.h
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */

#ifndef HAL_FREEEMS_INTERFACE_H_
#define HAL_FREEEMS_INTERFACE_H_

extern void PrimaryRPMISR();
extern void SecondaryRPMISR();
extern void IgnitionDwellISR();
extern void IgnitionFireISR();
extern void Injector1ISR();
extern void Injector2ISR();
extern void Injector3ISR();
extern void Injector4ISR();
extern void Injector5ISR();
extern void Injector6ISR();
extern void TimerOverflow();
extern void RTIISR();

#endif /* HAL_FREEEMS_INTERFACE_H_ */
