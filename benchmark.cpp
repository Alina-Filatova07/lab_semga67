#include "fenwick_tree.hpp"
#include "sparse_table.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <iomanip>
#include <cmath>

class RandomGenerator {
private:
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;

public:
    RandomGenerator(int seed = 42) : gen(seed), dist(1, 1000000) {}

    int generate() {
        return dist(gen);
    }

    std::vector<int> generate_array(int size) {
        std::vector<int> arr(size);
        for (int i = 0; i < size; ++i) {
            arr[i] = generate();
        }
        return arr;
    }
};

void benchmark_fenwick() {
    std::cout << "\n=== Benchmarking Fenwick Tree ===\n";
    
    #ifdef _WIN32
        system("mkdir data 2>nul");
    #else
        system("mkdir -p data");
    #endif
    
    RandomGenerator rng;
    std::ofstream build_file("data/fenwick_build.csv");
    std::ofstream query_file("data/fenwick_query.csv");
    std::ofstream update_file("data/fenwick_update.csv");
    
    build_file << "n,operations\n";
    query_file << "n,operations_per_query\n";
    update_file << "n,operations_per_update\n";

    std::vector<int> sizes = {100, 500, 1000, 5000, 10000, 50000, 100000};
    
    for (int n : sizes) {
        auto arr = rng.generate_array(n);
        
        FenwickTree<long long> ft;
        ft.reset_counters();
        std::vector<long long> long_arr(arr.begin(), arr.end());
        ft.init(long_arr);
        long long build_ops = ft.get_build_operations();
        build_file << n << "," << build_ops << "\n";
        
        std::cout << "Fenwick n=" << n << ": build_ops=" << build_ops << "\n";
        
        ft.reset_counters();
        int num_queries = 10000;
        for (int q = 0; q < num_queries; ++q) {
            int l = rng.generate() % n;
            int r = rng.generate() % n;
            if (l > r) std::swap(l, r);
            ft.query(l, r);
        }
        double avg_query_ops = static_cast<double>(ft.get_query_operations()) / num_queries;
        query_file << n << "," << std::fixed << std::setprecision(2) << avg_query_ops << "\n";
        
        ft.reset_counters();
        int num_updates = 10000;
        for (int u = 0; u < num_updates; ++u) {
            int idx = rng.generate() % n;
            ft.update(idx, 1);
        }
        double avg_update_ops = static_cast<double>(ft.get_update_operations()) / num_updates;
        update_file << n << "," << std::fixed << std::setprecision(2) << avg_update_ops << "\n";
    }
    
    std::cout << "Data saved to data/fenwick_*.csv\n";
}

void benchmark_sparse_table() {
    std::cout << "\n=== Benchmarking Sparse Table ===\n";
    
    RandomGenerator rng;
    std::ofstream build_file("data/sparse_build.csv");
    std::ofstream query_file("data/sparse_query.csv");
    
    build_file << "n,operations\n";
    query_file << "n,operations_per_query\n";

    std::vector<int> sizes = {100, 500, 1000, 5000, 10000, 50000, 100000};
    
    for (int n : sizes) {
        auto arr = rng.generate_array(n);
        
        SparseTable<int> st;
        st.reset_counters();
        st.init(arr);
        long long build_ops = st.get_build_operations();
        build_file << n << "," << build_ops << "\n";
        
        std::cout << "Sparse Table n=" << n << ": build_ops=" << build_ops << "\n";
        
        st.reset_counters();
        int num_queries = 10000;
        for (int q = 0; q < num_queries; ++q) {
            int l = rng.generate() % n;
            int r = rng.generate() % n;
            if (l > r) std::swap(l, r);
            st.query(l, r);
        }
        double avg_query_ops = static_cast<double>(st.get_query_operations()) / num_queries;
        query_file << n << "," << std::fixed << std::setprecision(2) << avg_query_ops << "\n";
    }
    
    std::cout << "Data saved to data/sparse_*.csv\n";
}

void run_all_benchmarks() {
    benchmark_fenwick();
    benchmark_sparse_table();
    std::cout << "\n=== All benchmarks completed ===\n";
}
