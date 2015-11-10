/**
 * $Id: head.tpl 499 2014-05-07 11:24:34Z klugeflo $
 * @file timer.h
 * @brief Register map, bit definitions and utility functions for timers.
 * @author Florian Kluge <kluge@informatik.uni-augsburg.de>
 * @copyright GNU General Public License v3.
 */

#ifndef DRIVER_TIMER_H
#define DRIVER_TIMER_H 1

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NIOS2_TIMER_STATUS	0
#define NIOS2_TIMER_CONTROL	4
#define NIOS2_TIMER_PERIODL	8
#define NIOS2_TIMER_PERIODH	12
#define NIOS2_TIMER_SNAPL	16
#define NIOS2_TIMER_SNAPH	20

#define NIOS2_TIMER_STATUS_TO	(1<<0)
#define NIOS2_TIMER_STATUS_RUN	(1<<1)

#define NIOS2_TIMER_CONTROL_ITO		(1<<0)
#define NIOS2_TIMER_CONTROL_CONT	(1<<1)
#define NIOS2_TIMER_CONTROL_START	(1<<2)
#define NIOS2_TIMER_CONTROL_STOP	(1<<3)

#define E_OK 0

/*!
  Activate periodic timer interrupts
  \param period 28 bit, use 0 to disable
  \return -#E_OK everything fine
*/
unsigned timer_periodic(uint32_t period);

/*!
  Activate single timer interrupt
  \param period cycles from now, use 0 to disable
  \return -#E_OK everything fine
*/
unsigned timer_single(uint32_t period);

/*!
  Get current snapshot of timer counter value
  \return Current snapshot of timer counter value
*/
uint32_t timer_getsnap(void);

/*!
  Disables the timer
*/
void timer_disable(void);

#ifdef __cplusplus
}
#endif

#endif /* DRIVER_TIMER_H */
