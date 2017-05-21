#include <parserExpression.h>
#include <parserStateMachine.h>
#include <operationCaller.h>

using namespace std;

/***
	Function to print the result of the expression applied in the state machine
	input: state machine, expression modified, original expression
***/
void printResult(vector<graphNode_t> &graph, string expression, string initialExpression){
	
	cout << "Expression: " << initialExpression << "\n";
	cout << "States: ";

	for (int i = 0; i < (int)graph.size(); ++i) {
		if(graph[i].nodes.count(expression)){
			cout << graph[i].id << ' ';
		}
	}
	cout << "\n";
}

int main(){

	vector<graphNode_t> smGraphy;
	treeNode_t *ctlTree;

	smGraphy = readStateMachine();

	string expression;
	cin >> expression;
	ctlTree = parserCtlExpression(expression);

	callOperation(ctlTree, smGraphy);
	printResult(smGraphy, ctlTree->content, expression);

	cleanTree(ctlTree);

	return 0;
}