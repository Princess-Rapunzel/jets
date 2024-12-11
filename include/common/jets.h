#ifndef __JETS_H__
#define __JETS_H__
#include "jetscfg.h"
#include "jetscomm.h"
#include <limits>

namespace jets
{

// Forward declarations
namespace parallel {
  class Communicator;
} // namespace parallel

class JetsApp
{
public:
#ifdef JETS_HAVE_MPI
    JetsApp(int argc, char *argv[],
              MPI_Comm COMM_WORLD_IN=MPI_COMM_WORLD, int n_threads=-1);
#else
    JetsApp(int argc, char *argv[],
              int COMM_WORLD_IN=0, int n_threads=-1);
#endif // JETS_HAVE_MPI
    virtual ~JetsApp();

    virtual void shutdown() {this->~JetsApp();};

    const parallel::Communicator & comm() const { return *_comm; }

    // const processor_id_type& n_processors() const { return _n_processors; };
    // const processor_id_type& processor_id() const { return _processor_id; };
private:
    parallel::Communicator * _comm;
    bool _is_initialized;
};

/**
 * Checks that library initialization has been done.  If it
 * hasn't an error message is printed and the code aborts.
 * It is useful to \p jets_assert(jets::initialized()) in library
 * object constructors.
 */
bool initialized ();

/**
 * Checks that the library has been closed.  This should
 * always return false when called from a library object.
 * It is useful to \p jets_assert(!jets::closed()) in library
 * object destructors.
 */
bool closed ();

/**
 * \f$ \pi=3.14159... \f$.
 */
const Real pi =
  static_cast<Real>(3.1415926535897932384626433832795029L);

/**
 * \f$ zero=0. \f$.
 */
const Number zero = 0.;

/**
 * A number which is used quite often to represent
 * an invalid or uninitialized value for an unsigned integer.
 */
const unsigned int invalid_uint = static_cast<unsigned int>(-1);

/**
 * A number which is used quite often to represent
 * an invalid or uninitialized value for an integer.
 */
const int invalid_int = std::numeric_limits<int>::max();

/**
 * A good way to suppress compiler warnings about unused variables.
 */
#define jets_unused(x) (void)(x)

// Some jets modifiers that help programming.

/**
 * Indicates that a function is inline.
 */
#define __jets_inline__ inline
/**
 * The `__jets_abstract__` macro is used to indicate that a class which
 * is abstract and should not be instantiated. 
 */
#define __jets_abstract__
} // namespace jets
#endif // __JETS_H__
