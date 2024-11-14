#ifndef __JETS_CONFIG_H__
#define __JETS_CONFIG_H__

// Configuration file for the JETS library.

/**
 * Debug mode.
 */
#define DEBUG

/**
 * JETS uses double precision by default.
 */
#define JETS_DEFAULT_DOUBLE_PRECISION

/**
 * Jets uses complex numbers.
 */
// #define JETS_HAVE_COMPLEX

#define JETS_ENABLE_TIMESTAMPS

/**
 * Define processor id storage type.
 */
#define JETS_PROCESSOR_ID_BYTES 4

#define JETS_DOF_ID_BYTES 4

#define JETS_MAX_THREADS 8

/**
 * Pthread support.
 */
// #define JETS_HAVE_PTHREAD

/**
 * Enable trowing exceptions.
 */
#define JETS_ENABLE_EXCEPTIONS
#endif // __JETS_CONFIG_H__