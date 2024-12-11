#ifndef __JETS_DENSE_VECTOR_H__
#define __JETS_DENSE_VECTOR_H__
#include "base_vector.h"
#include <vector>
namespace jets
{
class DenseVector : public BaseVector
{
public:
    DenseVector();
    DenseVector(size_type size);
    DenseVector(std::initializer_list<Real> init_list);
    DenseVector(const DenseVector& other);
    DenseVector(DenseVector&& other);
    virtual ~DenseVector();
    DenseVector& operator=(const DenseVector& other);
    DenseVector& operator=(DenseVector&& other);

    DenseVector operator+(const DenseVector& other) const;
    DenseVector operator-(const DenseVector& other) const;
    DenseVector operator*(const Real& scalar) const;
    Real operator*(const DenseVector& other) const;

    Real& operator[](size_type i);
    const Real& operator[](size_type i) const;
    size_type size() const;
    void resize(size_type size);
    void zero();
    void print(std::ostream& os=out) const;
    friend std::ostream& operator << (std::ostream & os, const DenseVector& m);
    void print_scientific(std::ostream & os, unsigned precision=8) const;
private:
    std::vector<Real> _val;
};
} // namespace jets

#endif // __JETS_DENSE_VECTOR_H__