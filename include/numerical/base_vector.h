#ifndef __JETS_BASE_VECTOR_H__
#define __JETS_BASE_VECTOR_H__
#include "jets.h"
#include "jetscomm.h"
namespace jets
{

__jets_abstract__ class BaseVector
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

__jets_inline__ BaseVector::BaseVector() : _m(0) {}
__jets_inline__ BaseVector::BaseVector(size_type size) : _m(size) {}
__jets_inline__ BaseVector::BaseVector(const BaseVector& other) : _m(other._m) {}
__jets_inline__ BaseVector::~BaseVector() = default;
__jets_inline__ BaseVector::BaseVector(BaseVector&& other) : _m(other._m) {}
} // namespace jets


#endif // __JETS_BASE_VECTOR_H__