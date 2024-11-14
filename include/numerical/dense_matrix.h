#ifndef __JETS_DENSE_MATRIX_H__
#define __JETS_DENSE_MATRIX_H__
#include "base_matrix.h"
#include "jetscomm.h"
#include <vector>

namespace jets
{
class DenseMatrix : public BaseMatrix
{
public:
    DenseMatrix(unsigned int m, unsigned int n);
    DenseMatrix (DenseMatrix &&);
    DenseMatrix (const DenseMatrix &);
    DenseMatrix& operator= (const DenseMatrix &);
    DenseMatrix& operator= (DenseMatrix &&);
    ~DenseMatrix();
    double& operator() (unsigned int i, unsigned int j);
    const double& operator() (unsigned int i, unsigned int j) const;

private:
    std::vector<Real> _val;
};
} // namespace jets

#endif // __JETS_DENSE_MATRIX_H__