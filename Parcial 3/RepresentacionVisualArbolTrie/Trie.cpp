#include "Trie.h"

Trie::Trie() {
    root = new TrieNode();
}

void Trie::insert(const std::wstring &word) {
    TrieNode* node = root;
    for (wchar_t ch : word) {
        if (node->children.find(ch) == node->children.end()) {
            node->children[ch] = new TrieNode();
        }
        node = node->children[ch];
    }
    node->isEndOfWord = true;
}

void Trie::display() {
    std::wcout << L"Root" << std::endl;
    displayHelper(root, L"", 0);
}

void Trie::showTraversal() {
    std::wcout << L"\nRecorrido del trie:\n";
    showTraversalHelper(root, L"");
}

int Trie::getHeight() {
    return getHeightHelper(root);
}

int Trie::getDepth(const std::wstring &word) {
    TrieNode* node = root;
    int depth = 0;
    for (wchar_t ch : word) {
        if (node->children.find(ch) == node->children.end()) {
            return -1; // Palabra no encontrada
        }
        node = node->children[ch];
        depth++;
    }
    return depth;
}

int Trie::getLevel(const std::wstring &word) {
    return getDepth(word);
}

void Trie::displayHelper(TrieNode* node, std::wstring prefix, int level) {
    if (node->isEndOfWord) {
        std::wcout << std::wstring(level * 2, L' ') << prefix << L" (end)" << std::endl;
    }
    for (auto it = node->children.begin(); it != node->children.end(); ++it) {
        std::wcout << std::wstring(level * 2, L' ') << L"|-- " << it->first;
        if (std::next(it) == node->children.end() && it->second->isEndOfWord) {
            std::wcout << L" (end)" << std::endl;
        } else {
            std::wcout << std::endl;
        }
        displayHelper(it->second, prefix + it->first, level + 1);
    }
}

void Trie::showTraversalHelper(TrieNode* node, std::wstring prefix) {
    if (node->isEndOfWord) {
        std::wcout << prefix << L" (end)" << std::endl;
    }
    for (auto &child : node->children) {
        std::wcout << prefix << L" -> " << child.first << std::endl;
        showTraversalHelper(child.second, prefix + child.first);
    }
}

int Trie::getHeightHelper(TrieNode* node) {
    if (node == nullptr) {
        return 0;
    }
    int maxHeight = 0;
    for (auto &child : node->children) {
        maxHeight = std::max(maxHeight, getHeightHelper(child.second));
    }
    return maxHeight + 1;
}
