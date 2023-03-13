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
        x /= scalar;
        y /= scalar;
        z /= scalar;

        return *this;
    }

    double norm_squared() const { return (x * x) + (y * y) + (z * z); }

    Vector_3D normalized() const;

    static Vector_3D random() {
        return {random_double(), random_double(), random_double()};
    }

    static Vector_3D random(const double min, const double max) {
        return {random_double(min, max), random_double(min, max),
                random_double(min, max)};
    }

    static Vector_3D random_in_unit_sphere() {
        while (true) {
            Vector_3D p = random(-1, 1);
            if (p.norm_squared() < 1) return p;
        }
    }

    static Vector_3D random_in_hemisphere(const Vector_3D &normal);

    static Vector_3D random_normalized() {
        return random_in_unit_sphere().normalized();
    }
};

inline Vector_3D operator+(const Vector_3D &lhs, const Vector_3D &rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

inline Vector_3D operator-(const Vector_3D &lhs, const Vector_3D &rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

inline Vector_3D operator*(const Vector_3D &lhs, const double rhs) {
    return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

inline Vector_3D operator*(const double lhs, const Vector_3D &rhs) {
    return {lhs * rhs.x, lhs * rhs.y, lhs * rhs.z};
}

inline Vector_3D operator/(const Vector_3D &lhs, const double rhs) {
    return {lhs.x / rhs, lhs.y / rhs, lhs.z / rhs};
}

inline Vector_3D cross_product(const Vector_3D &lhs, const Vector_3D &rhs) {
    return {(lhs.y * rhs.z) - (lhs.z * rhs.y),
            (lhs.z * rhs.x) - (lhs.x * rhs.z),
            (lhs.x * rhs.y) - (lhs.y * rhs.x)};
}

inline double dot_product(const Vector_3D &lhs, const Vector_3D &rhs) {
    return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

inline Vector_3D Vector_3D::normalized() const {
    return *this * inverse_sqrt(norm_squared());
}

inline Vector_3D Vector_3D::random_in_hemisphere(const Vector_3D &normal) {
    Vector_3D in_unit_sphere = random_in_unit_sphere();
    if (dot_product(in_unit_sphere, normal) > 0.0) return in_unit_sphere;
    else return -in_unit_sphere;
}

#endif