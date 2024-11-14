#include "jets.h"

#if defined(JETS_HAVE_MPI)
# include <mpi.h>
#endif
#include "getpot.h"
#ifdef JETS_HAVE_OPENMP
#include <omp.h>
#endif

#include <iostream>
#include <fstream>
#include <memory>
#ifdef JETS_ENABLE_EXCEPTIONS
#include <exception>
#endif

namespace jets
{
namespace private_data
{
/**
 * Flag that tells if \p init() has been called.
 */
extern bool _is_initialized;
} // namespace private_data

// jets data initialization
#ifdef JETS_HAVE_MPI
MPI_Comm           GLOBAL_COMM_WORLD = MPI_COMM_NULL;
#else
int                GLOBAL_COMM_WORLD = 0;
#endif

OStreamProxy out(std::cout);
OStreamProxy err(std::cerr);

std::unique_ptr<GetPot> command_line;
// std::set<std::string> command_line_name_set;

#ifdef JETS_HAVE_MPI
processor_id_type jets::private_data::_n_processors = 1;
processor_id_type jets::private_data::_processor_id = 0;
#endif
int           jets::private_data::_n_threads = 1;
bool         jets::private_data::_is_initialized = false;

bool initialized()
{
  return private_data::_is_initialized;
}

bool closed()
{
  return !private_data::_is_initialized;
}

#ifdef JETS_HAVE_MPI
JetsApp::JetsApp(int argc, char *argv[],
            MPI_Comm COMM_WORLD_IN, int n_threads)
#else
JetsApp::JetsApp(int argc, char *argv[],
            int COMM_WORLD_IN, int n_threads)
#endif // JETS_HAVE_MPI
{
    jets_assert(!initialized());
    command_line = std::make_unique<GetPot>(argc, argv);

    int n_threads_cmd;
    if (command_line->search("-n"))
        n_threads_cmd = command_line->next(-1);
    if (n_threads > 0 && n_threads < JETS_MAX_THREADS)
        jets::private_data::_n_threads = n_threads;
    else if (n_threads_cmd > 0 && n_threads_cmd < JETS_MAX_THREADS)
        jets::private_data::_n_threads = n_threads_cmd;
    else
        jets_error_msg("Invalid number of threads. It must be between 1 and " << std::to_string(JETS_MAX_THREADS) << ". Please use the -n option.");
#ifdef JETS_HAVE_OPENMP
    omp_set_num_threads(jets::private_data::_n_threads);
#endif

    jets::private_data::_is_initialized = true;
}

JetsApp::~JetsApp()
{
    jets::private_data::_is_initialized = false;

    delete jets::out.get();
    delete jets::err.get();

    jets::out.reset(std::cout);
    jets::err.reset(std::cerr);
}
}  // namespace jets