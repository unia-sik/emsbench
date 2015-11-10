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
 * $Id: tg.c 502 2015-11-05 14:18:19Z klugeflo $
 * @file tg.c
 * @brief Implementation of trace generation HAL
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#include <hal/tg/tg.h>
//#define __DEBUG__
#include <hal/log.h>

#include <stdbool.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencmsis/core_cm3.h>

#define	SPEED_NORMAL 1
#define SPEED_SLOW   2

#define LED  1
#define PORT 2

#define OUTPUT PORT
#define SPEED SPEED_NORMAL


#if OUTPUT == LED
#define TCPORTRCC RCC_GPIOD
#define TCPORT GPIOD
#define TC1PIN GPIO12
#define TC2PIN GPIO13
#elif OUTPUT == PORT
#define TCPORTRCC RCC_GPIOB
#define TCPORT GPIOB
#define TC1PIN GPIO6
#define TC2PIN GPIO7
#else
#error "OUTPUT" defined in config.h was set neither LED nor PORT
#endif

#if SPEED == SPEED_NORMAL
#define TCPERIOD 1
#define TCPRESCALER 66
#elif SPEED == SPEED_SLOW
#define TCPERIOD 19
#define TCPRESCALER 66
#else
#error "SPEED" defined in config.h was set neither SPEED_NORMAL nor SPEED_SLOW
#endif


static bool finished = false;


static void gpio_setup(void) {
  rcc_periph_clock_enable(TCPORTRCC);

  gpio_mode_setup(TCPORT, GPIO_MODE_AF, GPIO_PUPD_NONE, TC1PIN);
  gpio_mode_setup(TCPORT, GPIO_MODE_AF, GPIO_PUPD_NONE, TC2PIN);

  gpio_set_output_options(TCPORT, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, TC1PIN);
  gpio_set_output_options(TCPORT, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, TC2PIN);

  gpio_set_af(TCPORT, GPIO_AF2, TC1PIN);
  gpio_set_af(TCPORT, GPIO_AF2, TC2PIN);
}

static void tim_setup(void) {
  rcc_periph_clock_enable(RCC_TIM1);
  rcc_periph_clock_enable(RCC_TIM4);

  timer_reset(TIM1);
  timer_reset(TIM4);

  timer_set_mode(TIM1, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
  timer_set_mode(TIM4, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

  timer_set_master_mode(TIM1, TIM_CR2_MMS_UPDATE);
  timer_set_oc_mode(TIM1, TIM_OC1, TIM_OCM_FROZEN);

  timer_slave_set_trigger(TIM4, TIM_SMCR_TS_ITR0);
  timer_slave_set_mode(TIM4, TIM_SMCR_SMS_ECM1);

  timer_set_prescaler(TIM1, TCPRESCALER);
  timer_set_period(TIM1, TCPERIOD);

  timer_set_oc_mode(TIM4, TIM_OC1, TIM_OCM_FROZEN);
  timer_set_oc_mode(TIM4, TIM_OC2, TIM_OCM_FROZEN);

  timer_enable_irq(TIM4, TIM_DIER_CC1IE | TIM_DIER_CC2IE);

  timer_generate_event(TIM4, TIM_EGR_UG);

  timer_set_counter(TIM4, 0);

  timer_enable_oc_output(TIM4, TIM_OC1);
  timer_enable_oc_output(TIM4, TIM_OC2);
  timer_enable_counter(TIM4);
}

static void nvic_init() {
  nvic_enable_irq(NVIC_TIM4_IRQ);
}


void TIM4_IRQHandler(void) {
  if (timer_interrupt_source(TIM4, TIM_SR_CC1IF)) {
    timer_clear_flag(TIM4, TIM_SR_CC1IF);
    handle_primary(gpio_get(TCPORT, TC1PIN)!=0);
  }

  if (timer_interrupt_source(TIM4, TIM_SR_CC2IF)) {
    timer_clear_flag(TIM4, TIM_SR_CC2IF);
    handle_secondary(gpio_get(TCPORT, TC2PIN)!=0);
  }
}


void hal_tg_setup() {
  gpio_setup();
  tim_setup();
  nvic_init();
  rcc_periph_clock_enable(RCC_GPIOD);

  usbuart_init(); // Initialise vitual uart usb device
  usbuart_wait(); // Wait for keypress on virtual uart
  log_printf("Hello World from hal_tg_setup!\n");
}


void hal_tg_run() {
  debug_printf("HAL-TG run\n");
  // TODO: set 1st primary!
  hal_tg_set_primary_time(1, OC_MODE_ON);
  timer_enable_counter(TIM1);
  while (!finished) {
  }
  while(1) {
    ;
  }
}


void hal_tg_notify_finished() {
  debug_printf("HAL-TG finished\n");
  finished = true;
  timer_disable_irq(TIM4, TIM_DIER_CC1IE | TIM_DIER_CC2IE);
}


void hal_tg_set_primary_time(timctr_t time, oc_mode_t mode) {
  timer_set_oc_value(TIM4, TIM_OC1, time);
  timer_set_oc_mode(TIM4, TIM_OC1, mode);
  debug_printf("T1 set to %u, mode %d\n", time, mode);
}


void hal_tg_set_secondary_time(timctr_t time, oc_mode_t mode) {
  timer_set_oc_value(TIM4, TIM_OC2, time);
  timer_set_oc_mode(TIM4, TIM_OC2, mode);
  debug_printf("T2 set to %u, mode %d\n", time, mode);
}


void hal_tg_advance_primary_time(timctr_t adv, oc_mode_t mode) {
  timer_set_oc_value(TIM4, TIM_OC1, (TIM4_CCR1 + adv));
  timer_set_oc_mode(TIM4, TIM_OC1, mode);
  debug_printf("T1 advance by %u to %u, mode %d\n", adv, TIM4_CCR1, mode);
}


void hal_tg_advance_secondary_time(timctr_t adv, oc_mode_t mode) {
  timer_set_oc_value(TIM4, TIM_OC2, (TIM4_CCR2 + adv));
  timer_set_oc_mode(TIM4, TIM_OC2, mode);
  debug_printf("T2 advanced by %u to %u, mode %d\n", adv, TIM4_CCR2, mode);
}


timctr_t hal_tg_get_primary_time() {
  return TIM4_CCR1;
}


timctr_t hal_tg_get_secondary_time() {
  return TIM4_CCR2;
}


timctr_t hal_tg_get_time() {
  return TIM4_CNT;
}
