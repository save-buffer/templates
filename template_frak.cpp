#include <stdint.h>
#include <iostream>

template <int64_t n, int64_t d>
struct Frak
{
    static const int64_t num = n;
    static const int64_t den = d;
};

template <int64_t x, int64_t y>
struct GCD
{
    static const int64_t result = GCD<y, x % y>::result;
};

template <int64_t x>
struct GCD<x, 0>
{
    static const int64_t result = x;
};

template <class F>
struct Simplify
{
    static const int64_t gcd = GCD<F::num, F::den>::result;
    typedef Frak<F::num / gcd, F::den / gcd> result;
};

template <int64_t x, class F>
struct ScalarMultiply
{
    typedef typename Simplify<Frak<F::num * x, F::den>>::result result;
};

template <class F1, class F2>
struct Add
{
    typedef Frak<F1::num * F2::den, F1::den * F2::den> f1_commonbase;
    typedef Frak<F2::num * F1::den, F2::den * F1::den> f2_commonbase;
    typedef typename Simplify<Frak<f1_commonbase::num + f2_commonbase::num, f1_commonbase::den>>::result result;
};

template <class F1, class F2>
struct Subtract
{
    typedef typename Simplify<Frak<F1::num * F2::den - F2::num * F1::den, F1::den * F2::den>>::result result;
};

template <class F1, class F2>
struct Multiply
{
    typedef typename Simplify<Frak<F1::num * F2::num, F1::den * F2::den>>::result result;
};

template <class F1, class F2>
struct Divide
{
    typedef typename Simplify<Frak<F1::num * F2::den, F1::den * F2::num>>::result result;
};

int main(void)
{
    typedef Frak<4, 6> two_thirds;
    typedef Frak<1, 2> one_half;
    std::cout << Simplify<two_thirds>::result::num << "/" << Simplify<two_thirds>::result::den << std::endl;
    std::cout << ScalarMultiply<3, two_thirds>::result::num << "/" << ScalarMultiply<3, two_thirds>::result::den << std::endl;
    std::cout << Add<two_thirds, one_half>::result::num << "/" << Add<two_thirds, one_half>::result::den << std::endl;
    std::cout << Subtract<one_half, two_thirds>::result::num << "/" << Subtract<one_half, two_thirds>::result::den << std::endl;
    std::cout << Multiply<two_thirds, one_half>::result::num << "/" << Multiply<two_thirds, one_half>::result::den << std::endl;
    std::cout << Divide<two_thirds, one_half>::result::num << "/" << Divide<two_thirds, one_half>::result::den << std::endl;
    return 0;
}

