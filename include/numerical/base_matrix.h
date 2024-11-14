#ifndef __JETS_BASE_MATRIX_H__
#define __JETS_BASE_MATRIX_H__

namespace jets
{
class BaseMatrix
{
public:
    BaseMatrix(unsigned int m, unsigned int n);
    BaseMatrix (BaseMatrix &&);
    BaseMatrix (const BaseMatrix &);
    BaseMatrix& operator= (const BaseMatrix &);
    BaseMatrix& operator= (BaseMatrix &&);
    ~BaseMatrix();

    unsigned int m() const;
    unsigned int n() const;
protected:
    unsigned int _m;
    unsigned int _n;
};

inline unsigned int BaseMatrix::m() const { return _m; }
inline unsigned int BaseMatrix::n() const { return _n; }
} // namespace jets

#endif // __JETS_BASE_MATRIX_H__