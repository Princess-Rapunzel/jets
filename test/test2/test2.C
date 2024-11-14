// #include "node.h"
#include <vector>
#include <string>
#include <iostream>
class A
{
public:
A (std::initializer_list<std::string> il) : _edges(il) {}
std::vector<std::string> _edges;
};

int main(int argc, char const *argv[])
{
    // jets::Node n1(1.0, 2.0, 3.0, 1);
    // n1.print_info();
    A a({"a", "b", "c"});
    std::cout << a._edges.size() << std::endl;
    system("pause");
    return 0;
}
