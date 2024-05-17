#ifndef __QUEUE__CPP__
#define __QUEUE__CPP__


#include "queue.h"

namespace g3 {

// Default constructor
template <typename T, typename Container>
queue<T, Container>::queue() : ob() {}

// Copy constructor
template <typename T, typename Container>
queue<T, Container>::queue(const queue& rhv) : ob(rhv.ob) {}

// Move constructor
template <typename T, typename Container>
queue<T, Container>::queue(queue&& rhv) : ob(std::move(rhv.ob)) {}

// Initializer list constructor
template <typename T, typename Container>
queue<T, Container>::queue(std::initializer_list<value_type> init) : ob(init) {}

// Range constructor
template <typename T, typename Container>
template <typename InputIt>
queue<T, Container>::queue(InputIt first, InputIt last) : ob(first, last) {}

// Destructor
template <typename T, typename Container>
queue<T, Container>::~queue() {}

// Copy assignment operator
template <typename T, typename Container>
const queue<T, Container>& queue<T, Container>::operator=(const queue<T, Container>& rhv) {
    ob = rhv.ob;
    return *this;
}

// Move assignment operator
template <typename T, typename Container>
const queue<T, Container>& queue<T, Container>::operator=(queue<T, Container>&& rhv) {
    ob = std::move(rhv.ob);
    return *this;
}

// Access front element
template <typename T, typename Container>
typename queue<T, Container>::reference queue<T, Container>::front() {
    return ob.front();
}

template <typename T, typename Container>
typename queue<T, Container>::const_reference queue<T, Container>::front() const {
    return ob.front();
}

// Access back element
template <typename T, typename Container>
typename queue<T, Container>::reference queue<T, Container>::back() {
    return ob.back();
}

template <typename T, typename Container>
typename queue<T, Container>::const_reference queue<T, Container>::back() const {
    return ob.back();
}

// Check if the container is empty
template <typename T, typename Container>
bool queue<T, Container>::empty() const {
    return ob.empty();
}

// Return the size of the container
template <typename T, typename Container>
typename queue<T, Container>::size_type queue<T, Container>::size() const {
    return ob.size();
}

// Insert element
template <typename T, typename Container>
void queue<T, Container>::push(const_reference val) {
    ob.push_back(val);
}

// Remove element
template <typename T, typename Container>
void queue<T, Container>::pop() {
    ob.pop_front();
}

// Comparison operators
template <typename T, typename Container>
bool queue<T, Container>::operator==(const queue<T, Container>& other) {
    return ob == other.ob;
}

template <typename T, typename Container>
bool queue<T, Container>::operator!=(const queue<T, Container>& other) {
    return ob != other.ob;
}

template <typename T, typename Container>
bool queue<T, Container>::operator<(const queue<T, Container>& other) {
    return ob < other.ob;
}

template <typename T, typename Container>
bool queue<T, Container>::operator<=(const queue<T, Container>& other) {
    return ob <= other.ob;
}

template <typename T, typename Container>
bool queue<T, Container>::operator>(const queue<T, Container>& other) {
    return ob > other.ob;
}

template <typename T, typename Container>
bool queue<T, Container>::operator>=(const queue<T, Container>& other) {
    return ob >= other.ob;
}

}

template class g3::queue<int>;

#endif