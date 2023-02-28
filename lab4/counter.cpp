namespace counter {
    long xors = 0;
    template <typename T>
    void swap(T &a, T &b) {
        a ^= b ^= a ^= b;
        ++xors;
    }
}
