#include "vector.h"
#include <iostream>
#include <cmath>

int main() {
    Vector<2, float> v1({3.0f, 4.0f});
    Vector<2, float> v2({1.0f, 2.0f});

    std::cout << "Vector 1: " << v1 << std::endl;
    std::cout << "Vector 2: " << v2 << std::endl;
    std::cout << "Add: " << (v1 + v2) << std::endl;
    std::cout << "Subtract: " << (v1 - v2) << std::endl;
    std::cout << "Dot product: " << Vector<2, float>::dot_product(v1, v2) << std::endl;
    std::cout << "Cross product (2D): " << v1.cross_2d(v2) << std::endl; 
    std::cout << "Scale v1 by 2: " << (v1 * 2.0f) << std::endl;
    std::cout << "Delta x of v1: " << v1.dx() << std::endl;
    std::cout << "Delta y of v1: " << v1.dy() << std::endl;

    float w = 1.0f, h = 2.0f, a = M_PI / 4, d = 5.0f;
    v1 = v1.moved(w, h, a, d);
    std::cout << "After moving v1 (w=" << w << ", h=" << h << ", a=" << a << ", d=" << d << "): " << v1 << std::endl;

    Vector<2, float> v3 = v1;
    v3 += v2;
    std::cout << "v1 += v2: " << v3 << std::endl;
    v3 -= v2;
    std::cout << "v3 -= v2: " << v3 << std::endl;
    v3 *= 2.0f;
    std::cout << "v3 *= 2: " << v3 << std::endl;

    std::cout << "v1 == v2: " << (v1 == v2 ? "true" : "false") << std::endl;
    std::cout << "v1 != v2: " << (v1 != v2 ? "true" : "false") << std::endl;

    std::cout << "Normalized v1: " << v1.normalized() << std::endl;
    std::cout << "Magnitude of v1: " << v1.magnitude() << std::endl;

    v1.set_dx(10.0f);
    v1.set_dy(20.0f);
    std::cout << "After set_dx(10), set_dy(20): " << v1 << std::endl;

    Vector<3, float> v4({1.0f, 2.0f, 3.0f});
    Vector<3, float> v5({4.0f, 5.0f, 6.0f});
    std::cout << "3D Vector v4: " << v4 << std::endl;
    std::cout << "3D Vector v5: " << v5 << std::endl;
    std::cout << "Cross product (3D): " << Vector<3, float>::cross_product(v4, v5) << std::endl;

    try {
        Vector<2, float> v_invalid({1.0f});
        std::cout << "Error: Should not reach here" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught expected error: " << e.what() << std::endl;
    }

    try {
        v1[2];
        std::cout << "Error: Should not reach here" << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Caught expected error: " << e.what() << std::endl;
    }

    try {
        Vector<2, float> zero({0.0f, 0.0f});
        zero.normalized();
        std::cout << "Error: Should not reach here" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Caught expected error: " << e.what() << std::endl;
    }

    return 0;
}