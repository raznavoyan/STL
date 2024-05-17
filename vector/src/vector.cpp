#ifndef __VECTOR__CPP___
#define __VECTOR__CPP___

#include "vector.h"
#include <initializer_list>

template <typename T, typename Allocator>
g3::vector<T, Allocator>::vector() 
    : size_(0), capacity_(0), arr_(nullptr), allocator_() {}

template <typename T, typename Allocator>
g3::vector<T, Allocator>::vector(const g3::vector<T, Allocator>& rhv) 
    : size_(rhv.size_), capacity_(rhv.capacity_), arr_(allocator_.allocate(capacity_)) {
    std::uninitialized_copy(rhv.arr_, rhv.arr_ + size_, arr_);
}

template <typename T, typename Allocator>
g3::vector<T, Allocator>::vector(g3::vector<T, Allocator>&& rhv)
: size_(rhv.size_), capacity_(rhv.capacity_), arr_(rhv.arr_), allocator_(std::move(rhv.allocator_)) {
    if (this != &rhv) {  // Check for self-move
        rhv.size_ = 0;
        rhv.capacity_ = 0;
        rhv.arr_ = nullptr;
    }
}

// Destructor definition
template <typename T, typename Allocator>
g3::vector<T, Allocator>::~vector() {
    clear();
    allocator_.deallocate(arr_, capacity_);
}

template <typename T, typename Allocator>
// Constructor with initializer list (definition within the g3 namespace)
g3::vector<T, Allocator>::vector(std::initializer_list<value_type> init)
    : size_(init.size()), capacity_(init.size()), arr_(nullptr) {

    if (capacity_ > 0) {
        arr_ = allocator_type().allocate(capacity_);
        size_type i = 0;
        try {
            for (const auto& elem : init) {
                allocator_type().construct(arr_ + i, elem);
                ++i;
            }
        } catch (...) {
            // If construction fails, clean up constructed elements
            for (size_type j = 0; j < i; ++j) {
                allocator_type().destroy(arr_ + j);
            }
            allocator_type().deallocate(arr_, capacity_);
            throw; // Re-throw the exception
        }
    }
}


template <typename T, typename Allocator>
template <typename InputIt>
g3::vector<T, Allocator>::vector(InputIt first, InputIt last)
    : size_(0), capacity_(0), arr_(nullptr) {
    size_type num_elements = std::distance(first, last);
    if (num_elements > 0) {
        size_ = num_elements;
        capacity_ = num_elements;
        arr_ = allocator_type().allocate(capacity_);
        size_type i = 0;
        try {
            for (auto it = first; it != last; ++it, ++i) {
                allocator_type().construct(arr_ + i, *it);
            }
        } catch (...) {
            while (i > 0) {
                allocator_type().destroy(arr_ + (--i));
            }
            allocator_type().deallocate(arr_, capacity_);
            throw;
        }
    }
}

template <typename T, typename Allocator>
const g3::vector<T, Allocator>& g3::vector<T, Allocator>::operator=(const vector& rhv) {
    if (this != &rhv) { // Check for self-assignment
        // Clear existing elements
        clear();

        // Reserve capacity to avoid frequent reallocations
        if (rhv.size_ > capacity_) {
            reserve(rhv.size_);
        }

        // Copy elements from rhv
        for (size_type i = 0; i < rhv.size_; ++i) {
            allocator_.construct(arr_ + i, rhv.arr_[i]);
        }

        // Update size
        size_ = rhv.size_;
    }
    return *this;
}

