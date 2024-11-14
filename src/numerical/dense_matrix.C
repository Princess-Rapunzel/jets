#include "dense_matrix.h"
#include "dense_vector.h"
#include <vector>

namespace jets
{

DenseMatrix::DenseMatrix(size_type m, size_type n)
    : BaseMatrix(m, n), _val() { this->resize(m, n); }

DenseMatrix::DenseMatrix(size_type m, size_type n, std::initializer_list<Real> init_list): BaseMatrix(m, n), _val(init_list.begin(), init_list.end())
{ jets_assert_equal_to(m * n, init_list.size()); }

DenseMatrix::DenseMatrix(DenseMatrix && mat): 
BaseMatrix(mat.m(), mat.n()), _val(std::move(mat._val)) 
{ }

DenseMatrix::DenseMatrix(const DenseMatrix & mat)
: BaseMatrix(mat.m(), mat.n()), _val(mat._val) { }

DenseMatrix& DenseMatrix::operator= (const DenseMatrix& mat)
{
    size_type mat_m = mat.m(), mat_n = mat.n();
    this->resize(mat_m, mat_n);
    for (size_type i=0; i<mat_m; i++)
        for (size_type j=0; j<mat_n; j++)
            (*this)(i,j) = mat(i,j);
    return *this;
}

DenseMatrix& DenseMatrix::operator= (DenseMatrix && mat)
{
    if (this != &mat)
    {
        _val.swap(mat._val);
        std::swap(_m, mat._m);
        std::swap(_n, mat._n);
    }
    return *this;
}

DenseMatrix::~DenseMatrix()
{
    _val.clear();
    std::vector<Real>().swap(_val);
};

Real& DenseMatrix::operator() (size_type i, size_type j)
{
    jets_assert_less(i, _m);
    jets_assert_less(j, _n);
    return _val[i * _n + j];
}

const Real& DenseMatrix::operator() (size_type i, size_type j) const
{
    jets_assert_less(i, _m);
    jets_assert_less(j, _n);
    return _val[i * _n + j];
}

DenseMatrix DenseMatrix::operator+(const DenseMatrix& other)
{
    jets_assert_equal_to(_m, other.m());
    jets_assert_equal_to(_n, other.n());
    DenseMatrix result(_m, _n);
    for (size_type j = 0; j < _n; ++j)
        for (size_type i = 0; i < _m; ++i)
            result(i,j) = (*this)(i,j) + other(i,j);
    return result;
}

DenseMatrix DenseMatrix::operator-(const DenseMatrix& other)
{
    jets_assert_equal_to(_m, other.m());
    jets_assert_equal_to(_n, other.n());
    DenseMatrix result(_m, _n);
    for (size_type j = 0; j < _n; ++j)
        for (size_type i = 0; i < _m; ++i)
            result(i,j) = (*this)(i,j) - other(i,j);
    return result;
}

DenseMatrix DenseMatrix::operator*(const DenseMatrix& other)
{
    jets_assert_equal_to(_n, other.m());
    DenseMatrix result(_m, other.n());
    for (size_type i = 0; i < _m; ++i)
        for (size_type j = 0; j < other.n(); ++j)
            for (size_type k = 0; k < _n; ++k)
                result(i, j) += (*this)(i, k) * other(k, j);
    return result;
}

DenseMatrix DenseMatrix::operator*(const Real k)
{
    DenseMatrix result(_m, _n);
    for (size_type j = 0; j < _n; ++j)
        for (size_type i = 0; i < _m; ++i)
            result(i,j) = k * (*this)(i,j);
    return result;
}

DenseMatrix& DenseMatrix::add(const Real k, const DenseMatrix& m)
{
    jets_assert_equal_to(_m, m.m());
    jets_assert_equal_to(_n, m.n());
    for (size_type j = 0; j < _n; ++j)
        for (size_type i = 0; i < _m; ++i)
            (*this)(i,j) += k * m(i, j);
    return *this;
}

DenseMatrix& DenseMatrix::mult(const DenseMatrix& other)
{
    jets_assert_equal_to(_n, other.m());
    DenseMatrix result(_m, other.n());
    for (size_type i = 0; i < _m; ++i)
        for (size_type j = 0; j < other.n(); ++j)
            for (size_type k = 0; k < _n; ++k)
                result(i, j) += (*this)(i, k) * other(k, j);
    *this = std::move(result);
    return *this;
}

DenseMatrix& DenseMatrix::mult(const Real k)
{
    for (size_type j = 0; j < _n; ++j)
        for (size_type i = 0; i < _m; ++i)
            (*this)(i,j) *= k;
    return *this;
}

void DenseMatrix::zero() { std::fill(_val.begin(), _val.end(), static_cast<Real>(0)); }

DenseMatrix DenseMatrix::zeros(size_type m, size_type n)
{
    DenseMatrix result(m, n);
    result.zero();
    return result;
}

void DenseMatrix::resize(const size_type new_m, const size_type new_n)
{
    _val.resize(new_m * new_n);
    _m = new_m;
    _n = new_n;
    zero();
}

DenseMatrix& DenseMatrix::T()
{
    DenseMatrix tmp(_n, _m);
    for (size_type j = 0; j < _n; ++j)
        for (size_type i = 0; i < _m; ++i)
            tmp(j,i) = (*this)(i,j);
    *this = std::move(tmp);
    return *this;
}

DenseMatrix DenseMatrix::submatrix(size_type m_start, size_type m_end, size_type n_start, size_type n_end) const
{
    DenseMatrix result(m_end - m_start, n_end - n_start);
    for (size_type i = m_start; i < m_end; ++i) {
        for (size_type j = n_start; j < n_end; ++j) {
            result(i - m_start, j - n_start) = (*this)(i, j);
        }
    }
    return result;
}

void DenseMatrix::print(std::ostream& os=out) const
{
    for (size_type i = 0; i < _m; ++i)
    {
        os << "|";
        for (size_type j = 0; j < _n; ++j)
            os << _val[i * _n + j] << " ";
        os << "|" << std::endl;
    }
}

void DenseMatrix::print_scientific(std::ostream & os, unsigned precision) const
{
    os << std::scientific << std::setprecision(precision);
    print(os);
    os << std::fixed << std::setprecision(6);
}

std::ostream& operator << (std::ostream & os, const DenseMatrix& m)
{
    m.print_scientific(os);
    return os;
}
} // namespace jets
