#ifndef __JETS_EDGE_H__
#define __JETS_EDGE_H__
#include "node.h"
namespace jets
{
class Edge
{
public:
    Edge(Node& start, Node& end);
private:

Node& start_node;

Node& end_node;
};

} // namespace jets

#endif // __JETS_EDGE_H__