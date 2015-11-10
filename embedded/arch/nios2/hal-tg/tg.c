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
 * $Id: tg.c 512 2015-11-10 15:29:05Z meixnean $
 * @file tg.c
 * @brief Implementation of trace generation HAL
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#include <hal/tg/tg.h>
#include <hal/log.h>

#include <arch/nios2/intrinsics.h>
#include <arch/nios2/io.h>
#include <driver/scct.h>
#include <driver/board.h>
#include <driver/uart.h>
#include <output.h>
#include <spr-defs.h>


#define	SPEED_NORMAL 1
#define SPEED_SLOW   2

#if defined(__SPEED__fast)
#define SPEED SPEED_NORMAL
#elif defined (__SPEED__slow)
#define SPEED SPEED_SLOW
#else
#define SPEED = SPEED_NORMAL
#endif

#if SPEED == SPEED_NORMAL
#define TCPRESCALER 39
#elif SPEED == SPEED_SLOW
#define TCPRESCALER 3999 // this value has to be checked
#else
#error "SPEED" defined in config.h was set neither SPEED_NORMAL nor SPEED_SLOW
#endif


#define SET_FLAGS32(base_adress, offset, bitmask) { uint32_t register_content = IORD32(base_adress, offset); register_content |= bitmask; IOWR32(base_adress, offset, register_content); }
#define DELETE_FLAGS32(base_adress, offset, bitmask) { uint32_t register_content = IORD32(base_adress, offset); register_content &= ~bitmask; IOWR32(base_adress, offset, register_content); }

#define PRIMARY_CHANNEL_MASK 0x1
#define SECONDARY_CHANNEL_MASK 0x1 << 1

void hal_tg_setup() {
  debug_printf("setting up hal.\r\n");

  // start the interrupt system of nios2
  uint32_t sr = __rdctl_status();
  sr |= SPR_SR_PIE;
  __wrctl_status(sr);

  // tell the NIOS processor to enable the interrupt for the scct
  uint32_t interruptFlags = __rdctl_ienable();
  interruptFlags |= IRQ_SCCT_BIT;
  __wrctl_ienable(interruptFlags);

  // init scct to a frequency of 1.25MHz SPEED_NORMAL or a slower custom
  // frequency SPEED_SLOW
  IOWR32(A_SCCT, SCCT_PSC, TCPRESCALER);

  // init primary and secondary channel
  // set mode as OC
  IOWR32(A_SCCT, SCCT_CH_MS, SCCT_CH_MODE_OC(0) | SCCT_CH_MODE_OC(1));
}

uint32_t nextTime = 0;
void hal_tg_run() {
  debug_printf("starting tg.\r\n");
  log_printf("starting tg.\r\n");
  // start the timer(s)
  IOWR32(A_SCCT, SCCT_CH_IE, 0x3);//SCCT_CH_BITS_1(1,0) | SCCT_CH_BITS_1(1,1));
  // start output, by setting the first primary signal to occure in ... ticks.
  hal_tg_set_primary_time(hal_tg_get_time()+30,OC_MODE_ON);
  // just idle in a while loop
  while(1)
    { }
  debug_printf("oops.\r\n");
}


void hal_tg_notify_finished() {
  DELETE_FLAGS32(A_SCCT, SCCT_CTR_IE, PRIMARY_CHANNEL_MASK | SECONDARY_CHANNEL_MASK);
  debug_printf("tg finished.\r\n");
  log_printf("tg finished.\r\n");
}


#define SET_ACTION(channelNumber, mode) {switch(mode){\
  case OC_MODE_NONE:\
    IOWR32(A_SCCT, SCCT_CH_AS, (IORD32(A_SCCT, SCCT_CH_AS) & ~(0x3<<(channelNumber*2))) | SCCT_OC_NONE<<(channelNumber*2));\
    break;\
  case OC_MODE_ON:\
    IOWR32(A_SCCT, SCCT_CH_AS, (IORD32(A_SCCT, SCCT_CH_AS) & ~(0x3<<(channelNumber*2))) | SCCT_OC_HIGH<<(channelNumber*2));\
    break;\
  case OC_MODE_OFF:\
    IOWR32(A_SCCT, SCCT_CH_AS, (IORD32(A_SCCT, SCCT_CH_AS) & ~(0x3<<(channelNumber*2))) | SCCT_OC_LOW<<(channelNumber*2));\
    break;\
  case OC_MODE_TOGGLE:\
    IOWR32(A_SCCT, SCCT_CH_AS, (IORD32(A_SCCT, SCCT_CH_AS) & ~(0x3<<(channelNumber*2))) | SCCT_OC_TOGGLE<<(channelNumber*2));\
    break;\
  }\
}

