#pragma once
#include <bits/stdc++.h>
using namespace std;

// suffix link is a link to the node whose path from root is the longest proper suffix.
// terminal link is the link to the node whose path from root is the longest word in dict that is also a proper suffix.
// each node must have a suffix link, it may or may not have a terminal link.
// if no proper suffix in automaton, then suffix link points to root
// the root node has its suffix link point to itself

// how to get terminal link ?
// go to your suffix link and check if it is terminal, if yes great, 
// if not, the terminal link is the suffix link's terminal link.

struct Node {
    bool isRoot = false;
    string word = "";
    unordered_map<char, Node*> nexts;
    Node *suffixLink = nullptr, *terminalLink = nullptr;
};

struct AhoCorasick {
    vector<unique_ptr<Node>> nodeStore;

    Node *makeNode() {
        nodeStore.emplace_back(new Node());
        return nodeStore.back().get();
    }
    
    Node *root;

    AhoCorasick() {
        root = makeNode();
        root->isRoot = true;
    }

    void insert(const string& s, int i = 0, Node *node = nullptr) {
        if (node == nullptr) node = root;
        if (i == s.size()) {
            node->word = s;
            return;
        }

        char c = s[i];
        if (!node->nexts.contains(c)) {
            node->nexts[c] = makeNode();
        }
        insert(s, i + 1, node->nexts[c]);
    }

    bool isInDict(const string& s, int i = 0, Node *node = nullptr) {
        if (node == nullptr) node = root;
        if (i == s.size()) return node->word != ""; // the node must be a terminal node
        return (!node->nexts.contains(s[i])) ? false : isInDict(s, i + 1, node->nexts[s[i]]);
    }

    void getSuffixAndTerminalLinks() {
        queue<tuple<Node*, Node*, char>> q;
        
        root->suffixLink = root;
        for (auto& [key, val] : root->nexts) {
            val->suffixLink = root;
            
            for (auto [key2, val2] : val->nexts) {
                q.emplace(val2, val, key2);
            }
        }

        while (!q.empty()) {
            int len = q.size();
            for (int i = 0; i < len; i++) {
                auto [node, parent, c] = q.front(); q.pop();
                
                Node *curr = parent->suffixLink;
                while (1) {
                    if (curr->nexts.contains(c)) {
                        node->suffixLink = curr->nexts[c];
                        break;
                    } else if (curr == root) {
                        node->suffixLink = root;
                        break;
                    } else {
                        curr = curr->suffixLink;
                    }
                }
                
                node->terminalLink = (node->suffixLink->word != "") ? node->suffixLink : node->suffixLink->terminalLink;
                
                for (auto [key, val] : node->nexts) {
                    q.emplace(val, node, key);
                }
            }
        }
    }

    void getWords(const string& s, unordered_set<string>& store, int i = 0, Node *node = nullptr) {
        if (node == nullptr) node = root;
        if (node->word != "" && !store.contains(node->word)) {
            Node *curr = node;
            while (curr != nullptr) {
                store.insert(curr->word);
                curr = curr->terminalLink;
            }
        }
        if (i == s.size()) return;

        char c = s[i];
        if (node->nexts.contains(c)) {
            return getWords(s, store, i + 1, node->nexts[c]);
        } else if (node == root) {
            return getWords(s, store, i + 1, node);
        } else {
            return getWords(s, store, i, node->suffixLink);
        }
    }
};;