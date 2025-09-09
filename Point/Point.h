#ifndef POINT_H
#define POINT_H

#include <array>
#include <iostream>
#include <type_traits>

template <size_t D, typename Coord_t>
class Point {
public:
    static_assert(D > 0, "Dimension must be greater than zero");
    static_assert(std::is_arithmetic_v<Coord_t>, "Coordinate type must be arithmetic");

    std::array<Coord_t, D> coordinates;

    Point() {
        coordinates.fill(0);
    }

    Point(const std::array<Coord_t, D>& coords) : coordinates(coords) {}

    Point operator+(const Point& rhs) const {
        Point result;
        for (size_t i = 0; i < D; ++i) {
            result.coordinates[i] = coordinates[i] + rhs.coordinates[i];
        }
        return result;
    }

    Point operator-(const Point& rhs) const {
        Point result;
        for (size_t i = 0; i < D; ++i) {
            result.coordinates[i] = coordinates[i] - rhs.coordinates[i];
        }
        return result;
    }

    Coord_t dot(const Point& rhs) const {
        Coord_t result = 0;
        for (size_t i = 0; i < D; ++i) {
            result += coordinates[i] * rhs.coordinates[i];
        }
        return result;
    }

    std::enable_if_t<D == 2, Coord_t> cross(const Point& rhs) const {
        return coordinates[0] * rhs.coordinates[1] - coordinates[1] * rhs.coordinates[0];
    }

    Point operator*(Coord_t scalar) const {
        Point result;
        for (size_t i = 0; i < D; ++i) {
            result.coordinates[i] = coordinates[i] * scalar;
        }
        return result;
    }

    std::enable_if_t<D >= 1, Coord_t> dx() const {
        return coordinates[0];
    }

    std::enable_if_t<D >= 2, Coord_t> dy() const {
        return coordinates[1];
    }

    std::enable_if_t<D >= 1, void> set_dx(Coord_t delta_x) {
        coordinates[0] = delta_x;
    }

    std::enable_if_t<D >= 2, void> set_dy(Coord_t delta_y) {
        coordinates[1] = delta_y;
    }

    std::enable_if_t<D == 2, void> move(Coord_t delta_x, Coord_t delta_y) {
        coordinates[0] += delta_x;
        coordinates[1] += delta_y;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(";
        for (size_t i = 0; i < D; ++i) {
            os << p.coordinates[i];
            if (i < D - 1) os << ", ";
        }
        os << ")";
        return os;
    }
};

#endif