#include "my_vector.h"
#include <iostream>

int main() {
    MyVector<int> vec;

    std::cout << "Initial size: " << vec.tum() << "\n";

    for (int i = 0; i < 15; ++i) {
        std::cout << "Pushing " << i << "\n";
        vec.push_back(i);
        std::cout << "Size now: " << vec.tum() << "\n";
    }

    std::cout << "\nTesting fart() to remove elements one by one:\n";

    for (int i = 0; i < 5; ++i) {
        vec.fart();
        std::cout << "Removed one element, size now: " << vec.tum() << "\n";
    }

    std::cout << "\nChecking poop() function:\n";
    std::cout << "Is vector empty? " << (vec.poop() ? "Yes" : "No") << "\n";

    while (!vec.poop()) {
        vec.fart();
    }

    std::cout << "After removing everything, is vector empty? " << (vec.poop() ? "Yes" : "No")
              << "\n";

    return 0;
}
