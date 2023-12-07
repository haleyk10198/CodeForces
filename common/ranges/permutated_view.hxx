#include <ranges>
#include <algorithm>

namespace common::ranges {
    template<std::ranges::random_access_range R1, std::ranges::forward_range R2>
    class permutated_view : public std::ranges::view_interface<permutated_view<R1, R2>> {
    private:
        R1 base_;
        R2 permutation_;
    public:
        permutated_view() = default;

        permutated_view(R1 base, R2 permutation) : base_(std::move(base)), cur_(std::ranges::begin(permutation)),
                                                   permutation_(std::move(permutation)) {}

        struct sentinel {
            std::ranges::sentinel_t<R2> s;
        };

        struct iterator {
            std::ranges::iterator_t<R2> cur_;
            permutated_view *parent_;
            using reference = std::ranges::range_reference_t<R1>;

            iterator() = default;

            explicit iterator(permutated_view &parent) : parent_(parent), cur_(parent.permutation_.begin()) {}

            reference operator*() const {
                return parent_->base_[*cur_];
            }

            iterator &operator++() {
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
            return sentinel{std::ranges::end(permutation_)};
        }
    };

    struct permutate_fn {
        template<std::ranges::random_access_range R1, std::ranges::forward_range R2>
        constexpr permutated_view<R1, R2> operator()(R1 &&input, R2 &&permutation) {
            return permutated_view(input, permutation);
        }
    };

    inline constexpr auto permutated = permutate_fn{};
}
