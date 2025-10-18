#pragma once
#include <bits/stdc++.h>
using namespace std;

// K = key and must define <, == and >, i.e K is totally ordered
template <typename K>
concept Comparable = requires(K a, K b) {
    {a < b} -> convertible_to<bool>;
    {a == b} -> convertible_to<bool>;
    {a > b} -> convertible_to<bool>;
};

template <typename T>
concept Key = default_initializable<T> && Comparable<T>;

template<Key K, default_initializable V>
struct AvlNode {
    AvlNode *l = nullptr, *r = nullptr;
    
    int weight = 1, height = 0;
    
    K key, mi, ma;
    V val, range; // contains the (e.g sum of val) of the subtree rooted at this node
    
    AvlNode() {}

    AvlNode(K key, V val): key(key), mi(key), ma(key), val(val), range(val) {}

    static int getWeight(AvlNode *node) {
        return (node == nullptr) ? 0 : node->weight;
    }

    static int getHeight(AvlNode *node) {
        return (node == nullptr) ? 0 : node->height;
    }
};


template <Key K, default_initializable V, V DefV = V{}>
struct AvlTree {
    using Node = AvlNode<K, V>;
    
    vector<unique_ptr<Node>> nodeStore;

    Node* makeNode() {
        nodeStore.emplace_back(new Node());
        return nodeStore.back().get();
    }

    Node* makeNode(K key, V val) {
        nodeStore.emplace_back(new Node(key, val));
        return nodeStore.back().get();
    }

    // reducer should be identity function if 1 of the arguements is the default value for V
    function<V(V,V)> reducer; 

    Node *root = nullptr;

    AvlTree() {}

    AvlTree(function<V(V, V)> reducer): reducer(reducer) {}

    // n1, n2 can be nullptr, but par cannot be nullptr
    void recompute(Node *par, Node* l, Node* r) {
        par->l = l, par->r = r;
        
        par->weight = 1 + Node::getWeight(l) + Node::getWeight(r);
        par->height = 1 + max(Node::getHeight(l), Node::getHeight(r));
        
        par->mi = (l == nullptr) ? par->key : par->l->mi;
        par->ma = (r == nullptr) ? par->key : par->r->ma; 
        
        V rangeL = (l == nullptr) ? DefV : l->range;
        V rangeR = (r == nullptr) ? DefV : r->range;
        V myRange = par->val;
        par->range = reducer(reducer(rangeL, myRange), rangeR);
    }

    Node* forcedRightRotate(Node *par) {
        Node *newPar = par->l;
        recompute(par, par->l->r, par->r);
        recompute(newPar, newPar->l, par);
        return newPar;
    }

    Node* forcedLeftRotate(Node *par) {
        Node* newPar = par->r;
        recompute(par, par->l, par->r->l);
        recompute(newPar, par, newPar->r);
        return newPar;
    }

    // only call this on right heavy nodes. 
    // thus, par->r is never null
    Node* leftRotate(Node *par) {
        assert(par->r != nullptr);
        
        Node *newPar = par->r;
        int heightL = Node::getHeight(par->l);
        int heightMid = Node::getHeight(par->r->l);
        int heightR = Node::getHeight(par->r->r);

        if (heightMid <= max(heightL, heightR)) {
            recompute(par, par->l, par->r->l);
            recompute(newPar, par, newPar->r);
            return newPar;
        } else {
            par->r = forcedRightRotate(par->r);
            return leftRotate(par);
        }
    }
    
    // only call this on left heavy nodes
    Node* rightRotate(Node *par) {
        assert(par->l != nullptr);

        Node *newPar = par->l;
        int heightL = Node::getHeight(par->l->l);
        int heightMid = Node::getHeight(par->l->r);
        int heightR = Node::getHeight(par->r);

        if (heightMid <= max(heightL, heightR)) {
            recompute(par, par->l->r, par->r);
            recompute(newPar, newPar->l, par);
            return newPar;
        } else {
            par->l = forcedLeftRotate(par->l);
            return rightRotate(par);
        }
    }

    void insert(K key, V val) {
        root = insert(key, val, root);
    }

    Node* insert(K key, V val, Node *curr) {
        if (curr == nullptr) {
            return makeNode(key, val);
        }

        assert(key != curr->key);
        if (key < curr->key) {
            curr->l = insert(key, val, curr->l);
            recompute(curr, curr->l, curr->r);
            if (Node::getHeight(curr->l) - Node::getHeight(curr->r) > 1) {
                curr = rightRotate(curr);
            }
            return curr;
        } 
        
        
        if (key > curr->key) {
            curr->r = insert(key, val, curr->r);
            recompute(curr, curr->l, curr->r);
            if (Node::getHeight(curr->r) - Node::getHeight(curr->l) > 1) {
                curr = leftRotate(curr);
            }
            return curr;
        }

        return nullptr;
    }

