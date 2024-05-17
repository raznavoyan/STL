#include "../headers/stack.h"


int main() {
    stack<int> s = {5,7,8,9,5,4,3,2,1}; 
    stack<int> s1 = {4,3,1,2};

    s1.swap(s);
    // std::cout << s << std::endl; 
    std::cout << s1 << std::endl; 
    std::cout << s << std::endl;
    // s.push(55);
    // std::cout << s << std::endl; 
    // s.pop();
    // std::cout << s << std::endl; 
    // std::cout << s.top() << std::endl; 

}
