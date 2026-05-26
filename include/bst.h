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
        T data;
        int freq;
        Node* left;
        Node* right;
        explicit Node(const T& v) : data(v), freq(1), left(nullptr), right(nullptr) {}
    };
    Node* root;

    Node* put(Node* n, const T& v) {
        if (!n) return new Node(v);
        if (v < n->data) n->left = put(n->left, v);
        else if (v > n->data) n->right = put(n->right, v);
        else n->freq++;
        return n;
    }

    int depth(Node* n) const {
        if (!n) return -1;
        int dl = depth(n->left);
        int dr = depth(n->right);
        return 1 + (dl > dr ? dl : dr);
    }

    Node* get(Node* n, const T& v) const {
        if (!n || n->data == v) return n;
        if (v < n->data) return get(n->left, v);
        return get(n->right, v);
    }

    void scan(Node* n, std::vector<std::pair<T, int>>& out) const {
        if (!n) return;
        scan(n->left, out);
        out.push_back({ n->data, n->freq });
        scan(n->right, out);
    }

    void erase(Node* n) {
        if (!n) return;
        erase(n->left);
        erase(n->right);
        delete n;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { erase(root); }

    void insert(const T& v) { root = put(root, v); }
    int height() const { return depth(root); }
    int count(const T& v) const {
        Node* n = get(root, v);
        return n ? n->freq : 0;
    }
    std::vector<std::pair<T, int>> entries() const {
        std::vector<std::pair<T, int>> res;
        scan(root, res);
        return res;
    }
    bool empty() const { return root == nullptr; }
};

#endif
