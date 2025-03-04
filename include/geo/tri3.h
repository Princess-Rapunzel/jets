#ifndef __JETS_TRI3_H__
#define __JETS_TRI3_H__

#include "elem.h"
#include "measures.h"


namespace jets
{
// Forward declarations.
class Quadrature;

class Tri3 : public Elem
{
public:
    Tri3(std::initializer_list<Node*> init_list, int id = INVALID_ID);
    Tri3(std::vector<Node*> nodes, int id = INVALID_ID);
    Tri3 (Tri3 &&);
    Tri3 (const Tri3&);
    Tri3& operator= (const Tri3 &);
    Tri3& operator= (Tri3 &&);

    ~Tri3();

    virtual const Real& measure() const override;
    virtual const ElemType type() override;
    virtual DenseMatrix grad() const override;
    virtual Real shape_function(int i, const Point &p) const override;

    Real measure_coordinate(const Real& x, const Real& y, const Real &lambda) const;
    DenseMatrix get_unit_stiffness_matrix() const;
    // Matrix& get_unit_stiffness_matrix() const;
    DenseMatrix get_unit_mass_matrix() const;
    DenseVector get_rhs_vector(Real (*)(Point&), Quadrature*) const;
private:
#define tri3_measure(nodes) \
    triangle_measure((nodes)[0]->x(), (nodes)[0]->y(), (nodes)[1]->x(), (nodes)[1]->y(), (nodes)[2]->x(), (nodes)[2]->y())
};


std::ostream& operator << (std::ostream& os, const Tri3& tri);
} // namespace jets


#endif // __JETS_TRI3_H__