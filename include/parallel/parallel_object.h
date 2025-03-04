#ifndef __JETS_PARALLEL_OBJECT_H__
#define __JETS_PARALLEL_OBJECT_H__

#include "communicator.h"
namespace jets
{
/**
 * \brief An object whose state is distributed along a set of processors.
 *
 * This class forms the base class for all other classes
 * that are expected to be implemented in parallel. Each
 * \p ParallelObject *requires* a \p Parallel::Communicator object
 * for construction.
 */
class ParallelObject
{
public:

  /**
   * Constructor. Requires a reference to the communicator
   * that defines the object's parallel decomposition.
   */
  ParallelObject(const parallel::Communicator & comm_in) :
    _communicator(comm_in) {}

  /**
   * Copy Constructor.
   */
  ParallelObject(const ParallelObject& other) :
    _communicator(other._communicator) {}

  /**
   * "Assignment" operator.  Simply asserts our references
   * are identical because this is the only thing that makes
   * sense
   */
  ParallelObject & operator=(const ParallelObject& other)
  {
    libmesh_assert_equal_to(&_communicator, &other._communicator);
    return *this;
  }

  /**
   * Destructor.  Virtual because we are a base class.
   */
  virtual ~ParallelObject() = default;

  /**
   * \returns A reference to the \p Parallel::Communicator object
   * used by this mesh.
   */
  const parallel::Communicator& comm () const
  { return _communicator; }

  /**
   * \returns The number of processors in the group.
   */
  processor_id_type n_processors () const;
  // {
  //   processor_id_type returnval =
  //     cast_int<processor_id_type>(_communicator.size());
  //   libmesh_assert(returnval); // We never have an empty comm
  //   return returnval;
  // }

  /**
   * \returns The rank of this processor in the group.
   */
  processor_id_type processor_id () const;
  // { return cast_int<processor_id_type>(_communicator.rank()); }


protected:

  const parallel::Communicator& _communicator;
};
} // namespace jets

#endif // __JETS_PARALLEL_OBJECT_H__