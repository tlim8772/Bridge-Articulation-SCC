#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
requires default_initializable<T>
struct SparseTable {
    int N, MAX_P;
    vector<vector<T>> table;
    function<T(T,T)> func;

    SparseTable(const vector<T>& arr, function<T(T,T)> func): 
        N(arr.size()), 
        MAX_P(floor(log2(N))), 
        table(N, vector<T>(MAX_P + 1, T())),
        func(func) 
    {
        build(arr);
    }

    void build(const vector<T>& arr) {
        for (int i = 0; i < N; i++) table[i][0] = arr[i];

        for (int p = 1; p <= MAX_P; p++) {
            for (int i = 0; i < N; i++) {
                table[i][p] = (i + (1 << (p - 1)) >= N) ? table[i][p - 1] : func(table[i][p - 1], table[i + (1 << (p - 1))][p - 1]);
            }
        }
    }

    T rangeQuery(int l, int r) {
        int max_p = (int) floor(log2(r - l + 1));
        return func(table[l][max_p], table[r - (1 << max_p) + 1][max_p]);
    }
};