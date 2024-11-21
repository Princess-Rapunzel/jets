#include "edge.h"

namespace jets
{
Edge::Edge(Node* start, Node* end) : start_node(start), end_node(end) { }

Edge::Edge(const Edge& other) : start_node(other.start_node), end_node(other.end_node) { }

Edge& Edge::operator=(const Edge& other)
{
    if (this != &other)
    {
        start_node = other.start_node;
        end_node = other.end_node;
    }
    return *this;
}

Edge::Edge(Edge&& other)
{
    start_node = other.start_node;
    end_node = other.end_node;
    other.start_node = nullptr;
    other.end_node = nullptr;
}

Edge& Edge::operator=(Edge&& other)
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

bool Edge::operator==(const Edge& other) const
{
    // std::cout << start_node->id() << " -> " << end_node->id()
    // << "----" << other.end_node->id() << " -> " << other.end_node->id() << std::endl;
    // return  (start_node->id() == other.start_node->id() 
    //             && end_node->id() == other.end_node->id()) 
    //         ||
    //         (start_node->id() == other.end_node->id() 
    //             && end_node->id() == other.   start_node->id());
    return  (start_node == other.start_node
                && end_node == other.end_node) 
            ||
            (start_node == other.end_node
                && end_node == other.start_node);
}

Node* Edge::start() const { return start_node; }
Node* Edge::end() const { return end_node; }
Edge Edge::sort() const { return start_node->id() < end_node->id() ? *this : Edge(end_node, start_node); }

std::ostream& operator<<(std::ostream& os, const Edge& edge)
{
    os << "[" << edge.start()->id() << " -> " << edge.end()->id() << "]";
    return os;
}

size_t EdgeHash::operator()(const Edge& edge) const
{
    std::hash<Node *> hasher;
    return hasher(edge.start_node) ^ hasher(edge.end_node);
}


} // namespace jets
