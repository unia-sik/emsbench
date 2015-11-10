/**
 * $Id: head.tpl 499 2014-05-07 11:24:34Z klugeflo $
 * @file timer.c
 * @brief Utility functions for timers.
 * @author Florian Kluge <kluge@informatik.uni-augsburg.de>
 * @copyright GNU General Public License v3.
 */


#include <driver/timer.h>

#include <driver/board.h>
#include <stddef.h>

#include <io.h>
#include <driver/timer.h>


#ifndef STATIC
#define STATIC
#endif

unsigned timer_periodic(uint32_t period) {
  unsigned err = E_OK;

  if (period == 0) {
    timer_disable();
  }
  else {
    IOWR16(A_TIMER, NIOS2_TIMER_PERIODL, period & 0x0000ffff);
    IOWR16(A_TIMER, NIOS2_TIMER_PERIODH, period >> 16);
    IOWR16(A_TIMER, NIOS2_TIMER_CONTROL, NIOS2_TIMER_CONTROL_ITO  |
           NIOS2_TIMER_CONTROL_CONT |
           NIOS2_TIMER_CONTROL_START);
  }

  return err;
}

unsigned timer_single(uint32_t period) {
  unsigned err = E_OK;

  if (period == 0) {
    timer_disable();
  }
  else {
    IOWR16(A_TIMER, NIOS2_TIMER_PERIODL, period & 0x0000ffff);
    IOWR16(A_TIMER, NIOS2_TIMER_PERIODH, period >> 16);
    IOWR16(A_TIMER, NIOS2_TIMER_CONTROL, NIOS2_TIMER_CONTROL_ITO |
           NIOS2_TIMER_CONTROL_START);
  }

  return err;
}

uint32_t timer_getsnap(void) {
  IOWR16(A_TIMER, NIOS2_TIMER_SNAPL, 1);
  return IORD32(A_TIMER, NIOS2_TIMER_SNAPL);
}

void timer_disable(void) {
  IOWR16(A_TIMER, NIOS2_TIMER_CONTROL, NIOS2_TIMER_CONTROL_STOP);
}



