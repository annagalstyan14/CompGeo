#include "point.h"
#include <iostream>

int main() {
    Point<2, float> p1({3.0f, 4.0f});
    Point<2, float> p2({1.0f, 2.0f});

    std::cout << "Point 1: " << p1 << std::endl;
    std::cout << "Point 2: " << p2 << std::endl;
    std::cout << "Add: " << (p1 + p2) << std::endl;
    std::cout << "Subtract: " << (p1 - p2) << std::endl;
    std::cout << "Dot product: " << p1.dot(p2) << std::endl;
    std::cout << "Cross product: " << p1.cross(p2) << std::endl;
    std::cout << "Scale p1 by 2: " << (p1 * 2.0f) << std::endl;
    std::cout << "Delta x of p1: " << p1.dx() << std::endl;
    std::cout << "Delta y of p1: " << p1.dy() << std::endl;

    float delta_x_p = 2.0f, delta_y_p = -1.0f;
    p1.move(delta_x_p, delta_y_p);
    std::cout << "After moving p1 (delta_x=" << delta_x_p << ", delta_y=" << delta_y_p << "): " << p1 << std::endl;

    p1.set_dx(5.0f);
    p1.set_dy(6.0f);
    std::cout << "After setting dx=5, dy=6 for p1: " << p1 << std::endl;

    Point<3, float> p3({1.0f, 2.0f, 3.0f});
    std::cout << "3D Point: " << p3 << std::endl;

    return 0;
}
