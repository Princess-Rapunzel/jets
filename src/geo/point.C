#include "point.h"

namespace jets
{
Point::Point(): _coords{0, 0, 0} { }
Point::Point(Real x, Real y): _coords{x, y, 0} {}
Point::Point(Real x, Real y, Real z): _coords{x, y, z} {}

Point::Point(const Point& p)
{
    for (size_type i = 0; i < JETS_MAX_DIM; ++i)
    {
        _coords[i] = p._coords[i];
    }
}

Point::Point(Point&& p)
{
    for (size_type i = 0; i < JETS_MAX_DIM; ++i)
    {
        _coords[i] = p._coords[i];
        p._coords[i] = 0;
    }
}

Point& Point::operator=(const Point& p)
{
    if (this != &p)
    {
        for (size_type i = 0; i < JETS_MAX_DIM; ++i)
        {
            _coords[i] = p._coords[i];
        }
    }
    return *this;
}

Point& Point::operator=(Point&& p)
{
    if (this != &p)
    {
        for (size_type i = 0; i < JETS_MAX_DIM; ++i)
        {
            _coords[i] = p._coords[i];
            p._coords[i] = 0;
        }
    }
    return *this;
}

Point::~Point() = default;
} // namespace jets
