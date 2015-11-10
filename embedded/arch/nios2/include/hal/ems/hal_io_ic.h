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
 * $Id: hal_io_ic.h 502 2015-11-05 14:18:19Z klugeflo $
 * @ionGroup halInterface
 * @brief Functions to use input capture channels.
 * @file hal_io_ic.h
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */

#ifndef HAL_IO_IC_H_
#define HAL_IO_IC_H_


/**
 * @author Andreas Meixner
 * Returns the time stamp when the capture event on the given @a channel_id
 * occured.
 * @param channel_id The input capture channel id.
 * @return Time stamp of the capture event.
 */
extern uint16_t hal_timer_ic_capture_get(channelid_t channel_id);

/**
 * @author Andreas Meixner
 * Returns the pin state of the input capture channel.
 * @param channel_id The input capture channel id.
 * @return The pin state of input capture channel.
 */
extern pinstate_t hal_timer_ic_pin_get(channelid_t channel_id);



#endif /* HAL_IO_IC_H_ */
