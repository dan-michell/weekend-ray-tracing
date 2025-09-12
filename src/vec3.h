#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

struct vec3 {
  public:
    std::array<double, 3> e{};

    // Constructors. Initialise empty vec3 or with values
    vec3() : e{0, 0, 0} {}
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec3 operator-() const { return vec3{-e[0], -e[1], -e[2]}; }
    // Overload for const and non-const access. If vec3 is const return new value, otherwise return
    // reference which can be used to modify value at index 'i'
    double operator[](int i) const { return e[i]; }
    double &operator[](int i) { return e[i]; }

    // Add vector to current
    vec3 operator+=(const vec3 &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];

        return *this;
    }

    vec3 &operator*=(const double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;

        return *this;
    }

    vec3 &operator/=(double t) { return *this *= 1 / t; }

    // Pythagoras
    double length() const { return std::sqrt(length_squared()); }

    double length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;

// Vector Utility Functions
inline std::ostream &operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// Return new vector from the sum of two others
inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3{u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]};
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3{u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]};
}

// Overloads for multiplying by vector and scalar
inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3{u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]};
}

inline vec3 operator*(double t, const vec3 &v) { return vec3{t * v.e[0], t * v.e[1], t * v.e[2]}; }

// Allow for vec3 multiplication when placed either side of the operator
inline vec3 operator*(const vec3 &v, double t) { return t * v; }

inline vec3 operator/(const vec3 &v, double t) { return (1 / t) * v; }

inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3{u.e[1] * v.e[2] - u.e[2] * v.e[1], u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]};
}

inline vec3 unit_vector(const vec3 &v) { return v / v.length(); }

#endif
