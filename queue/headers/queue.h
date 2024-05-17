#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <iostream>
#include <deque>


template<typename T>
class queue {
private:
    std::deque<T> ob;
public:
    using value_type = T;
    using size_type = std::size_t;
    using referance = value_type&;
    using const_referance = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

public:
    //defolt
    queue();
    //copy constructor
    queue(const queue&);
    //move constructor
    queue(queue&&);
    //destructor
    ~queue();

public:
    const queue& operator=(const queue<T>&);
    const queue& operator=(queue<T>&&);
    queue(std::initializer_list<T>);
    void push(const_referance);
    void pop();

public:
    size_type front() const;
    size_type size()  const;
    void swap(queue&);
    bool empty() const;
    referance operator[](size_type index);
};

// operator owerloading
template<typename T>
bool operator<(const queue<T> lhs, const queue<T> rhs);

template<typename T>
bool operator<=(const queue<T> lhs, const queue<T> rhs);

template<typename T>
bool operator>(const queue<T> lhs, const queue<T> rhs);

template<typename T>
bool operator>=(const queue<T> lhs, const queue<T> rhs);

template<typename T>
bool operator==(const queue<T> lhs, const queue<T> rhs);

template<typename T>
bool operator!=(const queue<T> lhs, const queue<T> rhs);

template<typename T>
std::ostream& operator<<(std::ostream& os , const queue<T>&);

#include "queue.hpp"

#endif //  __STACK_H__
