#include <ranges>
#include <algorithm>

namespace common::ranges {

    template<std::ranges::random_access_range R, std::weakly_incrementable W,
            class Comp = std::ranges::less> requires
    std::sortable<std::ranges::iterator_t<R>, Comp> && std::convertible_to<std::ranges::range_value_t<R>, W>
    struct sorted_index_view {
    private:
        using index_view = std::ranges::iota_view<W>;
        index_view indices {};

    public:
        sorted_index_view(R base, Comp comp) {
            auto sz = std::ranges::size(base);
            indices = std::ranges::views::iota(sz) | std::ranges::sort(comp, [&base](auto &x) {
                return base[x];
            });
        }

        struct sentinel {
            std::ranges::sentinel_t<index_view> s;
        };

        struct iterator {
            using reference = std::ranges::range_reference_t<index_view>;
            index_view::iterator cur_;

            iterator() = default;

            explicit iterator(sorted_index_view &parent) : cur_(parent.indices.begin()) {}

            reference operator*() const {
                return cur_;
            }

            iterator& operator++() {
                ++cur_;
                return *this;
            }

            void operator++(int) {
                ++this;
            }

            bool operator==(const sentinel &sent) const {
                return cur_ == sent.s;
            }
        };

        iterator begin() {
            return iterator(*this);
        }

        sentinel end() {
            return sentinel { std::ranges::end(indices) };
        }
    };


    struct sorted_index_fn {
        template<std::ranges::random_access_range R, std::weakly_incrementable W,
                class Comp = std::ranges::less, class Proj = std::identity>
        constexpr sorted_index_view<R, W, Comp> operator()(R &&r, Comp comp = {}) {
            return sorted_index_view(sorted_index_view(std::views::all(std::forward<R>(r)), std::move(comp)));
        }
    };

    inline constexpr auto sorted_index = sorted_index_fn{};
}