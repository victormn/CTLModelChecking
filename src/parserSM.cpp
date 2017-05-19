#include <iostream>
#include <string>
#include <vector>

using namespace std;

/***
	Struct of the tree's nodes
***/
typedef struct treeNode_s {
	string id;
	string content;
	string operation;
	struct treeNode_s *left;
	struct treeNode_s *right;
} treeNode_t;

/***
	Struct of the state machine's nodes
***/
typedef struct graphNode_s {
	int id;
	vector<string> properties;
	vector<string> nodes;
	vector<int> next;
} graphNode_t;

/*** 
	Function to read the input
	output: the state machine
***/
vector<graphNode_t> readInput() {

	graphNode_t g;
	vector<graphNode_t> v;
	int N;
	int quant;
	string prop;
	int state;
	graphNode_t node;

	cin >> N;
	v.resize(N);

	while(N--) {
		cin >> g.id;
		cin >> quant;

		while(quant--) {
			cin >> prop;
			g.properties.push_back(prop);
		}
		cin >> quant;

		while (quant--) {
			cin >> state;
			g.next.push_back(state - 1);
		}
		v[g.id - 1] = g;

		g.properties.clear();
		g.next.clear();
	}

	return v;
}

/***
	Function to print the state machine
	input: state machine
***/
void printGraph (vector<graphNode_t> &graph) {

	for (int i = 0; i < (int)graph.size(); ++i) {
		cout << graph[i].id - 1 << '\n';

		cout << "Properties: \n";
		for (int j = 0; j < (int)graph[i].properties.size(); ++j) {
			cout << graph[i].properties[j] << " ";
		}
		cout << "\n";

		cout << "States: \n";
		for (int j = 0; j < (int)graph[i].next.size(); ++j) {
			cout << graph[i].next[j] << " ";
		}
		cout << "\n";

		cout << "Nodes: \n";
		for (int j = 0; j < (int)graph[i].nodes.size(); ++j) {
			cout << graph[i].nodes[j] << " ";
		}
		cout << "\n\n";
	}
}


int main(int argc, char const *argv[]) {

	vector<graphNode_t> graph;

	graph = readInput();

	//printGraph(graph);

	opAdd(graph, "S");
	opAdd(graph, "C");
	opAdd(graph, "H");
	opAdd(graph, "E");
	//opAnd(graph, "S", "E", "(S & E)");
	//opOr(graph, "S", "E", "(S | E)");
	//opNot(graph, "S", "(!S)");
	//opNot(graph, "(S & E)", "(!(S & E))");
	//opEX(graph, "S", "(EX(S))");
	//opEU(graph, "C", "H", "EU(C, H)");
	opEU(graph, "E", "S", "EU(E, S)");
	printGraph(graph);

	return 0;
}