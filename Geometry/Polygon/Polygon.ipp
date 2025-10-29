#ifndef POLYGON_IPP
#define POLYGON_IPP

#include "Polygon.h"
#include <cmath>
#include <algorithm>

template <size_t D, typename T>
Polygon<D, T>::Polygon(std::initializer_list<Point<2, T>> pts) : vertices(pts) {
    if (vertices.size() < 3)
        throw std::invalid_argument("Polygon must have at least 3 vertices");
}

template <size_t D, typename T>
bool Polygon<D, T>::operator==(const Polygon& other) const {
    return vertices == other.vertices;
}

template <size_t D, typename T>
bool Polygon<D, T>::operator!=(const Polygon& other) const {
    return !(*this == other);
}

template <size_t D, typename T>
const Point<2, T>& Polygon<D, T>::operator[](size_t i) const {
    if (i >= vertices.size()) throw std::out_of_range("Polygon index out of range");
    return vertices[i];
}

template <size_t D, typename T>
Point<2, T>& Polygon<D, T>::operator[](size_t i) {
    if (i >= vertices.size()) throw std::out_of_range("Polygon index out of range");
    return vertices[i];
}

template <size_t D, typename T>
T Polygon<D, T>::area() const {
    if (vertices.size() < 3) return 0;
    T sum = 0;
    for (size_t i = 0; i < vertices.size(); ++i) {
        size_t j = (i + 1) % vertices.size();
        sum += vertices[i][0] * vertices[j][1] - vertices[j][0] * vertices[i][1];
    }
    return std::abs(sum) / 2;
}

template <size_t D, typename T>
bool Polygon<D, T>::is_convex() const {
    if (vertices.size() < 3) return false;
    T prev = 0;
    for (size_t i = 0; i < vertices.size(); ++i) {
        Vector<2, T> a = vertices[(i+1)%vertices.size()] - vertices[i];
        Vector<2, T> b = vertices[(i+2)%vertices.size()] - vertices[(i+1)%vertices.size()];
        T cross = a[0]*b[1] - a[1]*b[0];
        if (cross != 0 && prev != 0 && cross * prev < 0) return false;
        prev = cross;
    }
    return true;
}

template <size_t D, typename T>
bool Polygon<D, T>::isInside(const Point<2, T>& p) const {
    bool inside = false;
    for (size_t i = 0; i < vertices.size(); ++i) {
        size_t j = (i + 1) % vertices.size();
        if ((vertices[i][1] > p[1]) != (vertices[j][1] > p[1]) &&
            (p[0] < vertices[i][0] + (vertices[j][0] - vertices[i][0]) *
             (p[1] - vertices[i][1]) / (vertices[j][1] - vertices[i][1] + 1e-10))) {
            inside = !inside;
        }
    }
    return inside;
}

template <size_t D, typename T>
Vector<2, T> Polygon<D, T>::normal(size_t edge_index) const {
    size_t i = edge_index % vertices.size();
    size_t j = (i + 1) % vertices.size();
    Vector<2, T> edge = vertices[j] - vertices[i];
    Vector<2, T> n{-edge[1], edge[0]};

    Point<2, T> centroid{0, 0};
    for (const auto& v : vertices) {
        centroid[0] += v[0];
        centroid[1] += v[1];
    }
    centroid[0] /= vertices.size();
    centroid[1] /= vertices.size();

    Vector<2, T> to_centroid = centroid - vertices[i];
    T dot = n[0] * to_centroid[0] + n[1] * to_centroid[1];

    if (dot < 0) {
        n[0] = -n[0];
        n[1] = -n[1];
    }

    return n.normalized();
}

template <size_t D, typename T>
bool Polygon<D, T>::intersect(const LineSegment<2, T>& seg, Point<2, T>* hit) const {
    for (size_t i = 0; i < vertices.size(); ++i) {
        size_t j = (i + 1) % vertices.size();
        LineSegment<2, T> edge(vertices[i], vertices[j]);
        auto opt = seg.intersect(edge);
        if (opt) {
            if (hit) *hit = *opt;
            return true;
        }
    }
    return false;
}

template <size_t D, typename T>
bool Polygon<D, T>::intersect(const Polygon<2, T>& other) const {
    for (size_t i = 0; i < vertices.size(); ++i) {
        size_t j = (i + 1) % vertices.size();
        LineSegment<2, T> e1(vertices[i], vertices[j]);
        for (size_t k = 0; k < other.size(); ++k) {
            size_t l = (k + 1) % other.size();
            LineSegment<2, T> e2(other[k], other[l]);
            if (e1.intersect(e2)) return true;
        }
    }
    if (isInside(other[0])) return true;
    if (other.isInside(vertices[0])) return true;
    return false;
}

template class Polygon<2, float>;

#endif // POLYGON_IPP