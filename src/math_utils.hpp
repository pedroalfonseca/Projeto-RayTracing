#ifndef MATH_UTILS_HPP
#define MATH_UTILS_HPP

#include <cstdlib>
#include <cmath>

constexpr double infinity = __DBL_MAX__;
constexpr double pi = 3.1415926535897932385;

inline double to_radians(const double degrees) { return (degrees * pi) / 180; }

inline double random_double() { return rand() / (RAND_MAX + 1.0); }

inline double random_double(const double min, const double max) {
    return min + ((max - min) * random_double());
}

inline double inverse_sqrt(const double number) {
    long long i;
    double half, result;

    half = number * 0.5;
    result = number;
    i  = *(long long *)&result;
    i  = 0x5fe6eb50c7b537a9 - (i >> 1);
    result  = *(double *)&i;
    result *= 1.5 - (half * result * result);

    return result;
}

inline double truncate(const double val, const double min, const double max) {
    if (val < min) return min;

    if (val > max) return max;

    return val;
}

#endif