void hal_tg_set_primary_time(timctr_t time, oc_mode_t mode) {
  // set the time when the primary channel has to change to the given mode
  // (high/low)

  // set mode as new OC mode (high/low)
  SET_ACTION(0, mode);
  // set time as new OC time
  // the new time is given as 16 bit value, so to set the time correctly the
  //following calculation has to be done
  // case 1: if the new time (16 bit value) is bigger than the two low bytes of
  //         the current counter value the new 32 bit timer value has to be
  //         calculated
  // case 2: if the new time is smaller than the two low bytes of the current
  //         counter value then the new time must be the two high bytes of the
  //         current counter value plus one, followed by the new time
  // NOTE: THE NEW TIME IS AN ABSOLUTE VALUE, NOT AN INCREMENT TO CURRENT TIME.
  uint32_t counterValue = IORD32(A_SCCT, SCCT_CTR);
  // new time is upper two bytes of current time followed by the two bytes
  // representing the new time
  uint32_t newTimeValue = (counterValue & 0xFFFF0000) | time;
  // in case the new time is new time is smaller than the lower two bytes of our
  // 32 bit counter value
  // we have to add 1 to the upper two bytes of the new 32 bit OC time.
  // this can be seen as simulating the timer overflow of a 16 bit timer.
  if((counterValue & 0x0000FFFF) > time) {
    newTimeValue += 0x00010000;
  }
  IOWR32(A_SCCT, SCCT_CH_CCR0, newTimeValue);
}


void hal_tg_set_secondary_time(timctr_t time, oc_mode_t mode) {
  // set the time when the secondary channel has to change to the given mode
  // (high/low)

  // set mode as new OC mode (high/low)
  SET_ACTION(1, mode);
  // set time as new OC time
  // the new time is given as 16 bit value, so to set the time correctly the
  // following calculation has to be done
  // case 1: if the new time (16 bit value) is bigger than the two low bytes of
  //         the current counter value the new 32 bit timer value has to be
  //         calculated
  // case 2: if the new time is smaller than the two low bytes of the current
  //         counter value then the new time must be the two high bytes of the
  //         current counter value plus one, followed by the new time
  // NOTE: THE NEW TIME IS AN ABSOLUTE VALUE, NOT AN INCREMENT TO CURRENT TIME.
  uint32_t counterValue = IORD32(A_SCCT, SCCT_CTR);
  // new time is upper two bytes of current time followed by the two bytes
  // representing the new time
  uint32_t newTimeValue = (counterValue & 0xFFFF0000) | time;
  // in case the new time is new time is smaller than the lower two bytes of our
  // 32 bit counter value
  // we have to add 1 to the upper two bytes of the new 32 bit OC time.
  // this can be seen as simulating the timer overflow of a 16 bit timer.
  if((counterValue & 0x0000FFFF) > time) {
    newTimeValue += 0x00010000;
  }
  IOWR32(A_SCCT, SCCT_CH_CCR1, newTimeValue);
}


void hal_tg_advance_primary_time(timctr_t adv, oc_mode_t mode) {
  // similar to hal_tg_set_primary_time but here the new time is calculated by
  // adding adv to the time currently set as oc time
  // get current OC time
  uint16_t newTime = IORD16(A_SCCT, SCCT_CH_CCR0);
  // add adv
  newTime += adv;
  // set new time and mode
  hal_tg_set_primary_time(newTime, mode);
}


void hal_tg_advance_secondary_time(timctr_t adv, oc_mode_t mode) {
  // similar to hal_tg_set_secondary_time but here the new time is calculated by
  // adding adv to the time currently set as oc time
  // get current OC time
  uint16_t newTime = IORD16(A_SCCT, SCCT_CH_CCR1);
  // add adv
  newTime += adv;
  // set new time and mode
  hal_tg_set_secondary_time(newTime, mode);
}


timctr_t hal_tg_get_primary_time() {
  //get current OC time
  uint16_t time = IORD16(A_SCCT, SCCT_CH_CCR0);
  return time;
}


timctr_t hal_tg_get_secondary_time() {
  //get current OC time
  uint16_t time = IORD32(A_SCCT, SCCT_CH_CCR1);
  return time;
}


timctr_t hal_tg_get_time() {
  // get current time of the timer that drives the OC channels
  uint16_t time = IORD16(A_SCCT, SCCT_CTR);
  return time;
}


void do_irq() {

  uint32_t irqFlags = __rdctl_ipending();
  if(irqFlags & IRQ_SCCT_BIT) {
    uint32_t ocFlags = IORD32(A_SCCT, SCCT_CH_IS);
    if(ocFlags & PRIMARY_CHANNEL_MASK) {
      // clear flags
      IOWR32(A_SCCT, SCCT_CH_IS, 0x1);
      // get current pin state
      int32_t pinState = (IORD32(A_SCCT, SCCT_CH_OUT) & PRIMARY_CHANNEL_MASK) != 0;
      // call handle_primary
      handle_primary(pinState);
    }
    if(ocFlags & SECONDARY_CHANNEL_MASK) {
      // clear flags
      IOWR32(A_SCCT, SCCT_CH_IS, 0x2);
      // get current pin state
      int32_t pinState = (IORD32(A_SCCT, SCCT_CH_OUT) & SECONDARY_CHANNEL_MASK) != 0;
      // call handle_secondary
      handle_secondary(pinState);
    }
  }
}


void exception_handle() {
  debug_printf("exception.\r\nb");
}

