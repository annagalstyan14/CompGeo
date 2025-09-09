#include "vector.h"
#include <iostream>

int main(){
    Vector<2, float> v1({3.0f, 4.0f});
    Vector<2, float> v2({1.0f, 2.0f});

    std::cout << "Vector 1: " << v1 << std::endl;
    std::cout << "Vector 2: " << v2 << std::endl;
    std::cout << "Add: " << (v1 + v2) << std::endl;
    std::cout << "Subtract: " << (v1 - v2) << std::endl;
    std::cout << "Dot product: " << v1.dot(v2) << std::endl;
    std::cout << "Cross product: " << v1.cross(v2) << std::endl;
    std::cout << "Scale v1 by 2: " << (v1 * 2.0f) << std::endl;
    std::cout << "Delta x of v1: " << v1.dx() << std::endl;
    std::cout << "Delta y of v1: " << v1.dy() << std::endl;

    float w = 1.0f, h = 2.0f, a = 0.785398f, d = 5.0f; 
    v1.move(w, h, a, d);
    std::cout << "After moving v1 (w=" << w << ", h=" << h << ", a=" << a << ", d=" << d << "): " << v1 << std::endl;

    Vector<3, float> v3({1.0f, 2.0f, 3.0f});
    std::cout << "3D Vector: " << v3 << std::endl;

    return 0;
}