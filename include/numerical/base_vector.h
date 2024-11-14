#ifndef __JETS_BASE_VECTOR_H__
#define __JETS_BASE_VECTOR_H__
#include "jets.h"
#include "jetscomm.h"
namespace jets
{

JETS_ABSTRACT class BaseVector
{
public:
    BaseVector();
    BaseVector(size_type size);
    BaseVector(const BaseVector& other);
    BaseVector(BaseVector&& other);
    virtual ~BaseVector();
protected:
    size_type _m;
};

JETS_INLINE BaseVector::BaseVector() : _m(0) {}
JETS_INLINE BaseVector::BaseVector(size_type size) : _m(size) {}
JETS_INLINE BaseVector::BaseVector(const BaseVector& other) : _m(other._m) {}
JETS_INLINE BaseVector::~BaseVector() = default;
JETS_INLINE BaseVector::BaseVector(BaseVector&& other) : _m(other._m) {}
} // namespace jets


#endif // __JETS_BASE_VECTOR_H__