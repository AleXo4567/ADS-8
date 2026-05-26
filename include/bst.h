// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <utility>
#include <algorithm>

template <typename T>
class BST {
 private:
    struct Node {
        T val;
        int freq;
        Node* lft;
        Node* rgt;
        explicit Node(const T& v) : val(v), freq(1), lft(nullptr), rgt(nullptr) {}
    };
    Node* root;

    Node* addNode(Node* n, const T& v) {
        if (!n) return new Node(v);
        if (v < n->val) n->lft = addNode(n->lft, v);
        else if (v > n->val) n->rgt = addNode(n->rgt, v);
        else n->freq++;
        return n;
    }

    int getDepthRec(Node* n) const {
        if (!n) return -1;
        int dl = getDepthRec(n->lft);
        int dr = getDepthRec(n->rgt);
        return 1 + (dl > dr ? dl : dr);
    }

    Node* searchRec(Node* n, const T& v) const {
        if (!n || n->val == v) return n;
        if (v < n->val) return searchRec(n->lft, v);
        return searchRec(n->rgt, v);
    }

    void collectInOrder(Node* n, std::vector<std::pair<T, int>>& out) const {
        if (!n) return;
        collectInOrder(n->lft, out);
        out.push_back({n->val, n->freq});
        collectInOrder(n->rgt, out);
    }

    void eraseTree(Node* n) {
        if (!n) return;
        eraseTree(n->lft);
        eraseTree(n->rgt);
        delete n;
    }

 public:
    BST() : root(nullptr) {}
    ~BST() { eraseTree(root); }

    void insert(const T& key) {
        root = addNode(root, key);
    }

    int depth() const {
        return getDepthRec(root);
    }

    int search(const T& value) const {
        Node* n = searchRec(root, value);
        return n ? n->freq : 0;
    }

    std::vector<std::pair<T, int>> getAllSortedByKey() const {
        std::vector<std::pair<T, int>> res;
        collectInOrder(root, res);
        return res;
    }

    bool empty() const {
        return root == nullptr;
    }
};

#endif  // INCLUDE_BST_H_
