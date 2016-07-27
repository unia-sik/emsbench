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
 * $Id: hal_init.h 546 2016-07-15 06:51:19Z klugeflo $
 * @ingroup halInterface
 * @brief All the functions needed to initialize the HAL.
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */

#ifndef HAL_INIT_H_
#define HAL_INIT_H_

/**
 * @author Andreas Meixner
 *
 * @brief Initializes the system clock.
 * This function must be called before hal_system_init(void).
 *
 * @seealso hal_system_init(void)
 */
extern void hal_system_clock(void);

/**
 * @author Andreas Meixner
 * @brief Initializes all necessary peripherial devices and sets them up.
 *
 * For an overview what this function hast to set up and configure refere to
 * this section @ref hal_hardware_desc.
 *
 * @seealso hal_system_clock(void)
 */
extern void hal_system_init(void);


/**
 * @brief Print HAL/system information.
 * @author Florian Kluge
 * 
 * This helper function is called during system startup after the system
 * has been initialised. Use it to output information that is relevant
 * for your evaluation.
 */

extern void hal_system_info(void);

#endif /* HAL_INIT_H_ */
