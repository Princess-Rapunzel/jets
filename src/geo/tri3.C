#include "tri3.h"

namespace jets
{
Tri3::Tri3(std::initializer_list<Node> init_list,int id)
    : Elem(init_list, id) {  __init_edges(); }

Tri3::Tri3 (Tri3 && other): Elem(std::move(other)) { }

Tri3::Tri3 (const Tri3& other): Elem(other) { }

Tri3& Tri3::operator= (const Tri3 & other)
{
    if (this != &other)
    {
        Elem::operator=(other);
    }
    return *this;
}

Tri3& Tri3::operator= (Tri3 && other)
{
    if (this != &other)
    {
        Elem::operator=(std::move(other));
    }
    return *this;
}

Tri3::~Tri3() = default;

const Real& Tri3::measure() const { return _measure; }

const ElemType Tri3::type() { return ElemType::TRI3; }

Real Tri3::grad() { jets_not_implemented(); }

Elem& Tri3::buid() { jets_not_implemented(); }

Real Tri3::measure_coordinate(const Real& x, const Real& y, const Real &lambda) const
{
    jets_not_implemented();
}

std::ostream& operator << (std::ostream& os, const Tri3& tri)
{
    os << "Tri3 " << tri.id() << "{";
    for (int i = 0; i < tri.num_of_nodes(); i++)
    {
        os << tri.node(i) << ", ";
    }
    os << "id=" << tri.id() <<  "}";
    return os;
}
} // namespace jets
