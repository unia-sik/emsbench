/**
* $Id: head.tpl 499 2014-05-07 11:24:34Z klugeflo $
* @file uart.h
* @brief Register map, bit definitions and utility functions for UART.
* @author Florian Kluge <kluge@informatik.uni-augsburg.de>
* @copyright GNU General Public License v3.
*/

#ifndef DRIVER_UART_H
#define DRIVER_UART_H 1

#ifdef __ALTERA_BOARD // only use these devices, if we compile for the board

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Register Map
#define UART_RX  0x00
#define UART_TX  0x04
#define UART_ST  0x08
#define UART_CT  0x0c
#define UART_DIV 0x10
#define UART_EOF 0x14


#define UART_ST_PE   0x00000001 /*!< Parity Error */
#define UART_ST_FE   0x00000002 /*!< Framing Error */
#define UART_ST_BRK  0x00000004 /*!< Break Detect */
#define UART_ST_ROE  0x00000008 /*!< Receive Overrun Error */
#define UART_ST_TOE  0x00000010 /*!< Transmit Overrun Error */
#define UART_ST_TMT  0x00000020 /*!< Transmit Empty */
#define UART_ST_TRDY 0x00000040 /*!< Transmit Ready */
#define UART_ST_RRDY 0x00000080 /*!< Receive Character Ready */
#define UART_ST_E    0x00000100 /*!< Exception */
#define UART_ST_DCTS 0x00000400 /*!< Change in Clear To Send (CTS) Signal (optional) */
#define UART_ST_CTS  0x00000800 /*!< Clear-To-Send (CTS) Signal (optional) */
#define UART_ST_EOP  0x00001000 /*!< End Of Packet encountered (optgional) */


#define UART_CT_IPE   0x00000001 /*!< Enable Interrupt for a Parity Error */
#define UART_CT_IFE   0x00000002 /*!< Enable Interrupt for a Framing Error */
#define UART_CT_IBRK  0x00000004 /*!< Enable Interrupt for a Break Detect */
#define UART_CT_IROE  0x00000008 /*!< Enable Interrupt for a Receiver Overrun Error */
#define UART_CT_ITOE  0x00000010 /*!< Enable Interrupt for a Transmitter Overrung Error */
#define UART_CT_ITMT  0x00000020 /*!< Enable Interrupt for a Transmitter Shift Register Empty */
#define UART_CT_ITRDY 0x00000040 /*!< Enable Interrupt for a Transmission Ready */
#define UART_CT_IRRDY 0x00000080 /*!< Enable Interrupt for a Read Ready */
#define UART_CT_IE    0x00000100 /*!< Enable Interrupt for an Exception */
#define UART_CT_TBRK  0x00000200 /*!< Transmit Break */
#define UART_CT_IDCTS 0x00000400 /*!< Enable Interrupt for a change in CTS signal */
#define UART_CT_RTS   0x00000800 /*!< Request To Send (RTS) Signal (optional) */
#define UART_CT_IEOP  0x00001000 /*!< Enable Interrupt for End-Of-Packet condition */


/*! Initialise the UART device */
void uart_init(void);

/*! Write one char to the UART device */
int32_t uart_putchar(int32_t c);

/*! Output a string over UART */
int32_t uart_puts(char *p);

#ifdef __cplusplus
}
#endif

#endif /* __ALTERA_BOARD */

#endif /* UART_H */
