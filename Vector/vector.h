#ifndef Vector2d_h
#define Vector2d_h
#include <array>
#include <type_traits>
#include <cassert>
#include <initializer_list>
#include <cmath>
#include <iostream>
#include <stdexcept>

template <size_t D, typename Coord_t>
class Vector{
    private:
    static_assert(std::is_arithmetic<Coord_t>::value, "Coordinate type must be arithmetic");
    std::array<Coord_t, D> components;
    public:
    Vector(){
        components.fill(0);
    }

    Vector(std::initializer_list<Coord_t> lst) {
        if (lst.size() != D) throw std::invalid_argument("Initializer list size must match dimension");
        size_t i = 0;
        for (const auto& c : lst)
            components[i++] = c;
    }

    const Vector& operator=(const Vector& other){
        Vector temp(other);
        std::swap(components, temp.components);
        return *this;
    }

    const Vector& operator=(Vector&& other) noexcept{
        std::swap(components, other.components);
        return *this;
    }

    Vector (const Vector&) = default;
    Vector (Vector&&) noexcept = default;
    
    bool operator==(const Vector& other) const{

        return components == other.components;
    }

    bool operator!=(const Vector& other) const{
        return !(*this == other);
    }

    Vector operator+(const Vector& other) const{
        Vector result;
        for (size_t i = 0; i<D; ++i){
            result.components[i] = components[i] + other.components[i];
        }
        return result;
    }

    Vector operator-(const Vector& other) const{
        Vector result;
        for (size_t i = 0; i<D; ++i){
            result.components[i] = components[i] - other.components[i];
        }
        return result;
    }

    Vector& operator+=(const Vector& other) {
        for (size_t i = 0; i < D; ++i) {
            (*this)[i] += other[i];
        }
        return *this;
    }
    
    Vector& operator-=(const Vector& other) {
        for (size_t i = 0; i < D; ++i) {
            (*this)[i] -= other[i];
        }
        return *this;
    }

    Coord_t& operator[] (size_t i) {
        if (i >= D) throw std::out_of_range("Index out of bounds");
        return components[i];
    }
    
    const Coord_t& operator[] (size_t i) const {
        if (i >= D) throw std::out_of_range("Index out of bounds");
        return components[i];
    }

    static auto dot_product(const Vector& vec1, const Vector& vec2)
	{
		decltype(vec1.components[0] * vec2.components[0]) res = 0;
		for (size_t i = 0; i < D; i++)
		{
			res += vec1.components[i] * vec2.components[i];
		}

		return res;
	}

    Coord_t cross_2d(const Vector& other) const {
        static_assert(D == 2, "cross_2d is only defined for 2D vectors");
        return (*this)[0] * other[1] - (*this)[1] * other[0];
    }

	static Vector cross_product(const Vector& vec1, const Vector& vec2)
	{
		static_assert(D == 3, "cross product supported only for 3d vectors");

		return { 
			vec1[1] * vec2[2] - vec1[2] * vec2[1], 
			vec1[2] * vec2[0] - vec1[0] * vec2[2],
			vec1[0] * vec2[1] - vec1[1] * vec2[0]
		};
	}

    Vector operator*(Coord_t scalar)const {
        Vector result;
        for (size_t i = 0; i < D; ++i){
            result.components[i] = components[i] * scalar;
        }
        return result;
    }

    Vector& operator*=(Coord_t scalar) {
        for (size_t i = 0; i < D; ++i) {
            (*this)[i] *= scalar;
        }
        return *this;
    }

    friend Vector operator*(Coord_t scalar, const Vector& vec) {
        return vec * scalar;
    }

    Coord_t magnitude() const {
        return std::sqrt(dot_product(*this, *this));
    }
    
    Vector normalized() const {
        Coord_t mag = magnitude();
        if (mag == 0) throw std::runtime_error("Cannot normalize zero vector");
        return *this * (static_cast<Coord_t>(1) / mag);
    }

    Coord_t dx() const {
        static_assert(D>=1, "dx requires at least 1 dimension");
        return components[0];
    }

    Coord_t dy() const {
        static_assert(D>=2, "dy requires at least 2 dimensions");
        return components[1];
    }

    void set_dx(Coord_t delta_x){
        static_assert(D>=1, "set_dx requires at least 1 dimension");
        components[0] = delta_x;
    }

    void set_dy(Coord_t delta_y){
        static_assert(D>=2, "set_dx requires at least 2 dimensions");
        components[1] = delta_y;
    }

    Vector moved(Coord_t w, Coord_t h, Coord_t a, Coord_t d) const {
        static_assert(D == 2, "moved is only defined for 2D vectors");
        Vector result;
        result[0] = std::cos(a) * d - w;
        result[1] = h - std::sin(a) * d;
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector& v){
        os << "(";
        for (size_t i =0 ; i <D; ++i){
            os << v.components[i];
            if(i<D -1) os << ", ";
        }
        os<< ")";
        return os;
    }

    ~Vector() = default;
};

#endif
