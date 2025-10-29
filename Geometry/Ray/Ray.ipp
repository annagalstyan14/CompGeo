#include "Ray.h"
#include <stdexcept>
#include <limits>
#include <optional>
#include "LineSegment.h"
#include "../Polygon/Polygon.h"

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
std::optional<T> Ray<D, T>::intersect(const Ray<D, T>& other) const
{
    Vector<D, T> p = other.origin - origin;   // vector from this origin to other origin
    Vector<D, T> d1 = direction;
    Vector<D, T> d2 = other.direction;

    if constexpr (D == 2) {
        T denom = d1[0] * d2[1] - d1[1] * d2[0];
        if (std::abs(denom) < static_cast<T>(1e-10)) return std::nullopt; // parallel / collinear

        T t = (p[0] * d2[1] - p[1] * d2[0]) / denom;
        T s = (p[0] * d1[1] - p[1] * d1[0]) / denom;

        if (t >= 0 && s >= 0) return t;
        return std::nullopt;
    }

    if constexpr (D == 3) {
        auto cross = Vector<D,T>::cross_product(d1, d2);
        T denom = cross.squared_magnitude();
        if (denom < static_cast<T>(1e-10)) return std::nullopt;

        T t = Vector<D,T>::dot_product( Vector<D,T>::cross_product(p, d2), cross ) / denom;
        T s = Vector<D,T>::dot_product( Vector<D,T>::cross_product(p, d1), cross ) / denom;

        if (t >= 0 && s >= 0) return t;
        return std::nullopt;
    }
}

template <size_t D, typename T>
std::optional<T> Ray<D, T>::intersect(const LineSegment<D, T>& seg) const
{
    Vector<D, T> ab = seg.b - seg.a;
    T ab2 = ab.squared_magnitude();
    if (ab2 == 0) return std::nullopt;

    Vector<D, T> ap = origin - seg.a;

    T proj = Vector<D,T>::dot_product(ap, ab) / ab2;

    if (proj >= 0 && proj <= 1) {
        if constexpr (D == 2) {
            T cross = direction[0]*ab[1] - direction[1]*ab[0];
            if (std::abs(cross) < static_cast<T>(1e-6)) return T(0);
        } else if constexpr (D == 3) {
            auto cr = Vector<D,T>::cross_product(direction, ab);
            if (cr.squared_magnitude() < static_cast<T>(1e-12)) return T(0);
        }
    }

    Ray<D,T> infLine(seg.a, ab);
    auto opt = intersect(infLine);
    if (!opt) return std::nullopt;

    T t = *opt;
    Point<D,T> hit = at(t);
    Vector<D,T> hit2a = hit - seg.a;
    T projHit = Vector<D,T>::dot_product(hit2a, ab) / ab2;

    if (projHit >= 0 && projHit <= 1) return t;
    return std::nullopt;
}

template <size_t D, typename T>
std::optional<T> Ray<D, T>::intersect(const Polygon<D, T>& poly) const
{
    static_assert(D == 2, "Ray-Polygon intersection is 2-D only");

    T t_min = std::numeric_limits<T>::max();
    bool hit = false;

    for (size_t i = 0; i < poly.size(); ++i) {
        size_t j = (i + 1) % poly.size();
        LineSegment<D, T> edge(poly[i], poly[j]);
        auto opt = intersect(edge);
        if (opt && *opt >= 0) {
            if (*opt < t_min) t_min = *opt;
            hit = true;
        }
    }
    return hit ? std::optional<T>(t_min) : std::nullopt;
}

template class Ray<2, float>;