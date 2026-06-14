import matplotlib.pyplot as plt
import numpy as np
import csv
import os

# Определяем базовую папку
if os.path.exists('data/fenwick_build.csv'):
    DATA_DIR = 'data'
elif os.path.exists('build/data/fenwick_build.csv'):
    DATA_DIR = 'build/data'
else:
    DATA_DIR = 'data'

def read_csv(filename):
    filepath = os.path.join(DATA_DIR, os.path.basename(filename))
    if not os.path.exists(filepath):
        print(f"File {filepath} not found!")
        return None, None
    
    n_values = []
    ops_values = []
    
    with open(filepath, 'r') as f:
        reader = csv.reader(f)
        next(reader, None)
        for row in reader:
            if row and len(row) >= 2:
                try:
                    n_values.append(int(row[0]))
                    ops_values.append(float(row[1]))
                except (ValueError, IndexError):
                    continue
    
    return n_values, ops_values

def plot_fenwick():
    fig, axes = plt.subplots(1, 3, figsize=(18, 5))
    
    n_build, ops_build = read_csv('fenwick_build.csv')
    if n_build and ops_build:
        theoretical = [n * np.log2(n) for n in n_build]
        axes[0].plot(n_build, ops_build, 'bo-', label='Actual', linewidth=2, markersize=8)
        axes[0].plot(n_build, theoretical, 'r--', label='O(n log n)', linewidth=2)
        axes[0].set_title('Fenwick Tree: Build', fontsize=14, fontweight='bold')
        axes[0].set_xlabel('Array size (n)', fontsize=12)
        axes[0].set_ylabel('Operations', fontsize=12)
        axes[0].legend()
        axes[0].grid(True, alpha=0.3)
    
    n_query, ops_query = read_csv('fenwick_query.csv')
    if n_query and ops_query:
        theoretical = [2 * np.log2(n) for n in n_query]
        axes[1].plot(n_query, ops_query, 'go-', label='Actual', linewidth=2, markersize=8)
        axes[1].plot(n_query, theoretical, 'r--', label='O(log n)', linewidth=2)
        axes[1].set_title('Fenwick Tree: Query', fontsize=14, fontweight='bold')
        axes[1].set_xlabel('Array size (n)', fontsize=12)
        axes[1].set_ylabel('Operations per query', fontsize=12)
        axes[1].legend()
        axes[1].grid(True, alpha=0.3)
    
    n_update, ops_update = read_csv('fenwick_update.csv')
    if n_update and ops_update:
        theoretical = [np.log2(n) for n in n_update]
        axes[2].plot(n_update, ops_update, 'mo-', label='Actual', linewidth=2, markersize=8)
        axes[2].plot(n_update, theoretical, 'r--', label='O(log n)', linewidth=2)
        axes[2].set_title('Fenwick Tree: Update', fontsize=14, fontweight='bold')
        axes[2].set_xlabel('Array size (n)', fontsize=12)
        axes[2].set_ylabel('Operations per update', fontsize=12)
        axes[2].legend()
        axes[2].grid(True, alpha=0.3)
    
    plt.tight_layout()
    os.makedirs('graphs', exist_ok=True)
    plt.savefig('graphs/fenwick.png', dpi=150, bbox_inches='tight')
    print(f"Saved: graphs/fenwick.png (data from {DATA_DIR})")
    plt.show()

def plot_sparse():
    fig, axes = plt.subplots(1, 2, figsize=(14, 5))
    
    n_build, ops_build = read_csv('sparse_build.csv')
    if n_build and ops_build:
        theoretical = [n * np.log2(n) for n in n_build]
        axes[0].plot(n_build, ops_build, 'bo-', label='Actual', linewidth=2, markersize=8)
        axes[0].plot(n_build, theoretical, 'r--', label='O(n log n)', linewidth=2)
        axes[0].set_title('Sparse Table: Build', fontsize=14, fontweight='bold')
        axes[0].set_xlabel('Array size (n)', fontsize=12)
        axes[0].set_ylabel('Operations', fontsize=12)
        axes[0].legend()
        axes[0].grid(True, alpha=0.3)
    
    n_query, ops_query = read_csv('sparse_query.csv')
    if n_query and ops_query:
        axes[1].plot(n_query, ops_query, 'go-', label='Actual', linewidth=2, markersize=8)
        axes[1].axhline(y=2, color='r', linestyle='--', label='O(1)', linewidth=2)
        axes[1].set_title('Sparse Table: Query', fontsize=14, fontweight='bold')
        axes[1].set_xlabel('Array size (n)', fontsize=12)
        axes[1].set_ylabel('Operations per query', fontsize=12)
        axes[1].legend()
        axes[1].grid(True, alpha=0.3)
    
    plt.tight_layout()
    os.makedirs('graphs', exist_ok=True)
    plt.savefig('graphs/sparse.png', dpi=150, bbox_inches='tight')
    print(f"Saved: graphs/sparse.png (data from {DATA_DIR})")
    plt.show()

if __name__ == '__main__':
    print("Plotting graphs...")
    plot_fenwick()
    plot_sparse()
    print("Done!")
    