/*
 * Creating a haskell style 'toList' function that converts a map into a list
 * of tuples
 */
#include <map>
#include <tuple>
#include <vector>
#include <string>
#include <iostream>

template<typename K, typename V>
std::vector<std::tuple<K, V>> to_vec(std::map<K, V> m)
{
    std::vector<std::tuple<K, V>> vec;
    for (auto it = m.cbegin(); it != m.cend(); ++it) {
        vec.emplace_back(std::make_tuple(it->first, it->second));
    }
    return vec;
}

template<typename K, typename V>
auto& operator<<(std::ostream& os, std::tuple<K, V> t)
{
    std::cout << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ")";
    return os;
}

template<typename T>
void print_vec(const std::vector<T>& vec)
{
    for (const auto& mem : vec)
        std::cout << mem << std::endl;
}

int main()
{
    std::map<int, int> m1 = {
        {1, 10},
        {2, 20},
        {3, 30}
    };

    std::map<char, std::string> m2 = {
        {'a', "Ayy Tarar"},
        {'b', "Lmao Wilson"},
        {'c', "CORAL!"}
    };

    std::map<float, std::tuple<int, int>> m3 = {
        {1.1f, std::make_tuple(1, 1)},
        {2.2f, std::make_tuple(2, 2)},
        {3.3f, std::make_tuple(3, 3)}
    };

    print_vec(to_vec(m1));
    print_vec(to_vec(m2));
    print_vec(to_vec(m3));
}
