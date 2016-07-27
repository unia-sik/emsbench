/**
 * $Id: performance.h 546 2016-07-15 06:51:19Z klugeflo $
 * @file performance.h
 * @brief Performance measurements
 * @author Florian Kluge <kluge@informatik.uni-augsburg.de>
 */

#ifndef EMS_PERFORMANCE_H
#define EMS_PERFORMANCE_H

#include <hal/ems/hal_performance.h>

#ifdef __PERF__
/**
 * @brief Wrapper for ISRs without execution path tracking.
 * @author Florian Kluge
 * @param name Name of the ISR
 * @param idc ID-char (as string!) for performance output
 */
#define PERF_WRAP_SIMPLE(name, idc)					\
  void name##_wrapped();						\
  void name () {							\
    hal_performance_startCounter();					\
    name## _wrapped();							\
    unsigned int executionDuration = hal_performance_stopCounter();	\
    perf_printf("*" idc "%u\r\n", executionDuration);			\
  }									\
  void name## _wrapped()

/**
 * @brief Wrapper for ISRs with execution path tracking.
 * @author Florian Kluge
 * @param name Name of the ISR
 * @param idc ID-char (as string!) for performance output
 */
#define PERF_WRAP_PATH(name, idc)					\
  char name##_wrapped();						\
  void name () {							\
    hal_performance_startCounter();					\
    char executionPathIdentifier = name## _wrapped();			\
    unsigned int executionDuration = hal_performance_stopCounter();	\
    perf_printf("*" idc "%c%u\r\n", executionPathIdentifier, executionDuration); \
  }									\
  char name## _wrapped()

/**
 * @brief Initialise path identifier for performance measurements
 * @author Florian Kluge
 * @param c initial value of path identifier
 * @see #PERF_WRAP_PATH
 */
#define PERF_PATH_INIT(c) char perf_executionPathIdentifier = (c);

/**
 * @brief Set the identifier for the execution path
 * @author Florian Kluge
 * @param c value of path identifier
 * @see #PERF_WRAP_PATH
 */
#define PERF_PATH_SET(c) perf_executionPathIdentifier = (c);

/**
 * @brief Initialise path identifier for performance measurements
 * @author Florian Kluge
 * @see #PERF_WRAP_PATH
 */
#define PERF_PATH_RETURN() return perf_executionPathIdentifier;

#else // __PERF__

/**
 * @brief Wrapper for ISRs without execution path tracking.
 * @author Florian Kluge
 * @param name Name of the ISR
 * @param idc ignored in !__PERF__
 */
#define PERF_WRAP_SIMPLE(name, idc)		\
  void name ()

/**
 * @brief Wrapper for ISRs without execution path tracking.
 * @author Florian Kluge
 * @param name Name of the ISR
 * @param idc ignored in !__PERF__
 */
#define PERF_WRAP_PATH(name, idc)		\
  void name ()

/**
 * @brief Ignored in !__PERF__
 * @author Florian Kluge
 */
#define PERF_PATH_INIT(c)

/**
 * @brief Ignored in !__PERF__
 * @author Florian Kluge
 */
#define PERF_PATH_SET(c)

/**
 * @brief Ignored in !__PERF__
 * @author Florian Kluge
 */
#define PERF_PATH_RETURN() return;

#endif // __PERF__



#endif // !EMS_PERFORMANCE_H
