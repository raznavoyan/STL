#ifndef __STACK_H__
#define __STACK_H__

#include <iostream>
#include <vector>

template<typename T>

class stack {
private:
    std::vector<T> m_data;

public:
    using value_type = T;
    using size_type = std::size_t;
    using referance = value_type&;
    using const_referance = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

public:
    //defolt constructor
    stack();
    //copy constructor
    stack(const stack&);
    //move constructor
    stack(stack&&);
    //initializer_list constructor
    stack(std::initializer_list<T>);
    //destructor
    ~stack()noexcept;

public:
    void push(const_referance );
    void pop();
    referance top();
    size_type size() const;
    void swap(stack&);
    bool empty();

public:
    const stack& operator=(const stack<T>&);
    const stack& operator=(stack<T>&&);
    referance operator[](size_type index);

};

template<typename T>
bool operator<( stack<T>& lhs, stack<T>& rhs);

template<typename T>
bool operator<=( stack<T>& lhs, stack<T>& rhs);

template<typename T>
bool operator>( stack<T>& lhs, stack<T>& rhs);

template<typename T>
bool operator>=( stack<T>& lhs, stack<T>& rhs);

template<typename T>
bool operator==( stack<T>& lhs, stack<T>& rhs);

template<typename T>
bool operator!=( stack<T>& lhs, stack<T>& rhs);

template<typename T>
std::ostream& operator<<(std::ostream& os, stack<T>& rhv);

#include "stack.cpp"

#endif //  __STACK_H__

