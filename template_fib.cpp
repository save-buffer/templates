#include <stdint.h>
#include <iostream>

template <uint64_t a>
struct fibonacci
{
    const static uint64_t value = fibonacci<a - 1>::value + fibonacci<a - 2>::value;
};

template <>
struct fibonacci<1>
{
    const static uint64_t value = 1;
};

template <>
struct fibonacci<0>
{
    const static uint64_t value = 0;
};


int main(void)
{
    std::cout << fibonacci<12>::value << std::endl;
    return 0;
}
