#ifndef ALGORITHMS_H_
#define ALGORITHMS_H_

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void opAdd (vector<graphNode_t> &graph, string value);

void opAnd (vector<graphNode_t> &graph, string a, string b, string value);

void opOr (vector<graphNode_t> &graph, string a, string b, string value);

void opNot (vector<graphNode_t> &graph, string a, string value);

void opEX (vector<graphNode_t> &graph, string a, string value);

void opEU (vector<graphNode_t> &graph, string a, string b, string value);

void opAF (vector<graphNode_t> &graph, string a, string value);

#endif