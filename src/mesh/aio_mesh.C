#include "aio_mesh.h"
#include "matlab_io.h"
#include "edge.h"

#include <unordered_map>
#include <unordered_set>

namespace jets
{

AIOMesh::AIOMesh(size_type dim) :
    BaseMesh(dim), 
    _nodes(),
    _num_of_nodes(0),
    _elems(),
    _num_of_elems(0),
    _boundary_nodes(),
    _num_of_boundary_nodes(0),
    _is_boundary_nodes_found(false) { }

AIOMesh::~AIOMesh(){ this->AIOMesh::clear(); }

void AIOMesh::read_mesh(const std::string& name)
{
    MatlabIO(*this).read(name);
}

void AIOMesh::write_mesh(const std::string& filename) const
{
    jets_not_implemented();
}

void AIOMesh::add_node(Node& node)
{
    if (node.valid_id())
    {
        size_type id = node.id();
        if (id < _nodes.size())
        jets_assert(!_nodes[id]);
        else
            _nodes.resize(id+1); 
        _nodes[id] = &node;
    }
    else
    {
        node.id() = _nodes.size();
        _nodes.push_back(&node);
    }
    ++_num_of_nodes;
}

void AIOMesh::add_elem(Elem& e)
{
    const size_type id = e.id();
    if (id < _elems.size())
        jets_assert(!_elems[id]);
    else
        _elems.resize(id+1, nullptr);

    ++_num_of_elems;
    _elems[id] = &e;
}

void AIOMesh::clear()
{
    for (auto node : _nodes)
        delete node;
    _nodes.clear();
    for (auto elem : _elems)
        delete elem;
    _elems.clear();
    _num_of_nodes = 0;
    _num_of_elems = 0;
}

Node& AIOMesh::get_node(size_type i)
{
    jets_assert_less(i, this->_nodes.size());
    jets_assert(this->_nodes[i]);
    jets_assert_equal_to(this->_nodes[i]->id(), i);
    return *this->_nodes[i];
}

const Node& AIOMesh::get_node(size_type i) const
{
    jets_assert_less(i, this->_nodes.size());
    jets_assert(this->_nodes[i]);
    jets_assert_equal_to(this->_nodes[i]->id(), i);
    return *this->_nodes[i];
}

Elem& AIOMesh::get_elem(size_type i)
{
    jets_assert_less(i, this->_elems.size());
    jets_assert(this->_elems[i]);
    jets_assert_equal_to(this->_elems[i]->id(), i);
    return *this->_elems[i];
}

const Elem& AIOMesh::get_elem(size_type i) const
{
    jets_assert_less(i, this->_elems.size());
    jets_assert(this->_elems[i]);
    jets_assert_equal_to(this->_elems[i]->id(), i);
    return *this->_elems[i];
}

size_type AIOMesh::num_of_nodes() const
{
    return this->_num_of_nodes;
}

size_type AIOMesh::num_of_elems() const
{
    return this->_num_of_elems;
}

std::vector<Node*>& AIOMesh::get_boundary_nodes()
{
    if (!this->_is_boundary_nodes_found)
    {
        this->__find_boundary_nodes();
        jets_assert_greater_msg(_boundary_nodes.size(), 0, 
                                "No boundary nodes found.");
        this->_is_boundary_nodes_found = true;
    }
    return _boundary_nodes;
}

std::vector<Node*>& AIOMesh::__find_boundary_nodes()
{
    jets_assert(!this->_elems.empty());
    jets_assert(!this->_nodes.empty());

    std::unordered_map<Edge, size_type, EdgeHash, EdgeEqual> edge_count;

    for ( Elem*& elem : _elems )
    {
        std::vector<Edge> edges = elem->edges();
        for ( Edge& e : edges )
        {   
            auto it = edge_count.find(e);
            if ( it == edge_count.end() )
                edge_count[e] = 1;
            else
                ++it->second;
        }
    }

    std::vector<Edge> boundary_edges;
    for ( auto& it : edge_count )
        if ( it.second == 1 )
            boundary_edges.push_back(it.first);
    
    std::unordered_set<Node*, NodePtrHash, NodePtrEqual> boundary_nodes;
    for ( auto& e : boundary_edges )
    {
        boundary_nodes.insert(e.start());
        boundary_nodes.insert(e.end());        
    }

    this->_boundary_nodes.assign(boundary_nodes.begin(), 
                                    boundary_nodes.end());
    return this->_boundary_nodes;
}
} // namespace jets
