#include "elem.h"

namespace jets
{
Elem::Elem(std::initializer_list<Node*> init_list, int id):
 _nodes(init_list), _edges(), _num_of_nodes(init_list.size()), _id(id) { }

 Elem::Elem(std::vector<Node*> nodes, int id):
    _nodes(nodes), _edges(), _num_of_nodes(nodes.size()), _id(id) { }

Elem::Elem (Elem && other) 
{
    _nodes = std::move(other._nodes);
    _edges = std::move(other._edges);
    _num_of_nodes = other._num_of_nodes;
    _id = other._id;
}

Elem::Elem (const Elem& other)
{
    _nodes = other._nodes;
    _edges = other._edges;
    _num_of_nodes = other._num_of_nodes;
    _id = other._id;
}

Elem& Elem::operator= (const Elem& other)
{
    if (this != &other)
    {
        _nodes = other._nodes;
        _edges = other._edges;
        _num_of_nodes = other._num_of_nodes;
        _id = other._id;
    }
    return *this;
}

Elem& Elem::operator= (Elem&& other)
{
    if (this != &other)
    {
        _nodes = std::move(other._nodes);
        _edges = std::move(other._edges);
        _num_of_nodes = other._num_of_nodes;
        _id = other._id;
    }
    return *this;
}
Elem::~Elem()
{
    for (Node*& node : _nodes)
        delete node;
};

int Elem::num_of_nodes() const { return _num_of_nodes; }

const int& Elem::id() const { return _id; }

int& Elem::id() { return _id; }

bool Elem::valid_id() const { return _id != INVALID_ID; }

const Node* Elem::node(int i) const 
{
    jets_assert_less(i, _num_of_nodes);
    return _nodes[i]; 
}

const int& Elem::node_id(int i) const 
{ 
    jets_assert_less(i, _num_of_nodes);
    return _nodes[i]->id();
}

const std::vector<Edge>& Elem::edges() const {  return _edges; }

const int Elem::num_of_edges() const
{ 
    jets_assert_not_equal_to(_edges.size(), 0);
    return _edges.size();
}

void Elem::__init_edges()
{
    for (int i = 0; i < _num_of_nodes; i++)
        _edges.push_back(Edge(_nodes[i], _nodes[(i+1)%_num_of_nodes]).sort());
}
} // namespace jets
