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
 * @file strategies.h
 * @brief 
 * <h> original author</h> Fred Cooke
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

/** @page generalStrategies General Strategies
 *
 * This page exists to document general coding strategies used in this
 * firmware. Each item should contain a title, description, situations
 * it is useful in and somewhere you can see an example of it in use.
 *
 * Reading/Writing from/to a specific page :
 *
 * Save the current page value to a variable, change the page value to the desired one, read or write the paged memory, change the page back and return the value
 *
 * This is applicable to all three available memory types: Flash, RAM and EEPROM.
 *
 * Examples of its use can be found in flashWrite.c
 *
 * @todo TODO TBC (other strategies)
 */

/**	@file strategies.h
 * @ingroup doxygenDocFiles
 * @brief Doxygen General Strategies page definition
 */
