#include <iostream>
#include <cassert>
#include <initializer_list>
#include "vector.h"

int main() {
    g3::vector<int> vec;

    assert(vec.empty());
    assert(vec.size() == 0);
    assert(vec.capacity() == 0);

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    assert(vec.size() == 3);
    assert(vec[0] == 1);
    assert(vec[1] == 2);
    assert(vec[2] == 3);

    vec.pop_back();
    assert(vec.size() == 2);
    assert(vec[0] == 1);
    assert(vec[1] == 2);

    vec.clear();
    assert(vec.empty());

    g3::vector<int> vec2 = {1, 2, 3, 4, 5};
    assert(vec2.size() == 5);
    assert(vec2[0] == 1);
    assert(vec2[1] == 2);
    assert(vec2[2] == 3);
    assert(vec2[3] == 4);
    assert(vec2[4] == 5);

    g3::vector<int> vec3 = vec2;
    assert(vec3.size() == 5);
    assert(vec3[0] == 1);
    assert(vec3[1] == 2);
    assert(vec3[2] == 3);
    assert(vec3[3] == 4);
    assert(vec3[4] == 5);

    g3::vector<int> vec4 = std::move(vec3);
    assert(vec4.size() == 5);
    assert(vec4[0] == 1);
    assert(vec4[1] == 2);
    assert(vec4[2] == 3);
    assert(vec4[3] == 4);
    assert(vec4[4] == 5);
    assert(vec3.size() == 0);

    g3::vector<int> vec5;
    vec5 = vec2;
    assert(vec5.size() == 5);
    assert(vec5[0] == 1);
    assert(vec5[1] == 2);
    assert(vec5[2] == 3);
    assert(vec5[3] == 4);
    assert(vec5[4] == 5);

    g3::vector<int> vec6;
    vec6 = std::move(vec5);
    assert(vec6.size() == 5);
    assert(vec6[0] == 1);
    assert(vec6[1] == 2);
    assert(vec6[2] == 3);
    assert(vec6[3] == 4);
    assert(vec6[4] == 5);
    assert(vec5.size() == 0);

    assert(vec6.at(0) == 1);
    assert(vec6.front() == 1);
    assert(vec6.back() == 5);

    vec6.resize(3);
    assert(vec6.size() == 3);
    assert(vec6[0] == 1);
    assert(vec6[1] == 2);
    assert(vec6[2] == 3);

    vec6.resize(5, 10);
    assert(vec6.size() == 5);
    assert(vec6[3] == 10);
    assert(vec6[4] == 10);

    vec.swap(vec6);
    assert(vec.size() == 5);
    assert(vec6.size() == 0);

    std::cout << "Ashxatuma Vahe jannn!\n";
    return 0;

}
