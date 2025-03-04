#ifndef __JETS_COMMUNICATOR_H__
#define __JETS_COMMUNICATOR_H__

#include "jetscomm.h"
#include "message_tag.h"
#include "mpi_micro.h"
#include "standard_type.h"
#include "opfunction.h"
#include "request.h"
#include "status.h"
// C++ includes
#include <vector>
#include <type_traits>
namespace jets
{
namespace parallel
{
#ifdef JETS_HAVE_MPI

/**
 * Communicator object for talking with subsets of processors
 */
typedef MPI_Comm communicator;

/**
 * Info object used by some MPI-3 methods
 */
typedef MPI_Info info;

/**
 * Processor id meaning "Accept from any source"
 */
const unsigned int any_source=
static_cast<unsigned int>(MPI_ANY_SOURCE);

#else

// These shouldn't actually be needed, but must be
// unique types for function overloading to work
// properly.
typedef int communicator; // Must match petsc-nompi definition

typedef int info;

const unsigned int any_source=0;
#endif

class Communicator
{
public:
  Communicator();
  explicit Communicator(const communicator& comm);
  ~Communicator();

  /*
   * Don't use copy construction or assignment, just copy by reference
   * or pointer - it's too hard to keep a common used_tag_values if
   * each communicator is shared by more than one Communicator
   */
  Communicator(const Communicator&)=delete;
  Communicator& operator= (const Communicator&)=delete;
  /*
   * Move constructor and assignment operator
   */
  Communicator(Communicator&&)=default;
  Communicator& operator= (Communicator&&)=default;

  communicator& get() { return _communicator; }

  const communicator& get() const { return _communicator; }

  /**
   * Free and reset this communicator
   */
  void clear();

  processor_id_type rank() const { return _rank; }

  processor_id_type size() const { return _size; }

  bool is_rank_at(const processor_id_type rank) const
  {
    return this->rank() == rank;
  }

  bool is_rank0() const { return this->is_rank_at(0); }

  /**
   * Whether to use default or synchronous sends?
   */
  enum SendMode { DEFAULT=0, SYNCHRONOUS };

  /**
   * What algorithm to use for parallel synchronization?
   */
  enum SyncType { NBX, ALLTOALL_COUNTS, SENDRECEIVE };


  /**
   * Explicitly sets the \p SendMode type used for send operations.
   */
  void send_mode(const SendMode sm) { _send_mode=sm; }

  /**
   * Gets the user-requested SendMode.
   */
  SendMode send_mode() const { return _send_mode; }

  /**
   * Explicitly sets the \p SyncType used for sync operations.
   */
  void sync_type(const SyncType st) { _sync_type=st; }

  /**
   * Sets the sync type used for sync operations via a string.
   *
   * Useful for changing the sync type via a CLI arg or parameter.
   */
  void sync_type(const unsigned int& st);

  /**
   * Gets the user-requested SyncType.
   */
  SyncType sync_type() const { return _sync_type; }

  /**
   * Pause execution until all processors reach a certain point.
   */
  void barrier() const;

  /**
   * Start a barrier that doesn't block
   */
  void nonblocking_barrier(Request& req) const;

 /**
  * Non-blocking minimum of the local value \p r into \p o
  * with the request \p req.
  */
  template <typename T>
  inline void min(const T& r, T& o, Request& req) const;

  /**
   * Take a local variable and replace it with the minimum of it's values
   * on all processors.  Containers are replaced element-wise.
   */
  template <typename T>
  inline void min(T& r) const;

  /**
   * Take a local variable and replace it with the minimum of it's values
   * on all processors, returning the minimum rank of a processor
   * which originally held the minimum value.
   */
  template <typename T>
  inline void minloc(T& r,
                unsigned int& min_id) const;

  /**
   * Non-blocking maximum of the local value \p r into \p o
   * with the request \p req.
   */
  template <typename T>
  inline void max(const T& r, T& o, Request& req) const;

  /**
   * Take a local variable and replace it with the maximum of it's values
   * on all processors.  Containers are replaced element-wise.
   */
  template <typename T>
  inline void max(T& r) const;

  /**
   * Take a local variable and replace it with the maximum of it's values
   * on all processors, returning the minimum rank of a processor
   * which originally held the maximum value.
   */
  template <typename T>
  inline void maxloc(T& r, unsigned int& max_id) const;

