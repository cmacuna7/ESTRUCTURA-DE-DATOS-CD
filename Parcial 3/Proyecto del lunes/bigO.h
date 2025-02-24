#ifndef BIGO_H
#define BIGO_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string readFile(const string& filename);
string extractFunctionName(const string& code);
bool containsNextPermutationLoop(const string& code);
bool hasTwoRecursiveCalls(const string& code, const string& funcName);
int countForLoops(const string& code);
bool containsStdSort(const string& code);
bool hasLoop(const string& code);
bool isRecursive(const string& code, const string& funcName);
bool hasLogNRecursion(const string& code, const string& funcName);
string determineBigO(const string& code);

#endif