template <typename T, typename Allocator>
const g3::vector<T, Allocator>& g3::vector<T, Allocator>::operator=(vector&& rhv) noexcept {
    if (this != &rhv) { // Check for self-assignment
        // Clear existing elements
        clear();

        // Move ownership of resources
        arr_ = rhv.arr_;
        size_ = rhv.size_;
        capacity_ = rhv.capacity_;

        // Reset rhv
        rhv.arr_ = nullptr;
        rhv.size_ = 0;
        rhv.capacity_ = 0;
    }
    return *this;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::allocator_type g3::vector<T, Allocator>::get_allocator() {
    return allocator_type(); // Return default-constructed allocator instance
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::reference g3::vector<T, Allocator>::at(size_type pos) {
    if (pos >= size_) {
        throw std::out_of_range("g3::vector::at() - index out of range");
    }
    return arr_[pos];
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_reference g3::vector<T, Allocator>::at(size_type pos) const {
    if (pos >= size_) {
        throw std::out_of_range("g3::vector::at() - index out of range");
    }
    return arr_[pos];
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::reference g3::vector<T, Allocator>::operator[](size_type pos) {
    return arr_[pos];
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_reference g3::vector<T, Allocator>::operator[](size_type pos) const {
    return arr_[pos];
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::reference g3::vector<T, Allocator>::front() {
    if (size_ == 0) {
        throw std::out_of_range("g3::vector::front() - vector is empty");
    }
    return arr_[0];
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_reference g3::vector<T, Allocator>::front() const {
    if (size_ == 0) {
        throw std::out_of_range("g3::vector::front() - vector is empty");
    }
    return arr_[0];
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::reference g3::vector<T, Allocator>::back() {
    if (size_ == 0) {
        throw std::out_of_range("g3::vector::back() - vector is empty");
    }
    return arr_[size_ - 1];
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_reference g3::vector<T, Allocator>::back() const {
    if (size_ == 0) {
        throw std::out_of_range("g3::vector::back() - vector is empty");
    }
    return arr_[size_ -1];
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::iterator g3::vector<T, Allocator>::begin() {
    return iterator(arr_);
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_iterator g3::vector<T, Allocator>::begin() const{
    return const_iterator(arr_);
}


template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_iterator g3::vector<T, Allocator>::cbegin() const{
    return const_iterator(arr_);
}
    

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::iterator g3::vector<T, Allocator>::end() {
    return iterator(arr_ + size_);
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_iterator g3::vector<T, Allocator>::end() const{
    return const_iterator(arr_ + size_);
}


template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_iterator g3::vector<T, Allocator>::cend() const{
    return const_iterator(arr_ + size);
}

template <typename T, typename Allocator>
bool  g3::vector<T, Allocator>::empty() const{
    return !size_;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::iterator g3::vector<T, Allocator>::rbegin() {
    if (size_ == 0) {
        return end(); 
    }
    return iterator(arr_ + size_ - 1); 
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_iterator g3::vector<T, Allocator>::rbegin() const {
    if (size_ == 0) {
        return cend(); 
    }
    return const_iterator(arr_ + size_ - 1); 
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_iterator g3::vector<T, Allocator>::crbegin() const {
    if (size_ == 0) {
        return cend(); 
    }
    return const_iterator(arr_ + size_ - 1);
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::iterator g3::vector<T, Allocator>::rend() {
    return iterator(arr_); 
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_iterator g3::vector<T, Allocator>::rend() const {
    return const_iterator(arr_); 
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_iterator g3::vector<T, Allocator>::crend() const {
    return const_iterator(arr_);
}

// template<typename T, typename Allocator>
// bool g3::vector<T, Allocator>::empty() const{
//     return size == 0;
// }

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::size_type g3::vector<T, Allocator>::size() const {
    return size_;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::size_type g3::vector<T, Allocator>::capacity() const {
    return capacity_;
}

template <typename T, typename Allocator>
void g3::vector<T, Allocator>::reserve(typename g3::vector<T, Allocator>::size_type new_cap) {
    if (new_cap > capacity_) {
        pointer new_arr = allocator_.allocate(new_cap);

        for (size_type i = 0; i < size_; ++i) {
            allocator_.construct(new_arr + i, std::move(arr_[i]));
            allocator_.destroy(arr_ + i);
        }

        allocator_.deallocate(arr_, capacity_);

        arr_ = new_arr;
        capacity_ = new_cap;
    }
}

template <typename T, typename Allocator>
void g3::vector<T, Allocator>::clear() noexcept{
        for (size_type i = 0; i < size_; ++i) {
            allocator_.destroy(arr_ + i);
        }
        allocator_.deallocate(arr_, capacity_);
        size_ = 0;
        arr_ = nullptr;
        capacity_ = 0;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::iterator g3::vector<T, Allocator>::insert(typename g3::vector<T, Allocator>::const_iterator pos, typename g3::vector<T, Allocator>::const_reference val) {
    int index = pos - begin();
    insert(pos, 1, val);
    return begin() + index;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::iterator g3::vector<T, Allocator>::insert(typename g3::vector<T, Allocator>::const_iterator pos, typename g3::vector<T, Allocator>::size_type count, typename g3::vector<T, Allocator>::const_reference val) {
    int index = pos - begin();
    if (size() + count > capacity()) {
        reserve(size() + count);
    }
    pointer insertion_point = arr_ + index;
    std::move_backward(insertion_point, end(), end() + count);
    std::fill_n(insertion_point, count, val);
    size_ += count;
    return iterator(insertion_point);
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::iterator g3::vector<T, Allocator>::insert(typename g3::vector<T, Allocator>::const_iterator pos, std::initializer_list<typename g3::vector<T, Allocator>::value_type> init) {
    return insert(pos, init.begin(), init.end());
}

template <typename T, typename Allocator>
template <typename InputIt>
typename g3::vector<T, Allocator>::iterator g3::vector<T, Allocator>::insert(typename g3::vector<T, Allocator>::const_iterator pos, InputIt first, InputIt last) {
    int index = pos - begin();
    size_type count = std::distance(first, last);
    if (size() + count > capacity()) {
        reserve(size() + count);
    }
    pointer insertion_point = begin() + index;
    std::move_backward(insertion_point, end(), end() + count);
    std::copy(first, last, insertion_point);
    size_ += count;
    return iterator(insertion_point);
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::iterator g3::vector<T, Allocator>::erase(typename g3::vector<T, Allocator>::const_iterator pos) {
    difference_type index = pos - begin();
    pointer erase_point = arr_ + index;
    std::move(erase_point + 1, end(), erase_point);
    size_--;
    return iterator(erase_point);
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::iterator g3::vector<T, Allocator>::erase(typename g3::vector<T, Allocator>::const_iterator first, typename g3::vector<T, Allocator>::const_iterator last) {
    difference_type start_index = first - begin();
    difference_type count = last - first;
    pointer erase_start = begin() + start_index;
    pointer erase_end = erase_start + count;
    std::move(erase_end, end(), erase_start);
    size_ -= count;
    return iterator(erase_start);
}

template <typename T, typename Allocator>
void g3::vector<T, Allocator>::push_back(typename g3::vector<T, Allocator>::const_reference val) {
    if (size_ == capacity_) {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    allocator_.construct(arr_ + size_, val);
    size_++;
}

template <typename T, typename Allocator>
void g3::vector<T, Allocator>::pop_back() {
    if (size_ > 0) {
        allocator_.destroy(arr_ + size_ - 1);
        size_--;
    }
}

template <typename T, typename Allocator>
void g3::vector<T, Allocator>::resize(typename g3::vector<T, Allocator>::size_type new_size, typename g3::vector<T, Allocator>::const_reference val) {
    if (new_size < size_) {
        for (size_type i = new_size; i < size_; ++i) {
            allocator_.destroy(arr_ + i);
        }
    } else if (new_size > size_) {
        if (new_size > capacity_) {
            reserve(new_size);
        }
        for (size_type i = size_; i < new_size; ++i) {
            allocator_.construct(arr_ + i, val);
        }
    }
    size_ = new_size;
}


template <typename T, typename Allocator>
bool g3::vector<T, Allocator>::operator==(const g3::vector<T, Allocator>& other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (size_type i = 0; i < size_; ++i) {
        if (!(arr_[i] == other.arr_[i])) {
            return false;
        }
    }
    return true;
}

template <typename T, typename Allocator>
bool g3::vector<T, Allocator>::operator!=(const g3::vector<T, Allocator>& other) const {
    return !(*this == other);
}

template <typename T, typename Allocator>
bool g3::vector<T, Allocator>::operator<(const g3::vector<T, Allocator>& other) const {
    size_type common_size = std::min(size_, other.size_);
    for (size_type i = 0; i < common_size; ++i) {
        if (arr_[i] < other.arr_[i]) {
            return true;
        } else if (arr_[i] > other.arr_[i]) {
            return false;
        }
    }
    return size_ < other.size_;
}

template <typename T, typename Allocator>
bool g3::vector<T, Allocator>::operator<=(const g3::vector<T, Allocator>& other) const {
    return (*this < other) || (*this == other);
}

template <typename T, typename Allocator>
bool g3::vector<T, Allocator>::operator>(const g3::vector<T, Allocator>& other) const {
    return !(*this <= other);
}

template <typename T, typename Allocator>
bool g3::vector<T, Allocator>::operator>=(const g3::vector<T, Allocator>& other) const {
    return !(*this < other);
}

template <typename T, typename Allocator>
int g3::vector<T, Allocator>::compare(const g3::vector<T, Allocator>& other) const {
    size_type min_size = std::min(size_, other.size_);
    for (size_type i = 0; i < min_size; ++i) {
        if (arr_[i] < other.arr_[i]) {
            return -1;
        } else if (arr_[i] > other.arr_[i]) {
            return 1;
        }
    }
    if (size_ < other.size_) {
        return -1;
    } else if (size_ > other.size_) {
        return 1;
    }
    return 0;
}

//ITERATORS

//CONSTITERATOR
template <typename T, typename Allocator>
g3::vector<T, Allocator>::const_iterator::const_iterator(typename g3::vector<T, Allocator>::pointer ptr)
    : ptr(ptr) {}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_iterator
g3::vector<T, Allocator>::const_iterator::operator+(typename g3::vector<T, Allocator>::size_type n) const {
    pointer target_ptr = ptr + n;

    if (target_ptr < ptr || target_ptr >= (ptr + size_)) {
        throw std::out_of_range("Invalid iterator offset");
    }

    return const_iterator(target_ptr);
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_iterator
g3::vector<T, Allocator>::const_iterator::operator-(typename g3::vector<T, Allocator>::size_type n) const {
    pointer target_ptr = ptr - n;

    if (target_ptr < ptr || target_ptr > (ptr + size_)) {
        throw std::out_of_range("Invalid iterator offset");
    }

    return const_iterator(target_ptr);
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_iterator&
g3::vector<T, Allocator>::const_iterator::operator++() {
    if (ptr == nullptr || ptr > (arr_ + size_)) {
        throw std::out_of_range("Iterator is already at the end");
    }
    ++ptr;
    return *this;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_iterator
g3::vector<T, Allocator>::const_iterator::operator++(int) {
    const_iterator old = *this;

    if (ptr == nullptr || ptr > (arr_ + size_)) {
        throw std::out_of_range("Iterator is already at the end");
    }

    ++ptr;

    return old;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_iterator&
g3::vector<T, Allocator>::const_iterator::operator--() {
    if (ptr == nullptr || ptr > (arr_ + size_)) {
        throw std::out_of_range("Iterator is already at the end");
    }
    --ptr;
    return *this;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_iterator
g3::vector<T, Allocator>::const_iterator::operator--(int) {
    const_iterator old = *this;

    if (ptr == nullptr || ptr > (arr_ + size_)) {
        throw std::out_of_range("Iterator is already at the end");
    }

    --ptr;

    return old;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_reference
g3::vector<T, Allocator>::const_iterator::operator*() const {
    if (ptr == nullptr || ptr >= (arr_ + size_)) {
        throw std::out_of_range("Iterator is out of range");
    }
    return *ptr;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_pointer
g3::vector<T, Allocator>::const_iterator::operator->() const {
    if (ptr == nullptr || ptr >= (arr_ + size_)) {
        throw std::out_of_range("Iterator is out of range");
    }
    return ptr;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_reference
g3::vector<T, Allocator>::const_iterator::operator[](size_type pos) const {
    if (ptr == nullptr || ptr + pos >= (arr_ + size_)) {
        throw std::out_of_range("Iterator is out of range");
    }
    return *(ptr + pos);
}

template <typename T, typename Allocator>
bool g3::vector<T, Allocator>::const_iterator::operator==(const const_iterator& other) const {
    return (*ptr) == *(other.ptr);
}

template <typename T, typename Allocator>
bool g3::vector<T, Allocator>::const_reverse_iterator::operator==(const const_reverse_iterator& other) const {
    return ptr == other.ptr;
}

template <typename T, typename Allocator>
bool g3::vector<T, Allocator>::const_reverse_iterator::operator!=(const const_reverse_iterator& other) const {
    return ptr != other.ptr;
}

template <typename T, typename Allocator>
bool g3::vector<T, Allocator>::const_reverse_iterator::operator<(const const_reverse_iterator& other) const {
    return ptr > other.ptr; // Compare pointers in reverse order for reverse iterators
}

template <typename T, typename Allocator>
bool g3::vector<T, Allocator>::const_reverse_iterator::operator<=(const const_reverse_iterator& other) const {
    return ptr >= other.ptr; // Compare pointers in reverse order for reverse iterators
}

template <typename T, typename Allocator>
bool g3::vector<T, Allocator>::const_reverse_iterator::operator>(const const_reverse_iterator& other) const {
    return ptr < other.ptr; // Compare pointers in reverse order for reverse iterators
}

template <typename T, typename Allocator>
bool g3::vector<T, Allocator>::const_reverse_iterator::operator>=(const const_reverse_iterator& other) const {
    return ptr <= other.ptr; // Compare pointers in reverse order for reverse iterators
}

//ITERATOR
template <typename T, typename Allocator>
g3::vector<T, Allocator>::iterator::iterator(typename g3::vector<T, Allocator>::pointer ptr)
 : g3::vector<T, Allocator>::const_iterator(ptr) {}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::iterator 
g3::vector<T, Allocator>::iterator::operator+(typename g3::vector<T, Allocator>::size_type n) const {
    return iterator(this->ptr + n);
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::iterator 
g3::vector<T, Allocator>::iterator::operator-(typename g3::vector<T, Allocator>::size_type n) const {
    return iterator(this->ptr - n);
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::iterator& 
g3::vector<T, Allocator>::iterator::operator++() {
    ++this->ptr;
    return *this;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::iterator 
g3::vector<T, Allocator>::iterator::operator++(int) {
    iterator tmp = *this;
    ++this->ptr;
    return tmp;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::iterator& 
g3::vector<T, Allocator>::iterator::operator--() {
    --this->ptr;
    return *this;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::iterator 
g3::vector<T, Allocator>::iterator::operator--(int) {
    iterator tmp = *this;
    --this->ptr;
    return tmp;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::reference 
g3::vector<T, Allocator>::iterator::operator*() {
    return *this->ptr;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::pointer 
g3::vector<T, Allocator>::iterator::operator->() {
    return this->ptr;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::reference
g3::vector<T, Allocator>::iterator::operator[](typename g3::vector<T, Allocator>::size_type pos) const {
    return this->ptr[pos];
}

//REVERSITERATORS
// Include the necessary header file
// Constructor
template <typename T, typename Allocator>
g3::vector<T, Allocator>::const_reverse_iterator::const_reverse_iterator(typename g3::vector<T, Allocator>::pointer ptr)
: ptr(ptr) {}

// Overloaded operators

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_reverse_iterator 
g3::vector<T, Allocator>::const_reverse_iterator::operator+(typename g3::vector<T, Allocator>::size_type n) const {
    return const_reverse_iterator(ptr - n);
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_reverse_iterator 
g3::vector<T, Allocator>::const_reverse_iterator::operator-(typename g3::vector<T, Allocator>::size_type n) const {
    return const_reverse_iterator(ptr + n);
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_reverse_iterator& 
g3::vector<T, Allocator>::const_reverse_iterator::operator++() {
    --ptr;
    return *this;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_reverse_iterator 
g3::vector<T, Allocator>::const_reverse_iterator::operator++(int) {
    const_reverse_iterator tmp = *this;
    --ptr;
    return tmp;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_reverse_iterator& 
g3::vector<T, Allocator>::const_reverse_iterator::operator--() {
    ++ptr;
    return *this;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::const_reverse_iterator 
g3::vector<T, Allocator>::const_reverse_iterator::operator--(int) {
    const_reverse_iterator tmp = *this;
    ++ptr;
    return tmp;
}

template <typename T, typename Allocator>
const typename g3::vector<T, Allocator>::value_type& 
g3::vector<T, Allocator>::const_reverse_iterator::operator*() const {
    return *ptr;
}

template<typename T, typename Allocator>
const typename g3::vector<T, Allocator>::value_type*
g3::vector<T, Allocator>::const_reverse_iterator::operator->() const {
    return ptr;
}

template <typename T, typename Allocator>
const typename g3::vector<T, Allocator>::value_type&
g3::vector<T, Allocator>::const_reverse_iterator::operator[](typename g3::vector<T, Allocator>::size_type pos) const {
    return ptr[-pos - 1];
}

// template <typename T, typename Allocator>
// bool g3::vector<T, Allocator>::const_reverse_iterator::operator==(const const_reverse_iterator& other) const {
//     return ptr == other.ptr;
// }

// template <typename T, typename Allocator>
// bool g3::vector<T, Allocator>::const_reverse_iterator::operator!=(const const_reverse_iterator& other) const {
//     return ptr != other.ptr;
// }

// template <typename T, typename Allocator>
// bool g3::vector<T, Allocator>::const_reverse_iterator::operator<(const const_reverse_iterator& other) const {
//     return ptr > other.ptr;
// }

// template <typename T, typename Allocator>
// bool g3::vector<T, Allocator>::const_reverse_iterator::operator<=(const const_reverse_iterator& other) const {
//     return ptr >= other.ptr;
// }

// template <typename T, typename Allocator>
// bool g3::vector<T, Allocator>::const_reverse_iterator::operator>(const const_reverse_iterator& other) const {
//     return ptr < other.ptr;
// }

// template <typename T, typename Allocator>
// bool g3::vector<T, Allocator>::const_reverse_iterator::operator>=(const const_reverse_iterator& other) const {
//     return ptr <= other.ptr;
// }

//CONSTREVERSEITERATOR

// Constructor
template <typename T, typename Allocator>
g3::vector<T, Allocator>::reverse_iterator::reverse_iterator(typename g3::vector<T, Allocator>::pointer ptr) : g3::vector<T, Allocator>::const_reverse_iterator(ptr) {}

// Overloaded operators

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::reverse_iterator 
g3::vector<T, Allocator>::reverse_iterator::operator+(typename g3::vector<T, Allocator>::size_type n) const {
    return reverse_iterator(this->ptr - n);
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::reverse_iterator 
g3::vector<T, Allocator>::reverse_iterator::operator-(typename g3::vector<T, Allocator>::size_type n) const {
    return reverse_iterator(this->ptr + n);
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::reverse_iterator& 
g3::vector<T, Allocator>::reverse_iterator::operator++() {
    --this->ptr;
    return *this;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::reverse_iterator 
g3::vector<T, Allocator>::reverse_iterator::operator++(int) {
    reverse_iterator tmp = *this;
    --this->ptr;
    return tmp;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::reverse_iterator& 
g3::vector<T, Allocator>::reverse_iterator::operator--() {
    ++this->ptr;
    return *this;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::reverse_iterator 
g3::vector<T, Allocator>::reverse_iterator::operator--(int) {
    reverse_iterator tmp = *this;
    ++this->ptr;
    return tmp;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::value_type& 
g3::vector<T, Allocator>::reverse_iterator::operator*() {
    return *(this->ptr);
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::value_type* 
g3::vector<T, Allocator>::reverse_iterator::operator->() {
    return this->ptr;
}

template <typename T, typename Allocator>
typename g3::vector<T, Allocator>::value_type& 
g3::vector<T, Allocator>::reverse_iterator::operator[](typename g3::vector<T, Allocator>::size_type pos) const {
    return *(this->ptr - pos - 1);  // Adjusted logic for reverse iterator
}


#endif