#include <stdexcept> // For std::out_of_range
#include <algorithm> // For std::copy, std::move, std::swap
#include <initializer_list>
#include <iostream>
#include <memory>
#include "myvector.h"

// Constructors

template<typename T, typename Allocator>
MyVector<T, Allocator>::MyVector()
    :m_data(nullptr),m_size(0),m_capacity(0)
{}

template<typename T, typename Allocator>
MyVector<T, Allocator>::MyVector(size_type count) 
: m_size(count), m_capacity(count), m_data(nullptr) {
    m_data = m_allocator.allocate(m_capacity);
    for (size_type i = 0; i < m_size; ++i) {
        
        m_allocator.construct(m_data + i, T());
    }
}

template<typename T, typename Allocator>
MyVector<T, Allocator>::MyVector(size_type count, const T& value)
    : m_size(count), m_capacity(count), m_data(nullptr) {
    m_data = m_allocator.allocate(m_capacity);
    for (size_type i = 0; i < m_size; ++i) {
        m_allocator.construct(m_data + i, value);
    }
}

template<typename T, typename Allocator>
MyVector<T, Allocator>::MyVector(const MyVector& other)
    : m_size(other.m_size), m_capacity(other.m_capacity), m_data(nullptr) {
    m_data = m_allocator.allocate(m_capacity);
    for (size_type i = 0; i < m_size; ++i) {
        m_allocator.construct(m_data + i, other.m_data[i]);
    }
}

template <typename T, typename Allocator>
MyVector<T, Allocator>::MyVector(MyVector&& other) noexcept
    : m_size(other.m_size), m_capacity(other.m_capacity), m_data(other.m_data) {
    other.m_size = 0;
    other.m_capacity = 0;
    other.m_data = nullptr;
}

template <typename T, typename Allocator>
MyVector<T, Allocator>::MyVector(std::initializer_list<T> init)
    :m_size(init.size()), m_capacity(init.size()), m_data(nullptr) {
    m_data = m_allocator.allocate(m_capacity);
    auto it = init.begin();
    for (size_type i = 0; i < m_size; ++i, ++it) {
        m_allocator.construct(m_data + i, *it);
    }
}

template <typename T, typename Allocator>
MyVector<T, Allocator>::~MyVector() {
    this->clear();
}

// Assignment operators
template <typename T, typename Allocator>
MyVector<T, Allocator>& MyVector<T, Allocator>::operator=(const MyVector& other) {
    // Step 1: Check for self-assignment
    if (this != &other) {
        // Step 2: Deallocate any resources currently held by *this
        for (size_type i = 0; i < m_size; ++i) {
            m_allocator.destroy(m_data + i);
        }
        m_allocator.deallocate(m_data, m_capacity);

        // Step 3: Allocate memory for new elements from other
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_data = m_allocator.allocate(m_capacity);

        // Step 4: Copy-construct elements into the allocated memory from other
        for (size_type i = 0; i < m_size; ++i) {
            m_allocator.construct(m_data + i, other.m_data[i]);
        }
    }
    return *this;
}


template <typename T, typename Allocator>
MyVector<T, Allocator>& MyVector<T, Allocator>::operator=(MyVector&& other) noexcept {
    // Step 1: Check for self-assignment
    if (this != &other) {
        // Step 2: Deallocate any resources currently held by *this
        for (size_type i = 0; i < m_size; ++i) {
            m_allocator.destroy(m_data + i);
        }
        m_allocator.deallocate(m_data, m_capacity);

        // Step 3: Transfer resources from other to *this
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_data = other.m_data;

        // Step 4: Reset other to a valid but unspecified state
        other.m_size = 0;
        other.m_capacity = 0;
        other.m_data = nullptr;
    }
    return *this;
}


// Element access
template<typename T, typename Allocator>
typename MyVector<T, Allocator>::reference MyVector<T, Allocator>::at(size_type pos) {
    if(pos >= m_size){
        throw std::out_of_range("MyVector::at: position out of range");
    }

    return m_data[pos];
}

template <typename T, typename Allocator>
typename MyVector<T, Allocator>::const_reference MyVector<T, Allocator>::at(size_type pos) const {
    // Step 1: Check if the position is within bounds
    if (pos >= m_size) {
        // Step 3: Throw an out-of-range exception
        throw std::out_of_range("MyVector::at: position out of range");
    }
    // Step 2: Return a reference to the element at the specified position
    return m_data[pos];
}


template<typename T, typename Allocator>
typename MyVector<T, Allocator>::reference MyVector<T, Allocator>::operator[](size_type pos) {
    if (pos >= m_size) {
        // Step 3: Throw an out-of-range exception
        throw std::out_of_range("MyVector::operator[]: position out of range");
    }
    return this->m_data[pos];
}

template<typename T, typename Allocator>
typename MyVector<T, Allocator>::const_reference MyVector<T, Allocator>::operator[](size_type pos) const {
        if (pos >= m_size) {
        // Step 3: Throw an out-of-range exception
        throw std::out_of_range("MyVector::operator[]: position out of range");
    }
    return m_data[pos];
}

