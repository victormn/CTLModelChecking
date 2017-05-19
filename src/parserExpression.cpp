#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

typedef struct treeNode_s {
	string id;
	string content;
	string type;
	string op;
	struct treeNode_s *left;
	struct treeNode_s *right;
} treeNode_t;

bool isLogicalOperator(char c){
	if(
		c == '&' ||
		c == '|' ||
		c == '!' ||
		c == ',' ||
		c == '<' ||
		c == '-'
	) return true;

	return false;
}

string getProp(string expression, int pos) {
	string result = "(";
	int level = 1;
	for(int i = pos+1; level != 0; ++i){
		result += expression[i];
		if(expression[i] == '(') level++;
		if(expression[i] == ')') level--;
	}
	return result;
}

string getFunction(string expression, int pos){
	string result = "";
	if(isLogicalOperator(expression[pos])){
		result += expression[pos];
		if(expression[pos] == '-') {
			result += expression[++pos];
		}
		else if(expression[pos] == '<') {
			result += expression[++pos];
			result += expression[++pos];
		}
	} else {
		result += expression[pos];
		result += expression[++pos];
	}
	return result;
}

bool isFunction(string expression, int pos) {
	if(isLogicalOperator(expression[pos]))
		return true;

	if(expression[pos] != 'A' && expression[pos] != 'E')
		return false;

	switch(expression[++pos]){
		case 'X':
		case 'F':
		case 'G':
		case 'U':
			if(expression[++pos] == '(')
				return true;
			else return false;
		default:
			return false;
	}
}

int findFunction(string expression){
	int level = 0;
	for (int i = 0; i < (int)expression.length(); ++i) {
		if(expression[i] == '(') level++;
		else if(expression[i] == ')') level--;
		else if(level == 1 && isFunction(expression, i)) return i;
	}
	return -1;
}

treeNode_t* parserCtlExpression(string expression) {

	string left, right;

	treeNode_t *node = (treeNode_t*) malloc (sizeof(treeNode_t));

	int posFunc = findFunction(expression);
	if (posFunc == -1){
		node->id = expression;
		node->content = expression;
		node->type = "prop";
		node->op = "add";
		node->left = NULL;
		node->right = NULL;

		return node;
	}

	string function = getFunction(expression, posFunc);

	if(function == "AX"){
		posFunc += 2;
		left = getProp(expression, posFunc);

		node->id = expression;
		node->content = expression;
		node->type = "function";
		node->op = function;
		node->left = parserCtlExpression(left);
		node->right = NULL;
	}
	else if(function == "EX"){
		posFunc += 2;
		left = getProp(expression, posFunc);

		node->id = expression;
		node->content = expression;
		node->type = "function";
		node->op = function;
		node->left = parserCtlExpression(left);
		node->right = NULL;
	}
	else if(function == "AF"){
		posFunc += 2;
		left = getProp(expression, posFunc);

		node->id = expression;
		node->content = expression;
		node->type = "function";
		node->op = function;
		node->left = parserCtlExpression(left);
		node->right = NULL;
	}
	else if(function == "EF"){
		posFunc += 2;
		left = getProp(expression, posFunc);

		node->id = expression;
		node->content = expression;
		node->type = "function";
		node->op = function;
		node->left = parserCtlExpression(left);
		node->right = NULL;
	}
	else if(function == "AG"){
		posFunc += 2;
		left = getProp(expression, posFunc);

		node->id = expression;
		node->content = expression;
		node->type = "function";
		node->op = function;
		node->left = parserCtlExpression(left);
		node->right = NULL;
	}
	else if(function == "EG"){
		posFunc += 2;
		left = getProp(expression, posFunc);

		node->id = expression;
		node->content = expression;
		node->type = "function";
		node->op = function;
		node->left = parserCtlExpression(left);
		node->right = NULL;
	}
	else if(function == "AU"){
		posFunc += 2;
		string child = getProp(expression, posFunc);

		int posColon = findFunction(child);
		left = getProp(child, 1);
		right = getProp(child, ++posColon);

		node->id = expression;
		node->content = expression;
		node->type = "function";
		node->op = function;
		node->left = parserCtlExpression(left);
		node->right = parserCtlExpression(right);
	}
	else if(function == "EU"){
		posFunc += 2;
		string child = getProp(expression, posFunc);

		int posColon = findFunction(child);
		left = getProp(child, 1);
		right = getProp(child, ++posColon);

		node->id = expression;
		node->content = expression;
		node->type = "function";
		node->op = function;
		node->left = parserCtlExpression(left);
		node->right = parserCtlExpression(right);
	}
	else if(function == "&"){
		left = getProp(expression, 1);
		right = getProp(expression, ++posFunc);

		node->id = expression;
		node->content = expression;
		node->type = "function";
		node->op = function;
		node->left = parserCtlExpression(left);
		node->right = parserCtlExpression(right);
	}
	else if(function == "|"){
		left = getProp(expression, 1);
		right = getProp(expression, ++posFunc);

		node->id = expression;
		node->content = expression;
		node->type = "function";
		node->op = function;
		node->left = parserCtlExpression(left);
		node->right = parserCtlExpression(right);
	}
	else if(function == "!"){
		left = getProp(expression, ++posFunc);

		node->id = expression;
		node->content = expression;
		node->type = "function";
		node->op = function;
		node->left = parserCtlExpression(left);
		node->right = NULL;
	}
	else if(function == "->"){
		posFunc += 2;
		left = getProp(expression, 1);
		right = getProp(expression, posFunc);

		node->id = expression;
		node->content = expression;
		node->type = "function";
		node->op = function;
		node->left = parserCtlExpression(left);
		node->right = parserCtlExpression(right);
	}
	else if(function == "<->"){
		posFunc += 3;
		left = getProp(expression, 1);
		right = getProp(expression, posFunc);

		node->id = expression;
		node->content = expression;
		node->type = "function";
		node->op = function;
		node->left = parserCtlExpression(left);
		node->right = parserCtlExpression(right);
	}
	else cout << "error: Function " << function << " does not exists!\n";

	return node;

}

// Just for debug
void printTree(treeNode_t *node){
	if(node == NULL) return;
	cout << node->id << " " << node->op << "\n";
	printTree(node->left);
	printTree(node->right);
}

int main(){

	treeNode_t *node = (treeNode_t*) malloc (sizeof(treeNode_t));
	node = parserCtlExpression("(!(((a)|(b))&((c)&(d))))");
	printTree(node);

	return 0;
}