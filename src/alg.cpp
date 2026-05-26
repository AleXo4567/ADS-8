// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <utility>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cout << "File error!" << std::endl;
        return;
    }
    std::string word;
    while (true) {
        int ch = in.get();
        if (in.eof()) break;
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            word += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }
    if (!word.empty()) tree.insert(word);
    in.close();
}

void printFreq(BST<std::string>& tree) {
    auto items = tree.getAllSortedByKey();
    std::sort(items.begin(), items.end(),
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            if (a.second != b.second) return a.second > b.second;
            return a.first < b.first;
        });
    for (const auto& p : items) {
        std::cout << p.first << " : " << p.second << "\n";
    }
    std::ofstream out("result/freq.txt");
    if (!out) {
        std::cout << "Cannot open result/freq.txt for writing!" << std::endl;
        return;
    }
    for (const auto& p : items) {
        out << p.first << " : " << p.second << "\n";
    }
    out.close();
}
