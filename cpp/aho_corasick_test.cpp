#include "aho_corasick.hpp"
#include <bits/stdc++.h>
using namespace std;

void test1() {
    AhoCorasick aho;
    vector<string> dict = {"a", "ab", "abc", "bca", "ca"};
    for (string& s : dict) aho.insert(s);
    assert(aho.isInDict("bca"));
    assert(!aho.isInDict("bc"));
    assert(!aho.isInDict("abcxx"));
    assert(aho.isInDict("ca"));
}

void test2() {
    AhoCorasick aho;
    vector<string> dict = {"ab", "a", "b"};
    for (string& s : dict) aho.insert(s);
    aho.getSuffixAndTerminalLinks();
    
    assert(aho.root->nexts['a']->suffixLink == aho.root);
    assert(aho.root->nexts['a']->word == "a");
    assert(aho.root->nexts['a']->nexts['b']->word == "ab");
    assert(aho.root->nexts['a']->nexts['b']->suffixLink->word == "b");
    assert(aho.root->nexts['a']->nexts['b']->terminalLink->word == "b");
}

void test3() {
    AhoCorasick aho;
    vector<string> dict = {"abc", "bc"};
    for (string& s : dict) aho.insert(s);
    aho.getSuffixAndTerminalLinks();

    assert(aho.root->nexts['a']->nexts['b']->nexts['c']->word == "abc");
    assert(aho.root->nexts['a']->nexts['b']->nexts['c']->suffixLink->word == "bc");
}

void test4() {
    AhoCorasick aho;
    vector<string> dict = {"abc", "bc"};
    for (string& s : dict) aho.insert(s);
    aho.getSuffixAndTerminalLinks();

    unordered_set<string> store;
    aho.getWords("xabcx", store);
    
    vector<string> out(store.begin(), store.end());
    sort(out.begin(), out.end());
    assert(out == vector<string>({"abc", "bc"}));
}

void test5() {
    AhoCorasick aho;
    vector<string> dict = {"a", "aa", "aaa", "aaaa", "abaa"};
    for (string& s : dict) aho.insert(s);
    aho.getSuffixAndTerminalLinks();

    unordered_set<string> store;
    aho.getWords("abaaaa", store);
    vector<string> out(store.begin(), store.end());
    sort(out.begin(), out.end());
    assert(out == vector<string>({"a", "aa", "aaa", "aaaa", "abaa"}));
}

void test6() {
    AhoCorasick aho;
    
    vector<string> dict;
    for (int i = 0; i < 1000; i++) {
        dict.emplace_back(i + 1, 'a');
        aho.insert(dict.back());
    }
    aho.getSuffixAndTerminalLinks();

    unordered_set<string> store;
    aho.getWords(string(1000, 'a'), store);
    assert(store.size() == 1000);
    assert(store.contains(string(519, 'a')));

}




int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
}