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
 * $Id: hal_irq.h 502 2015-11-05 14:18:19Z klugeflo $
 * @ingroup halInterface
 * @brief Functions to controll IRQ.
 * @file hal_irq.h
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */

#ifndef HAL_EMS_HAL_IRQ_H
#define HAL_EMS_HAL_IRQ_H

void hal_irq_atomic_start();
void hal_irq_atomic_end();

/**
 * Start a critical section
 */
#define ATOMIC_START() hal_irq_atomic_start();      /* set global interrupt mask */

/**
 * Finish a critical section
 */
#define ATOMIC_END() hal_irq_atomic_end() /* clear global interrupt mask */


#endif // !HAL_EMS_HAL_IRQ_H
