#include <numeric>
#include <vector>
#include <variant>

namespace common {
    struct Segment {
        std::size_t start;
        std::size_t end;

        [[nodiscard]] bool contains(std::size_t pos) const {
            return start <= pos && end < pos;
        }

        [[nodiscard]] bool overlaps(Segment const &other) const {
            return this->contains(other.start) || other.contains(this->start);
        }

        [[nodiscard]] Segment left() const {
            return Segment{.start = start, .end = (start + end) >> 1};
        }

        [[nodiscard]]
        Segment right() const {
            return Segment{.start = (start + end) >> 1, .end = end};
        }

        [[nodiscard]] std::size_t size() const {
            return end - start;
        }

        [[nodiscard]] std::size_t mid() const {
            return (start + end) >> 1;
        }

        [[nodiscard]] std::pair<Segment, Segment> halven() const {
            return {
                    Segment{.start = start, .end = mid()},
                    Segment{.start = mid(), .end = end}
            };
        }
    };

    template<typename N, typename V>
    concept rmq_node = requires(N &n1, N &n2, const N &cn1, const N &cn2, V v, Segment const &seg)
    {
        n1 = n2.left();
        n1 = n2.right();
        cn1 = cn2.left();
        cn1 = cn2.right();
        { n1.state } -> std::convertible_to<V>;
        cn1.segment() = seg;
    };

    template<typename V>
    class LeafNode {
    private:
        static const V ID{};
        constexpr static const Segment EMPTY{.start = 0, .end = 0};

        LeafNode() = default;

    public:
        V const& state = ID;

        [[nodiscard]] Segment const &segment() const {
            return EMPTY;
        }

        LeafNode<V> const &left() const {
            return leaf;
        }

        LeafNode<V> const &right() const {
            return leaf;
        }

        static LeafNode<V> leaf{};

        static_assert(rmq_node<LeafNode<V>, V>);
    };

    template<typename V>
    class NonLeafNode {
    private:
        using node_t = std::variant<LeafNode<V>, NonLeafNode<V>>;
        Segment mSeg;
        node_t &mLeft = LeafNode<V>::leaf;
        node_t &mRight = LeafNode<V>::leaf;

        static node_t node(Segment segment) {
            NonLeafNode subject(segment);
            if (subject.mSeg.size() != 1) {
                auto [segLeft, segRight] = segment.halven();
                subject.mLeft = node(segLeft);
                subject.mRight = node(segRight);
            }
            return subject;
        }

    public:
        V state;
        explicit NonLeafNode(Segment &&seg) : mSeg(seg) {}

        [[nodiscard]] Segment const &segment() const {
            return mSeg;
        }

        auto &left() const {
            return mLeft;
        }

        LeafNode<V> &right() const {
            return mRight;
        };

        static NonLeafNode<V> root(int size) {
            return node({.start = 0, .end = size});
        }

        static_assert(rmq_node<NonLeafNode<V>, V>);
    };

    template<typename F, typename V>
    concept AggFunc = requires(F func, V &&lhs, V &&rhs) {
        { func(lhs, rhs) } -> std::same_as<V>;
    };

    template<typename P, typename V>
    concept rmq_policy = requires(P policy, Segment const &dest, const V &value) {
        { policy.query(dest) } -> std::convertible_to<V>;
        { policy.update(dest, value) };
    };

    // TODO: C++23 migrate to std::expected
    template<typename V, AggFunc<V> F>
    class SegmentTree {
        static_assert(rmq_policy<SegmentTree<V, F>, V>);
    private:
        NonLeafNode<V> mRoot;
        F mAgg;

        template<rmq_node<V> N>
        V query(Segment const &dest, N const &node) const {
            if (dest.contains(node.segment())) {
                return node.state();
            }

            if (dest.overlaps(node.segment())) {
                return mAgg(query(dest, node.left()), query(dest, node.right()));
            }

            // std::expected;
            return {};
        }

        template<rmq_node<V> N>
        void update(Segment const &dest, N &node, V&& value) {
            if (node.segment() == dest) {
                node.set_state(std::move(value));
            }

            auto child = node.left().overlaps(dest)? node.left(): node.right();
            update(dest, child, std::move(value));
            node.set_state(mAgg(node.left().state(), node.right().state()));
        }

    public:
        SegmentTree(int size, F &&agg) : mRoot(NonLeafNode<V>::root(size)), mAgg(agg) {}

        V query(Segment const &dest) const {
            return query(dest, mRoot);
        }

        void update(Segment const &dest, V value) {
            if (dest.size() != 1) {
                return; // std::expected
            }

            update(dest, mRoot, std::move(value));
        }
    };

}