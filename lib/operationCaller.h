#ifndef OPCALLER_H_
#define OPCALLER_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <stack>

#include <parserExpression.h>
#include <parserSM.h>

using namespace std;

void callOperation(treeNode_t *node, vector<graphNode_t> &graph);

#endif