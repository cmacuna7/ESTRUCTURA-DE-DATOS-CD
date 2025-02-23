#include "bigO.h"
#include <algorithm>
#include <cstring>

string readFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        exit(1);
    }
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

string extractFunctionName(const string& code) {
    size_t pos = code.find("Calculadora::");
    if (pos == string::npos) {
        cerr << "No se encontró la función en la clase Calculadora." << endl;
        exit(1);
    }
    pos += strlen("Calculadora::");
    size_t end = code.find('(', pos);
    if (end == string::npos) {
        cerr << "Formato de función incorrecto." << endl;
        exit(1);
    }
    return code.substr(pos, end - pos);
}

bool containsNextPermutationLoop(const string& code) {
    size_t do_pos = code.find("do");
    if (do_pos == string::npos) return false;
    size_t next_perm_pos = code.find("next_permutation", do_pos);
    return next_perm_pos != string::npos;
}

bool hasTwoRecursiveCalls(const string& code, const string& funcName) {
    size_t pos = 0;
    while (true) {
        pos = code.find("return", pos);
        if (pos == string::npos) break;
        size_t line_end = code.find(';', pos);
        if (line_end == string::npos) break;
        string line = code.substr(pos, line_end - pos);
        size_t count = 0;
        size_t func_pos = 0;
        while ((func_pos = line.find(funcName, func_pos)) != string::npos) {
            count++;
            func_pos += funcName.length();
        }
        if (count >= 2) return true;
        pos = line_end + 1;
    }
    return false;
}

int countForLoops(const string& code) {
    int count = 0;
    size_t pos = 0;
    while ((pos = code.find("for", pos)) != string::npos) {
        count++;
        pos += 3;
    }
    return count;
}

bool containsStdSort(const string& code) {
    return code.find("std::sort") != string::npos;
}

bool hasLoop(const string& code) {
    return (code.find("for") != string::npos) || (code.find("while") != string::npos);
}

bool isRecursive(const string& code, const string& funcName) {
    return code.find(funcName + "(") != string::npos;
}

bool hasLogNRecursion(const string& code, const string& funcName) {
    size_t pos = code.find(funcName + "(");
    while (pos != string::npos) {
        size_t end = code.find(')', pos);
        if (end == string::npos) break;
        string args = code.substr(pos + funcName.length() + 1, end - (pos + funcName.length() + 1));
        if (args.find("/2") != string::npos || args.find(">>1") != string::npos) {
            return true;
        }
        pos = code.find(funcName + "(", end);
    }
    return false;
}

string determineBigO(const string& code) {
    string funcName = extractFunctionName(code);
    
    if (containsNextPermutationLoop(code)) {
        return "O(n!)";
    }
    
    if (isRecursive(code, funcName) && hasTwoRecursiveCalls(code, funcName)) {
        return "O(2^n)";
    }
    
    int forLoops = countForLoops(code);
    if (forLoops >= 2) {
        return "O(n^2)";
    }
    
    if (containsStdSort(code)) {
        return "O(n log n)";
    }
    
    if (hasLoop(code)) {
        return "O(n)";
    }
    
    if (isRecursive(code, funcName) && hasLogNRecursion(code, funcName)) {
        return "O(log n)";
    }
    
    return "O(1)";
}
