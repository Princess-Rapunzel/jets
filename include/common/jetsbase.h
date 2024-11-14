#ifndef __JETSBASE_H__
#define __JETSBASE_H__


#include "idtypes.h"

namespace jets
{
#ifndef JETS_HAVE_MPI
typedef int MPI_Comm;
#define MPI_COMM_WORLD 0
#endif

/**
 * \returns The number of processors libmesh was initialized with.
 */
processor_id_type global_n_processors();

/**
 * \returns The index of the local processor with respect to the
 * original MPI pool libmesh was initialized with.
 */
processor_id_type global_processor_id();

/**
 * \returns The maximum number of threads used in the simulation.
 */
unsigned int n_threads();

namespace private_data
{

#ifdef JETS_HAVE_MPI
/**
 * Total number of processors used.
 */
extern processor_id_type _n_processors;

/**
 * The local processor id.
 */
extern processor_id_type _processor_id;
#endif

/**
 * Total number of threads possible.
 */
extern int _n_threads;
} // namespace private_data

} // namespace jets

inline jets::processor_id_type jets::global_n_processors()
{
#ifdef JETS_HAVE_MPI
  return jets::private_data::_n_processors;
#else
  return 1;
#endif
}

inline jets::processor_id_type jets::global_processor_id()
{
#ifdef JETS_HAVE_MPI
  return jets::private_data::_processor_id;
#else
  return 0;
#endif
}


inline unsigned int jets::n_threads()
{
  return static_cast<unsigned int>(jets::private_data::_n_threads);
}
#endif // __JETSBASE_H__