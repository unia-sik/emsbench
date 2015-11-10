/**
 * $Id: nios2f-de2-70.h 803 2014-03-05 14:57:59Z klugeflo $
 * Addresses for NIOS2f on DE2-70 board
 */

#ifndef BOARD_INCLUDE
#error Do not directly include this file, use <board.h> instead!
#endif

#ifndef NIOS2_NIOS2F_DE2_70_H
#define NIOS2_NIOS2F_DE2_70_H

// RAMS
#define A_SDRAM       0x04000000
#define A_SSRAM       0x08200000
#define A_OCRAM       0x08408000

// uC Peripherals
#define A_JTAG_DBG	0x08410800
#define A_ETH		0x08411000
#define A_JTAG_UART	0x08411400
#define A_UART		0x08411420
#define A_PS2		0x08411440
#define A_SYSID		0x08411450
#define A_PIO_LGREEN	0x08411460
#define A_PIO_LRED	0x08411470
#define A_PIO_BUTTON	0x08411480
#define A_PIO_SWITCH	0x08411490
#define A_S7CTL		0x084114a0
#define A_LCD		0x084114c0
#define A_PIO_LCD_BL	0x084114d0
#define A_VGA		0x08411500
#define A_PCC		0x08411900
#define A_TIMER_0	0x08411980
#define A_TIMER_1	0x084119a0
#define A_TIMER_2	0x084119c0
#define A_TIMER_3	0x084119e0
#define A_SCCT		0x08411a00
#define A_PIO_IGN       0x08411a80

#define A_TIMER A_TIMER_0

#define HAVE_S7CTL       1
#define HAVE_PIO_LGREEN  1
#define N_PIO_LGREEN     9
#define HAVE_PIO_LRED    1
#define N_PIO_LRED      18
#define HAVE_PIO_LEDS    1 // summing up the above
#define HAVE_PIO_BUTTON  1
#define N_BUTTONS        4
#define HAVE_PIO_SWITCH  1
#define N_SWITCHES      18
#define HAVE_UART        1
#define HAVE_JTAG_UART   1
#define HAVE_PCC         1
#define HAVE_SYSID       1
#define HAVE_LCD         1

//#define A_RGB_MUX_CLK (A_VGA+0x40) /*!< VGA MUX clock address */


#define N_IRQS     20 /*!< Number of IRQs available */

#define IRQ_JTAG_UART_N   0
#define IRQ_PIO_BUTTON_N  1
#define IRQ_PIO_SWITCH_N  2
#define IRQ_UART_N        3
#define IRQ_PS2_N         4
#define IRQ_ETH_N         5
#define IRQ_TIMER0_N      6
#define IRQ_TIMER1_N      7
#define IRQ_TIMER2_N      8
#define IRQ_TIMER3_N      9
#define IRQ_SCCT_N       10

#define IRQ_BIT(n)    (1 << (n))

#define IRQ_JTAG_UART_BIT IRQ_BIT(IRQ_JTAG_UART_N)
#define IRQ_PIO_BUTTON_BIT IRQ_BIT(IRQ_PIO_BUTTON_N)
#define IRQ_PIO_SWITCH_BIT IRQ_BIT(IRQ_PIO_SWITCH_N)
#define IRQ_UART_BIT IRQ_BIT(IRQ_UART_N)
#define IRQ_PS2_BIT IRQ_BIT(IRQ_PS2_N)
#define IRQ_ETH_BIT IRQ_BIT(IRQ_ETH_N)
#define IRQ_TIMER0_BIT IRQ_BIT(IRQ_TIMER0_N)
#define IRQ_TIMER1_BIT IRQ_BIT(IRQ_TIMER1_N)
#define IRQ_TIMER2_BIT IRQ_BIT(IRQ_TIMER2_N)
#define IRQ_TIMER3_BIT IRQ_BIT(IRQ_TIMER3_N)
#define IRQ_SCCT_BIT IRQ_BIT(IRQ_SCCT_N)

#endif /* NIOS2_NIOS2F_DE2_70_H */

