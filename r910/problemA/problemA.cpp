#include "problemA.hxx"
#include <common/test-case.hxx>

namespace r910::problemA {

    void runTestCases() {
        int length, targeted;
        std::cin >> length >> targeted;

        std::string str;
        std::cout << *solve(str, targeted);
    }

    std::unique_ptr<Solution> solve(const std::string &str, unsigned long targeted) {
        unsigned long existing = std::count_if(str.begin(), str.end(), [](auto ch) { return ch == 'B'; });
        if(existing == targeted) {
            return std::make_unique<NoOp>();
        }

        unsigned long prefixAs = 0;
        unsigned long prefixBs = 0;
        for(int i = 0; (unsigned long) i < str.length(); ++i) {
            (str[i] == 'A'? prefixAs: prefixBs)++;
            auto baseLine = targeted - prefixBs;
            if(baseLine == targeted) {
                return std::make_unique<SingleOp>(i, 'A');
            }

            if(baseLine + (i+1) == targeted) {
                return std::make_unique<SingleOp>(i, 'B');
            }
        }

        return nullptr;
    }

}

#ifdef ONLINE_JUDGE

int main() {
    repeatingCases(&r910::problemA::runTestCases);
}

#endif