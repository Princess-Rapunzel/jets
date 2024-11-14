#ifndef __JETSCOMM_H__
#define __JETSCOMM_H__

#if defined(DEBUG) && defined(NDEBUG)
#  error DEBUG and NDEBUG should never be defined simultaneously
#endif
#include "jetscfg.h"

#include <typeinfo> // std::bad_cast
#include <type_traits> // std::decay
#include <functional> // std::less, etc
// #include <mutex>
#ifdef JETS_HAVE_MPI
# include <mpi.h>
#endif // JETS_HAVE_MPI
#include <iostream>
#include <iomanip>
#include <cmath>
// extern spin_mutex spin_mtx;
#include "ostream_proxy.h"
#include "jetsexp.h"
#include "jetsbase.h"
// Use actual timestamps or constant dummies (to aid ccache)
#ifdef JETS_ENABLE_TIMESTAMPS
#  define  JETS_TIME __TIME__
#  define  JETS_DATE __DATE__
#else
#  define  JETS_TIME "notime"
#  define  JETS_DATE "nodate"
#endif // jets_ENABLE_TIMESTAMPS
#ifdef JETS_HAVE_PTHREAD
# include <pthread.h>
#endif
namespace jets
{
namespace sync
{

#ifdef JETS_HAVE_PTHREAD
class spin_mutex
{
public:
  // Might want to use PTHREAD_MUTEX_ADAPTIVE_NP on Linux, but it's not available on OSX.
  spin_mutex() { pthread_spin_init(&slock, PTHREAD_PROCESS_PRIVATE); }
  ~spin_mutex() { pthread_spin_destroy(&slock); }

  void lock () { pthread_spin_lock(&slock); }
  void unlock () { pthread_spin_unlock(&slock); }

  class scoped_lock
  {
  public:
    scoped_lock () : smutex(nullptr) {}
    explicit scoped_lock ( spin_mutex & in_smutex ) : smutex(&in_smutex) { smutex->lock(); }

    ~scoped_lock () { release(); }

    void acquire ( spin_mutex & in_smutex ) { smutex = &in_smutex; smutex->lock(); }
    void release () { if (smutex) smutex->unlock(); smutex = nullptr; }

  private:
    spin_mutex * smutex;
  };

private:
  pthread_spinlock_t slock;
};
#else
class spin_mutex
{
public:
  spin_mutex() {}
  void lock () {}
  void unlock () {}

