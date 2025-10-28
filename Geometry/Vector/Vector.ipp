#include "Vector_new.h"
#include <stdexcept>
#include <cmath>

// --------------------- constructors ---------------------
template <size_t D, typename Coord_t>
Vector<D, Coord_t>::Vector(std::initializer_list<Coord_t> lst)
{
    if (lst.size() != D)
        throw std::invalid_argument("Initializer list size must match dimension");
    std::size_t i = 0;
    for (auto v : lst) components[i++] = v;
}

// --------------------- comparison ---------------------
template <size_t D, typename Coord_t>
bool Vector<D, Coord_t>::operator==(const Vector& other) const
{
    return components == other.components;
}

template <size_t D, typename Coord_t>
bool Vector<D, Coord_t>::operator!=(const Vector& other) const
{
    return !(*this == other);
}

// --------------------- arithmetic ---------------------
template <size_t D, typename Coord_t>
Vector<D, Coord_t> Vector<D, Coord_t>::operator+(const Vector& other) const
{
    Vector res;
    for (std::size_t i = 0; i < D; ++i)
        res.components[i] = components[i] + other.components[i];
    return res;
}

template <size_t D, typename Coord_t>
Vector<D, Coord_t> Vector<D, Coord_t>::operator-(const Vector& other) const
{
    Vector res;
    for (std::size_t i = 0; i < D; ++i)
        res.components[i] = components[i] - other.components[i];
    return res;
}

template <size_t D, typename Coord_t>
Vector<D, Coord_t>& Vector<D, Coord_t>::operator+=(const Vector& other)
{
    for (std::size_t i = 0; i < D; ++i) components[i] += other.components[i];
    return *this;
}

template <size_t D, typename Coord_t>
Vector<D, Coord_t>& Vector<D, Coord_t>::operator-=(const Vector& other)
{
    for (std::size_t i = 0; i < D; ++i) components[i] -= other.components[i];
    return *this;
}

template <size_t D, typename Coord_t>
Vector<D, Coord_t> Vector<D, Coord_t>::operator*(Coord_t s) const
{
    Vector res;
    for (std::size_t i = 0; i < D; ++i) res.components[i] = components[i] * s;
    return res;
}

template <size_t D, typename Coord_t>
Vector<D, Coord_t>& Vector<D, Coord_t>::operator*=(Coord_t s)
{
    for (std::size_t i = 0; i < D; ++i) components[i] *= s;
    return *this;
}

// --------------------- element access ---------------------
template <size_t D, typename Coord_t>
Coord_t& Vector<D, Coord_t>::operator[](std::size_t i)
{
    if (i >= D) throw std::out_of_range("Vector index out of range");
    return components[i];
}

template <size_t D, typename Coord_t>
const Coord_t& Vector<D, Coord_t>::operator[](std::size_t i) const
{
    if (i >= D) throw std::out_of_range("Vector index out of range");
    return components[i];
}

// --------------------- math functions ---------------------
template <size_t D, typename Coord_t>
Coord_t Vector<D, Coord_t>::dot_product(const Vector& a, const Vector& b)
{
    Coord_t sum = 0;
    for (std::size_t i = 0; i < D; ++i) sum += a[i] * b[i];
    return sum;
}

template <size_t D, typename Coord_t>
Coord_t Vector<D, Coord_t>::cross_2d(const Vector& other) const
{
    static_assert(D == 2, "cross_2d is only defined for 2-D vectors");
    return components[0] * other[1] - components[1] * other[0];
}

template <size_t D, typename Coord_t>
Vector<D, Coord_t> Vector<D, Coord_t>::cross_product(const Vector& a, const Vector& b)
{
    static_assert(D == 3, "cross_product is only defined for 3-D vectors");
    Vector<3, Coord_t> res;
    res[0] = a[1] * b[2] - a[2] * b[1];
    res[1] = a[2] * b[0] - a[0] * b[2];
    res[2] = a[0] * b[1] - a[1] * b[0];
    return res;
}

template <size_t D, typename Coord_t>
Coord_t Vector<D, Coord_t>::magnitude() const
{
    Coord_t sum = 0;
    for (std::size_t i = 0; i < D; ++i) sum += components[i] * components[i];
    return std::sqrt(sum);
}

template <size_t D, typename Coord_t>
Vector<D, Coord_t> Vector<D, Coord_t>::normalized() const
{
    Coord_t m = magnitude();
    if (m == 0) throw std::runtime_error("Cannot normalize zero vector");
    return *this * (Coord_t(1) / m);
}

// --------------------- 2-D helpers ---------------------
template <size_t D, typename Coord_t>
Coord_t Vector<D, Coord_t>::dx() const
{
    static_assert(D >= 1, "dx() requires at least 1 dimension");
    return components[0];
}

template <size_t D, typename Coord_t>
Coord_t Vector<D, Coord_t>::dy() const
{
    static_assert(D >= 2, "dy() requires at least 2 dimensions");
    return components[1];
}

template <size_t D, typename Coord_t>
void Vector<D, Coord_t>::set_dx(Coord_t x)
{
    static_assert(D >= 1, "set_dx() requires at least 1 dimension");
    components[0] = x;
}

template <size_t D, typename Coord_t>
void Vector<D, Coord_t>::set_dy(Coord_t y)
{
    static_assert(D >= 2, "set_dy() requires at least 2 dimensions");
    components[1] = y;
}

template <size_t D, typename Coord_t>
Vector<D, Coord_t> Vector<D, Coord_t>::moved(Coord_t w, Coord_t h,
                                            Coord_t a, Coord_t d) const
{
    static_assert(D == 2, "moved() is only defined for 2-D vectors");
    Coord_t off_x = d * std::cos(a);
    Coord_t off_y = d * std::sin(a);
    Vector<2, Coord_t> res = *this;
    res[0] += off_x - w;
    res[1] += off_y - h;
    return res;
}
