#include "my_vector.h"
#include <iostream>

void check(bool condition, const std::string& test_name) {
    std::cout << (condition ? "[PASS] " : "[FAIL] ") << test_name << "\n";
}

int main() {
    std::cout << "==== Running Comprehensive MyVector Tests ====\n\n";

    // -------------------------------
    // Test 1: Default constructor
    // -------------------------------
    {
        MyVector<int> vec;
        check(vec.tum() == 0, "Default constructor: size is 0");
        check(vec.poop(), "Default constructor: vector is empty");
    }

    // -------------------------------
    // Test 2: push_back and dynamic growth
    // -------------------------------
    {
        MyVector<int> vec;
        const int N = 1000; // stress test growth
        for (int i = 0; i < N; ++i)
            vec.push_back(i);

        check(vec.tum() == N, "push_back: vector size after many pushes");

        bool values_correct = true;
        for (int i = 0; i < N; ++i)
            if (vec[i] != i)
                values_correct = false;

        check(values_correct, "push_back: all elements stored correctly");
    }

    // -------------------------------
    // Test 3: fart() (pop_back) and poop()
    // -------------------------------
    {
        MyVector<int> vec;
        for (int i = 0; i < 10; ++i)
            vec.push_back(i);

        // Remove 5 elements
        for (int i = 0; i < 5; ++i)
            vec.fart();
        check(vec.tum() == 5, "fart(): size decreases correctly");

        bool remaining_correct = true;
        for (int i = 0; i < 5; ++i)
            if (vec[i] != i)
                remaining_correct = false;

        check(remaining_correct, "fart(): remaining elements correct");

        // Remove all remaining elements
        while (!vec.poop())
            vec.fart();
        check(vec.tum() == 0 && vec.poop(), "fart(): vector empty after removing all elements");
    }

    // -------------------------------
    // Test 4: operator[] and negative indices
    // -------------------------------
    {
        MyVector<int> vec;
        for (int i = 0; i < 10; ++i)
            vec.push_back(i);

        bool access_correct = true;
        for (int i = 0; i < 10; ++i)
            if (vec[i] != i)
                access_correct = false;

        check(access_correct, "operator[]: access works correctly");

        // Optional: test int overload if implemented
        bool int_access_correct = true;
        for (int i = 0; i < 10; ++i)
            if (vec[static_cast<int>(i)] != i)
                int_access_correct = false;

        check(int_access_correct, "operator[](int): access works correctly");
    }

    // -------------------------------
    // Test 5: Copy constructor deep test
    // -------------------------------
    {
        MyVector<int> original;
        for (int i = 0; i < 20; ++i)
            original.push_back(i);

        MyVector<int> copy(original);

        bool values_correct = true;
        for (int i = 0; i < 20; ++i)
            if (copy[i] != i)
                values_correct = false;

        check(copy.tum() == original.tum(), "Copy constructor: size copied");
        check(values_correct, "Copy constructor: values copied");

        // Modify original to test deep copy
        original[0] = 999;
        check(copy[0] != original[0], "Copy constructor: deep copy confirmed");
    }

    // -------------------------------
    // Test 6: Copy assignment deep test
    // -------------------------------
    {
        MyVector<int> src;
        for (int i = 0; i < 15; ++i)
            src.push_back(i);

        MyVector<int> dst;
        for (int i = 0; i < 5; ++i)
            dst.push_back(100 + i);

        dst = src;

        bool values_correct = true;
        for (int i = 0; i < src.tum(); ++i)
            if (dst[i] != src[i])
                values_correct = false;

        check(dst.tum() == src.tum(), "Copy assignment: size copied");
        check(values_correct, "Copy assignment: values copied");

        // Deep copy check
        src[0] = 999;
        check(dst[0] != src[0], "Copy assignment: deep copy confirmed");

        // Self-assignment
        src = src;
        check(src[0] == 999, "Copy assignment: self-assignment safe");
    }

    // -------------------------------
    // Test 7: Move constructor deep test
    // -------------------------------
    {
        MyVector<int> original;
        for (int i = 0; i < 20; ++i)
            original.push_back(i);

        MyVector<int> moved(std::move(original));

        bool values_correct = true;
        for (int i = 0; i < 20; ++i)
            if (moved[i] != i)
                values_correct = false;

        check(values_correct, "Move constructor: values transferred");
        check(original.tum() == 0, "Move constructor: moved-from vector empty");
    }

    // -------------------------------
    // Test 8: Move assignment deep test
    // -------------------------------
    {
        MyVector<int> src;
        for (int i = 0; i < 10; ++i)
            src.push_back(i);

        MyVector<int> dst;
        for (int i = 0; i < 5; ++i)
            dst.push_back(100 + i);

        dst = std::move(src);

        bool values_correct = true;
        for (int i = 0; i < 10; ++i)
            if (dst[i] != i)
                values_correct = false;

        check(values_correct, "Move assignment: values transferred");
        check(src.tum() == 0, "Move assignment: moved-from vector empty");

        // Self-move
        dst = std::move(dst);
        bool self_values_correct = true;
        for (int i = 0; i < 10; ++i)
            if (dst[i] != i)
                self_values_correct = false;

        check(self_values_correct, "Move assignment: self-move safe");
    }

    // -------------------------------
    // Test 9: Large stress test
    // -------------------------------
    {
        const int N = 10000;
        MyVector<int> vec;
        for (int i = 0; i < N; ++i)
            vec.push_back(i);

        MyVector<int> copy(vec);
        MyVector<int> moved(std::move(vec));

        bool copy_ok = true, moved_ok = true;
        for (int i = 0; i < N; ++i) {
            if (copy[i] != i)
                copy_ok = false;
            if (moved[i] != i)
                moved_ok = false;
        }

        check(copy_ok, "Stress test: copy constructor large vector");
        check(moved_ok, "Stress test: move constructor large vector");
        check(vec.tum() == 0, "Stress test: moved-from large vector empty");
    }

    std::cout << "\n==== All Comprehensive Tests Finished ====\n";
    return 0;
}
