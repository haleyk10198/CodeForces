#include <ranges>
#include <algorithm>

namespace common::ranges {
    template<std::ranges::random_access_range R1, std::ranges::forward_range R2>
    class permutated_view : public std::ranges::view_interface<permutated_view<R1, R2>> {
    private:
        R1 base_;
        std::ranges::iterator_t<R2> cur_;
        R2 permutation_;
    public:
        permutated_view() = default;

        permutated_view(R1 base, R2 permutation) : base_(std::move(base)), cur_(std::ranges::begin(permutation)),
                                                   permutation_(std::move(permutation)) {}

        struct sentinel {
            std::ranges::sentinel_t<R2> s;
        };

        struct iterator {
            using reference = std::ranges::range_reference_t<R1>;

            iterator() = delete;

            iterator(permutated_view &parent) : parent_(&parent) {}

            permutated_view &parent_;

            reference operator*() const {
                return parent_.base_[*parent_.cur];
            }

            iterator &operator++() {
                *parent_.cur++;
                return *this;
            }

            void operator++(int) {
                ++this;
            }

            bool operator==(const sentinel &sent) const {
                return parent_.cur_ == sent.s;
            }
        };

        iterator begin() {
            return iterator(*this);
        }

        sentinel end() {
            return sentinel{std::ranges::end(permutation_)};
        }
    };
}
