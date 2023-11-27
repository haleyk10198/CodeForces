#include <ranges>
#include <concepts>
#include <limits>
#include <common/int-math.hxx>

namespace r910::problemB {
    using size_t = unsigned long long int;

    template<std::integral V>
    class AdmiringArray {
    private:
        V mLast{std::numeric_limits<V>::max()};
        size_t mSize{};

        struct MinChunk {
            V size;
            V value;

        public:
            MinChunk(V sum, V sz) : size(sz), value(sum / sz) {}
        };

        static MinChunk chunk(V curr, V minNext) {
            if (curr <= minNext) {
                return MinChunk(curr, 1);
            }

            return MinChunk(curr, ::common::ceil(curr, minNext));
        }

        void push(const V &value) {
            auto minChunk = chunk(value, mLast);
            mLast = minChunk.value;
            mSize += static_cast<size_t> (minChunk.size);
        }

    public:
        AdmiringArray() = delete;

        template<std::ranges::bidirectional_range T>
        requires std::is_same_v<std::ranges::range_value_t<T>, V>
        explicit AdmiringArray(T input) {
            if (std::ranges::empty(input)) {
                return;
            }

            auto reversed = input | std::views::reverse;
            for (const V &value: reversed) {
                push(value);
            }
        }

        [[nodiscard]] size_t size() const {
            return mSize;
        }
    };

    template<typename V = int>
    size_t solve(auto const& array) {
        return AdmiringArray<V>(array).size() - std::ranges::size(array);
    }
}

