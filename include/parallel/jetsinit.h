#ifndef __JETS_INIT_H__
#define __JETS_INIT_H__

#include "jetscfg.h"
#include "semipermanent.h"
#ifdef JETS_HAVE_MPI
#include <mpi.h>
#endif // JETS_HAVE_MPI
#include <memory>
namespace jets
{

// Forward declarations
namespace parallel
{
class Communicator;
} // namespace parallel


/**
 * Initialize necessary libraries(MPI) environment.
 *
 * This class should be singleton, more than one instance
 * would cause undefined behavior.
 */
class JetsInit
{
public:
#ifdef JETS_HAVE_MPI
    JetsInit(int* argc, char*** argv, MPI_Comm comm=MPI_COMM_WORLD);
#else
    JetsInit(int* argc, char*** argv);
#endif // JETS_HAVE_MPI
    ~JetsInit();

    const parallel::Communicator& comm() const { return *_comm; };
    parallel::Communicator& comm() { return *_comm; };

private:
    std::unique_ptr<parallel::Communicator> _comm;
    // unique_ptr so we can free it *before* we MPI_Finalize
    std::unique_ptr<SemiPermanent::Ref> _ref;
#ifdef JETS_HAVE_MPI
    bool _mpi_initialized;
#endif // JETS_HAVE_MPI
};
} // namespace jets

#endif // __JETS_INIT_H__