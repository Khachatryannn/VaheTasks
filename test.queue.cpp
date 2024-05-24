#include "queue.h"
#include "queue.cpp"
#include <iostream>

int main() {
    g3::queue<int> q1;
    q1.push(1);
    q1.push(2);
    q1.push(3);

    std::cout << "Front element: " << q1.front() << std::endl;
    q1.pop();
    std::cout << "Front element after pop: " << q1.front() << std::endl;

    g3::queue<int> q2 = {4, 5, 6};
    std::cout << "Front element of q2: " << q2.front() << std::endl;

    std::cout << "q1 is " << (q1 == q2 ? "equal to" : "not equal to") << " q2" << std::endl;

    return 0;
}