template<typename T, typename Allocator>
typename MyVector<T, Allocator>::reference MyVector<T, Allocator>::front() {
    if(this->empty()){
        throw std::out_of_range("MyVector::front: vector is empty");
    }
    return m_data[0];
}

template<typename T, typename Allocator>
typename MyVector<T, Allocator>::const_reference MyVector<T, Allocator>::front() const {
    if(this->empty()){
        throw std::out_of_range("MyVector::front: vector is empty");
    }
    return m_data[0];
}

template<typename T, typename Allocator>
typename MyVector<T, Allocator>::reference MyVector<T, Allocator>::back() {
    if(this->empty()){
        throw std::out_of_range("MyVector::back: vector is empty");
    }
    return m_data[m_size - 1];    
}

template<typename T, typename Allocator>
typename MyVector<T, Allocator>::const_reference MyVector<T, Allocator>::back() const {
    if(this->empty()){
        throw std::out_of_range("MyVector::back: vector is empty");
    }
    return m_data[m_size - 1]; 
}

template<typename T, typename Allocator>
T* MyVector<T, Allocator>::data() noexcept {
    if(m_data == nullptr){
        throw std::out_of_range("MyVector::data: vector is not alocated");
    }
    return m_data;
}

// // Iterators
/*

// template<typename T, typename Allocator>
// typename MyVector<T, Allocator>::iterator MyVector<T, Allocator>::begin() noexcept {}

// template<typename T, typename Allocator>
// typename MyVector<T, Allocator>::const_iterator MyVector<T, Allocator>::begin() const noexcept {}

// template<typename T, typename Allocator>
// typename MyVector<T, Allocator>::iterator MyVector<T, Allocator>::end() noexcept {}

// template<typename T, typename Allocator>
// typename MyVector<T, Allocator>::const_iterator MyVector<T, Allocator>::end() const noexcept {}

// template<typename T, typename Allocator>
// typename MyVector<T, Allocator>::reverse_iterator MyVector<T, Allocator>::rbegin() noexcept {}

// template<typename T, typename Allocator>
// typename MyVector<T, Allocator>::const_reverse_iterator MyVector<T, Allocator>::rbegin() const noexcept {}

// template<typename T, typename Allocator>
// typename MyVector<T, Allocator>::reverse_iterator MyVector<T, Allocator>::rend() noexcept {}

// template<typename T, typename Allocator>
// typename MyVector<T, Allocator>::const_reverse_iterator MyVector<T, Allocator>::rend() const noexcept {}

// template<typename T, typename Allocator>
// typename MyVector<T, Allocator>::const_iterator MyVector<T, Allocator>::cbegin() const noexcept {}

// template<typename T, typename Allocator>
// typename MyVector<T, Allocator>::const_iterator MyVector<T, Allocator>::cend() const noexcept {}

// template<typename T, typename Allocator>
// typename MyVector<T, Allocator>::const_reverse_iterator MyVector<T, Allocator>::crbegin() const noexcept {}

// template<typename T, typename Allocator>
// typename MyVector<T, Allocator>::const_reverse_iterator MyVector<T, Allocator>::crend() const noexcept {}
*/

// Capacity
template<typename T, typename Allocator>
bool MyVector<T, Allocator>::empty() const noexcept {

    return 0 == m_size ? true : false;
}

template<typename T, typename Allocator>
typename MyVector<T, Allocator>::size_type MyVector<T, Allocator>::size() const noexcept {
    return m_size;
}

template<typename T, typename Allocator>
typename MyVector<T, Allocator>::size_type MyVector<T, Allocator>::max_size() const noexcept {
    return m_allocator.max_size();
}

template<typename T, typename Allocator>
void MyVector<T, Allocator>::reserve(size_type new_cap) {
    if (new_cap > m_capacity) {
        // Allocate new memory block with the new capacity
        pointer new_data = m_allocator.allocate(new_cap);
        // Copy existing elements to the new memory block
        for (size_type i = 0; i < m_size; ++i) {
            m_allocator.construct(new_data + i, std::move(m_data[i]));
            m_allocator.destroy(m_data + i);
        }
        // Deallocate old memory block
        m_allocator.deallocate(m_data, m_capacity);
        // Update capacity and data pointer
        m_capacity = new_cap;
        m_data = new_data;
    }
}

template<typename T, typename Allocator>
typename MyVector<T, Allocator>::size_type MyVector<T, Allocator>::capacity() const noexcept {
    return m_capacity;
}

template<typename T, typename Allocator>
void MyVector<T, Allocator>::shrink_to_fit() {
    if (m_capacity > m_size) {
        // Allocate new memory block with the size equal to the current size
        pointer new_data = m_allocator.allocate(m_size);
        // Copy existing elements to the new memory block
        for (size_type i = 0; i < m_size; ++i) {
            m_allocator.construct(new_data + i, std::move(m_data[i]));
            m_allocator.destroy(m_data + i);
        }
        // Deallocate old memory block
        m_allocator.deallocate(m_data, m_capacity);
        // Update capacity and data pointer
        m_capacity = m_size;
        m_data = new_data;
    }
}

