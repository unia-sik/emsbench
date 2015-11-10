/**
* $Id: head.tpl 499 2014-05-07 11:24:34Z klugeflo $
* @file usbuart.h
* @brief Functions for initialising and using UART for serial output.
* @author Florian Kluge <kluge@informatik.uni-augsburg.de>
* @copyright GNU General Public License v3.
*/
#ifndef USBUART_H_
#define USBUART_H_ 1

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void usbuart_init(void);
void usbuart_wait(void);
int32_t usbuart_putchar(int32_t c);
int32_t usbuart_puts(char *p);

#ifdef __cplusplus
}
#endif

#endif /* USBUART_H_ */
