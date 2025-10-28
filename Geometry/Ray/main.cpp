#include "Ray.h"          // pulls in LineSegment, Point, Vector, etc.
#include <iostream>

int main() {
    Point<2, float> o1{0, 0}, o2{3, 1};
    Vector<2, float> d1{1, 1}, d2{-1, 2};

    Ray<2, float> r1(o1, d1);
    Ray<2, float> r2(o2, d2);

    std::cout << r1 << "\n";
    std::cout << r2 << "\n";

    if (auto t = r1.intersect(r2)) {
        std::cout << "Intersect at t = " << *t << "\n";
        std::cout << "Hit point: " << r1.at(*t) << "\n";
    } else {
        std::cout << "No intersection\n";
    }

    // line-segment test
    Point<2, float> start{0, 0};
    Point<2, float> end{5, 5};
    LineSegment<2, float> seg(start, end);
    if (auto t_seg = r1.intersect(seg)) {
        std::cout << "Hits segment at t = " << *t_seg << "\n";
        std::cout << "Hit point: " << r1.at(*t_seg) << "\n";
    } else {
        std::cout << "No segment intersection\n";
    }

    return 0;
}