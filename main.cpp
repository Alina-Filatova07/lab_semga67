
#include "sparse_table.hpp"
#include <iostream>
#include <vector>
#include <string>

void demo_fenwick() {
    std::cout << "\n=== Fenwick Tree Demo ===\n";
    
    std::vector<long long> arr = {1, 3, 5, 7, 9, 11, 13, 15};
    
    std::cout << "Array: ";
    for (auto x : arr) std::cout << x << " ";
    std::cout << "\n";
    
    FenwickTree<long long> ft(arr);
    
    std::cout << "Sum [0, 3] = " << ft.query(0, 3) << " (expected: 16)\n";
    std::cout << "Sum [2, 5] = " << ft.query(2, 5) << " (expected: 32)\n";
    
    std::cout << "Updating index 2 from 5 to 10...\n";
    ft.set(2, 10);
    
    std::cout << "Sum [0, 3] after update = " << ft.query(0, 3) << "\n";
}

void demo_sparse_table() {
    std::cout << "\n=== Sparse Table Demo ===\n";
    
    std::vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    
    std::cout << "Array: ";
    for (auto x : arr) std::cout << x << " ";
    std::cout << "\n";
    
    SparseTable<int> st(arr);
    
    std::cout << "Min [0, 4] = " << st.query(0, 4) << " (expected: 1)\n";
    std::cout << "Min [2, 7] = " << st.query(2, 7) << " (expected: 1)\n";
}

void run_all_benchmarks();

void show_menu() {
    std::cout << "\n========================================\n";
    std::cout << "  RSQ & RMQ Implementation Menu\n";
    std::cout << "========================================\n";
    std::cout << "1. Demo Fenwick Tree (RSQ)\n";
    std::cout << "2. Demo Sparse Table (RMQ)\n";
    std::cout << "3. Run Benchmarks\n";
    std::cout << "4. Run All\n";
    std::cout << "0. Exit\n";
    std::cout << "========================================\n";
    std::cout << "Choose option: ";
}

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--benchmark") {
        run_all_benchmarks();
        return 0;
    }
    
    int choice;
    do {
        show_menu();
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                demo_fenwick();
                break;
            case 2:
                demo_sparse_table();
                break;
            case 3:
                run_all_benchmarks();
                break;
            case 4:
                demo_fenwick();
                demo_sparse_table();
                run_all_benchmarks();
                break;
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid option!\n";
        }
    } while (choice != 0);
    
    return 0;
}
