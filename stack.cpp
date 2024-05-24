#include "stack.h"
#include <utility>

namespace g3 {

template <typename T, typename Container>
stack<T, Container>::stack() = default;

template <typename T, typename Container>
stack<T, Container>::stack(const stack& rhv) : ob(rhv.ob) {}

template <typename T, typename Container>
stack<T, Container>::stack(stack&& rhv) noexcept : ob(std::move(rhv.ob)) {}

template <typename T, typename Container>
stack<T, Container>::stack(std::initializer_list<value_type> init) : ob(init) {}

template <typename T, typename Container>
template <typename InputIt>
stack<T, Container>::stack(InputIt first, InputIt last) : ob(first, last) {}

template <typename T, typename Container>
stack<T, Container>::~stack() = default;

template <typename T, typename Container>
const stack<T, Container>& stack<T, Container>::operator=(const stack& rhv) {
    if (this != &rhv) {
        ob = rhv.ob;
    }
    return *this;
}

template <typename T, typename Container>
const stack<T, Container>& stack<T, Container>::operator=(stack&& rhv) noexcept {
    if (this != &rhv) {
        ob = std::move(rhv.ob);
    }
    return *this;
}

template <typename T, typename Container>
typename stack<T, Container>::reference stack<T, Container>::top() {
    return ob.back();
}

template <typename T, typename Container>
typename stack<T, Container>::const_reference stack<T, Container>::top() const {
    return ob.back();
}

template <typename T, typename Container>
bool stack<T, Container>::empty() const {
    return ob.empty();
}

template <typename T, typename Container>
typename stack<T, Container>::size_type stack<T, Container>::size() const {
    return ob.size();
}

template <typename T, typename Container>
void stack<T, Container>::push(const_reference val) {
    ob.push_back(val);
}

template <typename T, typename Container>
void stack<T, Container>::pop() {
    ob.pop_back();
}

template <typename T, typename Container>
bool stack<T, Container>::operator==(const stack& other) const {
    return ob == other.ob;
}

template <typename T, typename Container>
bool stack<T, Container>::operator!=(const stack& other) const {
    return ob != other.ob;
}

template <typename T, typename Container>
bool stack<T, Container>::operator<(const stack& other) const {
    return ob < other.ob;
}

template <typename T, typename Container>
bool stack<T, Container>::operator<=(const stack& other) const {
    return ob <= other.ob;
}

template <typename T, typename Container>
bool stack<T, Container>::operator>(const stack& other) const {
    return ob > other.ob;
}

template <typename T, typename Container>
bool stack<T, Container>::operator>=(const stack& other) const {
    return ob >= other.ob;
}

template class stack<int>;

} 


