#include <iostream>
#include "tri3.h"
#include "node.h"

using namespace jets;

int main(int argc, char *argv[])
{
    Node node1(1, 2, 3, 1);
    Node node2(4, 5, 6, 2);
    Node node3(7, 8, 9, 3);
    Tri3 tri({node1, node2, node3}, 1);
    for (auto edge : tri.edges())
    {
        std::cout << edge << std::endl;
    }
    return 0;
}
