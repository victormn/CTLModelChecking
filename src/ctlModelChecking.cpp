#include <iostream>

#include <parserExpression.h>
#include <parserSM.h>

using namespace std;

// Just for debug
void printTree(treeNode_t *node){
	if(node == NULL) return;
	cout << node->content << " " << node->op << "\n";
	printTree(node->left);
	printTree(node->right);
}

int main(){

	treeNode_t *node = (treeNode_t*) malloc (sizeof(treeNode_t));
	node = parserCtlExpression("(AX(!(((a)|(b))&((c)&(d)))))");
	printTree(node);

	return 0;
}