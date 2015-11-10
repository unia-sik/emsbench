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
 * $Id: header-ems.c 480 2015-10-27 12:42:40Z klugeflo $
 * @file freeems.h
 * @brief 
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

#ifndef _FREEEMS_H
#define _FREEEMS_H

#include "inc/DummyDefs.h"

#undef BIT0
#undef BIT1
#undef BIT2
#undef BIT3
#undef BIT4
#undef BIT5
#undef BIT6
#undef BIT7

#include "inc/globalDefines.h"


extern void initVariables();

extern void main_freeems();
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

extern unsigned short masterPulseWidth;
extern unsigned short totalAngleAfterReferenceInjection;


#endif /* _FREEEMS_H */
