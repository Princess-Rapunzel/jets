#ifndef __JETS_BASE_MATRIX_H__
#define __JETS_BASE_MATRIX_H__
#include "jets.h"
#include "jetscomm.h"
namespace jets
{
class BaseMatrix
{
public:

    BaseMatrix(size_type m, size_type n);
    BaseMatrix (BaseMatrix &&);
    BaseMatrix (const BaseMatrix &);
    BaseMatrix& operator= (const BaseMatrix &);
    BaseMatrix& operator= (BaseMatrix &&);
    ~BaseMatrix();

    size_type m() const;
    size_type n() const;
protected:
    size_type _m;
    size_type _n;
};

__jets_inline__ BaseMatrix::BaseMatrix(size_type m, size_type n) : _m(m), _n(n) { }
__jets_inline__ BaseMatrix::BaseMatrix (BaseMatrix && mat) : _m(mat._m), _n(mat._n) { mat._m = 0; mat._n = 0; }
__jets_inline__ BaseMatrix::BaseMatrix (const BaseMatrix & mat) : _m(mat._m), _n(mat._n){ }
__jets_inline__ BaseMatrix& BaseMatrix::operator= (const BaseMatrix & mat) { _m = mat._m; _n = mat._n; return *this; }
__jets_inline__ BaseMatrix& BaseMatrix::operator= (BaseMatrix && mat) { if (this != &mat) { std::swap(_m, mat._m); std::swap(_n, mat._n); } return *this; }
__jets_inline__ BaseMatrix::~BaseMatrix() = default;
inline size_type BaseMatrix::m() const { return _m; }
inline size_type BaseMatrix::n() const { return _n; }
} // namespace jets

#endif // __JETS_BASE_MATRIX_H__