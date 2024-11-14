#include "node.h"
#include <sstream>
namespace jets
{

Node::Node()
{
    _coords[0] = 0.0;
    _coords[1] = 0.0;
    _coords[2] = 0.0;
    _id = -1;
}

Node::Node(Real x, Real y, Real z, int id)
{
    _coords[0] = x;
    _coords[1] = y;
    _coords[2] = z;
    _id = id;
}

Node::Node(const Node& n)
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
    oss << "Node id=" << _id << ", coords=(" << _coords[0] << ", " << _coords[1] << ", " << _coords[2] << ")";
    return oss.str();
}

void Node::print_info(std::ostream& os) const
{
    os << get_info() << std::endl;
}
} // namespace jets
