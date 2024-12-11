#ifndef __JETS_PAR_OPFUNCTION_H__
#define __JETS_PAR_OPFUNCTION_H__

#include "jetscfg.h"
#include "semipermanent.h"
#include "jetsinit.h"
#include "mpi_micro.h"
// C++ includes
#include <functional>
#include <type_traits>

namespace jets
{
namespace parallel
{
/**
 * Templated class to provide the appropriate MPI reduction operations
 * for use with built-in C types or simple C++ constructions.
 *
 * More complicated data types may need to provide a pointer-to-T so
 * that we can use MPI_Address without constructing a new T.
 */
template <typename T>
class OpFunction
{
    /*
     * The unspecialized class defines none of these functions;
     * specializations will need to define any functions that need to be
     * usable.
     *
     * Most specializations will just return MPI_MIN, etc, but we'll use
     * a whitelist rather than a default implementation, so that any
     * attempt to perform a reduction on an unspecialized type will be a
     * compile-time rather than a run-time failure.
     */
    // static MPI_Op max();
    // static MPI_Op min();
    // static MPI_Op sum();
    // static MPI_Op product();
    // static MPI_Op logical_and();
    // static MPI_Op bitwise_and();
    // static MPI_Op logical_or();
    // static MPI_Op bitwise_or();
    // static MPI_Op logical_xor();
    // static MPI_Op bitwise_xor();
    // static MPI_Op max_loc();
    // static MPI_Op min_loc();
};



// ------------------------------------------------------------
// Declare OpFunction specializations for C++ built-in types

#ifdef JETS_HAVE_MPI

#define JETS_PARALLEL_INTEGER_OPS(cxxtype)              \
  template<>                                            \
  class OpFunction<cxxtype>                             \
  {                                                     \
  public:                                               \
    static MPI_Op max()          { return MPI_MAX; }    \
    static MPI_Op min()          { return MPI_MIN; }    \
    static MPI_Op sum()          { return MPI_SUM; }    \
    static MPI_Op product()      { return MPI_PROD; }   \
    static MPI_Op logical_and()  { return MPI_LAND; }   \
    static MPI_Op bitwise_and()  { return MPI_BAND; }   \
    static MPI_Op logical_or()   { return MPI_LOR; }    \
    static MPI_Op bitwise_or()   { return MPI_BOR; }    \
    static MPI_Op logical_xor()  { return MPI_LXOR; }   \
    static MPI_Op bitwise_xor()  { return MPI_BXOR; }   \
    static MPI_Op max_location() { return MPI_MAXLOC; } \
    static MPI_Op min_location() { return MPI_MINLOC; } \
  }

#define JETS_PARALLEL_FLOAT_OPS(cxxtype)                \
  template<>                                            \
  class OpFunction<cxxtype>                             \
  {                                                     \
  public:                                               \
    static MPI_Op max()          { return MPI_MAX; }    \
    static MPI_Op min()          { return MPI_MIN; }    \
    static MPI_Op sum()          { return MPI_SUM; }    \
    static MPI_Op product()      { return MPI_PROD; }   \
    static MPI_Op max_location() { return MPI_MAXLOC; } \
    static MPI_Op min_location() { return MPI_MINLOC; } \
  }

#else

#define JETS_PARALLEL_INTEGER_OPS(cxxtype)  \
  template<>                                    \
  class OpFunction<cxxtype>                     \
  {                                             \
  }

#define JETS_PARALLEL_FLOAT_OPS(cxxtype)    \
  template<>                                    \
  class OpFunction<cxxtype>                     \
  {                                             \
  }

#endif

JETS_PARALLEL_INTEGER_OPS(char);
JETS_PARALLEL_INTEGER_OPS(signed char);
JETS_PARALLEL_INTEGER_OPS(unsigned char);
JETS_PARALLEL_INTEGER_OPS(short int);
JETS_PARALLEL_INTEGER_OPS(unsigned short int);
JETS_PARALLEL_INTEGER_OPS(int);
JETS_PARALLEL_INTEGER_OPS(unsigned int);
JETS_PARALLEL_INTEGER_OPS(long);
JETS_PARALLEL_INTEGER_OPS(long long);
JETS_PARALLEL_INTEGER_OPS(unsigned long);
JETS_PARALLEL_INTEGER_OPS(unsigned long long);

JETS_PARALLEL_FLOAT_OPS(float);
JETS_PARALLEL_FLOAT_OPS(double);
JETS_PARALLEL_FLOAT_OPS(long double);

#ifdef JETS_HAVE_MPI
// Helper class to avoid leaking MPI_Op when JETS exits
class ManageOp : public SemiPermanent
{
public:
  ManageOp(MPI_User_function* func, int commute, MPI_Op* op)
    : _op(op)
  {
    jets_call_mpi(MPI_Op_create(func, commute, _op));
  }

