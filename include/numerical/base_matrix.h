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

JETS_INLINE BaseMatrix::BaseMatrix(size_type m, size_type n) : _m(m), _n(n) { }
JETS_INLINE BaseMatrix::BaseMatrix (BaseMatrix && mat) : _m(mat._m), _n(mat._n) { mat._m = 0; mat._n = 0; }
JETS_INLINE BaseMatrix::BaseMatrix (const BaseMatrix & mat) : _m(mat._m), _n(mat._n){ }
JETS_INLINE BaseMatrix& BaseMatrix::operator= (const BaseMatrix & mat) { _m = mat._m; _n = mat._n; return *this; }
JETS_INLINE BaseMatrix& BaseMatrix::operator= (BaseMatrix && mat) { if (this != &mat) { std::swap(_m, mat._m); std::swap(_n, mat._n); } return *this; }
JETS_INLINE BaseMatrix::~BaseMatrix() = default;
inline size_type BaseMatrix::m() const { return _m; }
inline size_type BaseMatrix::n() const { return _n; }
} // namespace jets

#endif // __JETS_BASE_MATRIX_H__