#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cassert>
#include <array>

template<size_t M, size_t N>
class Matrix {
    std::array<std::array<double, N>, M> data;

public:
    Matrix()
    {
        for (auto &row : data)
            row.fill(0);
    }

    Matrix(const std::initializer_list<std::initializer_list<double>> &input_list)
    {
        assert(input_list.size() == M && (input_list.begin())->size() == N);

        for (size_t i = 0; i < M; i++)
            for (size_t j = 0; j < N; j++)
                data[i][j] = ((input_list.begin() + i)->begin())[j];
    }

    Matrix(const std::array<std::array<double, N>, M> &input_array)
    {
        for (size_t i = 0; i < M; i++)
            for (size_t j = 0; j < N; j++)
                data[i][j] = input_array[i][j];
    }

    Matrix(const Matrix<M, N> &input_matrix)
    {
        for (size_t i = 0; i < M; i++)
            for (size_t j = 0; j < N; j++)
                data[i][j] = input_matrix[i][j];
    }

    std::array<double, N>
    operator[](const size_t i) const
    {
        return data[i];
    }

    Matrix<M, N>
    operator-() const
    {
        std::array<std::array<double, N>, M> input_array;

        for (size_t i = 0; i < M; i++)
            for (size_t j = 0; j < N; j++)
                input_array[i][j] = -data[i][j];

        return {input_array};
    }

    Matrix<M, N> &
    operator+=(const Matrix<M, N> &other)
    {
        for (size_t i = 0; i < M; i++)
            for (size_t j = 0; j < N; j++)
                data[i][j] += other[i][j];

        return *this;
    }

    Matrix<M, N> &
    operator-=(const Matrix<M, N> &other)
    {
        for (size_t i = 0; i < M; i++)
            for (size_t j = 0; j < N; j++)
                data[i][j] -= other[i][j];

        return *this;
    }

    Matrix<M, N> &
    operator*=(const double scalar)
    {
        for (size_t i = 0; i < M; i++)
            for (size_t j = 0; j < N; j++)
                data[i][j] *= scalar;

        return *this;
    }
};

template<size_t M, size_t N>
inline Matrix<M, N>
operator+(const Matrix<M, N> &lhs,
          const Matrix<M, N> &rhs)
{
    Matrix<M, N> input_matrix{lhs};

    return {input_matrix += rhs};
}

template<size_t M, size_t N>
inline Matrix<M, N>
operator-(const Matrix<M, N> &lhs,
          const Matrix<M, N> &rhs)
{
    Matrix<M, N> input_matrix{lhs};

    return {input_matrix -= rhs};
}

template<size_t M, size_t N>
inline Matrix<M, N>
operator*(const Matrix<M, N> &lhs,
          const double       &rhs)
{
    Matrix<M, N> input_matrix{lhs};

    return {input_matrix *= rhs};
}

template<size_t M, size_t N>
inline Matrix<M, N>
operator*(const double       &lhs,
          const Matrix<M, N> &rhs)
{
    Matrix<M, N> input_matrix{rhs};

    return {input_matrix *= lhs};
}

template<size_t M, size_t N, size_t O>
inline Matrix<M, O>
operator*(const Matrix<M, N> &lhs,
          const Matrix<N, O> &rhs)
{
    std::array<std::array<double, O>, M> input_array;

    for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < O; j++)
            for (size_t k = 0; k < N; k++)
                input_array[i][j] += lhs[i][k] * rhs[k][j];

    return {input_array};
}



#endif