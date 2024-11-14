#ifndef __JETSEXP_H__
#define __JETSEXP_H__
#include "jetscfg.h"
#include <stdexcept>
#include <string>
#include <sstream>

namespace jets
{

/**
 * A class to represent the internal "this should never happen"
 * errors, to be thrown by "jets_error();"
 */
class LogicError : public std::logic_error
{
public:
  LogicError() : std::logic_error( "Error in jets internal logic" ) {}
  LogicError(const std::string & msg) : std::logic_error( msg ) {}
};


/**
 * A class to stub for features that should be in jets, but
 * haven't been written yet, to be thrown by
 * "jets_not_implemented();"
 */
class NotImplemented : public std::logic_error
{
public:
  NotImplemented(std::string msg="") : std::logic_error( "Error: feature not implemented!\n" + msg ) {}
};

/**
 * A class to represent that a class is abstract and cannot be
 * instantiated.
 */
class AbstractClassError : public std::logic_error
{
public:
  AbstractClassError(std::string msg="") : std::logic_error( "Error: abstract class cannot be instantiated!\n" + msg ) {}
};


/**
 * A class representing a failed attempt by the library to open a
 * file (or construct an fstream, etc), to be thrown by
 * "jets_file_error(filename);" For ease of debugging, "filename"
 * should include any (absolute or relative or implicit) pathname
 * that was part of the failed open.
 */
class FileError : public std::runtime_error
{
public:
  FileError(const std::string & filename, const std::string msg="") :
    std::runtime_error("Error with file `" + filename + "'\n" + std::move(msg)) {}
};


/**
 * A class representing a solver's failure to converge, to be thrown
 * by "jets_convergence_failure();"  This should be a last
 * resort; more often, a solve which has failed should be
 * reattempted after switching to a smaller timestep, adding
 * underrelaxation, taking a smaller continuation step, etc.
 */
class ConvergenceFailure : public std::runtime_error
{
public:
  ConvergenceFailure() : std::runtime_error( "Unrecoverable failure to converge" ) {}
};


/**
 * A class representing that a dynamic cast failed to produce expected output.
 */
class DynamicCastFailure:  public std::runtime_error
{
public:
  DynamicCastFailure() : std::runtime_error( "Failed dynamic cast!" ) {}
};

/**
 * A class representing a floating point exception.
 */
class FloatingPointException: public std::runtime_error
{
public:
  FloatingPointException() : std::runtime_error( "jets FPE!" ) {}
};
} // namespace jets

#ifdef JETS_ENABLE_EXCEPTIONS
#define jets_noexcept noexcept

#define JETS_THROW(e) do { throw e; } while (0)
#define jets_rethrow throw
#define jets_try try
#define jets_catch(e) catch(e)

#else

#define JETS_THROW(e) do { jets::err << e.what(); std::abort(); } while (0)
#define jets_rethrow
#define jets_try
#define jets_catch(e) if (0)
#endif // JETS_ENABLE_EXCEPTIONS
#endif // __JETSEXP_H__