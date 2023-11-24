#include <iostream>
#include <functional>

namespace {
    void repeatingCases(std::function<void()> const &solveEach) {
        int cases;
        std::cin >> cases;
        while (cases--) {
            solveEach();
        }
    }
}