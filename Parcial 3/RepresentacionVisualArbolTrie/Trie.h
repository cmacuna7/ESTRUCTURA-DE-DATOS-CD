#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <list>
#include "TrieNode.h"

class Trie {
public:
    Trie();
    void insert(const std::wstring &word);
    void display();
    void showTraversal();
    int getHeight();
    int getDepth(const std::wstring &word);
    int getLevel(const std::wstring &word);

private:
    TrieNode* root;
    void displayHelper(TrieNode* node, std::wstring prefix, int level);
    void showTraversalHelper(TrieNode* node, std::wstring prefix);
    int getHeightHelper(TrieNode* node);
};

#endif // TRIE_H
