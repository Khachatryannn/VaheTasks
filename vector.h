#ifndef VECTOR_H
#define VECTOR_H

#include <memory>
#include <initializer_list>
#include <stdexcept>

namespace g3 {

template<typename T, typename Allocator = std::allocator<T>>
class vector {
public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

    vector() noexcept(noexcept(Allocator())) : arr_(nullptr), size_(0), capacity_(0), allocator_(Allocator()) {}
    explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator());
    vector(std::initializer_list<value_type> init, const Allocator& alloc = Allocator());
    vector(const vector& other);
    vector(vector&& other) noexcept;
    ~vector();

    vector& operator=(const vector& other);
    vector& operator=(vector&& other) noexcept;
    vector& operator=(std::initializer_list<value_type> init);

    reference at(size_type pos);
    const_reference at(size_type pos) const;
    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    pointer data() noexcept;
    const_pointer data() const noexcept;

    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type capacity() const noexcept;
    void reserve(size_type new_cap);
    void shrink_to_fit();

    void clear() noexcept;
    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();
    void resize(size_type count, const value_type& value = value_type());
    void swap(vector& other) noexcept;

private:
    pointer arr_;
    size_type size_;
    size_type capacity_;
    allocator_type allocator_;

    void reallocate(size_type new_cap);
};

template<typename T, typename Allocator>
vector<T, Allocator>::vector(size_type count, const T& value, const Allocator& alloc)
    : size_(count), capacity_(count), allocator_(alloc) {
    arr_ = allocator_.allocate(capacity_);
    std::uninitialized_fill_n(arr_, size_, value);
}

template<typename T, typename Allocator>
vector<T, Allocator>::vector(std::initializer_list<value_type> init, const Allocator& alloc)
    : size_(init.size()), capacity_(init.size()), allocator_(alloc) {
    arr_ = allocator_.allocate(capacity_);
    std::uninitialized_copy(init.begin(), init.end(), arr_);
}

template<typename T, typename Allocator>
vector<T, Allocator>::vector(const vector& other)
    : size_(other.size_), capacity_(other.capacity_), allocator_(std::allocator_traits<Allocator>::select_on_container_copy_construction(other.allocator_)) {
    arr_ = allocator_.allocate(capacity_);
    std::uninitialized_copy(other.arr_, other.arr_ + size_, arr_);
}

template<typename T, typename Allocator>
vector<T, Allocator>::vector(vector&& other) noexcept
    : arr_(other.arr_), size_(other.size_), capacity_(other.capacity_), allocator_(std::move(other.allocator_)) {
    other.arr_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template<typename T, typename Allocator>
vector<T, Allocator>::~vector() {
    clear();
    allocator_.deallocate(arr_, capacity_);
}

template<typename T, typename Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& other) {
    if (this != &other) {
        clear();
        allocator_.deallocate(arr_, capacity_);

        size_ = other.size_;
        capacity_ = other.capacity_;
        allocator_ = std::allocator_traits<Allocator>::select_on_container_copy_construction(other.allocator_);
        arr_ = allocator_.allocate(capacity_);
        std::uninitialized_copy(other.arr_, other.arr_ + size_, arr_);
    }
    return *this;
}

template<typename T, typename Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(vector&& other) noexcept {
    if (this != &other) {
        clear();
        allocator_.deallocate(arr_, capacity_);

        arr_ = other.arr_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        allocator_ = std::move(other.allocator_);

        other.arr_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template<typename T, typename Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(std::initializer_list<value_type> init) {
    clear();
    if (init.size() > capacity_) {
        allocator_.deallocate(arr_, capacity_);
        capacity_ = init.size();
        arr_ = allocator_.allocate(capacity_);
    }
    size_ = init.size();
    std::uninitialized_copy(init.begin(), init.end(), arr_);
    return *this;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type pos) {
    if (pos >= size_) {
        throw std::out_of_range("vector::at: pos >= size()");
    }
    return arr_[pos];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::at(size_type pos) const {
    if (pos >= size_) {
        throw std::out_of_range("vector::at: pos >= size()");
    }
    return arr_[pos];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::operator[](size_type pos) {
    return arr_[pos];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::operator[](size_type pos) const {
    return arr_[pos];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::front() {
    return arr_[0];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::front() const {
    return arr_[0];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::back() {
    return arr_[size_ - 1];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::back() const {
    return arr_[size_ - 1];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::pointer vector<T, Allocator>::data() noexcept {
    return arr_;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_pointer vector<T, Allocator>::data() const noexcept {
    return arr_;
}

template<typename T, typename Allocator>
bool vector<T, Allocator>::empty() const noexcept {
    return size_ == 0;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::size() const noexcept {
    return size_;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::capacity() const noexcept {
    return capacity_;
}

template<typename T, typename Allocator>
void vector<T, Allocator>::reserve(size_type new_cap) {
    if (new_cap > capacity_) {
        reallocate(new_cap);
    }
}

template<typename T, typename Allocator>
void vector<T, Allocator>::shrink_to_fit() {
    if (size_ < capacity_) {
        reallocate(size_);
    }
}

template<typename T, typename Allocator>
void vector<T, Allocator>::clear() noexcept {
    for (size_type i = 0; i < size_; ++i) {
        std::allocator_traits<Allocator>::destroy(allocator_, arr_ + i);
    }
    size_ = 0;
}

template<typename T, typename Allocator>
void vector<T, Allocator>::push_back(const T& value) {
    if (size_ == capacity_) {
        reserve(capacity_ > 0 ? capacity_ * 2 : 1);
    }
    std::allocator_traits<Allocator>::construct(allocator_, arr_ + size_, value);
    ++size_;
}

template<typename T, typename Allocator>
void vector<T, Allocator>::push_back(T&& value) {
    if (size_ == capacity_) {
        reserve(capacity_ > 0 ? capacity_ * 2 : 1);
    }
    std::allocator_traits<Allocator>::construct(allocator_, arr_ + size_, std::move(value));
    ++size_;
}

template<typename T, typename Allocator>
void vector<T, Allocator>::pop_back() {
    if (size_ > 0) {
        std::allocator_traits<Allocator>::destroy(allocator_, arr_ + size_ - 1);
        --size_;
    }
}

template<typename T, typename Allocator>
void vector<T, Allocator>::resize(size_type count, const value_type& value) {
    if (count > size_) {
        reserve(count);
        for (size_type i = size_; i < count; ++i) {
            std::allocator_traits<Allocator>::construct(allocator_, arr_ + i, value);
        }
    } else {
        for (size_type i = count; i < size_; ++i) {
            std::allocator_traits<Allocator>::destroy(allocator_, arr_ + i);
        }
    }
    size_ = count;
}

template<typename T, typename Allocator>
void vector<T, Allocator>::swap(vector& other) noexcept {
    std::swap(arr_, other.arr_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(allocator_, other.allocator_);
}

template<typename T, typename Allocator>
void vector<T, Allocator>::reallocate(size_type new_cap) {
    pointer new_arr = allocator_.allocate(new_cap);
    std::uninitialized_move(arr_, arr_ + size_, new_arr);
    for (size_type i = 0; i < size_; ++i) {
        std::allocator_traits<Allocator>::destroy(allocator_, arr_ + i);
    }
    allocator_.deallocate(arr_, capacity_);
    arr_ = new_arr;
    capacity_ = new_cap;
}

} // namespace g3

#endif // VECTOR_H

