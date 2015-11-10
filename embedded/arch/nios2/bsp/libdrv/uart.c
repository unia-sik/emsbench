/**
* $Id: head.tpl 499 2014-05-07 11:24:34Z klugeflo $
* @file uart.c
* @brief Utility functions for UART.
* @author Florian Kluge <kluge@informatik.uni-augsburg.de>
* @copyright GNU General Public License v3.
*/


#include <stddef.h>

#include <driver/board.h>
#include <driver/uart.h>

#include <io.h>

void uart_init(void) {
  // nothing to do
}


int32_t uart_putchar(int32_t c) {
  char vc = (char) (c & 0xff);
  while ( !(htonl(IORD8(A_UART, UART_ST)) & UART_ST_TRDY) );
  IOWR8(A_UART, UART_TX, vc);
  return (int32_t) vc;
}

int32_t uart_puts(char *p) {
  uint32_t ctr = 0;
  if (p == NULL) {
    return -1;
  }
  do {
    // need to wait until UART gets ready to transmit
    if (htonl(IORD8(A_UART, UART_ST)) & UART_ST_TRDY) {
      IOWR8(A_UART, UART_TX, *p);
      ++p;
      ++ctr;
    }
  }
  while (*p);

  return ctr;
}
