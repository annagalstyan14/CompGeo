#include "Ray.h"
#include <stdexcept>
#include <limits>
#include <optional>

template <size_t D, typename T>
Ray<D, T>::Ray(const Point<D, T>& orig, const Vector<D, T>& dir)
    : origin(orig), direction(dir) {}

template <size_t D, typename T>
Point<D, T> Ray<D, T>::at(T t) const {
    return origin + direction * t;
}

template <size_t D, typename T>
Vector<D, T> Ray<D, T>::norm_dir() const {
    return direction.normalized();
}

template <size_t D, typename T>
T Ray<D, T>::length() const {
    return direction.magnitude();
}

template <size_t D, typename T>
std::optional<T> Ray<D, T>::intersect(const Ray<D, T>& other) const {
    Vector<D, T> p = other.origin - origin;
    Vector<D, T> d1 = direction;
    Vector<D, T> d2 = other.direction;

    // Find two axes with largest direction components
    size_t i = 0, j = 1;
    T best = 0;
    for (size_t a = 0; a < D; ++a) {
        for (size_t b = a + 1; b < D; ++b) {
            T m = std::abs(d1[a]) + std::abs(d1[b]);
            if (m > best) {
                best = m;
                i = a;
                j = b;
            }
        }
    }

    T denom = d1[i] * d2[j] - d1[j] * d2[i];
    if (std::abs(denom) < static_cast<T>(1e-10)) {
        return std::nullopt;  // parallel
    }

    T t = (p[i] * d2[j] - p[j] * d2[i]) / denom;
    T s = (p[i] * d1[j] - p[j] * d1[i]) / denom;

    if (t >= 0 && s >= 0) {
        return t;
    }
    return std::nullopt;
}

template <size_t D, typename T>
std::optional<T> Ray<D, T>::intersect(const LineSegment<D, T>& seg) const {
    Vector<D, T> ab = seg.b - seg.a;
    T ab2 = ab.squared_magnitude();
    if (ab2 == 0) return std::nullopt;

    Vector<D, T> ap = origin - seg.a;
    T proj = Vector<D, T>::dot_product(ap, ab) / ab2;

    // Special case: ray origin lies on the segment
    if (proj >= 0 && proj <= 1) {
        if constexpr (D == 2) {
            T cross = direction[0] * ab[1] - direction[1] * ab[0];
            if (std::abs(cross) < static_cast<T>(1e-6)) {
                return T(0);  // collinear and starts on segment
            }
        } else if constexpr (D == 3) {
            auto cross = Vector<D, T>::cross_product(direction, ab);
            if (cross.squared_magnitude() < static_cast<T>(1e-12)) {
                return T(0);
            }
        }
    }

    // General case: intersect ray with infinite line, then clamp
    Ray<D, T> line(seg.a, ab);
    auto opt = intersect(line);
    if (!opt) return std::nullopt;

    T t = *opt;
    Point<D, T> hit = at(t);
    Vector<D, T> hit_to_a = hit - seg.a;
    T proj_hit = Vector<D, T>::dot_product(hit_to_a, ab) / ab2;

    if (proj_hit >= 0 && proj_hit <= 1) {
        return t;
    }

    return std::nullopt;
}

template class Ray<2, float>;
template class Ray<3, float>;