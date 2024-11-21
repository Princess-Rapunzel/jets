#ifndef __JETS_AIO_MESH_H__
#define __JETS_AIO_MESH_H__

#include "base_mesh.h"
#include "jetscomm.h"
#include "jets.h"

namespace jets
{
/**
 * @brief AIO stands for All In One. This mesh class gather
 * all elements in one processor. Namely, it is a serial mesh.
 * 
 */
class AIOMesh : public BaseMesh
{
public:
    AIOMesh(size_type dim);

    ~AIOMesh();
    /**
     * @brief Read mesh from file.
     * There are so many formats for mesh files, how to read mesh file is not
     * clear. Therefore, this function will be implemented in derived classes.
     */
    void read_mesh(const std::string& filename) override final;

    /**
     * @brief Write mesh to file.
     * There are so many formats for mesh files, how to write mesh file is not
     * clear. Therefore, this function will be implemented in derived classes.
     */
    void write_mesh(const std::string& filename) const override final;

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

    Node& get_node(size_type i) override final;

    /**
     * @brief Get specific node at point `i`.
     * 
     * @param i the index of the node.
     */
    const Node& get_node(size_type i) const override final;

    /**
     * @brief Get specific element at point `i`.
     * 
     * @param i the index of the element.
     */
    Elem& get_elem(size_type i) override final;

    /**
     * @brief Get specific element at point `i`.
     * 
     * @param i the index of the element.
     */
    const Elem& get_elem(size_type i) const override final;

    const std::vector<Node*>& nodes() const { return _nodes; }

    const std::vector<Elem*>& elems() const { return _elems; }

    /**
     * @brief Get the number of nodes.
     */
    size_type num_of_nodes() const override final;

    size_type num_of_elems() const override final;
    /**
     * @brief Find the boundary nodes.
     * 
     * Boundary nodes are necessary for building boundary
     * conditions, and it's not easy to filter them out.
     * Once this function has found the boundary nodes, it
     * will store them in the vector `_boundary_nodes`.
     * 
     * @return const std::vector<Node*>& the boundary nodes.
     */
    std::vector<Node*>& get_boundary_nodes();
protected:

  /**
   * The vertices (spatial coordinates) of the mesh.
   */
  std::vector<Node*> _nodes;

  size_type _num_of_nodes;

  /**
   * The elements in the mesh.
   */
  std::vector<Elem*> _elems;

  size_type _num_of_elems;

  std::vector<Node*> _boundary_nodes;

  size_type _num_of_boundary_nodes;

  /**
   * @brief Flag to indicate whether the boundary nodes 
   * are found.
   */
  bool _is_boundary_nodes_found;

private:
  std::vector<Node*>& __find_boundary_nodes();
public:
#define __boundary_nodes_loopi__(mesh) for (size_type i = 0; i < (mesh)->get_boundary_nodes().size(); ++i)
#define __boundary_nodes_loop__(mesh) for (auto _node : (mesh)->get_boundary_nodes())
#define calc_free_nodes_idx(_all_nodes_idx, _bd_nodes_idx, _free_nodes_idx) std::set_difference(_all_nodes_idx->begin(), _all_nodes_idx->end(), _bd_nodes_idx->begin(), _bd_nodes_idx->end(), std::inserter(*_free_nodes_idx, _free_nodes_idx->begin()))
};
} // namespace jets

#endif // __JETS_AIO_MESH_H__