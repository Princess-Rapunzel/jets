#include "jetsinit.h"
#include "communicator.h"

namespace jets
{

#ifdef JETS_HAVE_MPI
JetsInit::JetsInit(int* argc, char*** argv, MPI_Comm comm)
{
    int mpi_initialized;
    MPI_Initialized(&mpi_initialized);
    if (!mpi_initialized)
    {
        MPI_Init(argc, argv);
        _mpi_initialized=true;
    }
    this->_comm=std::make_unique<parallel::Communicator>(comm);
    this->_ref=std::make_unique<SemiPermanent::Ref>();
}
#else
JetsInit(int argc, char** argv)
{
    this->_comm=std::make_unique<Communicator>(); // So comm() doesn't dereference null
    this->_ref=std::make_unique<SemiPermanent::Ref>();
}
#endif

JetsInit::~JetsInit()
{
    out << "Process " << this->comm().rank() << " is exiting." << std::endl;
    // Every processor had better be ready to exit at the same time.
    // This would be a timpi_parallel_only() function, except that
    // timpi_parallel_only() uses timpi_assert() which throws an
    // exception which causes compilers to scream about exceptions
    // inside destructors.

    // Even if we're not doing parallel_only debugging, we don't want
    // one processor to try to exit until all others are done working.
    this->comm().barrier();
    // Trigger any SemiPermanent cleanup before potentially finalizing MPI
    _ref.reset();
#ifdef JETS_HAVE_MPI
    this->_comm.reset();
    if (this->_mpi_initialized)
    {
        int error_code = MPI_Finalize();
        if (error_code != MPI_SUCCESS)
        {
            char error_string[MPI_MAX_ERROR_STRING + 1];
            int error_string_len;
            MPI_Error_string(error_code, error_string,
                             &error_string_len);
            std::cerr << "Failure from MPI_Finalize():\n"
                << error_string << std::endl;
        }
    }
#else
    this->_comm.reset();
#endif // JETS_HAVE_MPI
}
};