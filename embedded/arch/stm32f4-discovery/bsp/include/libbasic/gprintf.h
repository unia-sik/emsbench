/**
* $Id: head.tpl 499 2014-05-07 11:24:34Z klugeflo $
* @file gprintf.h
* @brief Declarations of the generic printf functions.
* @author Florian Kluge <kluge@informatik.uni-augsburg.de>
* @copyright GNU General Public License v3.
*/
#ifndef PRINTF_H
#define PRINTF_H 1


#include <stdint.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t gprintf(char * buf, uint32_t buf_len, int32_t(*put_fn)(int32_t), const char * format, ...);
uint32_t gprintf_va(char * buf, uint32_t buf_len, int32_t(*put_fn)(int32_t), const char * format, va_list ap);
#define gputs(put_fn, p) gprintf(NULL, 0, put_fn, p)

#ifdef __cplusplus
}
#endif

#endif /* PRINTF_H */
