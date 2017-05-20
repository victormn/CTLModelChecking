#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdio>

#include <parserSM.h>

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
			g.properties[prop] = true;
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
		cout << graph[i].id << '\n';

		cout << "Properties: \n";
		for (map<string, bool>::iterator it = graph[i].properties.begin(); it != graph[i].properties.end(); ++it) {
			cout << it->first << " ";
		}
		cout << "\n";

		cout << "States: \n";
		for (int j = 0; j < (int)graph[i].next.size(); ++j) {
			cout << graph[i].next[j]+1 << " ";
		}
		cout << "\n";

		cout << "Nodes: \n";
		for (map<string, bool>::iterator it = graph[i].nodes.begin(); it != graph[i].nodes.end(); ++it) {
			cout << it->first << " ";
		}
		cout << "\n\n";
	}
}


// int main(int argc, char const *argv[]) {

// 	vector<graphNode_t> graph;

// 	graph = readInput();

// 	printGraph(graph);

// 	cout << "\n\n\n\n";


// 	// opAdd(graph, "S");
// 	// opAdd(graph, "C");
// 	// opAdd(graph, "H");
// 	// opAdd(graph, "E");
// 	// opAnd(graph, "S", "E", "(S & E)");
// 	// opAnd(graph, "S", "C", "(S & C)");
// 	// opOr(graph, "S", "E", "(S | E)");
// 	// opOr(graph, "S", "C", "(S | C)");
// 	// opNot(graph, "S", "(!S)");
// 	// opNot(graph, "(S & E)", "(!(S & E))");
// 	// opEX(graph, "S", "(EX(S))");
// 	// opEX(graph, "E", "(EX(E))");
// 	// opEU(graph, "C", "H", "EU(C, H)");
// 	// opEU(graph, "E", "S", "EU(E, S)");
// 	// opAF(graph, "H", "AF(H)");
// 	// opAF(graph, "C", "AF(C)");
// 	printGraph(graph);

// 	return 0;
// }