  virtual ~ManageOp() override
  {
    MPI_Op_free(_op);
  }
private:
  MPI_Op* _op;
};
#endif

#define JETS_MPI_OPFUNCTION(mpiname, funcname) \
  static MPI_Op mpiname() { \
    static MPI_Op JETS_MPI_##mpiname = MPI_OP_NULL; \
    if (JETS_MPI_##mpiname == MPI_OP_NULL) \
      SemiPermanent::add \
        (std::make_unique<ManageOp>(jets_mpi_##funcname, true, &JETS_MPI_##mpiname)); \
    return JETS_MPI_##mpiname;  \
  }

#ifdef JETS_DEFAULT_QUADRUPLE_PRECISION
# ifdef JETS_HAVE_MPI
template<>
class OpFunction<JETS_DEFAULT_SCALAR_TYPE>
{
public:
  JETS_MPI_OPFUNCTION(max, quad_max)
    JETS_MPI_OPFUNCTION(min, quad_min)
    JETS_MPI_OPFUNCTION(sum, quad_plus)
    JETS_MPI_OPFUNCTION(product, quad_multiplies)

    JETS_MPI_OPFUNCTION(max_location, quad_max_location)
    JETS_MPI_OPFUNCTION(min_location, quad_min_location)
};

# else
JETS_PARALLEL_FLOAT_OPS(JETS_DEFAULT_SCALAR_TYPE);
# endif
#endif // JETS_DEFAULT_QUADRUPLE_PRECISION

#ifdef JETS_HAVE_MPI

#define JETS_MPI_PAIR_BINARY(funcname) \
static inline void \
jets_mpi_pair_##funcname(void * a, void * b, int * len, MPI_Datatype *) \
{ \
  const int size = *len; \
 \
  const std::pair<T,U> * in = static_cast<std::pair<T,U> *>(a); \
  std::pair<T,U> * inout = static_cast<std::pair<T,U> *>(b); \
  for (int i=0; i != size; ++i) \
    { \
      inout[i].first = std::funcname(in[i].first,inout[i].first); \
      inout[i].second = std::funcname(in[i].second,inout[i].second); \
    } \
}

# define JETS_MPI_PAIR_LOCATOR(funcname) \
static inline void \
jets_mpi_pair_##funcname##_location(void * a, void * b, int * len, MPI_Datatype *) \
{ \
  const int size = *len; \
 \
  typedef std::pair<std::pair<T,U>, int> dtype; \
 \
  dtype *in = static_cast<dtype*>(a); \
  dtype *inout = static_cast<dtype*>(b); \
  for (int i=0; i != size; ++i) \
    { \
      std::pair<T,U> old_inout = inout[i].first; \
      inout[i].first.first  = std::funcname(in[i].first.first, inout[i].first.first); \
      inout[i].first.second = std::funcname(in[i].first.second,inout[i].first.second); \
      if (old_inout != inout[i].first) \
        inout[i].second = in[i].second; \
    } \
}


# define JETS_MPI_PAIR_BINARY_FUNCTOR(funcname) \
static inline void \
jets_mpi_pair_##funcname(void * a, void * b, int * len, MPI_Datatype *) \
{ \
  const int size = *len; \
 \
  const std::pair<T,U> * in = static_cast<std::pair<T,U> *>(a); \
  std::pair<T,U> * inout = static_cast<std::pair<T,U> *>(b); \
  for (int i=0; i != size; ++i) \
    { \
      inout[i].first  = std::funcname<T>()(in[i].first, inout[i].first); \
      inout[i].second = std::funcname<T>()(in[i].second,inout[i].second); \
    } \
}


template<typename T, typename U>
class OpFunction<std::pair<T, U>>
{
  JETS_MPI_PAIR_BINARY(max)
    JETS_MPI_PAIR_BINARY(min)
    JETS_MPI_PAIR_LOCATOR(max)
    JETS_MPI_PAIR_LOCATOR(min)
    JETS_MPI_PAIR_BINARY_FUNCTOR(plus)
    JETS_MPI_PAIR_BINARY_FUNCTOR(multiplies)

public:
  JETS_MPI_OPFUNCTION(max, pair_max)
    JETS_MPI_OPFUNCTION(min, pair_min)
    JETS_MPI_OPFUNCTION(sum, pair_plus)
    JETS_MPI_OPFUNCTION(product, pair_multiplies)

    JETS_MPI_OPFUNCTION(max_location, pair_max_location)
    JETS_MPI_OPFUNCTION(min_location, pair_min_location)
};
# else // JETS_HAVE_MPI
template<typename T, typename U>
class OpFunction<std::pair<T, U>> {};
#endif

} // namespace parallel
} // namespace jets
#endif // __JETS_PAR_OPFUNCTION_H__