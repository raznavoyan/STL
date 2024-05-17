#ifndef __STACK_HPP__
#define __STACK_HPP__

#include "stack.h"

template<typename T>
stack<T>::stack(){}

template<typename T>
stack<T>::stack(const stack& rhv)  
    : m_data(rhv.m_data)
{}

template<typename T>
stack<T>::stack(stack&& rhv)
    : m_data(std::move(rhv.m_data))
{}

template<typename T>
stack<T>::stack(std::initializer_list<T> init)
    : m_data(init)
{}

template<typename T>
stack<T>::~stack() noexcept {}

template<typename T>
void stack<T>::push(const_referance arg){
    m_data.push_back(arg);
}

template<typename T>
void stack<T>::pop(){
    if(!m_data.empty()){
        m_data.pop_back();
    }else{
        throw std::runtime_error("Cannot pop from an empty stack");
    }
}

template<typename T>
stack<T>::referance stack<T>::top(){
    return m_data.back();
}

template<typename T>
stack<T>::size_type stack<T>::size() const{
    return m_data.size();
}

template<typename T>
void stack<T>::swap(stack& rhv){
    std::swap(m_data, rhv.m_data);
}

template<typename T>
bool stack<T>::empty(){
    return !m_data.empty();
}

template<typename T>
const stack<T>& stack<T>::operator=(const stack& rhv){
    if (this != &rhv){
        m_data.clear();
        m_data = rhv.m_data;
    }
    return *this;
}

template<typename T>
const stack<T>& stack<T>::operator=(stack&& rhv){
    if (this != &rhv){
        m_data = std::move(rhv.m_data);
    }
    return *this;
}

template<typename T>
stack<T>::referance stack<T>::operator[](size_type index) {
    return m_data[index];
}

///////////////////////////////////////////////////////////

template<typename T>
bool operator<( stack<T>& lhs, stack<T> &rhs){
    return lhs.size() < rhs.size(); 
}

template<typename T>
bool operator<=( stack<T>& lhs, stack<T>& rhs){
    return lhs.size() <= rhs.size();
}

template<typename T>
bool operator>( stack<T>& lhs, stack<T>& rhs){
    return  lhs.size() > rhs.size();
}

template<typename T>
bool operator>=( stack<T>& lhs, stack<T>& rhs){
    return lhs.size() >= rhs.size();
}

template<typename T>
bool operator==( stack<T>& lhs,  stack<T>& rhs){
    return lhs.size() == rhs.size();
}

template<typename T>
bool operator!=( stack<T>& lhs,  stack<T>& rhs){
    return lhs.size() != rhs.size();
}

template<typename T>
std::ostream& operator<<(std::ostream& os , stack<T>& rhv){
    for (size_t i = 0; i < rhv.size(); ++i){
        os << rhv[i] << " ";
    }
    return os;
}

#endif // STACK_HPP__
