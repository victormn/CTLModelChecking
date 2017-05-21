#ifndef PARSEREXPRESSION_H_
#define PARSEREXPRESSION_H_

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

/***
	Struct of the expression tree's nodes
***/
typedef struct treeNode_s {
	string content;
	string type;
	string op;
	struct treeNode_s *left;
	struct treeNode_s *right;
} treeNode_t;

treeNode_t* parserCtlExpression(string content);
void cleanTree(treeNode_t *node);

#endif