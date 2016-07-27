/**
 * $Id: main.c 537 2016-02-15 08:20:57Z klugeflo $
 * @brief Typical instruction sequences for estimation of static WCET model
 * @author Florian Kluge <kluge@informatik.uni-augsburg.de>
 */

#include <hal/ems/freeems_hal.h>
#include <hal/ems/hal_ubench.h>
#include <hal/log.h>
#include <ems/performance.h>
#include <limits.h>

void bm_init();
void bm_code();
void bm_finish();

int bm_linear(int a, int b, int c);
int bm_branches(int val);
int bm_switches(int val);
int bm_loop(int n);
int bm_long_loop(int n);

int bm_io();

int main(void) {
  hal_system_clock();

  bm_init();

  debug_puts("Entering code benchmarks...\r\n");
  bm_code();

  volatile int i;
  for (i = 0; i < 100000; ++i) {
    asm("nop");
  }

  debug_puts("Entering I/O benchmarks...\r\n");
  bm_io();

  bm_finish();
  return 0;
}


void bm_init() {
  hal_system_clock();

  log_init();
  
  debug_puts("Initializing stuff!\r\n");
  hal_system_init();

  hal_system_info();

  // Timer interrupts might disturb the measurements, so don't start
  // the timers
  //debug_puts("Starting Timers!\r\n");
  //hal_system_start();
}


void bm_finish() {
  debug_puts("Everything is over, waiting some time for UART to finish...\r\n");
  // the following loop is just to prohibit the program from finishing too
  // early - we have to wait until the "UART" buffer is emptied.
  volatile int i;
  for (i = 0; i < INT_MAX; ++i) {
    asm("nop");
  }
}

#define FNMEAS(function, n, args...) {					\
    int rv;								\
    hal_performance_startCounter();					\
    rv = function(args);						\
    executionDuration = hal_performance_stopCounter();			\
    perf_printf("**"#function" "#n" (%d): %u\r\n", rv, executionDuration); \
  }

void bm_code() {
  unsigned int executionDuration;

  hal_performance_startCounter();
  executionDuration = hal_performance_stopCounter();
  perf_printf("**Perf 1: %u\r\n", executionDuration);

  hal_performance_startCounter();
  executionDuration = hal_performance_stopCounter();
  perf_printf("**Perf 2: %u\r\n", executionDuration);

  hal_performance_startCounter();
  executionDuration = hal_performance_stopCounter();
  perf_printf("**Perf 3: %u\r\n", executionDuration);

  hal_performance_startCounter();
  executionDuration = hal_performance_stopCounter();
  perf_printf("**Perf 3: %u\r\n", executionDuration);

  FNMEAS(bm_linear, 1, 1, 2, 3); // bm_linear(1, 2, 3)
  FNMEAS(bm_linear, 2, 1, 2, 4); // bm_linear(1, 2, 4)

  FNMEAS(bm_branches, 1, 42); // bm_branches(42)
  FNMEAS(bm_branches, 2, 43); // bm_branches(43)

  FNMEAS(bm_switches, 1, 2); // bm_switches(2)
  FNMEAS(bm_switches, 2, 3); // bm_switches(3)
  FNMEAS(bm_loop, 1, 20); // bm_loop(20)
  FNMEAS(bm_loop, 2, 21); // bm_loop(21)

  FNMEAS(bm_long_loop, 1, 5); // bm_long_loop(5)
  FNMEAS(bm_long_loop, 2, 7); // bm_long_loop(7)

  FNMEAS(bm_stores, 1); // bm_stores()
  FNMEAS(bm_stores, 2); // bm_stores()
}


/*

- successive stores -- How???

*/

/**
 * @brief linear code with fetches from several flash lines
 *
 * This code fulfils no particular function, it simply calculates
 * (a+b+c)^3 in a very complex way.
 *
 * @return the result of the calculation
 */
int bm_linear(int a, int b, int c) {
  int h1 = a * a * a  +  b * b * b  +  c * c * c;
  int h2 = a * b * b  +  a * c * c  +  a * a * b  +  b * c * c
    +  a * a * c  +  b * b * c  +  a * b * c;
  int h3 = h1 + 3 * h2;  
  return h3;
}


/**
 * @brief Branches: if/else in three layers.
 *
 * The parameter is mapped to intervals of length 16, where [112,\infinity)
 * is the first, and (-\infinity,16] is the last.
 *
 * @param val some number
 *
 * @return The number of the interval where the parameter belongs to
 *
 */
int bm_branches(int val) {
  if (val > 64) {
    if (val > 96) {
      if (val > 112) {
	return 1;
      }
      else {
	return 2;
      }
    }
    else {
      if (val > 80) {
	return 3;
      }
      else {
	return 4;
      }
    }
  }
  else {
    if (val > 32) {
      if (val > 48) {
	return 5;
      }
      else {
	return 6;
      }
    }
    else {
      if (val > 16) {
	return 7;
      }
      else {
	return 8;
      }
    }
  }
  return 0;
}


/**
 * @brief switches: some meaningless calculations
 * @param val some number, preferable from 0 to 3
 * @return calculation result
 */
int bm_switches(int val) {
  int rv = 0;
  switch (val) {
  case 0:
    rv = val + 1;
    break;
  case 1:
    rv = val - 2;
    break;
  case 2:
    rv = val - 1;
    break;
  case 3:
    rv = val + 2;
    break;
  default:
    rv = val;
    break;
  }
  return rv;
}