  /**
   * Take a local variable and replace it with the sum of it's values
   * on all processors.  Containers are replaced element-wise.
   */
  template <typename T>
  inline void sum(T& r) const;

  /**
   * Non-blocking sum of the local value \p r into \p o
   * with the request \p req.
   */
  template <typename T>
  inline void sum(const T& r, T& o, Request& req) const;

  /**
   * Blocking message probe.  Allows information about a message to be
   * examined before the message is actually received.
   */
  status probe(const unsigned int src_processor_id,
               const MessageTag& tag=any_tag) const;

  /**
   * Blocking-send to one processor with data-defined type.
   */
  template <typename T>
  inline void send(const unsigned int dest_processor_id,
                   const T& buf,
                   const MessageTag& tag=no_tag) const;

  /**
   * Nonblocking-send to one processor with data-defined type.
   */
  template <typename T>
  inline void send(const unsigned int dest_processor_id,
                   const T& buf,
                   Request& req,
                   const MessageTag& tag=no_tag) const;

  /**
   * Blocking-send to one processor with user-defined type.
   *
   * If \p T is a container, container-of-containers, etc., then
   * \p type should be the DataType of the underlying fixed-size
   * entries in the container(s).
   */
  template <typename T>
  inline void send(const unsigned int dest_processor_id,
                   const T& buf,
                   const DataType& type,
                   const MessageTag& tag=no_tag) const;


  /**
   * Nonblocking-send to one processor with user-defined type.
   *
   * If \p T is a container, container-of-containers, etc., then
   * \p type should be the DataType of the underlying fixed-size
   * entries in the container(s).
   */
  template <typename T>
  inline void send(const unsigned int dest_processor_id,
                   const T& buf,
                   const DataType& type,
                   Request& req,
                   const MessageTag& tag=no_tag) const;

  /**
   * Nonblocking-send to one processor with user-defined packable type.
   * \p Packing<T> must be defined for \p T
   */
  template <typename T>
  inline void send(const unsigned int dest_processor_id,
                   const T& buf,
                   const NotADataType& type,
                   Request& req,
                   const MessageTag& tag=no_tag) const;


  template <typename T, typename A>
  inline void send(const unsigned int dest_processor_id,
                   const std::vector<T, A>& buf,
                   const MessageTag& tag=no_tag) const;

  template <typename T, typename A,
    typename std::enable_if<std::is_base_of<DataType, StandardType<T>>::value, int>::type=0>
  inline void send(const unsigned int dest_processor_id,
               const std::vector<T, A>& buf,
               Request& req,
               const MessageTag& tag=no_tag) const;

  template <typename T, typename A>
  inline void send(const unsigned int dest_processor_id,
                   const std::vector<T, A>& buf,
                   const DataType& type,
                   const MessageTag& tag=no_tag) const;


  template <typename T, typename A1, typename A2>
  inline void send(const unsigned int dest_processor_id,
                   const std::vector<std::vector<T, A1>, A2>& buf,
                   const MessageTag& tag=no_tag) const;


  template <typename T, typename A1, typename A2>
  inline void send(const unsigned int dest_processor_id,
                   const std::vector<std::vector<T, A1>, A2>& buf,
                   Request& req,
                   const MessageTag& tag=no_tag) const;


  /**
   * Blocking-receive from one processor with data-defined type.
   */
  template <typename T>
  inline Status receive(const unsigned int dest_processor_id,
                        T& buf,
                        const MessageTag& tag=any_tag) const;

  /**
   * Nonblocking-receive from one processor with data-defined type.
   */
  template <typename T>
  inline void receive(const unsigned int dest_processor_id,
                      T& buf,
                      Request& req,
                      const MessageTag& tag=any_tag) const;

  /**
   * Blocking-receive from one processor with user-defined type.
   *
   * If \p T is a container, container-of-containers, etc., then
   * \p type should be the DataType of the underlying fixed-size
   * entries in the container(s).
   */
  template <typename T>
  inline Status receive(const unsigned int dest_processor_id,
                        T& buf,
                        const DataType& type,
                        const MessageTag& tag=any_tag) const;

  /**
   * Nonblocking-receive from one processor with user-defined type.
   *
   * If \p T is a container, container-of-containers, etc., then
   * \p type should be the DataType of the underlying fixed-size
   * entries in the container(s).
   */
  template <typename T>
  inline void receive(const unsigned int dest_processor_id,
                      T& buf, const DataType& type,
                      Request& req,
                      const MessageTag& tag=any_tag) const;

