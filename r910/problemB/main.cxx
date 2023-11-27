#include "main.hxx"
#include <common/test-case.hxx>

namespace r910::problemB {
    void readAndSolve() {
        int sz;
        std::cin >> sz;
        std::vector<int> array;
        std::copy_n(std::istream_iterator<int>(std::cin), sz, std::back_inserter(array));

        std::cout << solve(array) << std::endl;
    }
}

#ifndef UNIT_TEST

int main() {
    common::repeatingCases(&r910::problemB::readAndSolve);
    return 0;
}

#endif
