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
 * $Id: tracegen.c 502 2015-11-05 14:18:19Z klugeflo $
 * @file tracegen.c
 * @brief Trace generation for emsbench
 * @author Florian Kluge <kluge@informatik.uni-augsburg.de>
 */

#include <stdbool.h>
#include <stdint.h>

#include <hal/hal.h>
#include <hal/log.h>
#include <hal/tg/tg.h>

#include <tg/tgdata.h>


/**
 * arm-none-eabi does not comprise libm with hard-float support, so we have
 * to provide our own sqrtf implementation.
 */
extern float sqrtf(float);


/**
 * Initialise TG status
 */
void init_tg(void);

/**
 * Does all the work.
 */
void perform_primary_calculations(void);


/**
 * @brief Current state of the trace generator.
 * Data stored in this struct relates to next primary signal to occur.
 */
typedef struct {
  /**
   * @brief Initial angular velocity of current subphase.
   */
  float omega_0;
  /**
   * @brief Initial angle of current subphase.
   * @todo Remove, no longer used
   */
  float phi_0;
  /**
   * @brief Duration of the current subphase.
   * This number is used to advance #tg_state_t::omega_0 on
   * renormalisation and phase change.
   */
  float duration_subphase;

  float t_cur; ///< time of next ISR
  float t_last; ///< time of last ISR (only needed temporarily during #perform_primary_calculations)
  float phi; ///< phi of next ISR
  /**
   * @brief Time offset for current subphase.
   * This variable is usually 0. It has only a meaning, if a phase change
   * occurred between two renormalisations. At the phase change, time is reset
   * to 0 to simplify calculations (and omit the phi_0 variable). For actual
   * IRQ release times, a positive offset must be added until the next
   * renormalisation.
   */
  float t_0; ///< time offset, required for phase change

  size_t subphase_ctr; ///< count teeth of current subphase, reset after one revolution

  size_t phase; ///< number of current phase (indexes #PHASES)
  float duration_phase; ///< duration of the current phase so far @todo maybe can be removed

  float stat_delta_t; ///< stores time differences between planned and actual phase change
  size_t stat_n_delta_t; ///< stores number of phase changes
} tg_state_t;


tg_state_t tgs;

int main() {
  hal_init();
  hal_tg_setup();

  debug_printf("N_P: %lu OM_I: %f D_P: %f O_S: %f\n",
               N_PHASES, OMEGA_IDLE, DIST_PRIMARY, OFFSET_SECONDARY);

  init_tg();

  hal_tg_run();
  return 0;
}


void init_tg(void) {
  tgs.omega_0 = OMEGA_IDLE;
  tgs.phi_0 = 0.0;
  tgs.duration_subphase = 0;

  tgs.t_cur = 0;
  tgs.t_last = 0;
  tgs.phi = 0;

  tgs.subphase_ctr = 0;
  tgs.t_0 = 0.0;

  tgs.phase = 0;
  tgs.duration_phase = 0;

  tgs.stat_delta_t = 0.0;
  tgs.stat_n_delta_t = 0;
}


void handle_primary(bool state) {
  if (state) {
    // pin was driven to high, so simply set timer for switch to low
    debug_printf("1 ON @ %u\n", hal_tg_get_time());
    hal_tg_advance_primary_time(TG_HIGH_TIME, OC_MODE_OFF);
  }
  else {
    // pin was driven to low, now calculate time for next impulse
    debug_printf("1 OFF @ %u\n", hal_tg_get_time());
    //set_primary_time(1000, STATUS_ON);
    perform_primary_calculations();
  }
}

void handle_secondary(bool state) {
  if (state) {
    // switched on, so set switch-off time
    debug_printf("2 ON @ %u\n", hal_tg_get_time());
    hal_tg_advance_secondary_time(TG_HIGH_TIME, OC_MODE_OFF);
  }
  else {
    // dow nothing, switch-on time is calculated by primary
    //set_secondary_time(2000, STATUS_ON);
    debug_printf("2 OFF @ %u\n", hal_tg_get_time());
  }
}


