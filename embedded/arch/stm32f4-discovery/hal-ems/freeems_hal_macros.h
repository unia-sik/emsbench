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
 * $Id: freeems_hal_macros.h 502 2015-11-05 14:18:19Z klugeflo $
 * @brief Various macros used by the HAL.
 * @file freeems_hal_macros.h
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#ifndef FILE_FREEEMS_HAL_MACROS_H_SEEN
#define FILE_FREEEMS_HAL_MACROS_H_SEEN

#include <hal/ems/hal_io_oc.h>
#include <hal/ems/hal_logging.h>

/**
 * Defines handler for unused timer interrupt sources
 *
 * \param timer The timer component (TIM1, TIM2, etc.)
 * \param flag The timer status flag (TIM_SR_UIF, TIM_SR_CC1IF, ...)
 */
#define IRQ_INVALID(timer, flag)                                       \
  {if (timer_interrupt_source(timer, flag)){                           \
    log_printf(#timer "_IRQHandler invalid interrupt! " #timer         \
               "_SR=%x " #timer "_DIER=%x\r\n",                        \
               timer ## _SR, timer ## _DIER);                          \
    timer_clear_flag(timer, flag);                                     \
  }}

/**
 * Defines handler for used timer interrupt sources
 *
 * \param timer The timer component (TIM1, TIM2, etc.)
 * \param flag The timer status flag (TIM_SR_UIF, TIM_SR_CC1IF, ...)
 * \param time The timer value, used for logging purposes
 * \param program The program code of the interrupt handler
 */
#define IRQ_HANDLE(timer, flag, time, program)                         \
  if (timer_interrupt_source(timer, flag)){                            \
    timer_clear_flag(timer, flag);                                     \
    {program};                                                         \
  }

/**
 * Activates/Deactivates interrupt and output of the output compare
 * timer.
 *
 * \param timer_peripheral The timer component (TIM1, TIM2, etc.)
 * \param channr The timer channel number (1, 2, 3 or 4)
 * \param value A boolean value (true: enable, false: disable)
 */
#define OC_ACTIVE_SET(timer_peripheral, channr, value)                 \
  { if(value){TIM_SR(timer_peripheral)&=~TIM_SR_CC ## channr ## IF;}   \
	TIM_DIER(timer_peripheral) =                                       \
     (TIM_DIER(timer_peripheral) & ~TIM_DIER_CC ## channr ## IE) |     \
       (value ? TIM_DIER_CC ## channr ## IE : 0x0);                    \
    TIM_CCER(timer_peripheral) =                                       \
     (TIM_CCER(timer_peripheral) & ~TIM_CCER_CC ## channr ## E) |      \
       (value ? TIM_CCER_CC ## channr ## E : 0x0); 			\
   }

/**
 *  Set output mode of the output compare timer.
 *
 * \param timer_peripheral The timer component (TIM1, TIM2, etc.)
 * \param regnr The CCMR register number of the assoziated channel
 *              (1 or 2)
 * \param channr The timer channel number (1, 2, 3 or 4)
 * \param value The output compare mode identifier (0: disabled,
 *              1: toggle output, 2: switch to low, 3: switch to high)
 */
#define OC_MODE_SET(timer_peripheral, regnr, channr, value)            \
  { TIM_CCMR ## regnr (timer_peripheral) =                             \
     (TIM_CCMR ## regnr (timer_peripheral) &                           \
      ~TIM_CCMR ## regnr ## _OC ## channr ## M_MASK) |                 \
        ((value == 3) ?                                              \
         TIM_CCMR ## regnr ## _OC ## channr ## M_ACTIVE :              \
         ((value == 2) ?                                             \
          TIM_CCMR ## regnr ## _OC ## channr ## M_INACTIVE :           \
          ((value == 1) ?                                            \
           TIM_CCMR ## regnr ## _OC ## channr ## M_TOGGLE :            \
           TIM_CCMR ## regnr ## _OC ## channr ## M_FROZEN)));          \
   TIM_CCER(timer_peripheral) =                                        \
    (TIM_CCER(timer_peripheral) & ~TIM_CCER_CC ## channr ## E) |       \
    ((value > 0x0 && value <= 0x3) ? TIM_CCER_CC ## channr ## E : 0x0);}

/**
 * Set the interval value of the periodic timer.
 *
 * \param timer The timer component (TIM1, TIM2, etc.)
 * \param channr The timer channel number (1, 2, 3 or 4)
 * \param value The interval value
 */
#define PIT_INTERVAL_SET(timer, channr, value)                         \
    { if (timer ## _DIER & TIM_DIER_CC ## channr ## IE) {\
        timer ## _CCR ## channr ## _NEXT = timer ## _CCR ## channr     \
                                           + (uint16_t)(value);        \
        timer ## _CCR ## channr ## _SET = 1; } else {                  \
        timer ## _CCR ## channr = (uint16_t)(timer ## _CNT + value); \
} }

/**
 * Activates/Deactivates interrupt of the periodic interrupt timer.
 *
 * \param timer The timer component (TIM1, TIM2, etc.)
 * \param channr The timer channel number (1, 2, 3 or 4)
 * \param value A boolean value (true: enable, false: disable)
 */
#define PIT_ACTIVE_SET(timer, channr, value)                           \
    {TIM_DIER(timer) =                                                \
       (TIM_DIER(timer) & ~TIM_DIER_CC ## channr ## IE) |              \
         (value ? TIM_DIER_CC ## channr ## IE : 0x0); 			\
     }

/**
 * Wraps all instructions needed for the periodic timers in one macro.
 *
 * \param timer The timer component (TIM1, TIM2, etc.)
 * \param channr The timer channel number (1, 2, 3 or 4)
 */
#define PIT_IRQ_WRAPPER(timer, channr)                                 \
    { if (timer ## _CCR ## channr ## _SET) {                           \
        timer ## _CCR ## channr ## _LAST = timer ## _CCR ## channr;    \
        timer ## _CCR ## channr = timer ## _CCR ## channr ## _NEXT;    \
        timer ## _CCR ## channr ## _SET = 0; } else {                  \
        uint16_t tmp = timer ## _CCR ## channr;                        \
        timer ## _CCR ## channr = (uint16_t)(                          \
          (timer ## _CCR ## channr << 1) -                             \
          timer ## _CCR ## channr ## _LAST);                           \
        timer ## _CCR ## channr ## _LAST = tmp; } }


/*
* Wraps all instructions needed for the periodic timers in one macro.
*
* \param timer : timer prefix (TIM2, TIM3, ...)
* \param channr : timer channel number
*/
#define PERIODIC_TIMER_WRAPPER(timer, channr)                          \
    { if (timer ## _CCR ## channr ## _SET) {                           \
        timer ## _CCR ## channr ## _LAST = timer ## _CCR ## channr;    \
        timer ## _CCR ## channr = timer ## _CCR ## channr ## _NEXT;    \
        timer ## _CCR ## channr ## _SET = 0; } else {                  \
        uint16_t tmp = timer ## _CCR ## channr;                        \
        timer ## _CCR ## channr = (uint16_t)(                          \
          (timer ## _CCR ## channr << 1) - timer ## _CCR ## channr ## _LAST); \
        timer ## _CCR ## channr ## _LAST = tmp; } }


/*
 * Converts TIM_CCMR and TIM_CCER of STM32 to S12X TCTL register.
 *
 * \param timer : timer prefix (TIM2, TIM3, ...)
 * \param regnr : number of TIM_CCMR register for timer
 * \param channr : timer channel number
 * \returns not shifted (normalized) TCTL value
 *          (one of those: 0x0, 0x1, 0x2 or 0x3)
 */
#define TO_TCTL(timer, regnr, channr)                                              \
    ((((timer ## _CCMR ## regnr & TIM_CCMR ## regnr ## _OC ## channr ## M_MASK)    \
         == TIM_CCMR ## regnr ## _OC ## channr ## M_ACTIVE &&                      \
         (timer ## _CCER & TIM_CCER_CC ## channr ## E) != 0) ? 0x3 :               \
      (((timer ## _CCMR ## regnr & TIM_CCMR ## regnr ## _OC ## channr ## M_MASK)   \
         == TIM_CCMR ## regnr ## _OC ## channr ## M_INACTIVE &&                    \
         (timer ## _CCER & TIM_CCER_CC ## channr ## E) != 0) ? 0x2 :               \
       (((timer ## _CCMR ## regnr & TIM_CCMR ## regnr ## _OC ## channr ## M_MASK)  \
         == TIM_CCMR ## regnr ## _OC ## channr ## M_TOGGLE &&                      \
         (timer ## _CCER & TIM_CCER_CC ## channr ## E) != 0) ? 0x1 : 0x0))))

/*
 * Converts TCTL value of S12X to STM32 TIM_CCMR register
 *
 * \param regnr : number of TIM_CCMR register for timer
 * \param channr : timer channel number
 * \param tctl_value : normalized tctl_value
 *                     (one of those: 0x0, 0x1, 0x2 or 0x3)
 * \returns TIM_CCMR value for this timer and channel
 */
#define TO_CCMR(regnr, channr, tctl_value)                                     \
    ((tctl_value == 0x3) ? TIM_CCMR ## regnr ## _OC ## channr ## M_ACTIVE :    \
     ((tctl_value == 0x2) ? TIM_CCMR ## regnr ## _OC ## channr ## M_INACTIVE : \
      ((tctl_value == 0x1) ? TIM_CCMR ## regnr ## _OC ## channr ## M_TOGGLE :  \
       TIM_CCMR ## regnr ## _OC ## channr ## M_FROZEN)))

/*
 * Converts TCTL value of S12X to STM32 TIM_CCER register
 *
 * \param channr : timer channel number
 * \param tctl_value : normalized tctl_value
 *                     (one of those: 0x0, 0x1, 0x2 or 0x3)
 * \returns TIM_CCER value for this timer and channel
 */
#define TO_CCER(channr, tctl_value)                           \
    ((tctl_value != 0x0) ? TIM_CCER_CC ## channr ## E : 0x0)

/*
 * Wraps the instructions needed to set the periodic timer for the next
 * interrupt.
 *
 * \param timer : timer prefix (TIM2, TIM3, ...)
 * \param channr : timer channel number
 * \param value : the time until the timer is called next time
 */
#define PERIODIC_TIMER_SET(timer, channr, value)                       \
    { if (timer ## _DIER & TIM_DIER_CC ## channr ## IE) {              \
        timer ## _CCR ## channr ## _NEXT = timer ## _CCR ## channr + (uint16_t)(value); \
        timer ## _CCR ## channr ## _SET = 1; } else {                  \
        timer ## _CCR ## channr = (uint16_t)(timer ## _CNT + value); } }

#endif /* FILE_FREEEMS_HAL_MACROS_H_SEEN */
