namespace common {
    template<std::integral V>
    V ceil(V num, V denom) {
        return (num + denom - 1) / denom;
    }
}