    void remove(K key) {
        root = remove(key, root);
    }

    Node* remove(K key, Node* curr) {
        if (curr == nullptr) return nullptr;
        
        if (key < curr->key) {
            curr->l = remove(key, curr->l);
            recompute(curr, curr->l, curr->r);
            if (Node::getHeight(curr->r) - Node::getHeight(curr->l) > 1) {
                curr = leftRotate(curr);
            }
            return curr;
        }

        if (key > curr->key) {
            curr->r = remove(key, curr->r);
            recompute(curr, curr->l, curr->r);
            if (Node::getHeight(curr->l) - Node::getHeight(curr->r) > 1) {
                curr = rightRotate(curr);
            }
            return curr;
        }

        if (curr->l == nullptr && curr->r == nullptr) return nullptr;

        if (curr->l != nullptr && curr->r == nullptr) return curr->l;

        if (curr->l == nullptr && curr->r != nullptr) return curr->r;

        // curr has 2 children, so have to find successor
        Node *succ = curr->r;
        while (succ->l != nullptr) succ = succ->l;
        
        Node *newRight = remove(succ->key, curr->r);
        recompute(succ, curr->l, newRight);
        if (Node::getHeight(succ->l) - Node::getHeight(succ->r) > 1) {
            succ = rightRotate(succ);
        }
        return succ;
    }

    pair<bool, V> atKey(K key) {
        return atKey(key, root);
    }

    // return {true, val} if key exist else {false, DefV}
    pair<bool, V> atKey(K key, Node* curr) {
        if (curr == nullptr) return pair{false, DefV};
        if (key == curr->key) return pair{true, curr->val};
        if (key < curr->key) return atKey(key, curr->l);
        if (key > curr->key) return atKey(key, curr->r);
        return pair{false, DefV};
    }

    pair<K, V> atRank(int rank) {
        assert(root != nullptr && rank < root->weight);
        return atRank(rank, root);
    }

    // rank queries. ranks are 0-indexed.
    // rank is in [0, size)
    // curr is never null
    pair<K, V> atRank(int rank, Node* curr) {
        int wl = Node::getWeight(curr->l);
        int wr = Node::getWeight(curr->r);
        if (rank == wl) {
            return pair{curr->key, curr->val};
        }

        if (rank < wl) {
            return atRank(rank, curr->l);
        }

        if (rank > wl) {
            return atRank(rank - wl - 1, curr->r);
        }

        return pair{K(), V()};
    }

    V rankRange(int l, int r) {
        assert(root != nullptr && l >= 0 && r < root->weight);
        return rankRange(l, r, root);
    }

    // rank range queries.
    // invariant: l <= r, curr != nullptr
    V rankRange(int l, int r, Node* curr) {
        int wl = Node::getWeight(curr->l);
        int wr = Node::getWeight(curr->r);

        if (l == 0 && r == wl + wr) return curr->range;
        if (l == r && l == wl) return curr->val;
        
        if (r < wl) {
            return rankRange(l, r, curr->l);
        }

        if (r == wl) {
            return reducer(rankRange(l, r - 1, curr->l), curr->val);
        }

        if (l > wl) {
            return rankRange(l - wl - 1, r - wl - 1, curr->r);
        }

        if (l == wl) {
            return reducer(curr->val, rankRange(0, r - wl - 1, curr->r));
        }

        // l < wl && r > wl
        V lres = rankRange(l, wl - 1, curr->l);
        V rres = rankRange(0, r - wl - 1, curr->r);
        return reducer(lres, reducer(curr->val, rres));
    }

    V keyRange(K l, K r) {
        return keyRange(l, r, root);
    }

    // invariant: l <= r.
    // it is possible for curr to be null if our [l, r] is outside of [mi, ma].
    V keyRange(K l, K r, Node *curr) {
        if (curr == nullptr) return DefV;
        if ((l < curr->mi || l == curr->mi) && (curr->ma < r || curr->ma == r)) return curr->range;
        if (r < curr->mi || l > curr->ma) return DefV;
        
        int wl = Node::getWeight(curr->l);
        int wr = Node::getWeight(curr->r);

        if (r < curr->key) {
            return keyRange(l, r, curr->l);
        } else if (r == curr->key) {
            return reducer(keyRange(l, r, curr->l), curr->val);
        }

        if (l > curr->key) {
            return keyRange(l, r, curr->r);
        } else if (l == curr->key) {
            return reducer(curr->val, keyRange(l, r, curr->r));
        }

        V lres = keyRange(l, r, curr->l);
        V rres = keyRange(l, r, curr->r);
        return reducer(lres, reducer(curr->val, rres));
    }

    void printInOrder(Node *curr) {
        if (curr == nullptr) return;
        printInOrder(curr->l);
        cout << curr->key << " " << curr->val << endl;
        printInOrder(curr->r);
    }

    
};
