#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <cstddef> // For std::size_t

template <typename T, typename Allocator = std::allocator<T>>
class MyVector {

public:
    // Member types
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // Member variables
private:
    pointer m_data;
    size_type m_size;
    size_type m_capacity;
    allocator_type m_allocator;
public:
    // Default constructor
    MyVector();
    // Constructor to initialize MyVector with count default-initialized elements
    explicit MyVector(size_type count);
    // Constructor to initialize MyVector with count elements, each initialized to value
    explicit MyVector(size_type count, const T& value);
    // Copy constructor
    MyVector(const MyVector& other);
    // Move constructor
    MyVector(MyVector&& other) noexcept;
    // Constructor to initialize MyVector with elements from an initializer list
    MyVector(std::initializer_list<T> init);
    // Destructor
    ~MyVector();


    // Assignment operators
    MyVector& operator=(const MyVector& other);
    MyVector& operator=(MyVector&& other) noexcept;

    // Element access
    reference at(size_type pos);
    const_reference at(size_type pos) const;
    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    T* data() noexcept;

    // Iterators
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

    // Capacity
    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;
    void reserve(size_type new_cap);
    size_type capacity() const noexcept;
    void shrink_to_fit();

    // Modifiers
    void clear() noexcept;
    void insert(iterator pos, const T& value);
    iterator insert(iterator pos, size_type count, const T& value);
    template <typename InputIt>
    void insert(iterator pos, InputIt first, InputIt last);
    void erase(iterator pos);
    void erase(iterator first, iterator last);
    void push_back(const T& value);
    void push_back(T&& value);
    template <typename... Args>
    reference emplace_back(Args&&... args);
    void pop_back();
    void resize(size_type count);
    void resize(size_type count, const T& value);
    void swap(MyVector& other);

    // Non-member functions
    friend bool operator==(const MyVector& lhs, const MyVector& rhs) {
        return lhs.data() == rhs.data();
    }
    friend bool operator!=(const MyVector& lhs, const MyVector& rhs) {
        return !(lhs == rhs);
    }
    friend bool operator<(const MyVector& lhs, const MyVector& rhs) {
        return lhs.size() < rhs.size();
    }
    friend bool operator<=(const MyVector& lhs, const MyVector& rhs) {
        return lhs.size() <= rhs.size();
    }
    friend bool operator>(const MyVector& lhs, const MyVector& rhs) {
        return lhs.size() > rhs.size();
    }
    friend bool operator>=(const MyVector& lhs, const MyVector& rhs) {
        return lhs.size() >= rhs.size();
    }
};

#include"rmmyvector.tpp"
#endif // MY_VECTOR_H
