#include "communicator.h"
#include "post_wait_dereference_tag.h"
#include "jetslog.h"
#include <string>
#include <memory>
#include <vector>
namespace jets
{
namespace parallel
{

template <typename T>
inline data_type dataplusint_type();

/**
 * Types combined with an int
 */
template <typename T>
class DataPlusInt
{
public:
    T val;
    int rank;
};

template<>
inline data_type dataplusint_type<short int>() { return MPI_SHORT_INT; }

template<>
inline data_type dataplusint_type<int>() { return MPI_2INT; }

template<>
inline data_type dataplusint_type<long>() { return MPI_LONG_INT; }

template<>
inline data_type dataplusint_type<float>() { return MPI_FLOAT_INT; }

template<>
inline data_type dataplusint_type<double>() { return MPI_DOUBLE_INT; }

template<>
inline data_type dataplusint_type<long double>() { return MPI_LONG_DOUBLE_INT; }

#ifdef  JETS_DEFAULT_QUADRUPLE_PRECISION
// We'll have to fall back on the pair<float128,int> derived type here
template<>
inline data_type dataplusint_type<JETS_DEFAULT_SCALAR_TYPE>() { return MPI_DATATYPE_NULL; }
#endif

template <typename T>
inline
std::pair<data_type, std::unique_ptr<StandardType<std::pair<T, int>>>>
dataplusint_type_acquire()
{
    std::pair<data_type, std::unique_ptr<StandardType<std::pair<T, int>>>> return_val;
    return_val.first=dataplusint_type<T>();
    if (return_val.first == MPI_DATATYPE_NULL)
    {
        return_val.second.reset(new StandardType<std::pair<T, int>>());
        return_val.first=*return_val.second;
    }
    return return_val;
}


template <typename T>
inline void Communicator::sum(T& r) const
{
    // JETS_PARALLEL_INTEGER_OPS(T);
    if (this->size() > 1)
    {
      //MPI_Allreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
        jets_call_mpi
        (MPI_Allreduce(MPI_IN_PLACE, &r, 1,
            StandardType<T>(&r),
            OpFunction<T>::sum(),
            this->get()));
    }
}


template <typename T>
inline void Communicator::sum(const T& r, T& o, Request& req) const
{
    if (this->size() > 1)
    {
        jets_call_mpi
        (MPI_Iallreduce(&r, &o, 1,
            StandardType<T>(&r),
            OpFunction<T>::sum(),
            this->get(),
            req.get()));
    }
    else
    {
        o=r;
        req=Request::null_request;
    }
}


template <typename T>
inline void Communicator::min(const T& r, T& o, Request& req) const
{
    if (this->size() > 1)
    {
        jets_call_mpi
        (MPI_Iallreduce(&r, &o, 1,
            StandardType<T>(&r),
            OpFunction<T>::min(),
            this->get(),
            req.get()));
    }
    else
    {
        o=r;
        req=Request::null_request;
    }
}


template <typename T>
inline void Communicator::min(T& jets_mpi_var(r)) const
{
    if (this->size() > 1)
    {
        jets_call_mpi
        (MPI_Allreduce(MPI_IN_PLACE, &r, 1,
            StandardType<T>(&r),
            OpFunction<T>::min(),
            this->get()));
    }
}


template <typename T>
inline void Communicator::minloc(T& r,
            unsigned int& min_id) const
{
    if (this->size() > 1)
    {
        DataPlusInt<T> data_in;
        ignore(data_in); // unused ifndef JETS_HAVE_MPI
        data_in.val=r;
        data_in.rank=this->rank();

        jets_call_mpi
        (MPI_Allreduce(MPI_IN_PLACE, &data_in, 1,
            dataplusint_type_acquire<T>().first,
            OpFunction<T>::min_location(), this->get()));
        r=data_in.val;
        min_id=data_in.rank;
    }
    else min_id=this->rank();
}


template <typename T>
inline void Communicator::max(const T& r,
                              T& o,
                              Request& req) const
{
    if (this->size() > 1)
    {
        jets_call_mpi
        (MPI_Iallreduce(&r, &o, 1,
            StandardType<T>(&r),
            OpFunction<T>::max(),
            this->get(),
            req.get()));
    }
    else
    {
        o=r;
        req=Request::null_request;
    }
}


template <typename T>
inline void Communicator::max(T& jets_mpi_var(r)) const
{
    if (this->size() > 1)
    {
        jets_call_mpi
        (MPI_Allreduce(MPI_IN_PLACE, &r, 1,
            StandardType<T>(&r),
            OpFunction<T>::max(),
            this->get()));
    }
}


template <typename T>
inline void Communicator::maxloc(T& r,
                                 unsigned int& max_id) const
{
    if (this->size() > 1)
    {
        DataPlusInt<T> data_in;
        ignore(data_in); // unused ifndef JETS_HAVE_MPI
        data_in.val=r;
        data_in.rank=this->rank();

        jets_call_mpi
        (MPI_Allreduce(MPI_IN_PLACE, &data_in, 1,
            dataplusint_type_acquire<T>().first,
            OpFunction<T>::max_location(), this->get()));
        r=data_in.val;
        max_id=data_in.rank;
    }
    else max_id=this->rank();
}


template<typename T>
inline void Communicator::send(const unsigned int dest_processor_id,
                               const T& buf,
                               const MessageTag& tag) const
{
    T* dataptr=const_cast<T*>(&buf);
    jets_assert_less(dest_processor_id, this->size());
    if (this->send_mode() == SendMode::SYNCHRONOUS)
    {
        jets_call_mpi
        (MPI_Ssend(dataptr, 1, StandardType<T>(dataptr),
            dest_processor_id, tag.value(), this->get()));
    }
    else // SendMode::DEFAULT
    {
        jets_call_mpi
        (MPI_Send(dataptr, 1, StandardType<T>(dataptr),
            dest_processor_id, tag.value(), this->get()));
    }
}


template <typename T>
inline void Communicator::send(const unsigned int dest_processor_id,
                               const T& buf,
                               Request& req,
                               const MessageTag& tag) const
{
    T* dataptr=const_cast<T*>(&buf);
    jets_assert_less(dest_processor_id, this->size());
    if (this->send_mode() == SendMode::SYNCHRONOUS)
    {
        jets_call_mpi
        (MPI_Issend(dataptr, 1, StandardType<T>(dataptr),
            dest_processor_id, tag.value(), this->get(), req.get()));
    }
    else // SendMode::DEFAULT
    {
        jets_call_mpi
        (MPI_Isend(dataptr, 1, StandardType<T>(dataptr),
            dest_processor_id, tag.value(), this->get(), req.get()));
    }
}

template <typename T, typename A>
inline void Communicator::send(const unsigned int dest_processor_id,
                               const std::vector<T, A>& buf,
                               const MessageTag& tag) const
{
    /*
    void send<std::vector<T, A>>(
        unsigned int, std::vector<T, A> const&,
        DataType const&,
        MessageTag const&
    ) const
    */
    this->send(dest_processor_id, buf,
               StandardType<T>(buf.empty() ? nullptr : &buf.front()), tag);
}

template <typename T, typename A>
inline void Communicator::send(const unsigned int dest_processor_id,
                                const std::vector<T, A>& buf,
                                const DataType& type,
                                const MessageTag& tag) const
{
    jets_call_mpi
    (
        ((this->send_mode() == SYNCHRONOUS) ?
            MPI_Ssend : MPI_Send) (
                buf.empty() ? nullptr : const_cast<T*>(buf.data()),
                jets_cast_int<int>(buf.size()),
                type,
                dest_processor_id,
                tag.value(),
                this->get())
    );
}


template <typename T, typename A1, typename A2>
inline void Communicator::send(const unsigned int dest_processor_id,
                               const std::vector<std::vector<T, A1>, A2>& buf,
                               Request& req,
                               const MessageTag& tag) const
{
    // this->send(dest_processor_id, buf,
    //            StandardType<T>((buf.empty() || buf.front().empty()) ?
    //                nullptr : &(buf.front().front())), req, tag);
}


/**
 * **Warning**: Do not use `receive()` with <span style="color:red">local</span> variables!
 * What will happen if you use `receive()` with local variables?
 * For example, you have to send a data from processor 0 to processor 2.
 * First you need to make a data and send it. You will do:
 * ```
 * if (comm->rank() == 0) {
 *     double* data = new double(100);
 *     comm->send(2, *data);
 * }
 * ```
 * and next you should receive the data in processor 2, and here
 * you create a local variable to store the data:
 * ```
 * else if (comm->rank() == 2)
 * {
 *     double data;
 *     comm->receive(0, data);
 * }
 * ```
 * After processor 2 invoking the function "receive", process will
 * be going on and jumping out of judgment `if (comm->rank() == 2)`,
 * and the local variable "data" will be destroyed. But now, processor
 * 2 most likely has not received the data from processor 0. So MPI
 * can not find the data memory when it receives the data from processor
 * 0. This will make a big problem!
 */
template <typename T>
inline Status Communicator::receive(const unsigned int src_processor_id,
                                    T& buf,
                                    const MessageTag& tag) const
{
    // Get the status of the message, explicitly provide the
    // datatype so we can later query the size
    Status stat(this->probe(src_processor_id, tag), StandardType<T>(&buf));
    jets_assert(src_processor_id < this->size() || src_processor_id == any_source);
    jets_call_mpi
    (MPI_Recv(&buf, 1, StandardType<T>(&buf),
        src_processor_id, tag.value(), this->get(), stat.get()));

    return stat;
}


template <typename T>
inline void Communicator::receive(const unsigned int src_processor_id,
                                  T& buf,
                                  Request& req,
                                  const MessageTag& tag) const
{
    jets_assert(src_processor_id < this->size() || src_processor_id == any_source);
    jets_call_mpi
    (MPI_Irecv(&buf, 1, StandardType<T>(&buf),
        src_processor_id, tag.value(), this->get(), req.get()));
    req.add_post_wait_work(new PostWaitDereferenceTag(tag));
}


template <typename T, typename A>
inline Status Communicator::receive(const unsigned int src_processor_id,
                                    std::vector<T, A>& buf,
                                    const MessageTag& tag) const
{
    return this->receive
    (src_processor_id, buf,
     StandardType<T>(buf.empty() ? nullptr : &(*buf.begin())), tag);
}


template <typename T, typename A>
inline void Communicator::receive(const unsigned int src_processor_id,
                                   std::vector<T, A>& buf,
                                   Request& req,
                                   const MessageTag& tag) const
{
    this->receive(src_processor_id, buf,
                   StandardType<T>(buf.empty() ? nullptr : &(*buf.begin())), req, tag);
}

template <typename T, typename A>
inline Status Communicator::receive(const unsigned int src_processor_id,
                                    std::vector<T, A>& buf,
                                    const DataType& type,
                                    const MessageTag& tag) const
{
    // Get the status of the message, explicitly provide the
    // datatype so we can later query the size
    Status stat(this->probe(src_processor_id, tag), type);
    buf.resize(stat.size());

    jets_assert(src_processor_id < this->size() ||
                  src_processor_id == any_source);
    
    // Use stat.source() and stat.tag() in the receive - if
    // src_processor_id is or tag is "any" then we want to be sure we
    // try to receive the same message we just probed.
    jets_call_mpi
    (MPI_Recv (buf.empty() ? nullptr : buf.data(),
               jets_cast_int<int>(buf.size()), type, stat.source(),
               stat.tag(), this->get(), stat.get()));
    
    jets_assert_equal_to (stat.size(), buf.size());
    return stat;
}


template <typename T1, typename T2,
    typename std::enable_if<std::is_base_of<DataType, StandardType<T1>>::value&&
    std::is_base_of<DataType, StandardType<T2>>::value,
    int>::type>
inline void Communicator::send_receive(const unsigned int dest_processor_id,
                                       const T1& senddata,
                                       const unsigned int source_processor_id,
                                       T2& recvdata,
                                       const MessageTag& send_tag,
                                       const MessageTag& recv_tag) const
{
    if (dest_processor_id == this->rank() && source_processor_id == this->rank())
    {
        recvdata=senddata;
        return;
    }
    jets_assert_less(dest_processor_id, this->size());
    jets_assert(source_processor_id < this->size() ||
                  source_processor_id == any_source);
    // MPI_STATUS_IGNORE is from MPI-2; using it with some versions of
    // MPICH may cause a crash:
    jets_call_mpi
    (MPI_Sendrecv(const_cast<T1*>(&senddata), 1, StandardType<T1>(&senddata),
        dest_processor_id, send_tag.value(), &recvdata, 1,
        StandardType<T2>(&recvdata), source_processor_id,
        recv_tag.value(), this->get(), MPI_STATUS_IGNORE));
}


template <typename T, typename A>
inline void Communicator::gather(const unsigned int root_id,
                                 const T& sendval,
                                 std::vector<T, A>& recv) const
{
    jets_assert_less(root_id, this->size());
    if (this->rank() == root_id)
    {
        recv.resize(this->size());
    }
    if (this->size() > 1)
    {
        StandardType<T> send_type(&sendval);
        jets_call_mpi
        (MPI_Gather(const_cast<T*>(&sendval), 1, send_type,
            recv.empty() ? nullptr : recv.data(), 1, send_type,
            root_id, this->get()));
    }
    else recv[0]=sendval;
}


template <typename T, typename A,
    typename std::enable_if
    <std::is_base_of<DataType, StandardType<T>>::value, int>::type>
inline void Communicator::allgather(const T& sendval, std::vector<T, A>& recv) const
{
    jets_assert(this->size());
    recv.resize(this->size());
    unsigned int comm_size=this->size();

    if (comm_size > 1)
    {
        StandardType<T> send_type(&sendval);
        jets_call_mpi
        (MPI_Allgather(const_cast<T*>(&sendval),
            1, send_type, recv.data(), 1, send_type, this->get()));
    }
    else if (comm_size > 0)
        recv[0]=sendval;
}


template <typename T, typename A>
void Communicator::scatter(const std::vector<T, A>& data,
                           T& recv,
                           const unsigned int root_id) const
{
    ignore(root_id)
        jets_assert_less(root_id, this->size());

        // Do not allow the root_id to scatter a nullptr vector.
        // That would leave recv in an indeterminate state.
    jets_assert(this->rank() != root_id || this->size() == data.size());

    if (this->size() == 1)
    {
        jets_assert(!this->rank());
        jets_assert(!root_id);
        recv=data[0];
        return;
    }
    T* data_ptr=const_cast<T*>(data.empty() ? nullptr : data.data());
    ignore(data_ptr);

    jets_assert_less(root_id, this->size());
    jets_call_mpi
    (MPI_Scatter(data_ptr, 1, StandardType<T>(data_ptr),
        &recv, 1, StandardType<T>(&recv),
        root_id, this->get()));
}


template <typename T, typename A>
inline void Communicator::alltoall(std::vector<T, A>& buf) const
{
    if (this->size() < 2 || buf.empty())
        return;
    // the per-processor size.  this is the same for all
    // processors using MPI_Alltoall, could be variable
    // using MPI_Alltoallv
    const int size_per_proc=
        jets_cast_int<int>(buf.size() / this->size());
    ignore(size_per_proc);

    jets_assert_equal_to(buf.size() % this->size(), 0);
    StandardType<T> send_type(buf.data());
    jets_call_mpi
    (MPI_Alltoall(MPI_IN_PLACE, size_per_proc, send_type, buf.data(),
        size_per_proc, send_type, this->get()));
}


#ifdef JETS_HAVE_MPI
template <typename T,
    typename std::enable_if<std::is_base_of<DataType, StandardType<T>>::value, int>::type>
#else
template <typename T>
#endif // JETS_HAVE_MPI
inline void Communicator::broadcast(T& data, const unsigned int root_id,
                      const bool identical_sizes) const
{
    ignore(root_id);
    if (this->size() == 1)
    {
        jets_assert(!this->rank());
        jets_assert(!root_id);
        return;
    }

    jets_assert_less(root_id, this->size());
    jets_call_mpi
    (MPI_Bcast(&data, 1, StandardType<T>(&data), root_id,
        this->get()));
}
} // namespace parallel
} // namespace jets