void perform_primary_calculations(void) {
  // use old alpha in sub/phase changes
  float alpha = PHASES[tgs.phase].alpha;


  // happen after each revolution if tooth_0 was released again
  if (tgs.subphase_ctr == N_PRIMARY) {
    // renormalise after one revolution
    tgs.omega_0 += tgs.duration_subphase * alpha;
    tgs.t_cur= 0;
    tgs.phi_0 = 0;
    tgs.phi = 0;
    tgs.duration_subphase = 0;
    tgs.subphase_ctr = 0;
    tgs.t_0 = 0.0;
    debug_printf("\tRenormalised, om_0: %f\n", tgs.omega_0);
  }

  // may happen on any tooth
  if (tgs.duration_phase > PHASES[tgs.phase].duration) {
    debug_printf("\tPhase switch %lu\n", tgs.phase);
    // next phase
    // store error
    tgs.stat_delta_t += tgs.duration_phase - PHASES[tgs.phase].duration;
    ++tgs.stat_n_delta_t;
    // switch
    tgs.omega_0 += tgs.duration_subphase * alpha;
    //tgs.phi_0 = tgs.phi;
    tgs.phi = 0;

    ++tgs.phase;
    tgs.t_0 = tgs.t_cur;

    if (tgs.phase >= N_PHASES) {
      log_printf("No more input data, finishing...\n");
      //finished = true;
      hal_tg_notify_finished();
      return;
    }
    else {
      debug_printf("\t, new alpha: %f, omega_0: %f t_0: %f\n", PHASES[tgs.phase].alpha, tgs.omega_0, tgs.t_0);
      tgs.duration_phase = 0;
      tgs.duration_subphase = 0;
    }
  }

  // now read new alpha
  alpha = PHASES[tgs.phase].alpha;

  tgs.t_last = tgs.t_cur;
  tgs.phi += DIST_PRIMARY;
  ++tgs.subphase_ctr;

  float t_off = 0.0;

  if (alpha == 0) { // strict comparison is valid, as \alpha is set directly to 0 without any rounding errors.
    t_off = (tgs.phi /*- tgs.phi_0*/) / tgs.omega_0;
  }
  else {
    float d = tgs.omega_0 * tgs.omega_0 - 2 * alpha * (/*tgs.phi_0*/ - tgs.phi);
    if (d < 0) {
      debug_printf("D = %f < 0!!!\n", d);
      //log_printf("om_0=%f alpha=%f phi=%f\n", tgs.omega_0, alpha, tgs.phi);
      hal_abort();
    }
    t_off = (-tgs.omega_0 + sqrtf(d)) / alpha;
  }

  tgs.t_cur = tgs.t_0 + t_off;

  /// @todo calculate timer value
  float interval_prim = tgs.t_cur - tgs.t_last;
  tgs.duration_phase += interval_prim;
  tgs.duration_subphase += interval_prim;
  debug_printf("t_next: %f (I: %f om: %f phi: %f t_off: %f)\n", tgs.t_cur, interval_prim, tgs.omega_0 + alpha*tgs.duration_subphase, tgs.phi, t_off);

  /*
  timctr_t tim_l_prim = get_last_primary();
  timctr_t tim_prim = tim_l_prim + interval_prim * TICKS_PER_SECOND;
  set_next_primary(tim_prim);
  */

  /*
  set_next_primary(interval_prim * TICKS_PER_SECOND - HIGH_TIME);
  log_printf("\tthe_prim: %u\n", the_primary);
  */
  timctr_t tim_last_prim = hal_tg_get_primary_time();
  timctr_t tim_interval_prim = interval_prim * TICKS_PER_SECOND - TG_HIGH_TIME;
  hal_tg_advance_primary_time(tim_interval_prim, OC_MODE_ON);

  if (tgs.subphase_ctr == 2) {
    // This was the calculation for the 3rd primary tooth, so also set
    // secondary tooth timer.
    /*
      The early calculation of 2ndary tooth can introduce a slight error,
      if a phase change occurrs at the next (3rd) tooth (before the 2ndary
      tooth is released). Then, the interval between the 3rd primary tooth
      and the 2ndary tooth can be too long or too short, depending on the
      acceleration of the new phase:
      - \alpha_n > \alpha_o : interval too long
      - \alpha_n < \alpha_o : interval too short
      Under which conditions will the 4th primary tooth be scheduled before
      the 2ndary tooth? This will possibly break engine control!
      @todo calculate \alpha resp. \Delta_{\alpha}!
     */
    float t_off;
    if (alpha == 0) {
      t_off = (tgs.phi + DIST_PRIMARY + OFFSET_SECONDARY) / tgs.omega_0;
    }
    else {
      float d2 = tgs.omega_0 * tgs.omega_0 - 2 * alpha * (/*tgs.phi_0*/ - tgs.phi - DIST_PRIMARY - OFFSET_SECONDARY);
      if (d2 < 0) {
        debug_printf("D2 = %f < 0!!!\n", d2);
        //debug_printf("om_0=%f alpha=%f phi=%f\n", tgs.omega_0, alpha, tgs.phi);
        hal_abort();
      }
      t_off = (-tgs.omega_0 + sqrtf(d2)) / alpha;
    }
    float t_sec = tgs.t_0 + t_off;
    debug_printf("t_next2: %f\n", t_sec);
    float interval_sec = t_sec - tgs.t_last;
    /*
    timctr_t tim_sec = tim_l_prim + interval_sec * TICKS_PER_SECOND;
    set_next_secondary(tim_sec);
    */
    /*
    timctr_t tim_sec = interval_sec * TICKS_PER_SECOND + last_primary;
    set_next_secondary(tim_sec);
    */
    timctr_t tim_sec = interval_sec * TICKS_PER_SECOND + tim_last_prim;
    hal_tg_set_secondary_time(tim_sec, OC_MODE_ON);
  }
}
