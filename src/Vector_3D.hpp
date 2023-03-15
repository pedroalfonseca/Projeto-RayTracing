#ifndef VECTOR_3D_HPP
#define VECTOR_3D_HPP

#include "math_utils.hpp"

struct Vector_3D {
    double x = 0, y = 0, z = 0;

    Vector_3D operator-() const { return {-x, -y, -z}; }

    Vector_3D &operator+=(const Vector_3D &other) {
        x += other.x;
        y += other.y;
        z += other.z;

        return *this;
    }

    Vector_3D &operator-=(const Vector_3D &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;

        return *this;
    }

    Vector_3D &operator*=(const Vector_3D &other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;

        return *this;
    }

    Vector_3D &operator*=(const double scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;

        return *this;
    }

    Vector_3D &operator/=(const double scalar) {
        const double quotient = 1 / scalar;

        return *this *= quotient;
    }

    bool is_near_null() const {
        constexpr double s = 1e-8;

        return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s);
    }

    double norm_squared() const { return (x * x) + (y * y) + (z * z); }
};

inline Vector_3D operator+(const Vector_3D &lhs, const Vector_3D &rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

inline Vector_3D operator-(const Vector_3D &lhs, const Vector_3D &rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

inline Vector_3D operator*(const Vector_3D &lhs, const Vector_3D &rhs) {
    return {lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
}

inline Vector_3D operator*(const Vector_3D &lhs, const double rhs) {
    return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

inline Vector_3D operator*(const double lhs, const Vector_3D &rhs) {
    return {lhs * rhs.x, lhs * rhs.y, lhs * rhs.z};
}

inline Vector_3D operator/(const Vector_3D &lhs, const double rhs) {
    const double quotient = 1 / rhs;

    return {lhs.x * quotient, lhs.y * quotient, lhs.z * quotient};
}

inline Vector_3D cross_product(const Vector_3D &lhs, const Vector_3D &rhs) {
    return {(lhs.y * rhs.z) - (lhs.z * rhs.y),
            (lhs.y * rhs.x) - (lhs.x * rhs.z),
            (lhs.x * rhs.y) - (lhs.y * rhs.x)};
}

inline double dot_product(const Vector_3D &lhs, const Vector_3D &rhs) {
    return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

inline Vector_3D unit_vector(const Vector_3D &vec) {
    return vec * inverse_sqrt(vec.norm_squared());
}

inline Vector_3D random_vector() {
    return {random_double(), random_double(), random_double()};
}

inline Vector_3D bounded_random_vector(const double min, const double max) {
    return {bounded_random_double(min, max), bounded_random_double(min, max),
            bounded_random_double(min, max)};
}

inline Vector_3D random_vector_in_unit_sphere() {
    while (true) {
        Vector_3D p = bounded_random_vector(-1, 1);
        if (p.norm_squared() < 1) return p;
    }
}

inline Vector_3D random_vector_in_hemisphere(const Vector_3D &normal) {
    Vector_3D in_unit_sphere = random_vector_in_unit_sphere();
    if (dot_product(in_unit_sphere, normal) > 0.0) return in_unit_sphere;
    else return -in_unit_sphere;
}

inline Vector_3D random_unit_vector() {
    return unit_vector(random_vector_in_unit_sphere());
}

inline Vector_3D reflected_vector(const Vector_3D &incident, const Vector_3D &normal) {
    return incident - 2 * dot_product(incident, normal) * normal;
}

#endif