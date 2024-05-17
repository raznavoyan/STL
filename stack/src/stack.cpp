#ifndef __STACK__CPP__
#define __STACK__CPP__

#include "stack.h"

namespace g3{

template<typename T, typename Container>
stack<T, Container>::stack() : ob() {}

template<typename T, typename Container>
stack<T, Container>::stack(const stack& rhv) : ob(rhv.ob) {}

template<typename T, typename Container>
stack<T, Container>::stack(stack&& rhv) : ob(std::move(rhv.ob)) {}

template<typename T, typename Container>
stack<T, Container>::stack(std::initializer_list<value_type> init) : ob(init) {}

template<typename T, typename Container>
template<typename InputIt>
stack<T, Container>::stack(InputIt first, InputIt last) : ob(first, last) {}

template<typename T, typename Container>
stack<T, Container>::~stack() {}

template<typename T, typename Container>
const stack<T, Container>& stack<T, Container>::operator=(const stack& rhv) {
    ob = rhv.ob;
    return *this;
}

template<typename T, typename Container>
const stack<T, Container>& stack<T, Container>::operator=(stack&& rhv) {
    ob = std::move(rhv.ob);
    return *this;
}

template<typename T, typename Container>
bool stack<T, Container>::empty() const {
    return ob.empty();
}

template<typename T, typename Container>
typename stack<T, Container>::size_type stack<T, Container>::size() const {
    return ob.size();
}

template<typename T, typename Container>
void stack<T, Container>::push(const value_type& value) {
    ob.push_back(value);
}

template<typename T, typename Container>
void stack<T, Container>::push(stack&& rhv){
    ob.push_back(std::move(rhv));
}

template<typename T, typename Container>
void stack<T, Container>::pop() {
    ob.pop_back();
}

template<typename T, typename Container>
typename stack<T, Container>::value_type& stack<T, Container>::top() {
    return ob.back();
}

template<typename T, typename Container>
const typename stack<T, Container>::value_type& stack<T, Container>::top() const {
    return ob.back();
}

}

#endif