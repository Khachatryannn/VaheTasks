#include "queue.h"
#include <utility>

namespace g3 {

template <typename T, typename Container>
queue<T, Container>::queue() = default;

template <typename T, typename Container>
queue<T, Container>::queue(const queue& rhv) : ob(rhv.ob) {}

template <typename T, typename Container>
queue<T, Container>::queue(queue&& rhv) noexcept : ob(std::move(rhv.ob)) {}

template <typename T, typename Container>
queue<T, Container>::queue(std::initializer_list<value_type> init) : ob(init) {}

template <typename T, typename Container>
template <typename InputIt>
queue<T, Container>::queue(InputIt first, InputIt last) : ob(first, last) {}

template <typename T, typename Container>
queue<T, Container>::~queue() = default;

template <typename T, typename Container>
const queue<T, Container>& queue<T, Container>::operator=(const queue& rhv) {
    if (this != &rhv) {
        ob = rhv.ob;
    }
    return *this;
}

template <typename T, typename Container>
const queue<T, Container>& queue<T, Container>::operator=(queue&& rhv) noexcept {
    if (this != &rhv) {
        ob = std::move(rhv.ob);
    }
    return *this;
}

template <typename T, typename Container>
typename queue<T, Container>::reference queue<T, Container>::front() {
    return ob.front();
}

template <typename T, typename Container>
typename queue<T, Container>::const_reference queue<T, Container>::front() const {
    return ob.front();
}

template <typename T, typename Container>
typename queue<T, Container>::reference queue<T, Container>::back() {
    return ob.back();
}

template <typename T, typename Container>
typename queue<T, Container>::const_reference queue<T, Container>::back() const {
    return ob.back();
}

template <typename T, typename Container>
bool queue<T, Container>::empty() const {
    return ob.empty();
}

template <typename T, typename Container>
typename queue<T, Container>::size_type queue<T, Container>::size() const {
    return ob.size();
}

template <typename T, typename Container>
void queue<T, Container>::push(const_reference val) {
    ob.push_back(val);
}

template <typename T, typename Container>
void queue<T, Container>::pop() {
    ob.pop_front();
}

template <typename T, typename Container>
bool queue<T, Container>::operator==(const queue& other) const {
    return ob == other.ob;
}

template <typename T, typename Container>
bool queue<T, Container>::operator!=(const queue& other) const {
    return ob != other.ob;
}

template <typename T, typename Container>
bool queue<T, Container>::operator<(const queue& other) const {
    return ob < other.ob;
}

template <typename T, typename Container>
bool queue<T, Container>::operator<=(const queue& other) const {
    return ob <= other.ob;
}

template <typename T, typename Container>
bool queue<T, Container>::operator>(const queue& other) const {
    return ob > other.ob;
}

template <typename T, typename Container>
bool queue<T, Container>::operator>=(const queue& other) const {
    return ob >= other.ob;
}

// Explicit instantiation for default template arguments to avoid linker errors
template class queue<int>;

} // namespace g3

