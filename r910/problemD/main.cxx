#include "main.hxx"
#include <common/test-case.hxx>

using namespace std;
using namespace common;

namespace r910::problemD {
    void readAndSolve() {
        BeautyArrays<int> question{};
        std::cin >> question;
    }
}

int main() {
    common::init();
    common::repeatingCases(&r910::problemD::readAndSolve);
    return 0;
}