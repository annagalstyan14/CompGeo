#include "Point.h"
#include "../Vector/Vector_new.h"

template <size_t D, typename Coord_t>
Point<D, Coord_t>::Point(std::initializer_list<Coord_t> lst) {
    if (lst.size() != D)
        throw std::invalid_argument("Initializer list size must match dimension");
    std::size_t i = 0;
    for (auto v : lst) coords[i++] = v;
}

template <size_t D, typename Coord_t>
Coord_t& Point<D, Coord_t>::operator[](std::size_t i) {
    if (i >= D) throw std::out_of_range("Point index out of range");
    return coords[i];
}

template <size_t D, typename Coord_t>
const Coord_t& Point<D, Coord_t>::operator[](std::size_t i) const {
    if (i >= D) throw std::out_of_range("Point index out of range");
    return coords[i];
}

template <size_t D, typename Coord_t>
Point<D, Coord_t> Point<D, Coord_t>::operator+(const Vector<D, Coord_t>& v) const {
    Point res;
    for (std::size_t i = 0; i < D; ++i) res[i] = coords[i] + v[i];
    return res;
}

template <size_t D, typename Coord_t>
Point<D, Coord_t> Point<D, Coord_t>::operator-(const Vector<D, Coord_t>& v) const {
    Point res;
    for (std::size_t i = 0; i < D; ++i) res[i] = coords[i] - v[i];
    return res;
}

template <size_t D, typename Coord_t>
Vector<D, Coord_t> operator-(const Point<D, Coord_t>& a, const Point<D, Coord_t>& b) {
    Vector<D, Coord_t> res;
    for (std::size_t i = 0; i < D; ++i) res[i] = a[i] - b[i];
    return res;
}

template <size_t D, typename Coord_t>
bool Point<D, Coord_t>::operator==(const Point& other) const {
    for (std::size_t i = 0; i < D; ++i)
        if (coords[i] != other.coords[i]) return false;
    return true;
}

template <size_t D, typename Coord_t>
bool Point<D, Coord_t>::operator!=(const Point& other) const {
    return !(*this == other);
}
