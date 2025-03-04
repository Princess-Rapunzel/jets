#ifndef __JETS_PARALLEL_DATA_TYPE_H__
#define __JETS_PARALLEL_DATA_TYPE_H__

#include "jetscfg.h"
#include "mpi_micro.h"

namespace jets
{

namespace parallel
{
#ifdef JETS_HAVE_MPI
//-------------------------------------------------------------------
/**
 * Data types for communication
 */
typedef MPI_Datatype data_type;

#else

// These shouldn't actually be needed, but must be
// unique types for function overloading to work
// properly.
struct data_type    { /* unsigned int t; */ };

#endif // TIMPI_HAVE_MPI



//-------------------------------------------------------------------
/**
 * Encapsulates the MPI_Datatype.
 */
class DataType
{
public:
  DataType () = default;
  DataType (const DataType & other) = default;
  DataType (DataType && other) = default;
  static const bool is_fixed_type = true;

  DataType (const data_type & type) :
    _datatype(type)
  {}

  DataType (const DataType & other, unsigned int count)
  {
    // FIXME - if we nest an inner type here will we run into bug
    // https://github.com/libMesh/libmesh/issues/631 again?
    jets_call_mpi(MPI_Type_contiguous(count, other._datatype, &_datatype));
    ignore(other, count); // ifndef TIMPI_HAVE_MPI
    this->commit();
  }

  virtual ~DataType () = default;

  DataType & operator = (const DataType & other) = default;
  DataType & operator = (DataType && other) = default;

  DataType & operator = (const data_type & type)
  { _datatype = type; return *this; }

  operator const data_type & () const
  { return _datatype; }

  operator data_type & ()
  { return _datatype; }

  //     operator data_type const * () const
  //     { return &_datatype; }

  //     operator data_type * ()
  //     { return &_datatype; }

  void commit ()
  {
    jets_call_mpi
      (MPI_Type_commit (&_datatype));
  }

  void free ()
  {
    jets_call_mpi
      (MPI_Type_free (&_datatype));
  }

protected:

  data_type _datatype;
};

/**
 * StandardType<T>'s which do not define a way to \p MPI_Type \p T should
 * inherit from this class. This class is primarily defined for backwards
 * compatability because it defines \p is_fixed_type = false for
 * non-fixed/non-mpi-typed StandardTypes. This class also provides a fairly
 * convenient way to define communication overloads that are antithetical to \p
 * DataType counterparts. E.g. when doing our parallel algorithms we may build a
 * \p StandardType and then call communication routines with that type. We want
 * to ensure that we dispatch to different methods when \p StandardType defines
 * MPI typing vs. when it does not. The \p DataType vs. \p NotADataType typing
 * accomplishes that goal
 */
class NotADataType
{
public:
  NotADataType () = default;
  NotADataType (const NotADataType & other) = default;
  NotADataType (NotADataType && other) = default;
  ~NotADataType () = default;
  NotADataType & operator = (const NotADataType & other) = default;
  NotADataType & operator = (NotADataType && other) = default;

  static const bool is_fixed_type = false;
};

template <bool>
struct MaybeADataType {
  typedef DataType type;
};

template <>
struct MaybeADataType<false>
{
  typedef NotADataType type;
};
} // namespace parallel
} // namespace jets
#endif // __JETS_PARALLEL_DATA_TYPE_H__