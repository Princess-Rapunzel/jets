#include "node.h"
#include <sstream>
namespace jets
{

Node::Node(): Point(), _id(INVALID_ID) { }

Node::Node(Real x, Real y, int id): Point(x, y), _id(id) { }

Node::Node(Real x, Real y, Real z, int id): Point(x, y, z), _id(id) { }

Node::Node(const Node& n): _id(n._id)
{
    _coords[0] = n._coords[0];
    _coords[1] = n._coords[1];
    _coords[2] = n._coords[2];
}

Node::Node(Node&& n): _id(n._id)
{
    _coords[0] = n._coords[0];
    _coords[1] = n._coords[1];
    _coords[2] = n._coords[2];
    n._coords[0] = 0;
    n._coords[1] = 0;
    n._coords[2] = 0;
    n._id = INVALID_ID;
}

Node& Node::operator=(const Node& n)
{
    if (this != &n)
    {
        _id = n._id;
        _coords[0] = n._coords[0];
        _coords[1] = n._coords[1];
        _coords[2] = n._coords[2];
    }
    return *this;
}

Node& Node::operator=(Node&& n)
{
    if (this != &n)
    {
        _id = n._id;
        _coords[0] = n._coords[0];
        _coords[1] = n._coords[1];
        _coords[2] = n._coords[2];
        n._coords[0] = 0;
        n._coords[1] = 0;
        n._coords[2] = 0;
        n._id = INVALID_ID;
    }
    return *this;
}


Node::~Node() { };

std::unique_ptr<Node> Node::build(const Real x, const Real y, const Real z, const int id)
{
    return std::make_unique<Node>(x, y, z, id);
}

// const Real& Node::x() const{ return _coords[0];}
// const Real& Node::y() const{ return _coords[1];}
// const Real& Node::z() const{ return _coords[2];}
const int& Node::id() const{ return _id;}
int& Node::id(){ return _id;}
bool Node::valid_id() const{ return _id != INVALID_ID; }

bool Node::operator==(const Node& other) const{ return _id == other._id; }

std::string Node::get_info() const
{
    std::ostringstream oss;
    oss << "(" << _coords[0] << ", " << _coords[1] << ", " << _coords[2] 
    << " id=" << _id << ")";
    return oss.str();
}
} // namespace jets
