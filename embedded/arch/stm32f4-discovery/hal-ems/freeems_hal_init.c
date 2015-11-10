/*
 * This file is part of EmsBench.
 *
 * Copyright 2015 University of Augsburg
 *
 * EmsBench is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EmsBench is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EmsBench.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * $Id: freeems_hal_init.c 502 2015-11-05 14:18:19Z klugeflo $
 * @brief Implementation of initialization functions.
 * @file freeems_hal_init.c
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#include <hal/ems/freeems_hal.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencmsis/core_cm3.h>

#define	SPEED_NORMAL 1
#define SPEED_SLOW   2

#define SPEED SPEED_NORMAL

#if SPEED == SPEED_NORMAL
#define TCPERIOD 1
#define TCPRESCALER 66
#elif SPEED == SPEED_SLOW
#define TCPERIOD 19
#define TCPRESCALER 66
#else
#error "SPEED" defined in config.h was set neither SPEED_NORMAL nor SPEED_SLOW
#endif


/**** Setup functions */

/*
 * Setup timers
 */
static void hal_priv_timer_setup() {
  /* Activate timer 1 to 5 */
  rcc_periph_clock_enable(RCC_TIM1);
  rcc_periph_clock_enable(RCC_TIM2);
  rcc_periph_clock_enable(RCC_TIM3);
  rcc_periph_clock_enable(RCC_TIM4);
  rcc_periph_clock_enable(RCC_TIM5);
  rcc_periph_clock_enable(RCC_TIM7);

  /* Reset timer 1 to 5 */
  timer_reset(TIM1);
  timer_reset(TIM2);
  timer_reset(TIM3);
  timer_reset(TIM4);
  timer_reset(TIM5);
  timer_reset(TIM7);

  /* Initialize timer 1 to 5 */
  timer_set_mode(TIM1, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
  timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
  timer_set_mode(TIM3, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
  timer_set_mode(TIM4, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
  timer_set_mode(TIM5, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
  timer_set_mode(TIM7, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

  /** Timer 1 (master) **/

  /* Setting timer 1 up as master timer that inputs its channel 1 output
   * as input clock into the other timers */

  /* prescaler = 0 == scaling factor 1!
   *
   * TIM1&8 is on APB2 with max 84MHz
   * TIM2-5 is on APB1 with max 42MHz
   *
   * period = 3, prescaler = 41999 => 1kHz output clock     (= 1ms)
   * period = 1, prescaler = 5250  => 8kHz output clock     (= 125µs)
   * period = 3, prescaler = 335   => 125kHz output clock   (= 8µs)
   * period = 1, prescaler = 66    => ≈1250kHz output clock (= 0.8µs)
   *
   * Formula: 84MHz/TargetClockInHz = (period+1)*(prescaler+1)/2
   */
  timer_set_period(TIM1, TCPERIOD);
  timer_set_prescaler(TIM1, TCPRESCALER);

  /* Set update event as output signal */
  timer_set_master_mode(TIM1, TIM_CR2_MMS_UPDATE);
  timer_set_oc_mode(TIM1, TIM_OC1, TIM_OCM_FROZEN);

  /** Timer 2-4 (slave) **/

  /* Setting timer 2-4 as slave to timer 1 */
  timer_slave_set_trigger(TIM2, TIM_SMCR_TS_ITR0);
  timer_slave_set_mode(TIM2, TIM_SMCR_SMS_ECM1);
  timer_set_period(TIM2, 0xFFFF); /* set Timer 2 to 16 Bit */

  timer_slave_set_trigger(TIM3, TIM_SMCR_TS_ITR0);
  timer_slave_set_mode(TIM3, TIM_SMCR_SMS_ECM1);


  timer_slave_set_trigger(TIM4, TIM_SMCR_TS_ITR0);
  timer_slave_set_mode(TIM4, TIM_SMCR_SMS_ECM1);

  /** Periodic Timer **/

  /* Enable update interrupt */
  timer_enable_irq(TIM2, TIM_DIER_UIE);
  /* Trigger interrupt only on overflow */
  timer_update_on_overflow(TIM2);

  /* Setting channel 3-4 of timer 2 as periodic interrupt */
  timer_set_oc_mode(TIM2, TIM_OC3, TIM_OCM_FROZEN);

  timer_set_oc_mode(TIM2, TIM_OC4, TIM_OCM_FROZEN);

  /** Output Compare **/

  /* Setting channel 1-4 of timer 3 to output compare */
  timer_set_oc_mode(TIM3, TIM_OC1, TIM_OCM_FROZEN);

  timer_set_oc_mode(TIM3, TIM_OC2, TIM_OCM_FROZEN);

  timer_set_oc_mode(TIM3, TIM_OC3, TIM_OCM_FROZEN);

  timer_set_oc_mode(TIM3, TIM_OC4, TIM_OCM_FROZEN);


  /* Setting channel 1-2 of timer 4 to output compare */
  timer_set_oc_mode(TIM4, TIM_OC1, TIM_OCM_FROZEN);

  timer_set_oc_mode(TIM4, TIM_OC2, TIM_OCM_FROZEN);

  /** Input Capture **/

  /* Setting channel 2 of timer 2 as input capture */
  timer_ic_set_input(TIM2, TIM_IC2, TIM_IC_IN_TI2);
  timer_ic_set_polarity(TIM2, TIM_IC2, TIM_IC_RISING);
  timer_ic_enable(TIM2, TIM_IC2);

  /* Setting channel 3 of timer 4 as input capture */
  timer_ic_set_input(TIM4, TIM_IC3, TIM_IC_IN_TI3);
  timer_ic_set_polarity(TIM4, TIM_IC3, TIM_IC_RISING);
  timer_ic_enable(TIM4, TIM_IC3);

  /* Enable IRQ for channel 4 of TIM4 an channel 2 of TIM2*/
  timer_enable_irq(TIM2, TIM_DIER_CC2IE);
  timer_enable_irq(TIM4, TIM_DIER_CC3IE);

  /** Real Time Clock (independant from TIM1) **/

  /* if TIM1 is set to 1.25MHz:
   * set TIM6 to period = 4, prescaler = 5250  => 8kHz output clock (= 125µs)
   *
   * if TIM1 is set to 8kHz:
   * set TIM6 to period = 276, prescaler= 46874 => 51.2Hz
   * to keep the ratio
   *
   * if TIM1 is set to 1kHz:
   * set TIM6 to period = 256, prescaler = 9999 => 6.4Hz
   */
  timer_set_period(TIM7, 4);
  timer_set_prescaler(TIM7, 5250);
  timer_enable_irq(TIM7, TIM_DIER_UIE); // This call kills the USBUART

  /*
   * timer 5 should just run and count up.
   * Its counter is only read to measure the runtime of code e.g. all the ISRs
   */
  timer_disable_irq(TIM5, TIM_DIER_UIE);

  /*
   * Bacause TIM1 is the master/input signal for these three timers
   *  they can be activated now but will only be active when TIM1 is started
   */
  timer_enable_counter(TIM2);
  timer_enable_counter(TIM3);
  timer_enable_counter(TIM4);
}

static void hal_priv_gpio_setup() {
  /** Input Pins **/

  /*
   * PB8 is TIM4_CH3 input
   * Triggers PrimaryRPMISR
   *
   * PA1 is TIM2_CH2 input
   * Triggers SecondaryRPMISR
   */

  rcc_periph_clock_enable(RCC_GPIOA);
  gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO1);
  gpio_set_af(GPIOA, GPIO_AF1, GPIO1);

  rcc_periph_clock_enable(RCC_GPIOB);
  gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO8);
  gpio_set_af(GPIOB, GPIO_AF2, GPIO8);

  /** Output Pins **/

  /*
   * PB4 is TIM3_CH1 output
   * Triggers Injector1ISR
   *
   * PB5 is TIM3_CH2 output
   * Triggers Injector2ISR
   *
   * PB0 is TIM3_CH3 output
   * Triggers Injector3ISR
   *
   * PB1 is TIM3_CH4 output
   * Triggers Injector4ISR
   *
   * PB6 is TIM4_CH1 output
   * Triggers Injector5ISR
   *
   * PB7 is TIM4_CH2 output
   * Triggers Injector6ISR
   */

  //rcc_periph_clock_enable(RCC_GPIOB);

  gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO4);
  gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO5);
  gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO0);
  gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO1);
  gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO6);
  gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO7);

  gpio_set_output_options(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, GPIO4);
  gpio_set_output_options(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, GPIO5);
  gpio_set_output_options(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, GPIO0);
  gpio_set_output_options(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, GPIO1);
  gpio_set_output_options(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, GPIO6);
  gpio_set_output_options(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, GPIO7);

  gpio_set_af(GPIOB, GPIO_AF2, GPIO4);
  gpio_set_af(GPIOB, GPIO_AF2, GPIO5);
  gpio_set_af(GPIOB, GPIO_AF2, GPIO0);
  gpio_set_af(GPIOB, GPIO_AF2, GPIO1);
  gpio_set_af(GPIOB, GPIO_AF2, GPIO6);
  gpio_set_af(GPIOB, GPIO_AF2, GPIO7);

  // init GPIO pins for ignition
  rcc_periph_clock_enable(RCC_GPIOC);
  gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO1);
  gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO2);
  gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO3);
  gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO4);
  gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
  gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO6);
  gpio_set_output_options(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, GPIO1);
  gpio_set_output_options(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, GPIO2);
  gpio_set_output_options(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, GPIO3);
  gpio_set_output_options(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, GPIO4);
  gpio_set_output_options(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, GPIO5);
  gpio_set_output_options(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, GPIO6);
}

