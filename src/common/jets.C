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
            MPI_Comm COMM_WORLD_IN, int n_threads):
#else
JetsApp::JetsApp(int argc, char *argv[],
            int COMM_WORLD_IN, int n_threads) :
#endif // JETS_HAVE_MPI
_is_initialized(false)
{
    jets_assert(!initialized());
    command_line = std::make_unique<GetPot>(argc, argv);
#ifdef JETS_HAVE_OPENMP
    int n_threads_cmd;
    if (command_line->search("-p"))
        n_threads_cmd = command_line->next(-1);
    if (n_threads > 0 && n_threads < JETS_MAX_THREADS)
        jets::private_data::_n_threads = n_threads;
    else if (n_threads_cmd > 0 && n_threads_cmd < JETS_MAX_THREADS)
        jets::private_data::_n_threads = n_threads_cmd;
    else
        jets_error_msg("Invalid number of threads. It must be between 1 and " << std::to_string(JETS_MAX_THREADS) << ". Please use the -n option.");

    omp_set_num_threads(jets::private_data::_n_threads);
#endif

    jets::private_data::_is_initialized = true;

#ifdef JETS_HAVE_MPI
    int flag;
    MPI_Initialized(&flag);
    if (!flag)
    {
        jets::out << "Initializing MPI..." << std::endl;
        MPI_Init(&argc, &argv);
        this->_is_initialized = true;
    }
    GLOBAL_COMM_WORLD = COMM_WORLD_IN;
    int n_processors, processor_id;
    MPI_Comm_size(GLOBAL_COMM_WORLD, &n_processors);
    MPI_Comm_rank(GLOBAL_COMM_WORLD, &processor_id);
    private_data::_n_processors = static_cast<processor_id_type>(n_processors);
    private_data::_processor_id = static_cast<processor_id_type>(processor_id);
#endif
}

JetsApp::~JetsApp()
{
    jets::private_data::_is_initialized = false;

    // delete jets::out.get();
    // delete jets::err.get();

    // jets::out.reset(std::cout);
    // jets::err.reset(std::cerr);
#ifdef JETS_HAVE_MPI
    if (this->_is_initialized)
    {
        jets::out << "Finalizing MPI..." << std::endl;
        MPI_Finalize();
    }
#endif
}
}  // namespace jets