#ifndef __JETS_EDGE_H__
#define __JETS_EDGE_H__
#include "node.h"
#include "jets.h"
#include  <ostream>
namespace jets
{
class Edge
{
public:
    Edge(Node* start, Node* end);
    Edge(const Edge& other);
    Edge& operator=(const Edge& other);
    Edge(Edge&& other);
    Edge& operator=(Edge&& other);
    ~Edge() = default;
    Node* start() const;
    Node* end() const;
private:

Node *start_node;

Node *end_node;
};

JETS_INLINE Edge::Edge(Node* start, Node* end) : start_node(start), end_node(end) { }
JETS_INLINE Edge::Edge(const Edge& other) : start_node(other.start_node), end_node(other.end_node) { }
JETS_INLINE Edge& Edge::operator=(const Edge& other)
{
    if (this != &other)
    {
        start_node = other.start_node;
        end_node = other.end_node;
    }
    return *this;
}

JETS_INLINE Edge::Edge(Edge&& other)
{
    start_node = other.start_node;
    end_node = other.end_node;
    other.start_node = nullptr;
    other.end_node = nullptr;
}
JETS_INLINE Edge& Edge::operator=(Edge&& other)
{
    if (this != &other)
    {
        start_node = other.start_node;
        end_node = other.end_node;
        other.start_node = nullptr;
        other.end_node = nullptr;
    }
    return *this;
}

JETS_INLINE Node* Edge::start() const { return start_node; }
JETS_INLINE Node* Edge::end() const { return end_node; }

JETS_INLINE std::ostream& operator<<(std::ostream& os, const Edge& edge)
{
    os << "[" << edge.start()->id() << " -> " << edge.end()->id() << "]";
    return os;
}
} // namespace jets

#endif // __JETS_EDGE_H__