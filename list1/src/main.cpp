#include "headers/List.hpp"

int
main()
{
    List<int> l(3);
    std::cout << l.empty() << std::endl;
    l.push_back(1);
    l.push_back(2);
    std::cout << l.empty() << std::endl;
 
    return 0;
}