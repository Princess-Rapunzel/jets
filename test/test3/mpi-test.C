// #include "jetsbase.h"
#include "jets.h"
#include "jetsinit.h"
#include "communicator.h"
#include "message_tag.h"
#include "jetslog.h"
#include <map>
#include <iostream>
#include <random>
using namespace jets;
using std::vector;
// mpicc mpi_test.c -o mpi_test
// mpiexec -n 4 ./test01

const std::string info_log_filename="/home/rapunzel/jets/logfile/log_info.log";
const std::string warn_log_filename="/home/rapunzel/jets/logfile/log_warn.log";
const std::string error_log_filename="/home/rapunzel/jets/logfile/log_error.log";

void test_sendRecv(parallel::Communicator* comm);
void test_sendRecv_vector(parallel::Communicator* comm);
void test_sendrecv(parallel::Communicator* comm);
void test_gather(parallel::Communicator* comm);
void test_allgather(parallel::Communicator* comm);
void test_scatter(parallel::Communicator* comm);
void test_broadcast(parallel::Communicator* comm);


int main(int argc, char** argv)
{
    JetsInit jetsInit(&argc, &argv);
    parallel::Communicator* comm=&jetsInit.comm();
    // test_gather(comm);
    // test_allgather(comm);
    // test_scatter(comm);
    // test_broadcast(comm);
    // test_sendrecv(comm);
    // test_sendRecv_vector(comm);
    return 0;
}

void test_sendRecv(parallel::Communicator* comm)
{
    parallel::Request req;
    Real* data=static_cast<Real*>(new double);
    if (comm->rank() == 0)
    {
        *data=jets::pi;
        comm->send(2, *data);
    }
    else if (comm->rank() == 2)
    {
        comm->receive(0, *data);
        std::cout << "data: " << *data << std::endl;
    }
    delete data;
}

void test_sendRecv_vector(parallel::Communicator* comm)
{
    vector<Real> data;
    
    if (comm->is_rank0())
    {
        data = {static_cast<Real>(jets::pi), static_cast<Real>(jets::pi * 2), static_cast<Real>(jets::pi * 3)};
        comm->send(1, data);
    }
    else if (comm->is_rank_at(1))
    {
        comm->receive(0, data);
        for (int i = 0; i < data.size(); i++)
        {
            std::cout << "data[" << i << "]: " << data[i] << std::endl;
        }
    }
}

void test_sendrecv(parallel::Communicator* comm)
{
    Real* senddata = static_cast<Real*>(new double(jets::pi * (comm->rank() + 1)));
    Real* recv = static_cast<Real*>(new double);
    if (comm->rank() == 0)
    {
        // Send to 1 and receive from 1.
        comm->send_receive(1, *senddata, 1, *recv);
        out << "process 0 send " << *senddata << " receive " << *recv << std::endl;
    }
    else if (comm->rank() == 1)
    {
        // Send to 0 and receive from 0.
        comm->send_receive(0, *senddata, 0, *recv);
        out << "process 1 send " << *senddata << " receive " << *recv << std::endl;
    }
    delete senddata;
    delete recv;
}

void test_gather(parallel::Communicator* comm) 
{
    vector<Real>* recv;
    Real* sendval = static_cast<Real*>(new double);
    *sendval = jets::pi;
    if (comm->is_rank0())
    {
        recv = new vector<Real>(comm->size());
    }
    comm->gather(0, *sendval, *recv);
    if (comm->is_rank0())
    {
        for (int i = 0; i < comm->size(); i++)
        {
            std::cout << "recv[" << i << "]: " << (*recv)[i] << std::endl;
        }
    }
    delete sendval;
    delete recv;
}

void test_allgather(parallel::Communicator* comm)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<Real> dis_float(0, 1);

    Real sendval = dis_float(gen);
    vector<Real> recv(comm->size());
    out << "before allgather: processor_id: " << comm->rank() << " sendval: " << sendval << std::endl;

    comm->allgather(sendval, recv);
    for (int i = 0; i < comm->size(); i++)
    {
        std::cout << "after allgather: processor_id" <<comm->rank()  << " recv[" << i << "]: " << recv[i] << std::endl;
    }
}

void test_scatter(parallel::Communicator* comm)
{
    vector<Real> data(comm->size());
    for (int i = 0; i < comm->size(); i++)
    {
        data[i] = jets::pi * i;
    }
    Real recv;
    comm->scatter(data, recv);
    out << "processor_id: " << comm->rank() << " recv: " << recv << std::endl;
}

void test_broadcast(parallel::Communicator* comm)
{
    Real data;
    if (comm->is_rank0())
    {
        data = jets::pi;
    }
    comm->broadcast(data, 0);
    out << "processor_id: " << comm->rank() << " data: " << data << std::endl;
}