#ifndef __JETS_MEASURES_H__
#define __JETS_MEASURES_H__
#include "jetscomm.h"
#include "jets.h"

namespace jets
{
/**
 * @brief Compute the measure of a triangle given its three nodes.
 * measure = (x2 * y3 - x3 * y2 - x1 * y3 + x3 * y1 + x1 * y2 - x2 * y1) / 2
 */
JETS_INLINE Real 
triangle_measure(const Real& x1, const Real& y1, const Real& x2, const Real& y2, const Real& x3, const Real& y3)
{ return (x2 * y3 - x3 * y2 - x1 * y3 + x3 * y1 + x1 * y2 - x2 * y1) / 2; }
}
#endif // __JETS_MEASURES_H__