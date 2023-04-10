#ifndef VECTOR_3D_HPP
#define VECTOR_3D_HPP

#include "math_utils.hpp"
#include "Matrix.hpp"

template<size_t N>
class Vector {
    std::array<double, N> data;

public:
    Vector()
    {
        data.fill(0.0);
    }

    Vector(const std::initializer_list<double> &list)
    {
        assert(list.size() == N);

        for (size_t i = 0; i < N; i++)
            data[i] = (list.begin())[i];
    }

    Vector(const std::array<double, N> &arr)
        : data(arr)
    {
    }

    Vector(const Vector<N> &other) = default;

    Vector<N> &
    operator=(const Vector<N> &other) = default;

    double
    operator[](const size_t i) const
    {
        return data[i];
    }

    Vector<N>
    operator-() const
    {
        std::array<double, N> arr;

        for (size_t i = 0; i < N; i++)
            arr[i] = -data[i];

        return {arr};
    }

    Vector<N> &
    operator+=(const Vector<N> &other)
    {
        for (size_t i = 0; i < N; i++)
            data[i] += other[i];

        return *this;
    }

    Vector<N> &
    operator-=(const Vector<N> &other)
    {
        for (size_t i = 0; i < N; i++)
            data[i] -= other[i];

        return *this;
    }

    Vector<N> &
    operator*=(const Vector<N> &other)
    {
        for (size_t i = 0; i < N; i++)
            data[i] *= other[i];

        return *this;
    }

    Vector<N> &
    operator*=(const double scalar)
    {
        for (size_t i = 0; i < N; i++)
            data[i] *= scalar;

        return *this;
    }

    Vector<N> &
    operator/=(const double scalar)
    {
        const double quotient = 1 / scalar;

        return *this *= quotient;
    }

    bool
    is_near_null() const
    {
        constexpr double s = 1e-8;

        bool flag = true;
        for (size_t i = 0; i < N && flag; i++)
            if (data[i] >= s)
                flag ^= 1;

        return flag;
    }

    double
    norm_squared() const
    {
        double ret = 0;
        for (size_t i = 0; i < N; i++)
            ret += data[i] * data[i];

        return ret;
    }
};

template<size_t N>
inline Vector<N>
operator+(const Vector<N> &lhs,
          const Vector<N> &rhs)
{
    Vector<N> vec{lhs};

    return vec += rhs;
}

template<size_t N>
inline Vector<N>
operator-(const Vector<N> &lhs,
          const Vector<N> &rhs)
{
    Vector<N> vec{lhs};

    return vec -= rhs;
}

template<size_t N>
inline Vector<N>
operator*(const Vector<N> &lhs,
          const Vector<N> &rhs)
{
    Vector<N> vec{lhs};

    return vec *= rhs;
}

template<size_t N>
inline Vector<N>
operator*(const Vector<N> &lhs,
          const double    &rhs)
{
    Vector<N> vec{lhs};

    return vec *= rhs;
}

template<size_t N>
inline Vector<N>
operator*(const double    &lhs,
          const Vector<N> &rhs)
{
    Vector<N> vec{rhs};

    return vec *= lhs;
}

template<size_t M, size_t N>
inline Vector<M>
operator*(const Matrix<M, N> &lhs,
          const Vector<N>    &rhs)
{
    std::array<double, M> arr;
    arr.fill(0.0);

    for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
            arr[i] += lhs[i][j] * rhs[j];

    return {arr};
}

template<size_t N>
inline Vector<N>
operator/(const Vector<N> &lhs,
          const double     rhs)
{
    const double quotient = 1 / rhs;

    return lhs * quotient;
}

template<size_t N>
inline Vector<N>
cross_product(const Vector<N> &lhs,
              const Vector<N> &rhs)
{
    return {(lhs[1] * rhs[2]) - (lhs[2] * rhs[1]),
            (lhs[2] * rhs[0]) - (lhs[0] * rhs[2]),
            (lhs[0] * rhs[1]) - (lhs[1] * rhs[0])};
}

template<size_t N>
inline double
dot_product(const Vector<N> &lhs,
            const Vector<N> &rhs)
{
    return (lhs[0] * rhs[0]) + (lhs[1] * rhs[1]) + (lhs[2] * rhs[2]);
}

template<size_t N>
inline Vector<N>
unit_vector(const Vector<N> &vec)
{
    return vec * inverse_sqrt(vec.norm_squared());
}

template<size_t N>
inline Vector<N>
random_vector()
{
    std::array<double, N> arr;

    for (size_t i = 0; i < N; i++)
        arr[i] = random_double();

    return {arr};
}

template<size_t N>
inline Vector<N>
bounded_random_vector(const double min,
                      const double max)
{
    std::array<double, N> arr;

    for (size_t i = 0; i < N; i++)
        arr[i] = bounded_random_double(min, max);

    return {arr};
}

template<size_t N>
inline Vector<N>
random_vector_in_unit_sphere()
{
    while (true) {
        const Vector<N> vec = bounded_random_vector<N>(-1, 1);

        if (vec.norm_squared() < 1)
            return vec;
    }
}

template<size_t N>
inline Vector<N>
random_vector_in_hemisphere(const Vector<N> &normal)
{
    const Vector<N> in_unit_sphere = random_vector_in_unit_sphere<N>();

    return (dot_product(in_unit_sphere, normal) > 0.0) ? in_unit_sphere : -in_unit_sphere;
}

template<size_t N>
inline Vector<N>
random_unit_vector()
{
    return unit_vector(random_vector_in_unit_sphere<N>());
}

template<size_t N>
inline Vector<N>
reflected_vector(const Vector<N> &incident,
                 const Vector<N> &normal)
{
    return incident - 2 * dot_product(incident, normal) * normal;
}

template<size_t N>
inline Vector<N>
refracted_vector(const Vector<N> &incident,
                 const Vector<N> &normal,
                 const double     etai_over_etat)
{
    const double cos_theta = fmin(dot_product(-incident, normal), 1.0);

    const Vector<N> r_out_perpendicular = etai_over_etat * (incident + cos_theta * normal);
    const Vector<N> r_out_parallel      = -sqrt(fabs(1.0 - r_out_perpendicular.norm_squared())) * normal;

    return r_out_perpendicular + r_out_parallel;
}

#endif