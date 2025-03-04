#include "dense_vector.h"

namespace jets
{

DenseVector::DenseVector() : BaseVector(), _val() {}
DenseVector::DenseVector(std::initializer_list<Real> init_list) : BaseVector(init_list.size()), _val(init_list) {}
DenseVector::DenseVector(size_type size) : BaseVector(size), _val(size) {}
DenseVector::DenseVector(const DenseVector& other) : BaseVector(other), _val(other._val) {}
DenseVector::~DenseVector() = default;
DenseVector::DenseVector(DenseVector&& other) : BaseVector(other), _val(std::move(other._val)) {}

DenseVector& DenseVector::operator=(const DenseVector& other) = delete;
DenseVector& DenseVector::operator=(DenseVector&& other) = delete;

DenseVector DenseVector::operator+(const DenseVector& other) const
{
    DenseVector result(_m);
    for (size_type i = 0; i < _m; ++i)
        result[i] = _val[i] + other[i];
    return result;
}

DenseVector DenseVector::operator-(const DenseVector& other) const
{
    DenseVector result(_m);
    for (size_type i = 0; i < _m; ++i)
        result[i] = _val[i] - other[i];
    return result;
}

DenseVector DenseVector::operator*(const Real& scalar) const
{
    DenseVector result(_m);
    for (size_type i = 0; i < _m; ++i)
        result[i] = _val[i] * scalar;
    return result;
}

Real DenseVector::operator*(const DenseVector& other) const
{
    Real result = 0;
    for (size_type i = 0; i < _m; ++i)
        result += _val[i] * other[i];
    return result;
}

Real& DenseVector::operator[](size_type i) { return _val[i]; }
const Real& DenseVector::operator[](size_type i) const { return _val[i]; }
size_type DenseVector::size() const { return _m; }
void DenseVector::resize(size_type size) { _m = size; _val.resize(size); }
void DenseVector::zero() { std::fill(_val.begin(), _val.end(), static_cast<Real>(0)); }
void DenseVector::print(std::ostream& os) const
{
    out << "[ ";
    for (size_type i = 0; i < _m; ++i)
        out << _val[i] << " ";
    out << "]" << std::endl;
}
void DenseVector::print_scientific(std::ostream & os, unsigned precision) const
{
    os << std::scientific << std::setprecision(precision);
    print(os);
    os << std::defaultfloat;
}

std::ostream& operator << (std::ostream & os, const DenseVector& v)
{
    v.print_scientific(os);
    return os;
}
} // namespace jets