#include <parserExpression.h>
#include <parserSM.h>
#include <operationCaller.h>

using namespace std;

/***
	Function to print the expression tree
	input: expression tree
***/
void printTree(treeNode_t *node){
	if(node == NULL) return;
	cout << node->content << " " << node->op << "\n";
	printTree(node->left);
	printTree(node->right);
}

/***
	Function to print the state machine
	input: state machine
***/
void printGraph (vector<graphNode_t> &graph) {

	for (int i = 0; i < (int)graph.size(); ++i) {
		cout << graph[i].id << '\n';
/*
		cout << "Properties: \n";
		for (map<string, bool>::iterator it = graph[i].properties.begin(); it != graph[i].properties.end(); ++it) {
			cout << it->first << " ";
		}
		cout << "\n";

		cout << "States: \n";
		for (int j = 0; j < (int)graph[i].next.size(); ++j) {
			cout << graph[i].next[j]+1 << " ";
		}
		cout << "\n";*/

		cout << "Nodes: \n";
		for (map<string, bool>::iterator it = graph[i].nodes.begin(); it != graph[i].nodes.end(); ++it) {
			cout << it->first << " ";
		}
		cout << "\n\n";
	}
}

void printResult(vector<graphNode_t> &graph, string expression, string initialExpression){
	
	cout << "Expression: " << initialExpression << "\n";
	cout << "State Machine: ";

	for (int i = 0; i < (int)graph.size(); ++i) {
		if(graph[i].nodes.count(expression)){
			cout << graph[i].id << ' ';
		}
	}
	cout << "\n";
}

int main(){

	vector<graphNode_t> statemachine;
	treeNode_t *ctlNode = new treeNode_t();

	statemachine = readSM();

	string expression;
	cin >> expression;
	ctlNode = parserCtlExpression(expression);

	callOperation(ctlNode, statemachine);
	printResult(statemachine, ctlNode->content ,expression);

	/*	TREE TEST

	treeNode_t *node = (treeNode_t*) malloc (sizeof(treeNode_t));
	node = parserCtlExpression("(AX(!(((a)|(b))&((c)&(d)))))");

	if(node != NULL) {
		printTree(node);
	}*/

	// --------------------------------------------------------------

	/*	GRAPH TEST

	vector<graphNode_t> graph;

	graph = readSM();


	cout << "\n\n\n\n";

	// opAdd(graph, "S");
	// opAdd(graph, "C");
	// opAdd(graph, "H");
	// opAdd(graph, "E");
	// opAnd(graph, "S", "E", "(S & E)");
	// opAnd(graph, "S", "C", "(S & C)");
	// opOr(graph, "S", "E", "(S | E)");
	// opOr(graph, "S", "C", "(S | C)");
	// opNot(graph, "S", "(!S)");
	// opNot(graph, "(S & E)", "(!(S & E))");
	// opEX(graph, "S", "(EX(S))");
	// opEX(graph, "E", "(EX(E))");
	// opEU(graph, "C", "H", "EU(C, H)");
	// opEU(graph, "E", "S", "EU(E, S)");
	// opAF(graph, "H", "AF(H)");
	// opAF(graph, "C", "AF(C)");
	printGraph(graph);
	*/

	return 0;
}