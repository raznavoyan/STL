#include "../headers/queue.h"


int main(){
    queue<int> s = {1,2,3,4,5 , 6, 7 , 8 , 9 , 10};
    queue<int> s1 = {1,2,3,4,6,9,8,7,5,4};
    std::cout << s << std::endl; 
    std::cout << s[0] << std::endl; 
    std::cout << s[1] << std::endl; 
    std::cout << s.front() << std::endl;
     s1.swap(s);
     std::cout << s1 << std::endl; 
     std::cout << s << std::endl; 
    
}
