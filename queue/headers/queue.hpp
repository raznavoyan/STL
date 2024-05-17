#ifndef __QUEUE__HPP__
#define __QUEUE__HPP__

#include "queue.h"

template<typename T>
queue<T>::queue()
{
    this->ob = nullptr;
}

template<typename T>
queue<T>::queue(const queue& rhv) 
    : queue()
{
    this->ob = rhv.ob;
}

template<typename T>
queue<T>::queue(queue&& rhv)
    : queue()
{
    this->ob = std::move(rhv.ob);
}

template<typename T>
queue<T>::~queue() {}

template<typename T>
queue<T>::queue(std::initializer_list<T> init)
{   
    for (const T& val : init){
        ob.push_back(val);
    }
}

template<typename T>
const queue<T>& queue<T>::operator=(const queue& rhv){
    if (this != &rhv){
        this->ob = rhv;
    }
     return *this; 
}

template<typename T>
const queue<T>& queue<T>::operator=(queue&& rhv){
        if (this != &rhv){
            this->ob = std::move(rhv.ob);
        }
    return *this;
}
template<typename T>
queue<T>::size_type queue<T>::front() const {
    return ob.front();
}

template<typename T>
void queue<T>::swap( queue& rhv){
    std::swap(ob , rhv.ob);
}

template<typename T>
bool queue<T>::empty() const {
    return !ob.size();
}


template<typename T>
queue<T>::size_type queue<T>::size() const {
    return ob.size();
}

template<typename T>
void queue<T>::push(const_referance elem){
   return ob.push_back(elem);
}

template<typename T>
void queue<T>::pop(){
    return ob.pop_front();
}

template<typename T>
queue<T>::referance queue<T>::operator[](size_type index) {
    return ob[index];
}

template<typename T>
bool operator<(const queue<T> lhs, const queue<T> rhs){
    return lhs.size() < rhs.size();
}

template<typename T>
bool operator>(const queue<T> lhs, const queue<T> rhs){
    return lhs.size() > rhs.size();
}

template<typename T>
bool operator<=(const queue<T> lhs, const queue<T> rhs){
    return lhs.size() <= rhs.size();
}

template<typename T>
bool operator>=(const queue<T> lhs, const queue<T> rhs){
    return lhs.size() >= rhs.size();
}

template<typename T>
bool operator==(const queue<T> lhs, const queue<T> rhs){
    return lhs.size() == rhs.size();
}

template<typename T>
bool operator!=(const queue<T> lhs, const queue<T> rhs){
    return lhs.size() != rhs.size();
}

template<typename T>
std::ostream& operator<<(std::ostream& os ,  queue<T>& rhv){
    for(size_t i = 0; i < rhv.size(); ++i){
        os << rhv[i] << " ";
    }
    return os; 
}

#endif // 
