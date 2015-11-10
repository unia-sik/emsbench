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
 * $Id: transformer.c 502 2015-11-05 14:18:19Z klugeflo $
 * @file transformer.h
 * @brief Tranformation of driving cycle operations to trace generator phases.
 * @author Florian Kluge <kluge@informatik.uni-augsburg.de>
 */

#include "transformer.h"

#include <math.h>

//#define N_PRIMARY 12

/**
 * @brief Fast access to car properties
 */
typedef struct {
  double flank; ///< tyre flank height (m)
  double wheel_diam; ///< wheel diameter (m)
  double circumference; ///< tyre circumference
  double om_i; ///< engine idle speed s^{-1}
  double alpha_i; ///< angular acceleration towards idle when no load present
  unsigned n_p; ///< number of primary teeth
  unsigned n_s; ///< number of secondary teeth
  double delta_p; ///< angular distance of primary teeth (r)
  double delta_s; ///< angular distance of secondary teeth (r)
  double gear[7]; ///< [0] unused
  double axle; ///< axle/cardan transmission
  const kv_file_t *rawdata;
} cardata_t;

/**
 * @brief Car properties for this run
 */
cardata_t cd;

/**
 * @brief Output file
 */
FILE *out;
/**
 * @brief Count the number of crank shaft phases
 */
size_t n_phases;

/**
 * @brief Initialise the #cd structure
 * @param cardata The key-value file with the car data
 */
void prepare_cardata(const kv_file_t *cardata);

/**
 * @name Conversion of driving phases to crank shaft phases.
 * For behaviour of these phases, see the enclosed documentation.
 * @{
 */

/**
 * @brief Driveaway of the car from standstill
 * @param om0 crank shaft speed at start of phase
 * @param op driving cycle operation
 * @return crank shaft speed at end of phase
 */
double perform_driveaway(double om0, const operation_t *op);


/**
 * @brief The car does not move
 * @param om0 crank shaft speed at start of phase
 * @param op driving cycle operation
 * @return crank shaft speed at end of phase
 */
double perform_standstill(double om0, const operation_t *op);


/**
 * @brief The car is rolling with the clutch disengaged.
 * @param om0 crank shaft speed at start of phase
 * @param op driving cycle operation
 * @return crank shaft speed at end of phase
 */
double perform_clutchdiseng(double om0, const operation_t *op);

/**
 * @brief The driver changes the gear.
 * @param om0 crank shaft speed at start of phase
 * @param op driving cycle operation
 * @return crank shaft speed at end of phase
 */
double perform_gearchange(double om0, const operation_t *op);


/**
 * @brief Uniform Ac-/Deceleration.
 * @param om0 crank shaft speed at start of phase
 * @param op driving cycle operation
 * @return crank shaft speed at end of phase
 */
double perform_regular(double om0, const operation_t *op);

/**
 * @}
 */

/**
 * @brief Write output file header
 */
void write_head();


/**
 * @brief Write output file footer
 */
void write_foot();


