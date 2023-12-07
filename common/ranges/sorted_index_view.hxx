#include <ranges>
#include <algorithm>

namespace common::ranges {

    template<std::ranges::random_access_range R, std::weakly_incrementable W,
            class Comp = std::ranges::less> requires
    std::sortable<std::ranges::iterator_t<R>, Comp> && std::convertible_to<std::ranges::range_value_t<R>, W>
    struct sorted_index_iterator {
    private:
        std::ranges::iota_view<W>::iterator cur_;

    public:
        sorted_index_iterator(R base, Comp comp) {
            auto sz = std::ranges::size(base);
            cur_ = std::ranges::views::iota(sz) | std::ranges::sort(comp, [&base](auto& x) {
                return base[x];
            }).begin();
        }
    };

    template<std::ranges::random_access_range R, std::weakly_incrementable W,
            class Comp = std::ranges::less, class Proj = std::identity> requires
    std::sortable<std::ranges::iterator_t<R>, Comp, Proj> && std::convertible_to<std::ranges::range_value_t<R>, W>
    class sorted_index_view : public std::ranges::view_interface<sorted_index_view<R, W, Comp, Proj>> {
    private:
        R base_;
        std::ranges::iota_view<W>::iterator_t indices;

    public:
        sorted_index_view() = default;

        explicit sorted_index_view(R base, Comp comp, Proj proj) : base_(std::move(base)) {
            auto sz = std::ranges::size(base_);
            indices = std::ranges::views::iota(sz) | std::ranges::sort(comp, proj);
        }

        auto begin() {
            return indices.begin();
        }

        auto end() {
            return indices.end();
        }
    };


    struct sorted_index_fn {
        template<std::ranges::random_access_range R, std::weakly_incrementable W,
                class Comp = std::ranges::less, class Proj = std::identity>
        constexpr auto operator()(R &&r, Comp comp = {}, Proj proj = {}) -> sorted_index_view<R, W, Comp, Proj> {
            return sorted_index_fn(
                    sorted_index_view(std::views::all(std::forward<R>(r)), std::move(comp), std::move(proj)));
        }
    };

    inline constexpr auto sorted_index = sorted_index_fn{};
}