/**
 * @brief loop: let's find a fibonacci number
 *
 * Actual indexing may deviate from what might be correct.
 * We don't care about that, we just want a loop!
 */
int bm_loop(int n) {
  int last = 0;
  int current = 1;
  int i;
  for (i = 0; i < n; ++i) {
    int tmp = current + last;
    last = current;
    current = tmp;
  }
  return current;
}



int va[] = { 26, 57, 44, 48, 89, 59, 62, 19, 71, 98 };
int vb[] = { 81, 18, 8, 71, 74, 28, 39, 85, 57, 84 };
int vc[] = { 32, 79, 20, 92, 3, 45, 69, 42, 55, 50 };
#define N 10
int bm_long_loop(int n) {
  if (n > N)
    return -1;
  
  int sum = 0;
  int i;
  for (i = 0; i < n; ++i) {
    int h1 = va[i] * va[i]  +  vb[i] * vb[i]  +  vc[i] * vc[i];
    int h2 = va[i] * vb[i]  +  va[i] * vc[i]  +  vb[i] * vc[i];
    sum += h1 + 2 * h2;
  }
  return sum;
}


#define IOMEAS(function, n, args...)\
  hal_performance_startCounter();\
  function(args);\
  executionDuration = hal_performance_stopCounter();\
  perf_printf("**"#function" "#n": %u\r\n", executionDuration);


/**
 * @brief I/O accesses
 */
int bm_io() {
  unsigned int executionDuration;

  perf_printf("***Timer:\r\n");
  IOMEAS(hal_timer_time_get, 1);
  IOMEAS(hal_timer_overflow_get, 1);

  perf_printf("***IgnitionDwell:\r\n");
  IOMEAS(hal_timer_pit_active_get, 1, IGNITION_DWELL_PIT);
  IOMEAS(hal_timer_pit_interval_set, 1, IGNITION_DWELL_PIT, 1546);
  IOMEAS(hal_timer_pit_active_set, 1, IGNITION_DWELL_PIT, 0);
  IOMEAS(hal_timer_pit_current_get, 1, IGNITION_DWELL_PIT);

  perf_printf("***IgnitionFire:\r\n");
  IOMEAS(hal_timer_pit_active_get, 1, IGNITION_FIRE_PIT);
  IOMEAS(hal_timer_pit_interval_set, 1, IGNITION_FIRE_PIT, 1546);
  IOMEAS(hal_timer_pit_active_set, 1, IGNITION_FIRE_PIT, 0);
  IOMEAS(hal_timer_pit_current_get, 1, IGNITION_FIRE_PIT);
  
  perf_printf("***Primary IC:\r\n");
  IOMEAS(hal_timer_ic_capture_get, 1, PRIMARY_RPM_INPUT);
  IOMEAS(hal_timer_ic_pin_get, 1, PRIMARY_RPM_INPUT);

  perf_printf("***Secondary IC:\r\n");
  IOMEAS(hal_timer_ic_capture_get, 1, SECONDARY_RPM_INPUT);
  IOMEAS(hal_timer_ic_pin_get, 1, SECONDARY_RPM_INPUT);

  int fuelChannel;
  for (fuelChannel = 0; fuelChannel < 6; ++ fuelChannel) {
    perf_printf("***Fuel channel %d\r\n", fuelChannel);
    IOMEAS(hal_timer_oc_pin_get, 1, INJECTIONX_OUTPUT(fuelChannel));
    IOMEAS(hal_timer_oc_active_get, 1, INJECTIONX_OUTPUT(fuelChannel));
    IOMEAS(hal_timer_oc_compare_get, 1, INJECTIONX_OUTPUT(fuelChannel));
    IOMEAS(hal_timer_oc_active_set, 1, INJECTIONX_OUTPUT(fuelChannel), 0);
    IOMEAS(hal_timer_oc_compare_set, 1, INJECTIONX_OUTPUT(fuelChannel), 1234);
    IOMEAS(hal_timer_oc_output_set, 1, INJECTIONX_OUTPUT(fuelChannel), OC_MODE_TO_HIGH);
  }

  perf_printf("***GPIO pins:\r\n");
  IOMEAS(hal_io_set, 1, DEBUG_OUTPUT_8, 1);
  IOMEAS(hal_io_set, 1, DEBUG_OUTPUT_1, HIGH);
  IOMEAS(hal_io_set, 1, DEBUG_OUTPUT_2, HIGH);
  IOMEAS(hal_io_set, 1, DEBUG_OUTPUT_3, HIGH);
  IOMEAS(hal_io_set, 1, DEBUG_OUTPUT_4, HIGH);
  IOMEAS(hal_io_set, 1, DEBUG_OUTPUT_5, HIGH);
  IOMEAS(hal_io_set, 1, DEBUG_OUTPUT_6, HIGH);
  IOMEAS(hal_io_set, 1, DEBUG_OUTPUT_7, HIGH);
  IOMEAS(hal_io_set, 1, IGNITIONX_OUTPUT(0), HIGH);
  IOMEAS(hal_io_set, 1, IGNITIONX_OUTPUT(0), LOW);

  return 0;
}
