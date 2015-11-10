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
#include <libbasic/gprintf.h>
#include <liboutput/usbuart.h>

#ifdef __cplusplus
extern "C" {
#endif
  /*!
    \def usbuart_printf
    \brief Formatted output on the USB UART device

    \param args see printf (3) man page
    \return see printf (3) man page
  */
#define usbuart_printf(args...) gprintf(NULL, 0, usbuart_putchar, args)

  /*!
    \brief printf into buffer
    \see snprintf (3) man page
    
  */
#define snprintf(buf, size, format...)	gprintf(buf, size, NULL, format)

  /*!
    \def log_printf
    \brief Generic printf for log output
    
    Redirects to #usbuart_printf
  */

  /*!
    \def log_puts
    \brief Generic puts for log output
    
    Redirects to #usbuart_puts
  */

  /*!
    \def log_putchar
    \brief Generic putchar for log output
    
    Redirects to #usbuart_putchar
  */

  // Log facilities
#ifdef __LOG__
#define log_printf usbuart_printf
#define log_puts usbuart_puts
#define log_putchar usbuart_putchar
//#warning Compiling with __LOG__ enabled
#else
#define log_printf(args...) ((void)0)
#define log_puts(args...) ((void)0)
#define log_putchar(args...) ((void)0)
#endif

/*!
   \def perf_printf
   \brief Generic printf for performance log output

   Redirects to #usbuart_printf
 */

 /*!
   \def perf_puts
   \brief Generic puts for performance log output

   Redirects to #usbuart_puts
 */

 /*!
   \def perf_putchar
   \brief Generic putchar for performance log output

   Redirects to #usbuart_putchar
 */

#ifdef __PERF__
#define perf_printf usbuart_printf
#define perf_puts usbuart_puts
#define perf_putchar usbuart_putchar
//#warning Compiling with __PERF__ enabled
#else
#define perf_printf(args...) ((void)0)
#define perf_puts(args...) ((void)0)
#define perf_putchar(args...) ((void)0)
#endif

/*!
  \def debug_printf
  \brief printf for debugging

  turn on by defining __DEBUG__ before including this file
*/

#ifdef __DEBUG__
#define debug_printf usbuart_printf
#define debug_puts usbuart_puts
#define debug_putchar usbuart_putchar
//#warning Compiling with __DEBUG__ enabled
#else
#define debug_printf(args...) ((void)0)
#define debug_puts(args...) ((void)0)
#define debug_putchar(args...) ((void)0)
#endif


#ifdef __cplusplus
}
#endif

#endif /* OUTPUT_H_ */
