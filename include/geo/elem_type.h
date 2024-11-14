#ifndef __JETS_ELEM_TYPE_H__
#define __JETS_ELEM_TYPE_H__

namespace jets
{
enum ElemType: int
{

    INVALID_TYPE = -1,

    LINE2 = 1,

    LINE3 = 2,

    TRI3 = 3,

    TRI6 = 4,

    QUAD4 = 5,

    QUAD8 = 6
};
} // namespace jets


#endif // __JETS_ELEM_TYPE_H__