// Modifiers
template<typename T, typename Allocator>
void MyVector<T, Allocator>::clear() noexcept {
    // Step 1: Destroy all elements stored in the vector
    for (size_type i = 0; i < m_size; ++i) {
        m_allocator.destroy(m_data + i);
    }
    
    // Step 2: Deallocate the memory used to store the elements
    m_allocator.deallocate(m_data, m_capacity);
}

template<typename T, typename Allocator>
void MyVector<T, Allocator>::insert(iterator pos, const T& value) {
    // Calculate the index corresponding to the iterator position
    size_type index = pos - this->begin();

    // Check if index is out of bounds
    if (index > m_size) {
        throw std::out_of_range("No such position!");
    }

    // Check capacity
    if (m_size >= m_capacity) {
        reserve((m_capacity == 0) ? 1 : m_capacity * 2);
    }

    // Shift elements after the insertion point to make room for the new element
    for (size_type i = m_size; i > index; --i) {
        m_data[i] = std::move(m_data[i - 1]);
    }

    // Insert the new element
    m_data[index] = value;

    // Increment size
    ++m_size;
}


// template<typename T, typename Allocator>
// typename MyVector<T, Allocator>::iterator MyVector<T, Allocator>::insert(iterator pos, size_type count, const T& value) {}

// template<typename T, typename Allocator>
// template<typename InputIt>
// void MyVector<T, Allocator>::insert(iterator pos, InputIt first, InputIt last) {}

template<typename T, typename Allocator>
void MyVector<T, Allocator>::erase(iterator pos) {
    // Calculate the index corresponding to the iterator position
    size_type index = pos - this->begin();

    // Check if index is out of bounds
    if (index >= m_size) {
        throw std::out_of_range("No such position!");
    }

    // Shift elements after the erase point
    for (size_type i = index; i < m_size - 1; ++i) {
        m_data[i] = std::move(m_data[i + 1]);
    }

    // Destroy last element
    m_allocator.destroy(m_data + m_size - 1);

    // Decrement size
    --m_size;
}

template<typename T, typename Allocator>
void MyVector<T, Allocator>::erase(iterator first, iterator last) {
    // Calculate the index corresponding to the iterators
    size_type index_first = first - this->begin();
    size_type index_last = last - this->begin();

    // Check if the range is valid
    if (index_first >= m_size || index_last > m_size || index_first >= index_last) {
        throw std::out_of_range("Invalid range!");
    }

    // Calculate the number of elements to erase
    size_type num_to_erase = index_last - index_first;

    // Shift elements after the erase range
    for (size_type i = index_first; i < m_size - num_to_erase; ++i) {
        m_data[i] = std::move(m_data[i + num_to_erase]);
    }

    // Destroy the removed elements
    for (size_type i = m_size - num_to_erase; i < m_size; ++i) {
        m_allocator.destroy(m_data + i);
    }

    // Update size
    m_size -= num_to_erase;
}

template<typename T, typename Allocator>
void MyVector<T, Allocator>::push_back(const T& value) {
    // Check if resizing is necessary
    if (m_size >= m_capacity) {
        // Allocate new memory block with increased capacity
        reserve((m_capacity == 0) ? 1 : m_capacity * 2);
    }

    // Insert the new element at the end of the vector
    m_allocator.construct(m_data + m_size, value);

    // Increment size
    ++m_size;
}

template<typename T, typename Allocator>
void MyVector<T, Allocator>::push_back(T&& value) {
    // Check if resizing is necessary
    if (m_size == m_capacity) {
        // Allocate new memory block with increased capacity
        size_type new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        reserve(new_capacity);
    }

    // Insert the new element at the end of the vector using move semantics
    m_allocator.construct(m_data + m_size, std::move(value));

    // Increment size
    ++m_size;
}

// template<typename T, typename Allocator>
// template<typename... Args>
// typename MyVector<T, Allocator>::reference MyVector<T, Allocator>::emplace_back(Args&&... args) {}

template<typename T, typename Allocator>
void MyVector<T, Allocator>::pop_back() {
    if (this->empty()) {
        throw std::out_of_range("Vector is empty!");
    }
    --m_size;
}

template<typename T, typename Allocator>
void MyVector<T, Allocator>::resize(size_type count) {
    if (count > m_size) {
        // Increase size
        if (count > m_capacity) {
            reserve(count);
        }
        // Insert default-initialized elements at the end
        for (size_type i = m_size; i < count; ++i) {
            m_allocator.construct(m_data + i, T());
        }
    } else if (count < m_size) {
        // Decrease size and destruct excess elements at the end
        for (size_type i = count; i < m_size; ++i) {
            m_allocator.destroy(m_data + i);
        }
    }
    // Set new size
    m_size = count;
}

// template<typename T, typename Allocator>
// void MyVector<T, Allocator>::resize(size_type count, const T& value) {}

// template<typename T, typename Allocator>
// void MyVector<T, Allocator>::swap(MyVector& other) {}

// Explicit Instantiation
template class MyVector<int>;  // Example for explicit instantiation with int type

