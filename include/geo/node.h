#ifndef __JETS_NODE_H__
#define __JETS_NODE_H__
// #include "jetscomm.h"
#include "ostream_proxy.h"
#include "jetscomm.h"
#include "point.h"
#include <memory>
namespace jets
{
// OStreamProxy out;

class Node: public Point
{
public:
    static const int INVALID_ID = -1;
    Node();
    Node(Real x, Real y, int id);
    Node(Real x, Real y, Real z, int id);
    Node(const Node &n);
    Node(Node &&n);
    Node & operator= (const Node & p);
    Node& operator= (Node && p);
    ~Node();
    std::unique_ptr<Node> build(const Real x, const Real y, const Real z, const int id);
    // const Real& x() const;
    // const Real& y() const;
    // const Real& z() const;
    const int& id() const;
    int& id();

    bool valid_id() const;

    bool operator==(const Node& other) const;

    std::string get_info() const;
private:
    int _id;
};

inline std::ostream & operator << (std::ostream & os, const Node & n)
{
  os << n.get_info();
  return os;
}

struct NodePtrHash {
    std::size_t operator()(const Node* node) const {
        return std::hash<int>()(node->id());
    }
};

struct NodePtrEqual {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->id() == rhs->id();
    }
};
} // namespace jets


#endif // __JETS_NODE_H__