#ifndef __STACK__
#define __STACK__
#include<vector>

template<typename T, typename Container = std::vector<T>>
class stack{
private:
    Container ob;
public:
    //stack(){};
    //copyconstructor
    //moveconstructor
    //initialazer list
    //~stack();
    //push();
    //pop();
    //size();
    //empty();
    //swap(stack&)
    //value_t& top();
}

#include"../sources/stack.tpp"

#endif
