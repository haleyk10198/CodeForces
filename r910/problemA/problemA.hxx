#include <ostream>
#include <memory>


namespace r910::problemA {
    struct Solution {
    protected:
        virtual std::ostream &print(std::ostream &os) const = 0;

    public:
        friend std::ostream &operator<<(std::ostream &os, const Solution &solution) {
            return solution.print(os);
        }

        virtual ~Solution() = default;
    };

    struct NoOp: public Solution {
    protected:
        std::ostream & print(std::ostream &os) const final {
            return os << 0 << std::endl;
        }
    };

    struct SingleOp: public Solution{
        const int mIdx;
        char mOperand;
    protected:
        std::ostream & print(std::ostream &os) const final {
            return os << 1 << std::endl
                << mIdx << ' ' << mOperand << std::endl;
        }
    public:
        SingleOp() = delete;
        SingleOp(int idx, char op): mIdx(idx), mOperand(op) {}
    };

    std::unique_ptr<Solution> solve(const std::string &str, unsigned long targeted);

    void runTestCases();
}
