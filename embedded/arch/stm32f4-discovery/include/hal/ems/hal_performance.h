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
 * $Id: hal_performance.h 546 2016-07-15 06:51:19Z klugeflo $
 * @ingroup halInterface
 * @brief Funktions for performance logging.
 * @file hal_performance.h
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#ifndef HAL_PERFORMANCE_H_
#define HAL_PERFORMANCE_H_


/**
 * @author Andreas Meixner
 * @brief Starts code runtime measurement.
 * This function starts a 32 bit counter counting up from 0 (zero) at the
 * maximum frequency of the current platform.
 * @see hal_performance_stopCounter()
 **/
extern void hal_performance_startCounter();

/**
 * @author Andreas Meixner
 * @brief Stops the counter and returns its value.
 * This function stops the counter started by hal_performance_startCounter().
 * Also the counter will be reset to 0 (zero).
 * @return the current value of the counter.
 */
extern unsigned int hal_performance_stopCounter();



#endif /* !HAL_PERFORMANCE_H_ */
