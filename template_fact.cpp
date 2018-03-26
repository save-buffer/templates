#include <iostream>
#include <stdint.h>

template <uint64_t a>
struct factorial
{
    static const uint64_t value = a * factorial<a - 1>::value;
};

template <>
struct factorial<0>
{
    static const uint64_t value = 1;
};

int main(void)
{
    std::cout << factorial<10>::value << std::endl;
    return 0;
}
