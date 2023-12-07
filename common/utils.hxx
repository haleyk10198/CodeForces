#include <iostream>
#include <type_traits>

namespace common {
    void init() {
        std::ios_base::sync_with_stdio(false);
    }

    template<typename T, typename = void>
    constexpr bool has_input_operator = false;

    template<typename T>
    constexpr bool has_input_operator<T, std::void_t<decltype(std::cin >> std::declval<T>())>> = true;

    template<typename T>
    std::enable_if_t<common::has_input_operator<std::ranges::range_reference_t<T>>, std::istream &>
    operator>>(std::istream &istream, T &iterable) {
        for (auto &iter: iterable) {
            istream >> iter;
        }
        return istream;
    }

}
