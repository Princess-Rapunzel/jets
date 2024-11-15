#ifndef __JETS_TRI3_H__
#define __JETS_TRI3_H__

#include "elem.h"

namespace jets
{
class Tri3 : public Elem
{
public:
    Tri3(std::initializer_list<Node> init_list, int id = INVALID_ID);
    Tri3 (Tri3 &&);
    Tri3 (const Tri3&);
    Tri3& operator= (const Tri3 &);
    Tri3& operator= (Tri3 &&);

    ~Tri3();

    virtual const Real& measure() const override;
    virtual const ElemType type() override;
    virtual DenseMatrix grad() const override;

    Real measure_coordinate(const Real& x, const Real& y, const Real &lambda) const;
    DenseMatrix get_unit_stiffness_matrix() const;
    // Matrix& get_unit_stiffness_matrix() const;
};

std::ostream& operator << (std::ostream& os, const Tri3& tri);
} // namespace jets


#endif // __JETS_TRI3_H__