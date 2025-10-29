#ifndef VECTOR_H
#define VECTOR_H

#include <array>
#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <cmath>
#include <type_traits>

template <size_t D, typename Coord_t>
class Vector
{
    static_assert(std::is_arithmetic<Coord_t>::value,
                  "Coord_t must be an arithmetic type");

    std::array<Coord_t, D> components;

public:
    Vector() { components.fill(0); }
    explicit Vector(std::initializer_list<Coord_t> lst);

    Vector(const Vector&) = default;
    Vector(Vector&&) noexcept = default;
    Vector& operator=(const Vector&) = default;
    Vector& operator=(Vector&&) noexcept = default;

    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);
    Vector operator*(Coord_t scalar) const;
    Vector& operator*=(Coord_t scalar);
    friend Vector operator*(Coord_t scalar, const Vector& v) { return v * scalar; }

    Coord_t& operator[](size_t i);
    const Coord_t& operator[](size_t i) const;

    static Coord_t dot_product(const Vector& a, const Vector& b);
    Coord_t cross_2d(const Vector& other) const;
    static Vector cross_product(const Vector& a, const Vector& b);

    Coord_t magnitude() const;
    Vector normalized() const;

    Coord_t dx() const;
    Coord_t dy() const;
    void set_dx(Coord_t x);
    void set_dy(Coord_t y);
    Vector moved(Coord_t w, Coord_t h, Coord_t a, Coord_t d) const;

    // operator<< defined inline
    friend std::ostream& operator<<(std::ostream& os, const Vector& v)
        {
    os << '(';
    for (std::size_t i = 0; i < D; ++i) {
        Coord_t val = v[i];
        if (val == 0) val = 0;  // Clamp -0 → +0
        os << val;
        if (i + 1 < D) os << ", ";
    }
    os << ')';
    return os;
    }

    Coord_t squared_magnitude() const {
        Coord_t sum = 0;
        for (size_t i = 0; i < D; ++i)
            sum += components[i] * components[i];
        return sum;
    }
};

#include "Vector.ipp"
#endif