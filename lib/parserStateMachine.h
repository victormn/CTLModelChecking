#ifndef PARSERSM_H_
#define PARSERSM_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdio>
#include <cstdlib>

using namespace std;

/***
	Struct of the state machine's nodes
***/
typedef struct graphNode_s {
	int id;
	vector<int> next;
	map<string, bool> properties;
	map<string, bool> nodes;
} graphNode_t;

vector<graphNode_t> readStateMachine();

#endif