  class scoped_lock
  {
  public:
    scoped_lock () {}
    explicit scoped_lock ( spin_mutex &  ) {}
    void acquire ( spin_mutex & ) {}
    void release () {}
  };
};
#endif // JETS_HAVE_PTHREAD
void lock_singleton_spin_mutex();
void unlock_singleton_spin_mutex();
} // namespace sync


extern OStreamProxy out;
extern OStreamProxy err;

// A namespace for functions used in the bodies of the macros below.
// The macros generally call these functions with __FILE__, __LINE__,
// __DATE__, and __TIME__ in the appropriate order.  These should not
// be called by users directly!  The implementations can be found in
// jets_common.C.
namespace MacroFunctions
{
void here(const char * file, int line, const char * date, const char * time, std::ostream & os = jets::err);
void stop(const char * file, int line, const char * date, const char * time);
void report_error(const char * file, int line, const char * date, const char * time, std::ostream & os = jets::err);
}

// Undefine any existing macros
#ifdef Real
#  undef Real
#endif

#ifdef Complex
#  undef Complex
#endif

#ifdef JETS_HAVE_COMPLEX
#include <complex>
typedef std::complex<double> Complex;
#endif // JETS_HAVE_COMPLEX

#ifdef JETS_DEFAULT_DOUBLE_PRECISION
typedef double Real;
#else
typedef float Real;
#endif // JETS_DEFAULT_DOUBLE_PRECISION
#ifdef JETS_HAVE_COMPLEX
typedef Complex Number;
#else
typedef Real Number;
#endif // JETS_HAVE_COMPLEX

enum class JETS_DIM: int {
  DIM_1 = 1,
  DIM_2 = 2,
  DIM_3 = 3
};

typedef JETS_DIM Dim;

static constexpr unsigned int JETS_MAX_DIM = 3;

static constexpr Real TOLERANCE = 1.e-6;

#define jets_isnan(x) (std::isnan(std::real(a)) || std::isnan(std::imag(a)))
#define jets_isinf(x) (std::isinf(x))
#define jets_iscinf(x) (std::isinf(std::real(a)) || std::isinf(std::imag(a)))

#ifdef jets_HAVE_MPI
/**
 * MPI Communicator used to initialize jets.
 */
extern MPI_Comm GLOBAL_COMM_WORLD;
#else

/**
 * Something to use with CHKERRABORT if we're just using PETSc's MPI
 * "uni" stub.
 */
extern int GLOBAL_COMM_WORLD;
#endif // jets_HAVE_MPI

// These are useful macros that behave like functions in the code.
// If you want to make sure you are accessing a section of code just
// stick a jets_here(); in it, for example
#define jets_here()                                                  \
  do {                                                                  \
    jets::MacroFunctions::here(__FILE__, __LINE__, JETS_DATE, JETS_TIME); \
  } while (0)

// the jets_stop() macro will stop the code until a SIGCONT signal
// is received.  This is useful, for example, when determining the
// memory used by a given operation.  A jets_stop() could be
// inserted before and after a questionable operation and the delta
// memory can be obtained from a ps or top.  This macro only works for
// serial cases.
#define jets_stop()                                                  \
  do {                                                                  \
    jets::MacroFunctions::stop(__FILE__, __LINE__, JETS_DATE, JETS_TIME); \
  } while (0)

// The jets_dbg_var() macro indicates that an argument to a function
// is used only in debug mode (i.e., when NDEBUG is not defined).
#ifndef NDEBUG
#define jets_dbg_var(var) var
#else
#define jets_dbg_var(var)
#endif

#ifdef NDEBUG
#define jets_assert_msg(asserted, msg)  ((void) 0)
#define jets_assert_equal_to_msg(expr1,expr2, msg)  ((void) 0)
#define jets_assert_not_equal_to_msg(expr1,expr2, msg)  ((void) 0)
#define jets_assert_less_msg(expr1,expr2, msg)  ((void) 0)
#define jets_assert_greater_msg(expr1,expr2, msg)  ((void) 0)
#define jets_assert_less_equal_msg(expr1,expr2, msg)  ((void) 0)
#define jets_assert_greater_equal_msg(expr1,expr2, msg)  ((void) 0)

#else
#define jets_assertion_types(expr1,expr2)                            \
  typedef typename std::decay<decltype(expr1)>::type jets_type1;     \
  typedef typename std::decay<decltype(expr2)>::type jets_type2

#define jets_assert_msg(asserted, msg)                               \
  do {                                                                  \
    if (!(asserted)) {                                                  \
      jets_error_msg(msg);                                           \
    } } while (0)


#define jets_assert_equal_to_msg(expr1,expr2, msg)                   \
  do {                                                                  \
    if (!((expr1) == (expr2))) {                                        \
      jets_error_msg(std::setprecision(17) << "Assertion `" #expr1 " == " #expr2 "' failed.\n" #expr1 " = " << (expr1) << "\n" #expr2 " = " << (expr2) << '\n' << msg << std::endl); \
    } } while (0)

#define jets_assert_not_equal_to_msg(expr1,expr2, msg)               \
  do {                                                                  \
    if (!((expr1) != (expr2))) {                                        \
      jets_error_msg(std::setprecision(17) << "Assertion `" #expr1 " != " #expr2 "' failed.\n" #expr1 " = " << (expr1) << "\n" #expr2 " = " << (expr2) << '\n' << msg << std::endl); \
    } } while (0)

template <template <class> class Comp>
struct casting_compare {

  template <typename T1, typename T2>
  bool operator()(const T1 & e1, const T2 & e2) const
  {
    typedef typename std::decay<T1>::type DT1;
    typedef typename std::decay<T2>::type DT2;
    return (Comp<DT2>()(static_cast<DT2>(e1), e2) &&
            Comp<DT1>()(e1, static_cast<DT1>(e2)));
  }

  template <typename T1>
  bool operator()(const T1 & e1, const T1 & e2) const
  {
    return Comp<T1>()(e1, e2);
  }
};

#define jets_assert_less_msg(expr1,expr2, msg)                       \
  do {                                                                  \
    if (!jets::casting_compare<std::less>()(expr1, expr2)) {         \
      jets_error_msg(std::setprecision(17) << "Assertion `" #expr1 " < " #expr2 "' failed.\n" #expr1 " = " << (expr1) << "\n" #expr2 " = " << (expr2) << '\n' << msg << std::endl); \
    } } while (0)

#define jets_assert_greater_msg(expr1,expr2, msg)                    \
  do {                                                                  \
    if (!jets::casting_compare<std::greater>()(expr1, expr2)) {      \
      jets_error_msg(std::setprecision(17) << "Assertion `" #expr1 " > " #expr2 "' failed.\n" #expr1 " = " << (expr1) << "\n" #expr2 " = " << (expr2) << '\n' << msg << std::endl); \
    } } while (0)

#define jets_assert_less_equal_msg(expr1,expr2, msg)                 \
  do {                                                                  \
    if (!jets::casting_compare<std::less_equal>()(expr1, expr2)) {   \
      jets_error_msg(std::setprecision(17) << "Assertion `" #expr1 " <= " #expr2 "' failed.\n" #expr1 " = " << (expr1) << "\n" #expr2 " = " << (expr2) << '\n' << msg << std::endl); \
    } } while (0)

#define jets_assert_greater_equal_msg(expr1,expr2, msg)              \
  do {                                                                  \
    if (!jets::casting_compare<std::greater_equal>()(expr1, expr2)) { \
      jets_error_msg(std::setprecision(17) << "Assertion `" #expr1 " >= " #expr2 "' failed.\n" #expr1 " = " << (expr1) << "\n" #expr2 " = " << (expr2) << '\n' << msg << std::endl); \
    } } while (0)

#endif

#define jets_assert(asserted) jets_assert_msg(asserted, "")
#define jets_assert_equal_to(expr1,expr2) jets_assert_equal_to_msg(expr1,expr2, "")
#define jets_assert_not_equal_to(expr1,expr2) jets_assert_not_equal_to_msg(expr1,expr2, "")
#define jets_assert_less(expr1,expr2) jets_assert_less_msg(expr1,expr2, "")
#define jets_assert_greater(expr1,expr2) jets_assert_greater_msg(expr1,expr2, "")
#define jets_assert_less_equal(expr1,expr2) jets_assert_less_equal_msg(expr1,expr2, "")
#define jets_assert_greater_equal(expr1,expr2) jets_assert_greater_equal_msg(expr1,expr2, "")

// prints a message and throws a LogicError exception.
#define jets_error_msg(msg)                                          \
  do {                                                                  \
    std::stringstream message_stream;                                   \
    message_stream << msg << '\n';                                      \
    jets::sync::lock_singleton_spin_mutex();                      \
    jets::MacroFunctions::report_error(__FILE__, __LINE__, JETS_DATE, JETS_TIME, message_stream); \
    jets::sync::unlock_singleton_spin_mutex();                    \
    JETS_THROW(jets::LogicError(message_stream.str()));         \
  } while (0)

#define jets_error() jets_error_msg("")

#define jets_error_msg_if(cond, msg)         \
  do {                                          \
    if (cond)                                   \
      jets_error_msg(msg);                   \
  } while (0)

#define jets_not_implemented_msg(msg)                                \
  do {                                                                  \
    std::stringstream message_stream;                                   \
    message_stream << msg << '\n';                                      \
    jets::sync::lock_singleton_spin_mutex();                      \
    jets::MacroFunctions::report_error(__FILE__, __LINE__, JETS_DATE, JETS_TIME, message_stream); \
    jets::sync::unlock_singleton_spin_mutex();                    \
    JETS_THROW(jets::NotImplemented(message_stream.str()));       \
  } while (0)

#define jets_abstract_class_msg(msg)                            \
  do {                                                              \
    std::stringstream message_stream;                               \
    message_stream << msg << '\n';                                  \
    jets::sync::lock_singleton_spin_mutex();                  \
    jets::MacroFunctions::report_error(__FILE__, __LINE__, JETS_DATE, JETS_TIME, message_stream); \
    jets::sync::unlock_singleton_spin_mutex();                \
    JETS_THROW(jets::AbstractClassError(message_stream.str())); \
  } while (0)

#define jets_not_implemented() jets_not_implemented_msg("")

#define jets_abstract_class() jets_abstract_class_msg("")

#define jets_file_error_msg(filename, msg)                           \
  do {                                                                  \
    std::stringstream message_stream;                                   \
    message_stream << msg << '\n';                                      \
    jets::sync::lock_singleton_spin_mutex();                      \
    jets::MacroFunctions::report_error(__FILE__, __LINE__, JETS_DATE, JETS_TIME, message_stream); \
    jets::sync::unlock_singleton_spin_mutex();                    \
    JETS_THROW(jets::FileError(filename, message_stream.str()));  \
  } while (0)

// The jets_warning macro outputs a file/line/time stamped warning
// message, if warnings are enabled.
#ifdef JETS_ENABLE_WARNINGS
#define jets_warning(message)                                        \
  jets_do_once(jets::out << message                               \
                  << __FILE__ << ", line " << __LINE__ << ", compiled " << JETS_DATE << " at " << JETS_TIME << " ***" << std::endl;)
#else
#define jets_warning(message)  ((void) 0)
#endif

// A function template for ignoring unused variables.  This is a way
// to shut up unused variable compiler warnings on a case by case
// basis.
template<class ...Args> inline void jets_ignore( const Args&... ) { }

// cast_ref and cast_ptr do a dynamic cast and assert
// the result, if we have RTTI enabled and we're in debug or
// development modes, but they just do a faster static cast if we're
// in optimized mode.
//
// Use these casts when you're certain that a cast will succeed in
// correct code but you want to be able to double-check.
template <typename Tnew, typename Told>
inline Tnew cast_ref(Told & oldvar)
{
#if !defined(NDEBUG) && defined(JETS_HAVE_RTTI) && defined(JETS_ENABLE_EXCEPTIONS)
  try
    {
      Tnew newvar = dynamic_cast<Tnew>(oldvar);
      return newvar;
    }
  catch (std::bad_cast &)
    {
      jets::err << "Failed to convert " << typeid(Told).name()
                   << " reference to " << typeid(Tnew).name()
                   << std::endl;
      jets::err << "The " << typeid(Told).name()
                   << " appears to be a "
                   << typeid(*(&oldvar)).name() << std::endl;
      jets_error();
    }
#else
  return(static_cast<Tnew>(oldvar));
#endif
}

// We use two different function names to avoid an odd overloading
// ambiguity bug with icc 10.1.008
template <typename Tnew, typename Told>
inline Tnew cast_ptr (Told * oldvar)
{
#if !defined(NDEBUG) && defined(JETS_HAVE_RTTI)
  Tnew newvar = dynamic_cast<Tnew>(oldvar);
  if (!newvar)
    {
      jets::err << "Failed to convert " << typeid(Told).name()
                   << " pointer to " << typeid(Tnew).name()
                   << std::endl;
      jets::err << "The " << typeid(Told).name()
                   << " appears to be a "
                   << typeid(*oldvar).name() << std::endl;
      jets();
    }
  return newvar;
#else
  return(static_cast<Tnew>(oldvar));
#endif
}

// static constexpr std::size_t jets_dim = JETS_DIM;

} // namespace jets
#endif // __JETSCOMM_H__