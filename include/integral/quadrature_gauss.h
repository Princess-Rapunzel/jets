#ifndef __JETS_QUADRATURE_GAUSS_H__
#define __JETS_QUADRATURE_GAUSS_H__
#include "quadrature.h"
namespace jets
{
class QuadratureGauss : public Quadrature
{
public:
    explicit QuadratureGauss(size_type dim): Quadrature(dim) {}

    QuadratureGauss(const QuadratureGauss &q) = default;
    QuadratureGauss(QuadratureGauss &&q) = default;
    QuadratureGauss &operator=(const QuadratureGauss &q) = default;
    QuadratureGauss &operator=(QuadratureGauss &&q) = default;

    virtual ~QuadratureGauss() = default;

    /**
     * \returns \p QGAUSS.
     */
  virtual QuadratureType type() const override;

private:

  virtual void init_1D (const ElemType) override;
  virtual void init_2D (const ElemType) override;
  virtual void init_3D (const ElemType) override;
};
} // namespace jets

#endif // __JETS_QUADRATURE_GAUSS_H__