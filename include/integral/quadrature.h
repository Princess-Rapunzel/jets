#ifndef __JETS_QUADRATURE_H__
#define __JETS_QUADRATURE_H__

#include "jets.h"
#include "point.h"
#include "elem_type.h"
#include <vector>
#include <memory>
namespace jets
{
// Forward declarations.
class QuadratureType;

typedef unsigned int q_order;

__jets_abstract__ class Quadrature
{
public:

    explicit Quadrature(int dim): _dim(dim) {}
    Quadrature(const Quadrature &q) = default;
    Quadrature(Quadrature &&q) = default;
    Quadrature &operator=(const Quadrature &q) = default;
    Quadrature &operator=(Quadrature &&q) = default;

    virtual ~Quadrature() = default;

    /**
     * @return The quadrature type in derived classes.
     */
    virtual QuadratureType type() const = 0;

    /**
   * Builds a specific quadrature rule based on the `name`
   * string. This enables selection of the quadrature rule at
   * run-time. 
   *
   * This function allocates memory, therefore a 
   * `std::unique_ptr<Quadrature>`
   * is returned so that the user does not accidentally leak it.
   */
  static std::unique_ptr<Quadrature> 
  build(std::string_view name, const size_type dim);

/**
   * \returns The number of points associated with the quadrature rule.
   */
  unsigned int n_points() const
  {
    jets_assert(!_points.empty());
    return _points.size();
  }

  /**
   * \returns The spatial dimension of the quadrature rule.
   */
  unsigned int get_dim() const { return _dim; }

  /**
   * \returns A \p std::vector containing the quadrature point locations
   * in reference element space.
   */
  const std::vector<Point>& get_points() const { return _points; }

  /**
   * \returns A \p std::vector containing the quadrature point locations
   * in reference element space as a writable reference.
   */
  std::vector<Point>& get_points() { return _points; }

  /**
   * \returns A constant reference to a \p std::vector containing the
   * quadrature weights.
   */
  const std::vector<Real>& get_weights() const { return _weights; }

  /**
   * \returns A writable references to a \p std::vector containing the
   * quadrature weights.
   */
  std::vector<Real>& get_weights() { return _weights; }

  /**
   * \returns The \f$ i^{th} \f$ quadrature point in reference element space.
   */
  Point p(const unsigned int i) const
  {
    jets_assert_less (i, _points.size());
    return _points[i];
  }

  /**
   * \returns The \f$ i^{th} \f$ quadrature weight.
   */
  Real w(const unsigned int i) const
  {
    jets_assert_less (i, _weights.size());
    return _weights[i];
  }

protected:
  /**
   * Initializes the 1D quadrature rule by filling the points and
   * weights vectors with the appropriate values.  The order of
   * the rule will be defined by the implementing class.
   * It is assumed that derived quadrature rules will at least
   * define the init_1D function, therefore it is pure virtual.
   *
   * \note The arguments should no longer be used for anything in
   * derived classes, they are only maintained for backwards
   * compatibility and will eventually be removed.
   */
  virtual void init_1D (const ElemType type=INVALID_TYPE);

  /**
   * Initializes the 2D quadrature rule by filling the points and
   * weights vectors with the appropriate values.  The order of
   * the rule will be defined by the implementing class.
   * Should not be pure virtual since a derived quadrature rule
   * may only be defined in 1D.  If not overridden, throws an
   * error.
   *
   * \note The arguments should no longer be used for anything in
   * derived classes, they are only maintained for backwards
   * compatibility and will eventually be removed.
   */
  virtual void init_2D (const ElemType type=INVALID_TYPE);

  /**
   * Initializes the 3D quadrature rule by filling the points and
   * weights vectors with the appropriate values.  The order of
   * the rule will be defined by the implementing class.
   * Should not be pure virtual since a derived quadrature rule
   * may only be defined in 1D.  If not overridden, throws an
   * error.
   *
   * \note The arguments should no longer be used for anything in
   * derived classes, they are only maintained for backwards
   * compatibility and will eventually be removed.
   */
  virtual void init_3D (const ElemType type=INVALID_TYPE);

protected:
  size_type _dim;
  /**
   * The locations of the quadrature points in reference element
   * space.
   */
  std::vector<Point> _points;

  /**
   * The quadrature weights.  The order of the weights matches the
   * ordering of the _points vector.
   */
  std::vector<Real> _weights;

  /**
   * The type of element for which the current values have been
   * computed.
   */
  ElemType _type;

  /**
   * The polynomial order which the quadrature rule is capable of
   * integrating exactly.
   */
  q_order _order;
};
} // namespace jets

#endif // __JETS_QUADRATURE_H__