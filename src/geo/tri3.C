#include "tri3.h"
#include "measures.h"
#include "dense_vector.h"

namespace jets
{
Tri3::Tri3(std::initializer_list<Node> init_list,int id)
    : Elem(init_list, id) 
{
    _measure = triangle_measure(_nodes[0].x(), _nodes[0].y(), _nodes[1].x(), _nodes[1].y(), _nodes[2].x(), _nodes[2].y());
    __init_edges(); 
}

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

const Real& Tri3::measure() const {  return _measure; }

const ElemType Tri3::type() { return ElemType::TRI3; }

DenseMatrix Tri3::grad() const
{
    DenseMatrix grad_matrix(2, 3);
    grad_matrix(0, 0) = _nodes[1].y() - _nodes[2].y();
    grad_matrix(0, 1) = _nodes[2].y() - _nodes[0].y();
    grad_matrix(0, 2) = _nodes[0].y() - _nodes[1].y();
    grad_matrix(1, 0) = _nodes[2].x() - _nodes[1].x();
    grad_matrix(1, 1) = _nodes[0].x() - _nodes[2].x();
    grad_matrix(1, 2) = _nodes[1].x() - _nodes[0].x();
    return grad_matrix.mult(1/(_measure * 2));
}

Real Tri3::measure_coordinate(const Real& x, const Real& y, const Real &lambda) const
{
    if (lambda == 1) return triangle_measure(x, y, _nodes[1].x(), _nodes[1].y(), _nodes[2].x(), _nodes[2].y()) / _measure;
    else if (lambda == 2) return triangle_measure(_nodes[0].x(), _nodes[0].y(), x, y, _nodes[2].x(), _nodes[2].y()) / _measure;
    else if (lambda == 3) return triangle_measure(_nodes[0].x(), _nodes[0].y(), _nodes[1].x(), _nodes[1].y(), x, y) / _measure;
    else return -1;
}

DenseMatrix Tri3::get_unit_stiffness_matrix() const
{
    DenseMatrix grad_matrix = grad();
    DenseMatrix _unit_stiffness_matrix = DenseMatrix(3, 3);
    for (size_type i = 0; i < 3; i++)
        for (size_type j = 0; j < 3; j++)
            _unit_stiffness_matrix(i, j) = grad_matrix.col(i) * grad_matrix.col(j);
    return _unit_stiffness_matrix.mult(_measure);
}

std::ostream& operator << (std::ostream& os, const Tri3& tri)
{
    os << "Tri3 " << tri.id() << "{";
    for (size_type i = 0; i < tri.num_of_nodes(); i++)
    {
        os << tri.node(i) << ", ";
    }
    os << "id=" << tri.id() <<  "}";
    return os;
}
} // namespace jets
