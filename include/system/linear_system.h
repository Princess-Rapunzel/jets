#ifndef __JETS_LINEAR_SYSTEM_H__
#define __JETS_LINEAR_SYSTEM_H__
#include "base_mesh.h"
#include "quadrature.h"
#include <Eigen/Dense>
#include <memory>
namespace jets
{

class LinearSystem
{
public:
    LinearSystem(const char* name);
    virtual ~LinearSystem();

    void attach_mesh(BaseMesh* mesh) { _mesh = mesh; }

    void solve();

    std::shared_ptr<Eigen::MatrixXd>& system_matrix() { return matrix; }

    const std::shared_ptr<Eigen::MatrixXd>& system_matrix() const {  return matrix; }

    const std::shared_ptr<Eigen::VectorXd>& solution() const { return x; }

    std::shared_ptr<Eigen::VectorXd>& rhs() { return b; }

    const std::shared_ptr<Eigen::VectorXd>& rhs() const { return b; }

    void set_rhs_func(Real (*f)(Point&)) { _f = f; }

    void set_boundary_func(Real (*g)(Point&)) { _g = g; }

    virtual void assemble();

    void set_quadrature_rule(Quadrature* qrule) { _quadrature_rule = qrule; }
protected:
    /**
     * @brief The name of the linear system.
     */
    const char* _name;

    /**
     * @brief The mesh attached to the linear system.
     */
    BaseMesh* _mesh;

    /**
     * @brief The matrix of the linear system.
     * This should be the 'A' of 'Ax = b'.
     */
    std::shared_ptr<Eigen::MatrixXd> matrix;

    /**
     * @brief The solution vector of the linear system.
     * This should be the 'x' of 'Ax = b'.
     */
    std::shared_ptr<Eigen::VectorXd> x;

    /**
     * @brief The right hand side vector of the linear system.
     * This should be the 'b' of 'Ax = b'.
     */
    std::shared_ptr<Eigen::VectorXd> b;

    /**
     * @brief Function pointer to the right hand side function.
     */
    Real (*_f)(Point&);

    /**
     * @brief Function pointer to the boundary function.
     */
    Real (*_g)(Point&);

    /**
     * @brief The quadrature rule used to assemble the linear system.
     */
    Quadrature* _quadrature_rule;
};
} // namespace jets

#endif // __JETS_LINEAR_SYSTEM_H__