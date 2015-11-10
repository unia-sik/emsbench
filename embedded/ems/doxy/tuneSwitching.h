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
 * @file tuneSwitching.h
 * @brief 
 * <h> original author</h> Fred Cooke
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

/** @page tuneSwitching Tune Switching
 *
 * This feature is similar to one known as "table switching" that you may
 * have used before on other systems except that instead of just switching
 * the tables, the entire tune is switched. The only exceptions to this are
 * physical constants that there is only one available copy of.
 *
 * @todo TODO insert discussion about various uses of tune switching here.
 *
 * The primary copy of all switchable items is enabled by default and is
 * normally what you want to adjust while tuning the engine. It is also what is
 * in use when the tune switching mechanism is enabled and not engaged. The
 * secondary copy of a given switchable item is enabled when the tune switching
 * mechanism is enabled and engaged. If tune switching is not enabled then the
 * secondary copy is never used.
 *
 * @b Warning:
 *
 * Although this boils down to paranoia, some precautions are best taken when
 * tuning your vehicle with FreeEMS. Because there are always two copies of all
 * settings and the code has the ability to switch between them you you should
 * always configure the secondary copy explicitly.
 *
 * If you are not using the tune switching feature it is wise to configure all
 * values in the secondary set to be exactly the same as what is in the primary
 * set. This way if you have tune switching	turned on by accident and the input
 * pin is floating you will not get erratic engine behaviour.
 *
 * @b Developers:
 *
 * When adding things to the set of switchable data please ensure you insert
 * appropriate default values in both the primary and secondary copies.
 */

/**	@file tuneSwitching.h
 * @ingroup doxygenDocFiles
 * @brief Doxygen Tune Switching page definition
 */
