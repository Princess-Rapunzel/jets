#ifndef __JETS_POINT_H__
#define __JETS_POINT_H__
#include "jetscomm.h"
namespace jets
{

class Point
{
public:
    Point();
    Point(Real x, Real y);
    Point(Real x, Real y, Real z);
    Point(const Point& p);
    Point(Point&& p);
    Point& operator=(const Point& p);
    Point& operator=(Point&& p);
    const inline Real& x() const { return _coords[0]; }
    const inline Real& y() const { return _coords[1]; }
    const inline Real& z() const { return _coords[2]; }
    ~Point();
protected:
    Real _coords[JETS_MAX_DIM];
};
} // namespace jets

#endif // __JETS_POINT_H__