static void hal_priv_isr_setup() {
  nvic_enable_irq(NVIC_TIM2_IRQ); /* enable TIM2 interrupt */
  nvic_enable_irq(NVIC_TIM3_IRQ); /* enable TIM3 interrupt */
  nvic_enable_irq(NVIC_TIM4_IRQ); /* enable TIM4 interrupt */
  nvic_enable_irq(NVIC_TIM5_IRQ); /* enable TIM5 interrupt */
  nvic_enable_irq(NVIC_TIM7_IRQ); /* enable TIM6 interrupt */
}

void hal_system_clock(void) {
  /*
   * Set STM32 to 168 MHz.
   * Also change the frequency of AHB1/APB1 to 168MHz by setting the prescaler
   * to 0. This means all timers on AHB1/APB1 that are driven by the internal
   * clock signal (CK_INT) will run at 168MHz. Default is 42MHz.
   * This will only affect TIM5 and TIM6.
   * TIM2, TIM3 and TIM4 are not affected because they are driven by the signal
   * of TIM1.
   * For more information on which devices are affected see refman page 18.
   *
   */
  clock_scale_t myConfig = hse_8mhz_3v3[CLOCK_3V3_168MHZ];
  myConfig.ppre1 = RCC_CFGR_PPRE_DIV_NONE;
  rcc_clock_setup_hse_3v3(&myConfig);
}

void hal_system_init(void) {
  hal_priv_timer_setup();
  hal_priv_gpio_setup();
  hal_priv_isr_setup();
}

void hal_system_start(void) {
  timer_enable_counter(TIM7); /* TIM5 is slower than TIM1 therefore it is started before */
  timer_enable_counter(TIM1);
  timer_enable_counter(TIM5);
}