int transform(const kv_file_t *cardata, const cycle_t *cycle, FILE* outfile) {
  prepare_cardata(cardata);
  out = outfile;
  n_phases = 0;
  printf("h_f: %f d_w: %f c_w: %f om_i: %f alpha_i: %f\nn_p: %u n_s %u delta_p: %f delta_s: %f\n",
         cd.flank, cd.wheel_diam, cd.circumference, cd.om_i, cd.alpha_i,
         cd.n_p, cd.n_s, cd.delta_p, cd.delta_s);

  size_t i;
  operation_t prev = { 0.0, 0, 0, 0, 0 };
  operation_t *op_cur, *op_prev;
  op_prev = &prev;
  double om0 = cd.om_i;

  write_head();

  for (i = 0; i < cycle->used_entries; ++i) {
    op_cur = &cycle->operations[i];
    printf("Acc: %f vs: %ld ve: %ld dur: %u gear: %u (trans: %f)\n",
           op_cur->acceleration, op_cur->speed_start, op_cur->speed_end, op_cur->duration, op_cur->gear, cd.gear[op_cur->gear]*cd.axle);

    printf("\t%2lu: ", i);
    if (op_cur->speed_start == 0 && op_cur->speed_end != 0) {
      printf("Driveaway\n");
      om0 = perform_driveaway(om0, op_cur);
    }
    else
      if (op_cur->speed_start == 0 && op_cur->speed_end == 0) {
        printf("Standstill\n");
        om0 = perform_standstill(om0, op_cur);
      }
      else
        if (op_cur->speed_start != 0 && op_cur->gear == 0) {
          printf("Clutch disengaged\n");
          om0 = perform_clutchdiseng(om0, op_cur);
        }
        else
          if (op_cur->gear != 0 && op_cur->gear != op_prev->gear) {
            printf("Gear change\n");
            om0 = perform_gearchange(om0, op_cur);
          }
          else {
            printf("regular\n");
            om0 = perform_regular(om0, op_cur);
          }

    op_prev = op_cur;
  }

  write_foot();

  printf("Wrote %lu phases\n", n_phases);
  return 0;
}


void prepare_cardata(const kv_file_t *cardata) {
  double twidth = kv_get_ll(cardata, "width") / 1000.0; // -> m
  double tratio = kv_get_ll(cardata, "aspect_ratio") / 100.0; // -> [0..1]
  double trdiam = kv_get_ll(cardata, "diameter") * 2.54 / 100; // -> m

  cd.flank = twidth * tratio;
  cd.wheel_diam = trdiam + 2 * cd.flank;
  cd.circumference = cd.wheel_diam * M_PI;

  cd.om_i = kv_get_ll(cardata, "idle_rpm") / 60.0;
  cd.alpha_i = kv_get_ll(cardata, "acc_to_idle");
  cd.n_p = kv_get_ll(cardata, "primary_teeth"); //N_PRIMARY;
  cd.n_s = 1;
  cd.delta_p = 1.0 / cd.n_p;
  cd.delta_s = 1.0 / cd.n_s;

  cd.gear[0] = 0;
  cd.gear[1] = kv_get_float(cardata, "gear[1]");
  cd.gear[2] = kv_get_float(cardata, "gear[2]");
  cd.gear[3] = kv_get_float(cardata, "gear[3]");
  cd.gear[4] = kv_get_float(cardata, "gear[4]");
  cd.gear[5] = kv_get_float(cardata, "gear[5]");
  cd.gear[6] = kv_get_float(cardata, "gear[6]");
  cd.axle = kv_get_float(cardata, "axle");
  cd.rawdata = cardata;
}


double perform_driveaway(double om0, const operation_t *op) {
  double a = (op->speed_end - op->speed_start) / (3.6 * op->duration);
  double t_I = cd.om_i * cd.circumference / (cd.axle * cd.gear[op->gear] * a);
  double t_R = op->duration - t_I;
  printf("\t# t_I: %f t_R: %f\n", t_I, t_R);
  double alpha = a * cd.axle * cd.gear[op->gear] / cd.circumference;
  double omN = om0 + t_R * alpha;
  printf("\t# om0: %f omN: %f\n", om0, omN);
  printf("\t# a: %f alpha %f\n", a, alpha);
  printf("\t# v(t_I) = %f v@om_i = %f\n",
         t_I * a,
         cd.om_i / (cd.gear[op->gear] * cd.axle) * cd.circumference);

  fprintf(out, "\t{ %2.6f, %2.6f },\n", t_I, 0.0);
  ++n_phases;
  fprintf(out, "\t{ %2.6f, %2.6f },\n", t_R, alpha);
  ++n_phases;

  return omN;
  // 1.465 m/s
}


