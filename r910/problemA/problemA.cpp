#include "problemA.hxx"
#include <common/test-case.hxx>

namespace r910::problemA {

    void runTestCases() {
        int length, targeted;
        std::cin >> length >> targeted;

        std::string str; std::cin >> str;
        std::cout << *solve(str, targeted);
    }

    std::unique_ptr<Solution> solve(const std::string &str, unsigned long targeted) {
        unsigned long existing = std::count_if(str.begin(), str.end(), [](auto ch) { return ch == 'B'; });
        if(existing == targeted) {
            return std::make_unique<NoOp>();
        }

        unsigned long prefixAs = 0;
        unsigned long prefixBs = 0;
        for(unsigned long i = 0; i < str.length(); ++i) {
            (str[i] == 'A'? prefixAs: prefixBs)++;
            auto baseLine = existing - prefixBs;
            if(baseLine == targeted) {
                return std::make_unique<SingleOp>(i+1, 'A');
            }

            if(baseLine + (i+1) == targeted) {
                return std::make_unique<SingleOp>(i+1, 'B');
            }
        }

        return nullptr;
    }

}

#ifndef UNIT_TEST

int main() {
    common::repeatingCases(&r910::problemA::runTestCases);
}

#endif