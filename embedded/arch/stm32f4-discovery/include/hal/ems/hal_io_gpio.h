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
 * $Id: hal_io_gpio.h 502 2015-11-05 14:18:19Z klugeflo $
 * @ingroup halInterface
 * @brief Read/write GPIO pins.
 * @file hal_io_gpio.h
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#ifndef HAL_IO_GPIO_H_
#define HAL_IO_GPIO_H_
#include "hal_io.h"

/**
 * @author Andreas Meixner
 *
 * Returns the pin state of the io channel.
 * @param channel_id The io channel id.
 * @return The state of the pin.
 */
extern pinstate_t hal_io_get(channelid_t channel_id);

/**
 * @author Andreas Meixner
 *
 * Sets the pin state of the io channel.
 * @param channel_id The io channel id.
 * @param value The new value to which the pin will be set.
 * @return The pin state of the io channel to change to.
 */
extern void hal_io_set(channelid_t channel_id, pinstate_t value);


#endif /* HAL_IO_GPIO_H_ */
