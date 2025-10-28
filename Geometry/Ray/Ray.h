#ifndef RAY_H
#define RAY_H

#include "../Point/Point.h"
#include "../Vector/Vector_new.h"
#include <optional>
#include <cmath>
#include <algorithm>

template <size_t D, typename T>
class Polygon;      // still only forward-declared

template <size_t D, typename T>
struct LineSegment {
    Point<D, T> a, b;
    LineSegment(const Point<D, T>& a_, const Point<D, T>& b_) : a(a_), b(b_) {}
};

template <size_t D, typename T>
class Ray {
    static_assert(D == 2 || D == 3, "Ray supports only 2D or 3D.");

public:
    Point<D, T> origin;
    Vector<D, T> direction;

    Ray() = default;
    Ray(const Point<D, T>& orig, const Vector<D, T>& dir);

    Point<D, T> at(T t) const;
    Vector<D, T> norm_dir() const;
    T length() const;

    std::optional<T> intersect(const Ray<D, T>& other) const;
    std::optional<T> intersect(const LineSegment<D, T>& seg) const;
    std::optional<T> intersect(const Polygon<D, T>& poly) const;  // stub

    friend std::ostream& operator<<(std::ostream& os, const Ray& r) {
        return os << "Ray[origin: " << r.origin << ", dir: " << r.direction << "]";
    }
};

#include "Ray.ipp"   // now LineSegment is fully defined

#endif // RAY_H