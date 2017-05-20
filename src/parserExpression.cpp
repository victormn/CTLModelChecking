#include <parserExpression.h>
#include <cstdio>

using namespace std;

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
	while(expression[pos] != '('){
		result += expression[pos];
		pos++;
	}
	return result;
}

bool isFunction(string expression, int pos) {
	while(expression[pos] != '('){
		if (expression[pos] == ')') 
			return false;
		pos++;
	}
	return true;
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

string ax2ex(string p){
	string result = "(!(EX(!";
	result += p;
	result += ")))"; 
	return result;
}

string ef2eu(string p){
	string result = "(EU((TRUE),";
	result += p;
	result += "))"; 
	return result;
}

string ag2eu(string p){
	string result = "(!(EU((TRUE),(!";
	result += p;
	result += "))))"; 
	return result;
}

string eg2af(string p){
	string result = "(!(AF(!";
	result += p;
	result += ")))"; 
	return result;
}

string au2afeu(string left, string right){
	string result = "((AF";
	result += right;
	result += ")&(!(EU((!"; 
	result += left;
	result += "),((!"; 	
	result += left;
	result += ")&(!"; 	
	result += right;
	result += "))))))"; 
	return result;
}

string impl2or(string left, string right){
	string result = "((!";
	result += left;
	result += ")|";
	result += right;
	result += ")";
	return result;
}

string if2and(string left, string right){
	string result = "(((!";
	result += left;
	result += ")|";
	result += right;
	result += ")&((!";
	result += right;
	result += ")|";
	result += left;
	result += "))";
	return result;
}

string removeParenthesisInLeaf(string leaf){
	string result = "";
	for(int i = 1; i < (int)leaf.length()-1; ++i){
		result += leaf[i];
	}
	return result;
}

treeNode_t* parserCtlExpression(string expression) {
	string left, right;

	treeNode_t *node = new treeNode_t();
	
	int posFunc = findFunction(expression);
	if (posFunc == -1){
		node->content = removeParenthesisInLeaf(expression);
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

		expression = ax2ex(left);
		function = "!";
		posFunc = 1;
	} 
	else if(function == "EF"){
		posFunc += 2;
		left = getProp(expression, posFunc);

		expression = ef2eu(left);
		function = "EU";
		posFunc = 1;
	}
	else if(function == "AG"){
		posFunc += 2;
		left = getProp(expression, posFunc);

		expression = ag2eu(left);
		function = "!";
		posFunc = 1;
	}
	else if(function == "EG"){
		posFunc += 2;
		left = getProp(expression, posFunc);

		expression = eg2af(left);
		function = "!";
		posFunc = 1;
	}
	else if(function == "AU"){
		posFunc += 2;
		string child = getProp(expression, posFunc);

		int posColon = findFunction(child);
		left = getProp(child, 1);
		right = getProp(child, ++posColon);

		expression = au2afeu(left, right);
		function = "&";
		posFunc = findFunction(expression);
	}
	else if(function == "->"){
		posFunc += 2;
		left = getProp(expression, 1);
		right = getProp(expression, posFunc);

		expression = impl2or(left, right);
		function = "|";
		posFunc = findFunction(expression);
	}
	else if(function == "<->"){
		posFunc += 3;
		left = getProp(expression, 1);
		right = getProp(expression, posFunc);

		expression = if2and(left, right);
		function = "&";
		posFunc = findFunction(expression);
	}

	if(function == "EX"){
		posFunc += 2;
		left = getProp(expression, posFunc);

		node->content = expression;
		node->type = "function";
		node->op = function;
		node->left = parserCtlExpression(left);
		node->right = NULL;
	}
	else if(function == "AF"){
		posFunc += 2;
		left = getProp(expression, posFunc);

		node->content = expression;
		node->type = "function";	
		node->op = function;
		node->left = parserCtlExpression(left);
		node->right = NULL;
	}
	else if(function == "EU"){
		posFunc += 2;
		string child = getProp(expression, posFunc);

		int posColon = findFunction(child);
		left = getProp(child, 1);
		right = getProp(child, ++posColon);

		node->content = expression;
		node->type = "function";
		node->op = function;
		node->left = parserCtlExpression(left);
		node->right = parserCtlExpression(right);
	}
	else if(function == "&"){
		left = getProp(expression, 1);
		right = getProp(expression, ++posFunc);

		node->content = expression;
		node->type = "function";
		node->op = function;
		node->left = parserCtlExpression(left);
		node->right = parserCtlExpression(right);
	}
	else if(function == "|"){
		left = getProp(expression, 1);
		right = getProp(expression, ++posFunc);

		node->content = expression;
		node->type = "function";
		node->op = function;
		node->left = parserCtlExpression(left);
		node->right = parserCtlExpression(right);
	}
	else if(function == "!"){
		left = getProp(expression, ++posFunc);

		node->content = expression;
		node->type = "function";
		node->op = function;
		node->left = parserCtlExpression(left);
		node->right = NULL;
	}
	else {
		cout << "Invalid function: " << function << "\n";
		return NULL;
	}

	return node;
}