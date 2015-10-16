/*
 * Playing around with std::async and std::future by parallelizing a trivial,
 * but long runing task.
 */
#include <future>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <numeric>

constexpr std::initializer_list<int> nums = {1, 2, 3, 4, 5, 6};

auto slow_increment(int i)
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
    return i++;
}

template<typename T>
auto& operator<<(std::ostream& os, std::initializer_list<T> il)
{
    os << "{ ";
    for (auto& x : il) {
        os << x << " ";
    }
    os << "}";
    return os;
}

auto sum_result_of_function(std::function<int(int)> func, std::initializer_list<int> il)
{
    std::vector<int> ret;

    for (auto& i : il) {
        ret.emplace_back(func(i));
    }

    return std::accumulate(ret.begin(), ret.end(), 0);
}

auto sum_result_of_function_async(std::function<int(int)> func, std::initializer_list<int> il)
{
    std::vector<std::future<int>> ret;

    for (auto& i : il) {
        ret.emplace_back(std::async(func, i));
    }

    return std::accumulate(ret.begin(), ret.end(), 0, [](const int& acc, auto& val) {
            return acc + val.get();
        });
}


using clk = std::chrono::high_resolution_clock;
int main()
{
    std::cout << "Starting synchronous test for values: " << nums << std::endl;
    auto start = clk::now();
    auto result = sum_result_of_function(slow_increment, nums);
    auto finish = clk::now();

    std::cout << "Result: " << result << std::endl;
    std::cout << "Synchronous process took " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << " milliseconds to complete" << std::endl;

    std::cout << "Starting asynchronous test for values: " << nums << std::endl;
    start = clk::now();
    result = sum_result_of_function_async(slow_increment, nums);
    finish = clk::now();

    std::cout << "Result: " << result << std::endl;
    std::cout << "Asynchronous process took " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << " milliseconds to complete" << std::endl;
}

