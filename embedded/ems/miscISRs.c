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
 * @file miscISRs.c
 * @ingroup interruptHandlers
 *
 * @brief Miscellaneous Interrupt Handlers
 *
 * Various non-descript interrupt handlers that don't really fit anywhere else
 * and aren't big enough to live on their own just yet.
 *
 * <h> original author</h> Fred Cooke
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

#include "inc/freeEMS.h"
#include "inc/interrupts.h"


/** @brief Unimplemented Interrupt Handler
 *
 * Unimplemented interrupt service routine for calls  we weren't expecting.
 * Currently this simply counts bad calls like any other event type.
 *
 * @author Fred Cooke
 */
void UISR(void) {
  /* Increment the unimplemented ISR execution counter */
  Counters.callsToUISRs++;
}


/** @brief Port P pins ISR
 *
 * Interrupt handler for edge events on port P pins. Not currently used.
 *
 * @author Fred Cooke
 */
void PortPISR(void) {
  /* Clear all port P flags (we only want one at a time) */
  PIFP = ONES;
  /* Increment the unimplemented ISR execution counter */
  Counters.callsToUISRs++;
}			/* Port P interrupt service routine */


/** @brief Port J pins ISR
 *
 * Interrupt handler for edge events on port J pins. Not currently used.
 *
 * @author Fred Cooke
 */
void PortJISR(void) {
  /* Clear all port H flags (we only want one at a time) */
  PIFJ = ONES;
  /* Increment the unimplemented ISR execution counter */
  Counters.callsToUISRs++;
}


/** @brief Port H pins ISR
 *
 * Interrupt handler for edge events on port H pins. Not currently used.
 *
 * @author Fred Cooke
 */
void PortHISR(void) {
  // debounce
  if(portHDebounce == 0) {
    portHDebounce = 2;
  }
  else {
    return;
  }
}


/** @brief IRQ/PE1 pin ISR
 *
 * Interrupt handler for edge events on the IRQ/PE1 pin. Not currently used.
 *
 * @author Fred Cooke
 */
void IRQISR(void) {
  /* Clear the flag */
  // ?? TODO

  /* Increment the unimplemented ISR execution counter */
  Counters.callsToUISRs++;
}


/** @brief XIRQ/PE0 pin ISR
 *
 * Interrupt handler for edge events on the XIRQ/PE0 pin. Not currently used.
 *
 * @author Fred Cooke
 */
void XIRQISR(void) {
  /* Clear the flag */
  // ?? TODO

  /* Increment the unimplemented ISR execution counter */
  Counters.callsToUISRs++;
}


/** @brief Low Voltage Counter
 *
 * Count how often our voltage drops lower than it should without resetting.
 *
 * @author Fred Cooke
 */
void LowVoltageISR(void) {
  /* Clear the flag */
  VREGCTRL |= 0x01;

  /* Increment the counter */
  Counters.lowVoltageConditions++;
}
