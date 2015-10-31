/*
 * Playing around with fairly trivial recursive templates, perfect-forwarding
 * and printing tuples.
 */
#include <tuple>
#include <iostream>
#include <type_traits>

template<long l>
struct factorial : std::integral_constant<long, l * factorial<l - 1>()> {};

template<>
struct factorial<1> : std::integral_constant<long, 1> {};

template<typename ... T>
auto tuple_factory(T&& ... t)
{
    return std::make_tuple(std::forward<T>(t)...);
}

template<size_t I, typename... T>
struct tuple_printer
{
    static void print(std::ostream& out, std::tuple<T...> t)
    {
        tuple_printer<I - 1, T...>::print(out, t);
        out << ", " << std::get<I - 1>(t);
    }
};

template<typename... T>
struct tuple_printer<1, T...>
{
    static void print(std::ostream& out, std::tuple<T...> t)
    {
        out << std::get<0>(t);
    }
};

template<typename ... T>
auto& operator<<(std::ostream& os, std::tuple<T...> t)
{
    os << "(";
    tuple_printer<sizeof...(T), T...>::print(os, t);
    os << ")";
    return os;
}

int main() {
    auto t = tuple_factory(42, 3.14, "Hello!", factorial<6>());
    std::cout << t << std::endl;
    static_assert(std::is_integral<factorial<1>::value_type>(), "factorial value type is not an integral type");
    return 0;
}
