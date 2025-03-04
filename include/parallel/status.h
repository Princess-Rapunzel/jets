#ifndef __JETS_PARALLEL_STATUS_H__
#define __JETS_PARALLEL_STATUS_H__

#include "jetscfg.h"
#include "data_type.h"
#include "jetscomm.h"
namespace jets
{

namespace parallel
{
#ifdef JETS_HAVE_MPI

//-------------------------------------------------------------------

/**
 * Status object for querying messages
 */
typedef MPI_Status status;

#else

// This shouldn't actually be needed, but must be
// unique types for function overloading to work
// properly.
struct status { /* unsigned int s; */ };

#endif // JETS_HAVE_MPI



//-------------------------------------------------------------------
/**
 * Encapsulates the MPI_Status struct.  Allows the source and size
 * of the message to be determined.
 */
class Status
{
public:
    Status()=default;
    ~Status()=default;
    Status(const Status&)=default;
    Status(Status&&)=default;
    Status& operator=(const Status&)=default;
    Status& operator=(Status&&)=default;

    explicit Status(const data_type& type);

    explicit Status(const status& status);

    Status(const status& status,
            const data_type& type);

    Status(const Status& status,
            const data_type& type);

    status* get() { return &_status; }

    status const* get() const { return &_status; }

    int source() const;

    int tag() const;

    data_type& datatype() { return _datatype; }

    const data_type& datatype() const { return _datatype; }

    unsigned int size(const data_type& type) const;

    unsigned int size() const;

private:

    status    _status;
    data_type _datatype;
};

// ------------------------------------------------------------
// Status member functions

inline Status::Status(const data_type& type) :
    _status(),
    _datatype(type)
{}

inline Status::Status(const status& stat) :
    _status(stat),
    _datatype()
{}

inline Status::Status(const status& stat,
                       const data_type& type) :
    _status(stat),
    _datatype(type)
{}

inline Status::Status(const Status& stat,
                       const data_type& type) :
    _status(stat._status),
    _datatype(type)
{}

inline int Status::source() const
{
#ifdef JETS_HAVE_MPI
    return _status.MPI_SOURCE;
#else
    return 0;
#endif
}

inline int Status::tag() const
{
#ifdef JETS_HAVE_MPI
    return _status.MPI_TAG;
#else
    jets_not_implemented();
    return 0;
#endif
}

inline unsigned int Status::size(const data_type& type) const
{
    ignore(type); // We don't use this ifndef JETS_HAVE_MPI
    int msg_size=1;
    jets_call_mpi
    (MPI_Get_count(const_cast<MPI_Status*>(&_status), type,
        &msg_size));

    jets_assert_greater_equal(msg_size, 0);
    return msg_size;
}

inline unsigned int Status::size() const
{
    return this->size(this->datatype());
}

} // namespace parallel
} // namespace jets

#endif // __JETS_PARALLEL_STATUS_H__