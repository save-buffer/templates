#include <iostream>
#include <stdint.h>

struct NIL
{
    typedef NIL head;
    typedef NIL tail;
};

template <typename Head, typename Tail = NIL>
struct List
{
    typedef Head head;
    typedef Tail tail;
};

template <int64_t n>
struct Int
{
    static const int64_t result = n;
};

template <typename Lst>
struct Length
{
    typedef typename Lst::tail tail;
    static const uint64_t result = 1 + Length<tail>::result;
};

template <>
struct Length<NIL>
{
    static const uint64_t result = 0;
};


template <typename Lst, uint64_t N>
struct Nth
{
    typedef typename Lst::tail tail;
    typedef typename Nth<tail, N-1>::result result;
};

template <typename Lst>
struct Nth<Lst, 0>
{
    typedef typename Lst::head result;
};

template <typename X, typename Y>
struct Equal
{
    static const bool result = false;
};

template <typename X>
struct Equal<X, X>
{
    static const bool result = true;
};

template <typename Lst, typename Element>
struct Exists
{
    typedef typename Lst::head head;
    typedef typename Lst::tail tail;
    static const bool result = Equal<head, Element>::result || Exists<tail, Element>::result;
//    static const bool result = Element::result == head::result ? true : Exists<tail, Element>::result;
};

template <typename Element>
struct Exists<NIL, Element>
{
    static const bool result = false;
};

template <typename Lst, typename Element>
struct Find
{
    typedef typename Lst::head head;
    typedef typename Lst::tail tail;
    static const int result = Exists<Lst, Element>::result ? 
	(Equal<head, Element>::result ? 0 : 1 + Find<tail, Element>::result) 
	: -1;
};

template <typename Element>
struct Find<NIL, Element>
{
    static const int result = 0;
};

template <typename Lst, typename Element>
struct Prepend
{
    typedef List<Element, Lst> result;
};

template <typename Lst, typename Element>
struct Append
{
    typedef typename Lst::head head;
    typedef typename Lst::tail tail;
    typedef List<head, typename Append<tail, Element>::result> result;
};
template <typename Element>
struct Append<NIL, Element>
{
    typedef List<Element> result;
};

int main(void)
{
    typedef List< Int<0>, List< Int<1>, List< Int<2>, List< Int<3> > > > > zero_to_three;
    std::cout << Length<zero_to_three>::result << std::endl;
    std::cout << Nth<zero_to_three, 2>::result::result << std::endl;
    std::cout << Exists<zero_to_three, Int<2>>::result << std::endl;
    std::cout << Exists<zero_to_three, Int<42>>::result << std::endl;
    std::cout << Find<zero_to_three, Int<3>>::result << std::endl;
    std::cout << Find<zero_to_three, Int<42>>::result << std::endl;
    typedef typename Prepend<zero_to_three, Int<42>>::result fourty_two;
    std::cout << Nth<fourty_two, 0>::result::result << std::endl;
    typedef typename Append<zero_to_three, Int<100>>::result one_hundred;
    std::cout << Nth<one_hundred, 4>::result::result << std::endl;
    return 0;
}