  // Specialization.


  template <typename T, typename A>
  inline Status receive(const unsigned int src_processor_id,
                        std::vector<T, A>& buf,
                        const MessageTag& tag=any_tag) const;


  template <typename T, typename A>
  inline void receive(const unsigned int src_processor_id,
                      std::vector<T, A>& buf,
                      Request& req,
                      const MessageTag& tag=any_tag) const;


  template <typename T, typename A1, typename A2>
  inline Status receive(const unsigned int src_processor_id,
                        std::vector<std::vector<T, A1>, A2>& buf,
                        const MessageTag& tag=any_tag) const;

  template <typename T, typename A>
  inline Status receive(const unsigned int src_processor_id,
                        std::vector<T, A>& buf,
                        const DataType& type,
                        const MessageTag& tag=any_tag) const;

  template<typename T, typename A1, typename A2>
  inline void receive(const unsigned int src_processor_id,
                      std::vector<std::vector<T, A1>, A2>& buf,
                      Request& req,
                      const MessageTag& tag=any_tag) const;


  /**
   * Send data `send` to one processor while simultaneously receiving
   * other data `recv` from a (potentially different) processor.
   *
   * This overload is defined for fixed-size data; other overloads
   * exist for many other categories.
   */
  template <typename T1, typename T2,
    typename std::enable_if<std::is_base_of<DataType, StandardType<T1>>::value&&
    std::is_base_of<DataType, StandardType<T2>>::value,
    int>::type=0>
  inline void send_receive(const unsigned int dest_processor_id,
                           const T1& send_data,
                           const unsigned int source_processor_id,
                           T2& recv_data,
                           const MessageTag& send_tag=no_tag,
                           const MessageTag& recv_tag=any_tag) const;

  /**
   * Send data \p send to one processor while simultaneously receiving
   * other data \p recv from a (potentially different) processor, using
   * a user-specified MPI Dataype.
   */
  template <typename T1, typename T2>
  inline
    void send_receive(const unsigned int dest_processor_id,
                      const T1& send_data,
                      const DataType& type1,
                      const unsigned int source_processor_id,
                      T2& recv_data,
                      const DataType& type2,
                      const MessageTag& send_tag=no_tag,
                      const MessageTag& recv_tag=any_tag) const;

  /**
   * Take a vector of length comm.size(), and on processor root_id fill in
   * recv[processor_id] = the value of send on processor processor_id
   */
  template <typename T, typename A>
  inline void gather(const unsigned int root_id,
                     const T& send_data,
                     std::vector<T, A>& recv) const;

  /**
   * Take a vector of length \p this->size(), and fill in
   * \p recv[processor_id] = the value of \p send on that processor. This
   * overload works on fixed size types
   */
  template <typename T, typename A,
    typename std::enable_if<std::is_base_of
    <DataType, StandardType<T>>::value, int>::type=0>
  inline void allgather(const T& send_data, std::vector<T, A>& recv_data) const;

  /**
   * Take a vector of local variables and scatter the ith item to the ith
   * processor in the communicator. The result is saved into recv.
   */
  template <typename T, typename A>
  inline void scatter(const std::vector<T, A>& data,
                      T& recv,
                      const unsigned int root_id=0) const;

  /**
   * Effectively transposes the input vector across all processors.
   * The jth entry on processor i is replaced with the ith entry
   * from processor j.
   */
  template <typename T, typename A>
  inline void alltoall(std::vector<T, A>& r) const;

  /**
   * Take a local value and broadcast it to all processors.
   * Optionally takes the \p root_id processor, which specifies
   * the processor initiating the broadcast.
   *
   * If \p data is a container, it will be resized on target
   * processors.  When using pre-sized target containers, specify
   * \p identical_sizes=true on all processors for an optimization.
   *
   * Fixed variant
   */
#ifdef JETS_HAVE_MPI
  template <typename T,
    typename std::enable_if<std::is_base_of<DataType, StandardType<T>>::value, int>::type=0>
#else
  template <typename T>
#endif // JETS_HAVE_MPI
  inline void broadcast(T& data,
                        const unsigned int root_id=0,
                        const bool identical_sizes=false) const;
private:
  communicator _communicator;
  processor_id_type _rank, _size;
  SendMode _send_mode;
  SyncType _sync_type;

  void assign(const communicator& comm);
};
} // namespace parallel
}
#include "communicator_impl.inl"
#endif // __JETS_COMMUNICATOR_H__