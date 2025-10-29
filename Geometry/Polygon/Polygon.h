#ifndef POLYGON_H
#define POLYGON_H

#include "../Point/Point.h"
#include "../Vector/Vector_new.h"
#include "../Ray/LineSegment.h"
#include <vector>
#include <iostream>

template <size_t D, typename T>
class Polygon {
    static_assert(D == 2, "Polygon is 2D only for this version.");
    std::vector<Point<2, T>> vertices;

public:
    Polygon() = default;
    explicit Polygon(std::initializer_list<Point<2, T>> pts);

    size_t size() const { return vertices.size(); }
    const Point<2, T>& operator[](size_t i) const;
    Point<2, T>& operator[](size_t i);

    T area() const;
    bool is_convex() const;
    bool isInside(const Point<2, T>& p) const;

    Vector<2, T> normal(size_t edge_index) const;

    bool intersect(const LineSegment<2, T>& seg, Point<2, T>* hit = nullptr) const;
    bool intersect(const Polygon<2, T>& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Polygon& poly) {
        os << "Polygon[";
        for (size_t i = 0; i < poly.size(); ++i) {
            os << poly[i];
            if (i + 1 < poly.size()) os << ", ";
        }
        os << "]";
        return os;
    }
};

#include "Polygon.ipp"

#endif // POLYGON_H