#include "stack.h"
#include "stack.cpp"
#include <iostream>

int main() {
    
    g3::stack<int> a1;
    a1.push(1);
    a1.push(2);
    a1.push(3);

    std::cout << "Top element: " << a1.top() << std::endl;
    a1.pop();
    std::cout << "Top element after pop: " << a1.top() << std::endl;

    g3::stack<int> a2 = {4, 5, 6};
    std::cout << "Top element of s2: " << a2.top() << std::endl;

    std::cout << "s1 is " << (a1 == a2 ? "equal to" : "not equal to") << " a2" << std::endl;

    return 0;
}

