#ifndef Vector2d_h
#define Vector2d_h

#include <cmath>
#include <array>
#include <type_traits>
#include <iostream>

template <size_t D, typename Coord_t>
class Vector{
    public:
    static_assert(D>0, "Dimension must be greater than zero");
    static_assert(std::is_arithmetic_v<Coord_t>, "Coordinate type must be arithmetic"); 

    std::array<Coord_t, D> components;

    Vector(){
        components.fill(0);
    }

    Vector(const std::array<Coord_t, D>& comps): components(comps){}

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

    Coord_t cross(const Vector& other) const{
        static_assert(D==2, "Cross product is only defined for 2D vectors");
        return components[0] * other.components[1] - components[1] * other.components[0];
    }

    Coord_t dot(const Vector& other) const {
        Coord_t result = 0;
        for (size_t i =0; i<D; ++i){
            result += components[i] * other.components[i];
        }
        return result;
    }

    Vector operator*(Coord_t scalar)const {
        Vector result;
        for (size_t i = 0; i < D; ++i){
            result.components[i] = components[i] * scalar;
        }
        return result;
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
        static_assert(D<=1, "set_dx requires at least 1 dimension");
        components[0] = delta_x;
    }

    void set_dy(Coord_t delta_y){
        static_assert(D<=2, "set_dx requires at least 2 dimensions");
        components[1] = delta_y;
    }

    void move(Coord_t w, Coord_t h, Coord_t a, Coord_t d){
        static_assert(D ==2, "move is only defined for 2D vectors");
        components[0] = std::cos(a)*d -w;
        components[1] = h- std::sin(a)*d;
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
};

#endif