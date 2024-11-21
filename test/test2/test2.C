// #include "node.h"
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#include <set>

class Edge
{
public:
    Edge(const std::string& start, const std::string& end):
    start_node(start), end_node(end) { }
    ~Edge() = default;
    bool operator==(const Edge& other) const
    { return start_node == other.start_node && end_node == other.end_node; }

const std::string& start_node;

const std::string& end_node;

friend class EdgeHash;
};

struct EdgeHash {
    size_t operator()(const Edge& edge) const {
        std::hash<std::string> hasher;
        return hasher(edge.start_node) ^ hasher(edge.end_node);
    }
};

struct EdgeEqual {
    bool operator()(const Edge& lhs, const Edge& rhs) const {
        return lhs == rhs;
    }
};

int main(int argc, char const *argv[])
{
    std::set<int> s = {1, 2, 3, 4, 5};
    
    system("pause");
    return 0;
}
