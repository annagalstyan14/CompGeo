#include "Polygon.h"
#include "../Ray/LineSegment.h"
#include <iostream>

int main() {
    Polygon<2, float> tri({
        Point<2, float>{0, 0},
        Point<2, float>{4, 0},
        Point<2, float>{2, 3}
    });

    Polygon<2, float> quad({
        Point<2, float>{1, 1},
        Point<2, float>{3, 1},
        Point<2, float>{3, 2},
        Point<2, float>{1, 2}
    });

    std::cout << tri << "\n";
    std::cout << "Area: " << tri.area() << "\n";
    std::cout << "Convex: " << (tri.is_convex() ? "YES" : "NO") << "\n";
    std::cout << "Inside (2,1): " << (tri.isInside(Point<2, float>{2, 1}) ? "YES" : "NO") << "\n";

    std::cout << "Normal[0]: " << tri.normal(0) << "\n";

    LineSegment<2, float> seg(
        Point<2, float>{-1, 1},
        Point<2, float>{5, 1}
    );
    Point<2, float> hit;
    if (tri.intersect(seg, &hit))
        std::cout << "Segment hits at: " << hit << "\n";

    std::cout << "Tri ∩ Quad: " << (tri.intersect(quad) ? "YES" : "NO") << "\n";

    return 0;
}