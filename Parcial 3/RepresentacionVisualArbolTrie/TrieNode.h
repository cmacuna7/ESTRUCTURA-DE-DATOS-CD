#ifndef TRIENODE_H
#define TRIENODE_H

#include <map>

struct TrieNode {
    std::map<wchar_t, TrieNode*> children;
    bool isEndOfWord;
    
    TrieNode() : isEndOfWord(false) {}
};

#endif // TRIENODE_H
