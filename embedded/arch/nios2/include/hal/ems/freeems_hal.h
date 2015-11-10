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
 * $Id: freeems_hal.h 502 2015-11-05 14:18:19Z klugeflo $
 * @ingroup halInterface
 * @brief This header defines the complete interface needed by FreeEMS to
 *        operate on any hardware.
 * @file freeems_hal.h
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#ifndef FILE_FREEEMS_HAL_H_SEEN
#define FILE_FREEEMS_HAL_H_SEEN

// stdlibs
#include <stdint.h>
#include <stdbool.h>

// nios2 specific hardware libs
#include <driver/board.h>
#include <driver/scct.h>
#include <driver/timer.h>
#include <intrinsics.h>
#include <spr-defs.h>
#include <io.h>

// all hal headers
#include "hal/ems/hal_init.h"
#include "hal/ems/hal_io.h"
#include "hal/ems/hal_io_ic.h"
#include "hal/ems/hal_io_oc.h"
#include "hal/ems/hal_io_gpio.h"
#include "hal/ems/hal_timer.h"
#include "hal/ems/hal_timer_pit.h"
#include "hal/ems/hal_logging.h"
#include "hal/ems/hal_irq.h"
#include "hal/ems/hal_performance.h"

/**
 * @author Andreas Meixner
 * @brief Starts up all neened hardware.
 * The Hardware must be configured by calling hal_system_clock(void) and
 * hal_system_init(void) first.
 *
 * @see hal_system_clock(void)
 * @see hal_system_init(void)
 */
extern void hal_system_start(void);


#endif /* FILE_FREEEMS_HAL_H_SEEN */
