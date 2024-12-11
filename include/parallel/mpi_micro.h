#ifndef __JETS_MPI_MICRO_H__
#define __JETS_MPI_MICRO_H__
#include "jetscomm.h"
#include "jetscfg.h"

#ifdef JETS_HAVE_MPI

#define jets_mpi_var(var) var

#define ignore(...)
/**
 * Macros to test MPI return values
 */
#ifndef NDEBUG
#define jets_assert_mpi_success(error_code)                  \
  do                                                         \
  {                                                          \
    if (error_code != MPI_SUCCESS)                           \
    {                                                        \
      char jets_mpi_error_string[MPI_MAX_ERROR_STRING + 1];  \
      int jets_mpi_error_string_len;                         \
      MPI_Error_string(error_code, jets_mpi_error_string,    \
                       &jets_mpi_error_string_len);          \
      jets_assert_equal_to_msg(error_code, MPI_SUCCESS,      \
                               jets_mpi_error_string);       \
    }                                                        \
  } while (0)

#else

#define jets_assert_mpi_success(error_code) ((void)0)
#endif // NDEBUG
 // Only catch MPI return values when asserts are active.
#ifndef NDEBUG
#define jets_call_mpi(mpi_call)                     \
  do                                                \
  {                                                 \
    int jets_mpi_error_code = mpi_call;            \
    jets_assert_mpi_success(jets_mpi_error_code); \
  } while (0)

#else

#define jets_call_mpi(mpi_call) \
  do                            \
  {                             \
    mpi_call;                   \
  } while (0)
#endif // NDEBUG
#else  // JETS_HAVE_MPI

#define jets_mpi_var(var)

#define jets_call_mpi(mpi_call) \
  do                            \
  {                             \
  } while (0)
#endif // JETS_HAVE_MPI
#endif // __JETS_MPI_MICRO_H__