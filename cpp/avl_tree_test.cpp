#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "avl_tree.hpp"

void test1() {
    auto summer = [](int x, int y) {return x + y;};
    AvlTree<int, int, 0> tree{summer};
    for (int i = 0; i < 100; i++) {
        tree.insert(i, i);
    }
    cout << tree.root->height << endl;
    assert(tree.root->range == 4950);
}

void test2() {
    auto summer = [](ll x, ll y) {return x + y;};
    AvlTree<int,ll,0> tree{summer};
    for (int i = 0; i < 100000; i++) {
        tree.insert(i, i);
    }
    cout << tree.root->height << endl;
    cout << tree.root->range << endl;
}

void test3() {
    auto summer = [](int x, int y) {return x + y;};
    AvlTree<int, int, 0> tree{summer};
    for (int i = 0; i < 100; i++) {
        tree.insert(i, i);
    }
    tree.remove(10);
    assert(tree.root->range == 4940);
}

void test4() {
    auto summer = [](ll x, ll y) {return x + y;};
    AvlTree<int,ll,0> tree{summer};
    for (int i = 0; i < 100000; i++) {
        tree.insert(i, i);
    }
    cout << tree.root->height << endl;
    //cout << tree.root->range << endl;

    for (int i = 10; i < 20; i++) {
        tree.remove(i);
    }

    //cout << tree.root->range << endl;
    assert(tree.root->range == 4999949855L);
}

void test5() {
    auto summer = [] (int x, int y) {return x + y;};
    AvlTree<char, int, 0> tree{summer};
    for (int i = 0; i < 26; i++) {
        tree.insert('a' + i, i);
    }
    cout << tree.root->range << endl;
}

struct Pair {
    int x = 0, y = 0;

    Pair() {};

    Pair(int x, int y): x(x), y(y) {}

    bool operator<(Pair p) {
        return x < p.x || (x == p.x && y < p.y);
    }

    bool operator==(Pair p) {
        return x == p.x && y == p.y;
    }

    bool operator>(Pair p) {
        return x > p.x || (x == p.x && y > p.y);
    }
};

void test6() {
    auto summer = [] (int x, int y) {return x + y;};
    AvlTree<Pair, int, 0> tree{summer};
    for (int i = 0; i < 100; i++) {
        tree.insert({i, i + 1}, i);
    }
    cout << tree.root->range << endl;
}

void test7() {
    auto summer = [](int x, int y) {return x + y;};
    AvlTree<int, int, 0> tree{summer};
    for (int i = 0; i < 100; i++) {
        tree.insert(i, i);
    }
    assert(tree.atRank(10).first == 10);
    tree.remove(10);
    assert(tree.atRank(10).first == 11);
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
}



