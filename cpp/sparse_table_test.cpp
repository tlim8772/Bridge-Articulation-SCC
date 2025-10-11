#include "sparse_table.hpp"

void test1() {
    function<int(int,int)> func = [](int x, int y) { return min(x, y); };
    vector<int> arr = {3,1,2,4,7,6,9};
    SparseTable st(arr, func);
    assert(st.rangeQuery(0, 3) == 1);
    assert(st.rangeQuery(4, 6) == 6);
    assert(st.rangeQuery(0, 6) == 1);
}

void test2() {
    function<int(int,int)> func = [](int x, int y) { return max(x, y); };
    vector<int> arr = {3,1,2,4,7,6,9};
    SparseTable st(arr, func);
    assert(st.rangeQuery(0, 3) == 4);
    assert(st.rangeQuery(4, 6) == 9);
    assert(st.rangeQuery(0, 6) == 9);
}

void test3() {
    function<pair<int,string>(pair<int,string>,pair<int,string>)> func = 
        [] (pair<int,string> p1, pair<int,string> p2) {
            return (p1.first <= p2.first) ? p1 : p2; 
        };
    vector<pair<int,string>> arr = {{3, "bob"}, {1, "tom"}, {2, "a"}, {99, "mary"}, {10, "h"}};
    SparseTable st(arr, func);
    assert(st.rangeQuery(0, 2) == arr[1]);
    assert(st.rangeQuery(1, 3) == arr[1]);
    assert(st.rangeQuery(2, 4) == arr[2]);
}

int main() {
    test1();
    test2();
}