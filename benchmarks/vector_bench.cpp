/**
 * vector_bench.cpp
 * benchmark comparing MyVector vs std::vector
 */

#include <iostream>
#include <vector>

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

#include "my_vector.hpp"
#include <concepts>


namespace detect {

template <class T, class E>
concept has_push_back = requires(T t, E e) { t.push_back(e); };

} // namespace detect

// Benchmark

void benchmark_push_back() {
    constexpr size_t N = 1'000'000;

    // Check if MyVector has push_back
    if constexpr (!detect::has_push_back<MyVector<int>, int>) {
        std::cout << "[SKIP] MyVector missing push_back()";
        return;
    }

    ankerl::nanobench::Bench bench;
    bench.title("push_back 1M ints").unit("element").batch(N);

    bench.run("std::vector", [&] {
        std::vector<int> v;
        for (size_t i = 0; i < N; ++i) {
            v.push_back(static_cast<int>(i));
        }
        ankerl::nanobench::doNotOptimizeAway(v);
    });

    bench.run("MyVector", [&] {
        MyVector<int> v;
        for (size_t i = 0; i < N; ++i) {
            v.push_back(static_cast<int>(i));
        }
        ankerl::nanobench::doNotOptimizeAway(v);
    });
}

int main() {
    std::cout << "=== MyVector Benchmark ===\n\n";

    benchmark_push_back();

    std::cout << "\nDone!\n";
    return 0;
}
