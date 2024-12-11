#include <iostream>
#include "aio_mesh.h"
#include "jetscomm.h"
#include "linear_system.h"
#include <Eigen/Dense>

using namespace jets;
using namespace Eigen;

const std::string MESH_PATH = "/home/rapunzel/jets/mesh/matlab_mesh/tri3_21_24.txt";

/**
 * @brief Right hand side function for the Poisson equation.
 * 
 * Latex formula: $f(x, y, z) = \cos(\frac{\pi}{2}x)\sin(\frac{\pi}{2}y)\cos(\frac{\pi}{2}z)$. 
 */
Real u_exact(Point& p);

Real f(Point& p);

Real g(Point& p);

const std::string equaltion_info = "求解泊松方程：\n \
-△u = f(x, y, z), (x, y, z) ∈ Ω\n \
u = g(x, y, z), (x, y, z) ∈ ∂Ω\n \
其中：\n \
  Ω = {(x, y, z) | 0 < x < 1, 0 < y < 1, 0 < z < 1}\n \
  f(x, y, z) = 0\n \
  g(x, y, z) = u_exact(x, y, z) = cos(π/2*x)*sin(π/2*y)*cos(π/2*z) \n"; 

int main(int argc, char *argv[])
{

    AIOMesh mesh(2);
    mesh.read_mesh(MESH_PATH);

    LinearSystem system("poisson");
    system.attach_mesh(&mesh);

    size_type dof = mesh.num_of_nodes();
    auto& matrix = system.system_matrix();
    matrix = std::make_shared<Eigen::MatrixXd>(Eigen::MatrixXd::Zero(dof, dof));
    auto& rhs = system.rhs();
    rhs = std::make_shared<Eigen::VectorXd>(Eigen::VectorXd::Zero(dof));

    system.set_rhs_func(f);
    system.set_boundary_func(g);
    system.assemble();
    system.solve();
    jets::out << equaltion_info << std::endl;
    jets::out << "数值解为: " << std::endl;
    jets::out << *system.solution() << std::endl;
    return 0;
}

Real u_exact(Point& p)
{
    // r = sqrt(sum(p.^2, 2));
    // theta = atan2(p(:, 2), p(:, 1));
    // theta = (theta>=0).*theta+(theta<0).*(theta+2*pi);
    // z = r.^(2/3).*sin(2*theta/3);
    Real r = sqrt(p.x()*p.x() + p.y()*p.y() + p.z()*p.z());
    Real theta = atan2(p.y(), p.x());
    theta = (theta >= 0) ? theta : theta + 2*pi;
    return pow(r, 2./3.)*sin(2*theta/3);
}

Real f(Point& p) { return 0; }

Real g(Point& p) { return u_exact(p); }