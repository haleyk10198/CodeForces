#include <vector>
#include <istream>
#include <ranges>
#include <algorithm>
#include <common/ranges/sorted_index_view.hxx>
#include <common/ranges/to_view.hxx>
#include <common/utils.hxx>

namespace r910::problemD {
    using beauty_t = unsigned long long int;

    template<std::integral T>
    class BeautyArrays {
    private:
        std::size_t sz{};
        std::vector<T> mA{};
        std::vector<T> mB{};

    public:
        BeautyArrays() = default;

        template<typename I>
        friend std::istream &operator>>(std::istream &in, BeautyArrays<I> &arrays);
    };

    template<typename I>
    std::istream &operator>>(std::istream &in, BeautyArrays<I> &arrays) {
        in >> arrays.sz;
        arrays.mA = std::ranges::istream_view<int>(in) | std::views::take(arrays.sz) | common::ranges::to<std::vector>();
        arrays.mB = std::ranges::istream_view<int>(in) | std::views::take(arrays.sz) | common::ranges::to<std::vector>();
        return in;
    }

    template<std::integral I>
    class best_beauty_view {
        private:

        explicit best_beauty_view(BeautyArrays<I> arrays) {}
    };


}