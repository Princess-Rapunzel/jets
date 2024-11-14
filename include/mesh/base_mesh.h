#ifndef __BASE_MESH_H__
#define __BASE_MESH_H__

// #pragma once
#include "jetscomm.h"
namespace jets
{
class BaseMesh
{
public:
    BaseMesh(jets_dim dim);
    virtual ~BaseMesh();
    BaseMesh& operator=(const BaseMesh& other);

    void read_mesh(const std::string& filename) const;

    void write_mesh(const std::string& filename) const;

    jets_dim dim() const;
private:
    jets_dim _dim;
#ifdef JETS_HAVE_MPI
    processor_id_type _n_processors;
    processor_id_type _processor_id;
#endif // JETS_HAVE_MPI
#ifdef JETS_HAVE_OPENMP
    unsigned int _n_threads;
#endif // JETS_HAVE_OPENMP
};
} // namespace jets

#endif // __BASE_MESH_H__