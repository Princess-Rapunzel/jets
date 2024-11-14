#ifndef __JETS_NODE_H__
#define __JETS_NODE_H__
// #include "jetscomm.h"
#include "ostream_proxy.h"
#include "jetscomm.h"
#include <memory>
namespace jets
{
// OStreamProxy out;

class Node
{
public:
    Node();
    Node(Real x, Real y, Real z, int id);
    Node(const Node &n);
    ~Node();
    Node & operator= (const Node & p);
    std::unique_ptr<Node> build(const Real x, const Real y, const Real z, const int id);
    const Real& x() const;
    const Real& y() const;
    const Real& z() const;
    const int& id() const;
    int& id();

    bool operator==(const Node& other) const;

    std::string get_info() const;
    void print_info(std::ostream& os=out) const;
private:
Real _coords[JETS_MAX_DIM];
int _id;
};

inline std::ostream & operator << (std::ostream & os, const Node & n)
{
  n.print_info(os);
  return os;
}
} // namespace jets


#endif // __JETS_NODE_H__