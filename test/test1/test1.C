#include <iostream>
#include "tri3.h"
#include "node.h"

using namespace jets;

int main(int argc, char *argv[])
{
    Node node1(0, 0, 3);
    Node node2(3, 0, 1);
    Node node3(0, 4, 2);
    Tri3 tri({node1, node2, node3}, 1);
    auto m = tri.get_unit_stiffness_matrix();
    std::cout << tri.grad() << std::endl;
    std::cout << tri.measure() << std::endl;
    std::cout << m << std::endl;
    return 0;
}