double perform_standstill(double om0, const operation_t *op) {

  double alpha;
  double tc = 0;
  double omN = om0;
  if (fabs(om0 - cd.om_i) > 0.01) {
    if (om0 > cd.om_i) {
      alpha = -cd.alpha_i;
    }
    else {
      alpha = cd.alpha_i;
    }
    double t = (cd.om_i - om0) / alpha;
    tc = fmin(t, op->duration);
    printf("\t{ %2.6f, %2.6f },\n", tc, alpha);
    omN += tc * alpha;
  }
  if (tc < op->duration) {
    fprintf(out, "\t{ %2.6f, %2.6f },\n", (op->duration - tc), 0.0);
    ++n_phases;
  }
  printf("\t# om0: %f omN: %f\n", om0, omN);
  return omN;
}


double perform_clutchdiseng(double om0, const operation_t *op) {
  double omN = om0;

  double alpha;
  double tc = 0;
  if (fabs(om0 - cd.om_i) > 0.01) {
    if (om0 > cd.om_i) {
      alpha = -cd.alpha_i;
    }
    else {
      alpha = cd.alpha_i;
    }
    double t = (cd.om_i - om0) / alpha;
    tc = fmin(t, op->duration);
    fprintf(out, "\t{ %2.6f, %2.6f },\n", tc, alpha);
    ++n_phases;
    omN += tc * alpha;
  }
  if (tc < op->duration) {
    fprintf(out, "\t{ %2.6f, %2.6f },\n", (op->duration - tc), 0.0);
    ++n_phases;
  }
  printf("\t# om0: %f omN: %f\n", om0, omN);
  return omN;
}


double perform_gearchange(double om0, const operation_t *op) {
  double omN = om0;
  double d2 = op->duration / 2.0;
  // first half
  double tc = 0;
  double alpha;
  if (fabs(om0 - cd.om_i) > 0.01) {
    double alpha;
    if (om0 > cd.om_i) {
      alpha = -cd.alpha_i;
    }
    else {
      alpha = cd.alpha_i;
    }
    double t = (cd.om_i - om0) / alpha;
    tc = fmin(t, d2);
    fprintf(out, "\t{ %2.6f, %2.6f },\n", tc, alpha);
    ++n_phases;
    omN += tc * alpha;
  }
  printf("\t# omN: %f\n", omN);
  if (tc < d2) { // some more time at idle
    fprintf(out, "\t{ %2.6f, %2.6f },\n", (d2 - tc), 0.0);
    ++n_phases;
  }

  // second half with new gear
  alpha = 1 / d2 * (cd.axle * cd.gear[op->gear] * op->speed_start / (3.6 * cd.circumference) - omN);
  omN += d2 * alpha;
  fprintf(out, "\t{ %2.6f, %2.6f },\n", d2, alpha);
  ++n_phases;
  printf("\t# om0: %f omN: %f\n", om0, omN);
  return omN;
}


double perform_regular(double om0, const operation_t *op) {
  double omN = om0;
  double alpha = cd.axle * cd.gear[op->gear] * (op->speed_end - op->speed_start) / (3.6 * cd.circumference * op->duration);
  fprintf(out, "\t{ %2.6f, %2.6f },\n", (double)op->duration, alpha);
  ++n_phases;
  omN += alpha * op->duration;
  printf("\t# om0: %f omN: %f\n", om0, omN);
  return omN;
}


void write_head() {
  fprintf(out, "#include <tg/tgdata.h>\n\n");
  fprintf(out, "const cs_phase_t PHASES[] = {\n");
}


void write_foot() {
  fprintf(out, "};\n\n");
  fprintf(out, "const size_t N_PHASES = %lu;\n", n_phases);
  fprintf(out, "const float OMEGA_IDLE = %f;\n", cd.om_i);
  fprintf(out, "const size_t N_PRIMARY = %u;\n", cd.n_p);
  fprintf(out, "const float DIST_PRIMARY = %f;\n", cd.delta_p);
  fprintf(out, "const float OFFSET_SECONDARY = %f;\n",
          kv_get_float(cd.rawdata, "offset_secondary"));
}

