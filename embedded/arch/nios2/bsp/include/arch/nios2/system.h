/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'cpu' in SOPC Builder design 'mynioscore'
 * SOPC Builder design path: ../../mynioscore.sopcinfo
 *
 * Generated: Fri Oct 19 14:31:28 CEST 2012
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_qsys"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x10820
#define ALT_CPU_CPU_FREQ 60000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "small"
#define ALT_CPU_DATA_ADDR_WIDTH 0x11
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x8020
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 60000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 2048
#define ALT_CPU_INST_ADDR_WIDTH 0x11
#define ALT_CPU_NAME "cpu"
#define ALT_CPU_RESET_ADDR 0x08008000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x10820
#define NIOS2_CPU_FREQ 60000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "small"
#define NIOS2_DATA_ADDR_WIDTH 0x11
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x8020
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 2048
#define NIOS2_INST_ADDR_WIDTH 0x11
#define NIOS2_RESET_ADDR 0x08008000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_QSYS


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone II"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart"
#define ALT_STDERR_BASE 0x11030
#define ALT_STDERR_DEV jtag_uart
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart"
#define ALT_STDIN_BASE 0x11030
#define ALT_STDIN_DEV jtag_uart
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart"
#define ALT_STDOUT_BASE 0x11030
#define ALT_STDOUT_DEV jtag_uart
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "mynioscore"


/*
 * hal configuration
 *
 */

#define ALT_MAX_FD 32
#define ALT_SYS_CLK SYS_CLK_TIMER
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart altera_avalon_jtag_uart
#define JTAG_UART_BASE 0x11030
#define JTAG_UART_IRQ 16
#define JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_NAME "/dev/jtag_uart"
#define JTAG_UART_READ_DEPTH 64
#define JTAG_UART_READ_THRESHOLD 8
#define JTAG_UART_SPAN 8
#define JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_WRITE_DEPTH 64
#define JTAG_UART_WRITE_THRESHOLD 8


/*
 * led_pio configuration
 *
 */

#define ALT_MODULE_CLASS_led_pio altera_avalon_pio
#define LED_PIO_BASE 0x11020
#define LED_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define LED_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LED_PIO_CAPTURE 0
#define LED_PIO_DATA_WIDTH 8
#define LED_PIO_DO_TEST_BENCH_WIRING 0
#define LED_PIO_DRIVEN_SIM_VALUE 0x0
#define LED_PIO_EDGE_TYPE "NONE"
#define LED_PIO_FREQ 60000000u
#define LED_PIO_HAS_IN 0
#define LED_PIO_HAS_OUT 1
#define LED_PIO_HAS_TRI 0
#define LED_PIO_IRQ -1
#define LED_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LED_PIO_IRQ_TYPE "NONE"
#define LED_PIO_NAME "/dev/led_pio"
#define LED_PIO_RESET_VALUE 0x0
#define LED_PIO_SPAN 16
#define LED_PIO_TYPE "altera_avalon_pio"


/*
 * onchip_mem configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_mem altera_avalon_onchip_memory2
#define ONCHIP_MEM_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_MEM_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_MEM_BASE 0x08008000
#define ONCHIP_MEM_CONTENTS_INFO ""
#define ONCHIP_MEM_DUAL_PORT 0
#define ONCHIP_MEM_GUI_RAM_BLOCK_TYPE "Automatic"
#define ONCHIP_MEM_INIT_CONTENTS_FILE "onchip_mem"
#define ONCHIP_MEM_INIT_MEM_CONTENT 1
#define ONCHIP_MEM_INSTANCE_ID "NONE"
#define ONCHIP_MEM_IRQ -1
#define ONCHIP_MEM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_MEM_NAME "/dev/onchip_mem"
#define ONCHIP_MEM_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_MEM_RAM_BLOCK_TYPE "Auto"
#define ONCHIP_MEM_READ_DURING_WRITE_MODE "DONT_CARE"
#define ONCHIP_MEM_SINGLE_CLOCK_OP 0
#define ONCHIP_MEM_SIZE_MULTIPLE 1
#define ONCHIP_MEM_SIZE_VALUE 20480u
#define ONCHIP_MEM_SPAN 20480
#define ONCHIP_MEM_TYPE "altera_avalon_onchip_memory2"
#define ONCHIP_MEM_WRITABLE 1


/*
 * sys_clk_timer configuration
 *
 */

#define ALT_MODULE_CLASS_sys_clk_timer altera_avalon_timer
#define SYS_CLK_TIMER_ALWAYS_RUN 0
#define SYS_CLK_TIMER_BASE 0x11000
#define SYS_CLK_TIMER_COUNTER_SIZE 32
#define SYS_CLK_TIMER_FIXED_PERIOD 0
#define SYS_CLK_TIMER_FREQ 60000000u
#define SYS_CLK_TIMER_IRQ 1
#define SYS_CLK_TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SYS_CLK_TIMER_LOAD_VALUE 59999ull
#define SYS_CLK_TIMER_MULT 0.0010
#define SYS_CLK_TIMER_NAME "/dev/sys_clk_timer"
#define SYS_CLK_TIMER_PERIOD 1
#define SYS_CLK_TIMER_PERIOD_UNITS "ms"
#define SYS_CLK_TIMER_RESET_OUTPUT 0
#define SYS_CLK_TIMER_SNAPSHOT 1
#define SYS_CLK_TIMER_SPAN 32
#define SYS_CLK_TIMER_TICKS_PER_SEC 1000u
#define SYS_CLK_TIMER_TIMEOUT_PULSE_OUTPUT 0
#define SYS_CLK_TIMER_TYPE "altera_avalon_timer"


/*
 * sysid configuration
 *
 */

#define ALT_MODULE_CLASS_sysid altera_avalon_sysid_qsys
#define SYSID_BASE 0x11038
#define SYSID_ID 0
#define SYSID_IRQ -1
#define SYSID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_NAME "/dev/sysid"
#define SYSID_SPAN 8
#define SYSID_TIMESTAMP 1347606672
#define SYSID_TYPE "altera_avalon_sysid_qsys"

#endif /* __SYSTEM_H_ */
