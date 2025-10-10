#include "aho_corasick.hpp"
#include <bits/stdc++.h>
using namespace std;

void test1() {
    AhoCorasick aho;
    vector<string> dict = {"a", "ab", "abc", "bca", "ca"};
    for (auto& s : dict) aho.insert(s);
    assert(aho.isInDict("bca"));
    assert(!aho.isInDict("bc"));
    assert(!aho.isInDict("abcxx"));
    assert(aho.isInDict("ca"));
}

void test2() {
    AhoCorasick aho;
    vector<string> dict = {"ab", "a", "b"};
    for (auto& s : dict) aho.insert(s);
    aho.getSuffixAndTerminalLinks();
    
    assert(aho.root->nexts['a']->suffixLink == aho.root);
    assert(aho.root->nexts['a']->word == "a");
    assert(aho.root->nexts['a']->nexts['b']->word == "ab");
    assert(aho.root->nexts['a']->nexts['b']->suffixLink->word == "b");
    assert(aho.root->nexts['a']->nexts['b']->terminalLink->word == "b");
}

int main() {
    //test1();
    test2();
}