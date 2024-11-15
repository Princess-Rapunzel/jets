#ifndef __BASE_MESH_H__
#define __BASE_MESH_H__

// #pragma once
#include "jetscomm.h"
#include "jets.h"
namespace jets
{
class BaseMesh
{
public:
    BaseMesh(size_type dim);
    virtual ~BaseMesh();

    /**
     * Following four functions will not be implemented as they are not needed.
     */
    BaseMesh(const BaseMesh& other);
    BaseMesh(BaseMesh&& other);
    BaseMesh& operator=(const BaseMesh& other);
    BaseMesh& operator=(BaseMesh&& other);

    /**
     * @brief Read mesh from file.
     * There are so many formats for mesh files, how to read mesh file is not
     * clear. Therefore, this function will be implemented in derived classes.
     */
    void read_mesh(const std::string& filename) const;

    /**
     * @brief Write mesh to file.
     * There are so many formats for mesh files, how to write mesh file is not
     * clear. Therefore, this function will be implemented in derived classes.
     */
    void write_mesh(const std::string& filename) const;

    size_type dim() const;
#ifdef JETS_HAVE_MPI
    processor_id_type n_processors() const;
    processor_id_type processor_id() const;
#endif // JETS_HAVE_MPI
#ifdef JETS_HAVE_OPENMP
    unsigned int n_threads() const;
#endif // JETS_HAVE_OPENMP
protected:
    size_type _dim;
#ifdef JETS_HAVE_MPI
    processor_id_type _n_processors;
    processor_id_type _processor_id;
#endif // JETS_HAVE_MPI
#ifdef JETS_HAVE_OPENMP
    unsigned int _n_threads;
#endif // JETS_HAVE_OPENMP
};
JETS_INLINE BaseMesh::BaseMesh(size_type dim) : _dim(dim){ }
JETS_INLINE BaseMesh::BaseMesh(const BaseMesh& other) = delete;
JETS_INLINE BaseMesh::BaseMesh(BaseMesh&& other) = delete;
JETS_INLINE BaseMesh& BaseMesh::operator=(const BaseMesh& other) = delete;
JETS_INLINE BaseMesh& BaseMesh::operator=(BaseMesh&& other) = delete;
JETS_INLINE size_type BaseMesh::dim() const { return _dim; }
#ifdef JETS_HAVE_MPI
JETS_INLINE processor_id_type BaseMesh::n_processors() const { return _n_processors; }
JETS_INLINE processor_id_type BaseMesh::processor_id() const { return _processor_id; }
#endif // JETS_HAVE_MPI
#ifdef JETS_HAVE_OPENMP
JETS_INLINE unsigned int BaseMesh::n_threads() const { return _n_threads; }
#endif // JETS_HAVE_OPENMP
} // namespace jets

#endif // __BASE_MESH_H__