#ifndef __BASE_MESH_H__
#define __BASE_MESH_H__

#include <vector>
// #pragma once
#include "jetscomm.h"
#include "jets.h"
#include "node.h"
#include "elem.h"

namespace jets
{
__jets_abstract__ class BaseMesh
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
    virtual void read_mesh(const std::string& filename) = 0;

    /**
     * @brief Write mesh to file.
     * There are so many formats for mesh files, how to write mesh file is not
     * clear. Therefore, this function will be implemented in derived classes.
     */
    virtual void write_mesh(const std::string& filename) const = 0;

    /**
     * @brief return the dimension of the mesh.
     */
    size_type dim() const;

    /**
     * @brief set the dimension of the mesh.
     * 
     * @param dim the dimension of the mesh.
     */
    void set_dim(size_type);

    /**
     * @brief Add a node to the mesh.
     * 
     * @param n the node to be added.
     */
    virtual void add_node(Node&) = 0;

    /**
     * @brief Add an element to the mesh.
     * 
     * @param e the element to be added.
     */
    virtual void add_elem(Elem&) = 0;

    /**
     * @brief Clear the mesh.
     */
    virtual void clear() = 0;

    /**
     * @brief Get specific node at point `i`.
     * 
     * @param i the index of the node.
     */
    virtual Node& get_node(size_type i) = 0;

    /**
     * @brief Get specific node at point `i`.
     * 
     * @param i the index of the node.
     */
    virtual const Node& get_node(size_type i) const = 0;

    
    /**
     * @brief Get specific element at point `i`.
     * 
     * @param i the index of the element.
     */
    virtual Elem& get_elem(size_type i) = 0;

    /**
     * @brief Get specific element at point `i`.
     * 
     * @param i the index of the element.
     */
    virtual const Elem& get_elem(size_type i) const = 0;

    virtual size_type num_of_nodes() const = 0;

    virtual size_type num_of_elems() const = 0;
#ifdef JETS_HAVE_MPI
    processor_id_type n_processors() const;
    processor_id_type processor_id() const;
#else
    int n_processors() const;
    int processor_id() const;
#endif // JETS_HAVE_MPI
#ifdef JETS_HAVE_OPENMP
    unsigned int n_threads() const;
#else
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
public:
#define __all_nodes_loopi__(mesh) for (size_type i = 0; i < (mesh)->num_of_nodes(); ++i)
};
__jets_inline__ BaseMesh::BaseMesh(size_type dim) : _dim(dim){ }
__jets_inline__ BaseMesh::BaseMesh(const BaseMesh& other) = delete;
__jets_inline__ BaseMesh::BaseMesh(BaseMesh&& other) = delete;
__jets_inline__ BaseMesh& BaseMesh::operator=(const BaseMesh& other) = delete;
__jets_inline__ BaseMesh& BaseMesh::operator=(BaseMesh&& other) = delete;
__jets_inline__ BaseMesh::~BaseMesh() = default;
__jets_inline__ size_type BaseMesh::dim() const { return _dim; }
__jets_inline__ void BaseMesh::set_dim(size_type dim) { this->_dim = dim; }
#ifdef JETS_HAVE_MPI
JETS_INLINE processor_id_type BaseMesh::n_processors() const { return _n_processors; }
JETS_INLINE processor_id_type BaseMesh::processor_id() const { return _processor_id; }
#else
__jets_inline__ int BaseMesh::n_processors() const { return 1; }
__jets_inline__ int BaseMesh::processor_id() const { return 0; }
#endif // JETS_HAVE_MPI
#ifdef JETS_HAVE_OPENMP
JETS_INLINE unsigned int BaseMesh::n_threads() const { return _n_threads; }
#else
__jets_inline__ unsigned int BaseMesh::n_threads() const { return 1; }
#endif // JETS_HAVE_OPENMP
} // namespace jets

#endif // __BASE_MESH_H__