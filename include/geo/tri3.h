#ifndef __JETS_TRI3_H__
#define __JETS_TRI3_H__

#include "elem.h"

namespace jets
{
class Tri3 : public Elem
{
public:
    Tri3(Node** nodes);
    Tri3 (Tri3 &&);
    Tri3 (const Tri3 &);
    Tri3& operator= (const Tri3 &);
    Tri3& operator= (Tri3 &&);

    ~Tri3();

    virtual const Real& measure() const override;
    virtual Elem& buid() override;
    virtual ElemType& type() override;
    virtual Real grad() override;

    Real measure_coordinate(const Real& x, const Real& y, const Real &lambda) const;

    // Matrix& get_unit_stiffness_matrix() const;
};
} // namespace jets


#endif // __JETS_TRI3_H__