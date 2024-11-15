#include "node.h"
#include <sstream>
namespace jets
{

Node::Node(): _id(INVALID_ID), _coords{0, 0, 0} { }

Node::Node(Real x, Real y, int id): _id(id), _coords{x, y, 0} {}

Node::Node(Real x, Real y, Real z, int id): _id(id), _coords{x, y, z} {}

Node::Node(const Node& n): _id(n._id)
{
    _coords[0] = n._coords[0];
    _coords[1] = n._coords[1];
    _coords[2] = n._coords[2];
}

Node& Node::operator=(const Node& p)
{
    _coords[0] = p._coords[0];
    _coords[1] = p._coords[1];
    _coords[2] = p._coords[2];
    return *this;
}

Node::~Node() = default;

std::unique_ptr<Node> Node::build(const Real x, const Real y, const Real z, const int id)
{
    return std::make_unique<Node>(x, y, z, id);
}

const Real& Node::x() const{ return _coords[0];}
const Real& Node::y() const{ return _coords[1];}
const Real& Node::z() const{ return _coords[2];}
const int& Node::id() const{ return _id;}
int& Node::id(){ return _id;}

bool Node::operator==(const Node& other) const{ return _id == other._id; }

std::string Node::get_info() const
{
    std::ostringstream oss;
    oss << "(" << _coords[0] << ", " << _coords[1] << ", " << _coords[2] 
    << " id=" << _id << ")";
    return oss.str();
}
} // namespace jets
