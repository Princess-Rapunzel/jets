#include "quadrature_gauss.h"
#include "quadrature_type.h"

namespace jets
{
QuadratureType QuadratureGauss::type() const { return QGAUSS; }

// void QuadratureGauss::init_2D (const ElemType elem_type)
// {
//     switch ( elem_type )
//     {
//     case TRI3:
//         // TODO: Implement the Gauss quadrature rule for a triangle element. 
//         _points = { Point()};
//         _weights = { 1.0 };
//         break;
//     }
// }

/**
 * For triangle elements, Gauss quadrature is:
 * \int_{\Omega} f(x, y) d\Omega = S \sum_{i=1} W_i f(L_1^{(i)}, L_2^{(i)}, L_3^{(i)})
 * where S is the area of the triangle, W_i are the weights, and L_i^{(i)} are the Gauss points.
 */
Real QuadratureGauss::integrate(Real (*f)(const Point&), const ElemType elem_type) const
{
    Real _integral = 0;
    switch ( elem_type )
    {
        case TRI3:
            for (size_type i = 0; i < 3; i++)
            {
                Real x = _points[i].x();
                Real y = _points[i].y();
                Real w = _weights[i];
                Real fxy = f(_points[i]);
                _integral += w * fxy;
            }
        break;
    }
    return _integral;
}
} // namespace jets