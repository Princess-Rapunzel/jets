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
    bool operator==(const Edge&) const;
    ~Edge() = default;
    Node* start() const;
    Node* end() const;

    Edge sort() const;
private:

Node *start_node;

Node *end_node;

friend class EdgeHash;
};

struct EdgeHash 
{
    size_t operator()(const Edge& edge) const;
};

struct EdgeEqual 
{
    bool operator()(const Edge& lhs, const Edge& rhs) const 
    { return lhs == rhs; }
};

std::ostream& operator<<(std::ostream& os, const Edge& edge);
} // namespace jets

#endif // __JETS_EDGE_H__