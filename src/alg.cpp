// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cout << "File error!" << std::endl;
        return;
    }
    std::string word;
    while (true) {
        int c = in.get();
        if (in.eof()) break;
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            word += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
        else {
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
    auto vec = tree.entries();
    std::sort(vec.begin(), vec.end(),
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            if (a.second != b.second) return a.second > b.second;
            return a.first < b.first;
        });
    for (const auto& p : vec) {
        std::cout << p.first << " : " << p.second << "\n";
    }
    std::ofstream out("resultfreq.txt");
    if (!out) {
        std::cout << "Cannot open resultfreq.txt for writing!" << std::endl;
        return;
    }
    for (const auto& p : vec) {
        out << p.first << " : " << p.second << "\n";
    }
    out.close();
}
