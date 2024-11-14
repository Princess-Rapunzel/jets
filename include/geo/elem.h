#ifndef __JETS_ELEM_H__
#define __JETS_ELEM_H__

#include "jetscomm.h"
#include "node.h"
#include "elem_type.h"
#include "edge.h"

#include <vector>

namespace jets
{
JETS_ABSTRACT class Elem
{
public:

    const static int INVALID_ID = -1;

    Elem(std::initializer_list<Node> init_list, int id = INVALID_ID);
    Elem (Elem &&);
    Elem(const Elem &);
    Elem& operator= (const Elem &);
    Elem& operator= (Elem &&);

    virtual ~Elem();


    virtual const Real& measure() const = 0;
    virtual const ElemType type() = 0;
    virtual Real grad() = 0;

    int num_of_nodes() const;
    const int& id() const;
    int& id();
    const Node& node(int i) const;
    const int& node_id(int i) const;

    const std::vector<Edge>& edges() const;
    const int num_of_edges() const;
protected:
    std::vector<Node> _nodes;
    int _num_of_nodes;
    Real _measure;
    int _id;
    std::vector<Edge> _edges;

    void __init_edges();
#ifdef JETS_HAVE_MPI
    int processor_id;
#endif // JETS_HAVE_MPI
};
} // namespace jets

#endif // __JETS_ELEM_H__