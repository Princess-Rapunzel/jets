// ditributed_mesh.h
#ifndef __JETS_PARALLEL_MESH_H__
#define __JETS_PARALLEL_MESH_H__

#include "base_mesh.h"
#include "parallel_object.h"
namespace jets
{
/**
 * @brief A parallel mesh.
 * In this mesh, elements and nodes of the mesh are distributed 
 * among processors. When needed, processors can communicate with
 * each other to get the information of the elements and nodes that
 * they need.
 */
class ParallelMesh : public BaseMesh, public ParallelObject
{
public:
    ParallelMesh(size_type dim, MPI_Comm comm);

    virtual ~ParallelMesh();

    /**
     * @brief Read mesh from file.
     * There are so many formats for mesh files, how to read mesh file is not
     * clear. Therefore, this function will be implemented in derived classes.
     */
    void read_mesh(const std::string& filename) override;

        /**
     * @brief Add a node to the mesh.
     * 
     * @param n the node to be added.
     */
    void add_node(Node&) override final;

    /**
     * @brief Add an element to the mesh.
     * 
     * @param e the element to be added.
     */
    void add_elem(Elem&) override final;

    /**
     * @brief Clear the mesh.
     */
    void clear() override;
}

} // namespace jets

#endif // __JETS_PARALLEL_MESH_H__