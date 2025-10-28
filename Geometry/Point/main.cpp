#include "../Vector/Vector_new.h"  // ← FIRST
#include "Point.h"
#include <iostream>
#include <cmath>

int main() {
    Point<2, float> p1({3.0f, 4.0f});
    Point<2, float> p2({1.0f, 2.0f});
    Vector<2, float> v({1.0f, 1.0f});

    std::cout << "Point 1: " << p1 << "\n";
    std::cout << "Point 2: " << p2 << "\n";

    std::cout << "p1 + v: " << (p1 + v) << "\n";
    std::cout << "p1 - v: " << (p1 - v) << "\n";

    Vector<2, float> diff = p1 - p2;
    std::cout << "p1 - p2: " << diff << "\n";

    std::cout << "dx: " << p1.dx() << ", dy: " << p1.dy() << "\n";

    p1.move(2.0f, -1.0f);
    std::cout << "After move(2,-1): " << p1 << "\n";

    p1.set_dx(5.0f); p1.set_dy(6.0f);
    std::cout << "After set_dx(5), set_dy(6): " << p1 << "\n";
    return 0;
}