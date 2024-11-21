#ifndef __JETS_QUADRATURE_TYPE_H__
#define __JETS_QUADRATURE_TYPE_H__

namespace jets
{
enum QuadratureType : int {
                     QGAUSS            = 0,
                     QJACOBI_1_0       = 1,
                     QJACOBI_2_0       = 2,
                     QSIMPSON          = 3,
                     QTRAP             = 4,
                     QGRID             = 5,
                     QGRUNDMANN_MOLLER = 6,
                     QMONOMIAL         = 7,
                     QCONICAL          = 8,
                     QGAUSS_LOBATTO    = 9,
                     QCLOUGH           = 21,
                     QCOMPOSITE        = 31,
                     QNODAL            = 32,
                     // Invalid
                     INVALID_Q_RULE    = 127};
} // namespace jets

#endif // __JETS_QUADRATURE_TYPE_H__