#include "communicator.h"
#include "mpi_micro.h"
#include "standard_type.h"
#include "opfunction.h"

namespace jets
{

namespace parallel
{

Communicator::Communicator() :
#ifdef JETS_HAVE_MPI
  _communicator(MPI_COMM_SELF),
#endif
  _rank(0),
  _size(1),
  _send_mode(DEFAULT),
  _sync_type(NBX)
{}

Communicator::Communicator(const communicator& comm) :
#ifdef JETS_HAVE_MPI
  _communicator(MPI_COMM_WORLD),
#endif
  _rank(0),
  _size(1),
  _send_mode(DEFAULT),
  _sync_type(NBX)
  // used_tag_values(),
  // _next_tag(0),
  // _max_tag(std::numeric_limits<int>::max()),
  // _I_duped_it(false)
{
  this->assign(comm);
}

Communicator::~Communicator()
{
  this->clear();
}

void Communicator::clear()
{
#ifdef JETS_HAVE_MPI
  // if (_I_duped_it)
  //   {
  //     timpi_assert (_communicator != MPI_COMM_NULL);
  //     timpi_call_mpi
  //       (MPI_Comm_free(&_communicator));

  //     _communicator = MPI_COMM_NULL;
  //   }
  // _I_duped_it = false;
  jets_assert(_communicator != MPI_COMM_NULL);
  // TODO: Free the communicator correctly.
  // Error: Cannot free permanent communicator MPI_COMM_WORLD
  // jets_call_mpi(MPI_Comm_free(&_communicator));

  // _communicator=MPI_COMM_NULL;
#endif
}

void Communicator::barrier() const
{
  if (this->size() > 1)
  {
    jets_call_mpi(MPI_Barrier(this->get()));
  }
}

#ifdef JETS_HAVE_MPI
void Communicator::nonblocking_barrier (Request & req) const
{
  if (this->size() > 1)
    {
      jets_call_mpi(MPI_Ibarrier (this->get(), req.get()));
    }
}
#else
void Communicator::nonblocking_barrier (Request & /*req*/) const {}
#endif

void Communicator::assign(const communicator& comm)
{
  this->_communicator=comm;
#ifdef JETS_HAVE_MPI
  if (_communicator != MPI_COMM_NULL)
  {
    int i;
    jets_call_mpi(MPI_Comm_size(_communicator, &i));
    jets_assert_greater_equal(i, 0);
    this->_size=jets_cast_int<processor_id_type>(i);

    jets_call_mpi(MPI_Comm_rank(_communicator, &i));
    jets_assert_greater_equal(i, 0);
    this->_rank=jets_cast_int<processor_id_type>(i);

  //   int * maxTag;
  //   int flag = false;
  //   timpi_call_mpi(MPI_Comm_get_attr(MPI_COMM_WORLD, MPI_TAG_UB, &maxTag, &flag));
  //   timpi_assert(flag);
  //   _max_tag = *maxTag;
  }
  else
  {
    _rank=0;
    _size=1;
  //   _max_tag = std::numeric_limits<int>::max();
  }
//   _next_tag = _max_tag / 2;
#endif
}

status Communicator::probe(const unsigned int src_processor_id,
                            const MessageTag& tag) const
{
#ifndef JETS_HAVE_MPI
  jets_not_implemented();
  ignore(src_processor_id, tag);
#endif
  jets_assert(src_processor_id < this->size() ||
                  src_processor_id == any_source);
  status stat;
  jets_call_mpi
  (MPI_Probe(int(src_processor_id), tag.value(), this->get(), &stat));
  return stat;
}
} // namespace parallel
} // namespace jets
