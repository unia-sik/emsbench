/**
* $Id: head.tpl 499 2014-05-07 11:24:34Z klugeflo $
* @file output.h
* @brief Definitions of various output functions.
* @author Florian Kluge <kluge@informatik.uni-augsburg.de>
* @copyright GNU General Public License v3.
*/
#ifndef OUTPUT_H_
#define OUTPUT_H_ 1


#include <stddef.h>
#include <basic/gprintf.h>

#ifdef __ALTERA_BOARD
#include <driver/uart.h>
#else /* __ALTERA_BOARD */
#include <driver/sim.h>
#endif /* __ALTERA_BOARD */

#ifdef __cplusplus
extern "C" {
#endif

/*!
  \def uart_printf
  \brief Formatted output on UART

  Only available when compiled for __ALTERA_BOARD

  \param args see printf (3) man page
  \return see printf (3) man page
*/

#ifdef __ALTERA_BOARD
#define uart_printf(args...) gprintf(NULL, 0, uart_putchar, args)
#else /* __ALTERA_BOARD */
#define uart_printf(args...) ((void) 0)
#endif /* __ALTERA_BOARD */

/*!
  \brief printf into buffer
  \see snprintf (3) man page

*/
#define snprintf(buf, size, format...)	gprintf(buf, size, NULL, format)

/*!
  \def log_printf
  \brief Generic printf for log output

  Redirects to #uart_printf, if compiled for __ALTERA_BOARD
*/

/*!
  \def log_puts
  \brief Generic puts for log output

  Redirects to #uart_puts, if compiled for __ALTERA_BOARD
*/

/*!
  \def log_putchar
  \brief Generic putchar for log output

  Redirects to #uart_putchar, if compiled for __ALTERA_BOARD
*/

// Log facilities
#if 0
#ifdef __ALTERA_BOARD
#define log_printf uart_printf
#define log_puts uart_puts
#define log_putchar uart_putchar
#else /* __ALTERA_BOARD */
#define log_printf ((void) 0)
#define log_puts ((void) 0)
#define log_putchar ((void) 0)
#endif /* __ALTERA_BOARD */
#endif


/*!
  \def debug_printf
  \brief printf for debugging

  turn on by defining __DEBUG__ before including this file
*/
#if 0
#ifdef __DEBUG__
#define debug_printf log_printf
#warning Compiling with __DEBUG__ enabled
#else
#define debug_printf(args...) ((void)0)
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* OUTPUT_H_ */
