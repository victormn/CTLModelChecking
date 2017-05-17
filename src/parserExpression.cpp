#include <iostream>
#include <string>

using namespace std;

string getProp(string expression, int pos) {
	string result = "";
	for(int i = pos; expression[i] != ')'; ++i){
		result += expression[i];
	}
	return result;
}

string getFunction(string expression, int pos){
	string result = "";
	if(expression[pos] == '&' || expression[pos] == '|' || expression[pos] == '!' || expression[pos] == ','){
		result += expression[pos];
	}
	else{
		result += expression[pos++];
		result += expression[pos];
	}
	return result;
}

bool isFunction(string expression, int pos) {

	if(expression[pos] == '&' || expression[pos] == '|' || expression[pos] == '!' || expression[pos] == ',')
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

void parserCtlExpression(string expression) {
	int parenthesisLevel = 0;
	
	for (int i = 0; i < (int)expression.length(); ++i) {
		if(expression[i] == '('){
			parenthesisLevel++;
		} else if(expression[i] == ')') {
			parenthesisLevel--;
		} else if(isFunction(expression, i)){
			cout << "function: " << getFunction(expression, i) << "\n";
			i++;
		} else {
			string prop = getProp(expression, i);
			i += prop.length();
			cout << "prop: " << prop << "\n";
		}
	}

}


int main(){

	parserCtlExpression("(!(EU(((abc),(a))&(def))))");

	return 0;
}