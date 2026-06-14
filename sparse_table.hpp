#ifndef SPARSE_TABLE_HPP
#define SPARSE_TABLE_HPP

#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

template<typename T = int>
class SparseTable {
private:
    std::vector<std::vector<T>> table;
    std::vector<int> log_table;
    int n;
    mutable long long build_operations = 0;
    mutable long long query_operations = 0;

public:
    SparseTable() : n(0) {}

    explicit SparseTable(const std::vector<T>& arr) {
        init(arr);
    }

    void init(const std::vector<T>& arr) {
        n = static_cast<int>(arr.size());
        if (n == 0) return;

        build_operations = 0;

        int max_log = static_cast<int>(std::log2(n)) + 1;
        
        log_table.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i) {
            log_table[i] = log_table[i / 2] + 1;
            build_operations++;
        }

        table.assign(max_log, std::vector<T>(n));
        
        for (int i = 0; i < n; ++i) {
            table[0][i] = arr[i];
            build_operations++;
        }

        for (int j = 1; j < max_log; ++j) {
            for (int i = 0; i + (1 << j) - 1 < n; ++i) {
                table[j][i] = std::min(table[j-1][i], table[j-1][i + (1 << (j-1))]);
                build_operations++;
            }
        }
    }

    T query(int l, int r) const {
        assert(l >= 0 && r < n && l <= r);
        query_operations++;
        
        int len = r - l + 1;
        int k = log_table[len];
        
        return std::min(table[k][l], table[k][r - (1 << k) + 1]);
    }

    int size() const {
        return n;
    }

    long long get_build_operations() const { return build_operations; }
    long long get_query_operations() const { return query_operations; }

    void reset_counters() {
        build_operations = 0;
        query_operations = 0;
    }
};

#endif
