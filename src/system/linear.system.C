#include "linear_system.h"
#include "aio_mesh.h"
#include "tri3.h"
#include "dense_vector.h"
#include <set>
#include <algorithm>

namespace jets
{

LinearSystem::LinearSystem(const char* name):
    _name(name),
    matrix(nullptr),
    b(nullptr),
    x(nullptr),
    _f(nullptr),
    _g(nullptr),
    _quadrature_rule(nullptr) { }

LinearSystem::~LinearSystem()
{
    this->matrix->resize(0, 0);
    this->b->resize(0);
}

void LinearSystem::assemble()
{
    jets_assert(this->_mesh);
    jets_assert_equal_to(this->_mesh->num_of_nodes(), this->matrix->rows());
    jets_assert_equal_to(this->_mesh->num_of_nodes(), this->matrix->cols());
    jets_assert_equal_to(this->_mesh->num_of_nodes(), this->b->size());

    jets_assert_msg(this->_f, "Right hand side function is not set.");
    jets_assert_msg(this->_g, "Boundary function is not set.");
    AIOMesh* mesh = dynamic_cast<AIOMesh*>(this->_mesh);
    this->matrix->setZero();
    this->b->setZero();
    size_type dof = this->_mesh->num_of_elems();
    for (size_type i = 0; i < dof; ++i)
    {
        // TODO: unit stiffness matrix only works for Tri3 now.
        auto& elem = dynamic_cast<Tri3&>(mesh->get_elem(i));
        auto Ke = elem.get_unit_stiffness_matrix();

        size_type um = Ke.m();
        size_type un = Ke.n();

        for (size_type j = 0; j < um; ++j)
        {
            size_type idx_j = elem.node(j)->id(); 
            for (size_type k = 0; k < un; ++k)
            {
                size_type idx_k = elem.node(k)->id();
                (*this->matrix)(idx_j, idx_k) += Ke(j, k);
            }
        }

        auto Fe = elem.get_rhs_vector(_f, this->_quadrature_rule);
        for (size_type j = 0; j < um; ++j)
        {
            size_type idx_j = elem.node(j)->id();
            (*this->b)(idx_j) += Fe[j];
        }
    }

    // Boundary condition
    // F = F - A[:, bd_indecies] @ bd_value
    auto& boundary_nodes = mesh->get_boundary_nodes();
    for (size_type i = 0; i < matrix->rows(); ++i)
    {
        Real _row = 0;
        __boundary_nodes_loop__(mesh)
        {
            Real bd_value = _g(*_node);
            _row += (*this->matrix)(i, _node->id()) * bd_value;
        }
        (*this->b)(i) -= _row;
    }
}

void LinearSystem::solve()
{
    this->x = std::make_shared<Eigen::VectorXd>(Eigen::VectorXd::Zero(this->b->size()));
    AIOMesh* mesh = dynamic_cast<AIOMesh*>(this->_mesh);
    size_type free_dof = mesh->num_of_nodes() - mesh->get_boundary_nodes().size();
    Eigen::MatrixXd* A = new Eigen::MatrixXd(free_dof, free_dof);
    Eigen::VectorXd* F = new Eigen::VectorXd(free_dof);
    std::vector<Node*>& bd_nodes = mesh->get_boundary_nodes();
    
    std::set<size_type>* _nodes_idx    = new std::set<size_type>();
    std::set<size_type>* _bd_nodes_idx = new std::set<size_type>();

    __all_nodes_loopi__(mesh)
    {
        _nodes_idx->insert(mesh->get_node(i).id());
    }

    __boundary_nodes_loop__(mesh)
    {
        _bd_nodes_idx->insert(_node->id());
    }
    std::set<size_type>* _free_nodes_idx = new std::set<size_type>();
    calc_free_nodes_idx(_nodes_idx, _bd_nodes_idx, _free_nodes_idx);

    size_type i = 0, j = 0;
    for (size_type _idx_i : *_free_nodes_idx)
    {   
        j = 0;
        for (size_type _idx_j : *_free_nodes_idx)
        {
            (*A)(i, j) = (*this->matrix)(_idx_i, _idx_j);
            ++j;
        }
        (*F)(i) = (*this->b)(_idx_i);
        ++i;
    }

    Eigen::FullPivLU<Eigen::MatrixXd> lu_decomp(*A);
    auto uh_free = std::make_shared<Eigen::VectorXd>(lu_decomp.solve(*F));
    i = 0, j = 0;
    for (size_type _idx : *_free_nodes_idx)
    {
        (*this->x)(_idx) = (*uh_free)(i);
        ++i;
    }
    for (size_type _idx : *_bd_nodes_idx)
    {
        (*this->x)(_idx) = _g(mesh->get_node(_idx));
    }
    delete A;
    delete F;
    delete _nodes_idx;
    delete _bd_nodes_idx;
    delete _free_nodes_idx;
    uh_free.reset();
}
} // namespace jets