
#ifndef LINE_SEGMENT_H
#define LINE_SEGMENT_H

#include "../Point/Point.h"
#include "../Vector/Vector_new.h"
#include <optional>

template <size_t D, typename T>
struct LineSegment {
    Point<D, T> a, b;
    LineSegment(const Point<D, T>& a_, const Point<D, T>& b_) : a(a_), b(b_) {}

    std::optional<Point<D, T>> intersect(const LineSegment<D, T>& other) const {
        Vector<D, T> d1 = b - a;
        Vector<D, T> d2 = other.b - other.a;
        Vector<D, T> d = other.a - a;

        T denom = d1[0]*d2[1] - d1[1]*d2[0];
        if (std::abs(denom) < 1e-10) return std::nullopt;

        T t = (d[0]*d2[1] - d[1]*d2[0]) / denom;
        T s = (d[0]*d1[1] - d[1]*d1[0]) / denom;

        if (t >= 0 && t <= 1 && s >= 0 && s <= 1) {
            return a + d1 * t;
        }
        return std::nullopt;
    }
};

#endif // LINE_SEGMENT_H