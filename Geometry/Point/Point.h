#ifndef POINT_H
#define POINT_H

#include <array>
#include <iostream>
#include <type_traits>
#include <stdexcept>

template <size_t D, typename Coord_t>
class Vector;

template <size_t D, typename Coord_t>
class Point {
    static_assert(D >= 1, "Dimension must be at least 1");
    static_assert(std::is_arithmetic<Coord_t>::value,
                  "Coordinate type must be arithmetic");

    std::array<Coord_t, D> coords;

public:
    Point() { coords.fill(0); }
    explicit Point(std::initializer_list<Coord_t> lst);

    Coord_t& operator[](std::size_t i);
    const Coord_t& operator[](std::size_t i) const;

    Point operator+(const Vector<D, Coord_t>& v) const;
    Point operator-(const Vector<D, Coord_t>& v) const;
    friend Point operator+(const Vector<D, Coord_t>& v, const Point& p) { return p + v; }

    friend Vector<D, Coord_t> operator-(const Point& a, const Point& b) {
        Vector<D, Coord_t> res;
        for (std::size_t i = 0; i < D; ++i)
            res[i] = a[i] - b[i];
        return res;
    }

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;

    Coord_t dx() const { return (D >= 1) ? coords[0] : throw std::out_of_range("dx() not available"); }
    Coord_t dy() const { return (D >= 2) ? coords[1] : throw std::out_of_range("dy() not available"); }
    void set_dx(Coord_t x) { if (D >= 1) coords[0] = x; else throw std::out_of_range("set_dx() not available"); }
    void set_dy(Coord_t y) { if (D >= 2) coords[1] = y; else throw std::out_of_range("set_dy() not available"); }
    void move(Coord_t dx, Coord_t dy) {
        if (D >= 2) { coords[0] += dx; coords[1] += dy; }
        else throw std::out_of_range("move() only for 2D");
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << '(';
        for (std::size_t i = 0; i < D; ++i) {
            os << p[i];
            if (i + 1 < D) os << ", ";
        }
        os << ')';
        return os;
    }
};

#include "Point.ipp"   // MUST BE HERE

#endif // POINT_H