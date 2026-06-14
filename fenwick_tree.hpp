#ifndef FENWICK_TREE_HPP
#define FENWICK_TREE_HPP

#include <vector>
#include <cassert>

template<typename T = long long>
class FenwickTree {
private:
    std::vector<T> tree;
    int n;
    mutable long long build_operations = 0;
    mutable long long query_operations = 0;
    mutable long long update_operations = 0;

public:
    FenwickTree() : n(0) {}

    explicit FenwickTree(const std::vector<T>& arr) {
        init(arr);
    }

    void init(const std::vector<T>& arr) {
        n = static_cast<int>(arr.size());
        tree.assign(n + 1, 0);
        build_operations = 0;

        for (int i = 0; i < n; ++i) {
            update(i, static_cast<T>(arr[i]));
            build_operations++;
        }
    }

    void update(int idx, T delta) {
        assert(idx >= 0 && idx < n);
        update_operations++;
        
        for (int i = idx + 1; i <= n; i += i & (-i)) {
            tree[i] += delta;
            update_operations++;
        }
    }

    void set(int idx, T value) {
        assert(idx >= 0 && idx < n);
        T current = get_prefix_sum(idx) - get_prefix_sum(idx - 1);
        update(idx, value - current);
    }

    T get_prefix_sum(int idx) const {
        if (idx < 0) return 0;
        assert(idx < n);
        query_operations++;
        
        T sum = 0;
        for (int i = idx + 1; i > 0; i -= i & (-i)) {
            sum += tree[i];
            query_operations++;
        }
        return sum;
    }

    T query(int l, int r) const {
        assert(l >= 0 && r < n && l <= r);
        return get_prefix_sum(r) - get_prefix_sum(l - 1);
    }

    int size() const {
        return n;
    }

    long long get_build_operations() const { return build_operations; }
    long long get_query_operations() const { return query_operations; }
    long long get_update_operations() const { return update_operations; }

    void reset_counters() {
        build_operations = 0;
        query_operations = 0;
        update_operations = 0;
    }
};

#endif
