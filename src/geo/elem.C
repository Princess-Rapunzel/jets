#include "elem.h"

namespace jets
{
Elem::Elem(Node** nodes): _nodes(nodes){}
Elem::Elem (Elem &&) = delete;
Elem::Elem (const Elem &) = delete;
Elem& Elem::operator= (const Elem &) = delete;
Elem& Elem::operator= (Elem &&) = delete;
Elem::~Elem() = default;

int Elem::num_of_nodes() const
    { return _num_of_nodes; }

const int& Elem::id() const
    { return _id; }

int& Elem::id()
    { return _id; }

Node* Elem::node(int i) const
    { return _nodes[i]; }

const int& Elem::node_id(int i)
    { return _nodes[i]->id(); }

const std::vector<Edge>& Elem::edges()
    {  return _edges; }

const int& Elem::num_of_edges()
{ 
    jets_assert_not_equal_to(_edges.size(), 0);
    return _edges.size();
}

void Elem::__init_edges()
{
    for (int i = 0; i < _num_of_nodes; i++)
    {
        _edges.push_back(Edge(*_nodes[i], *_nodes[(i+1)%_num_of_nodes]));
    }
}
} // namespace jets
