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
	strint operation;
	struct treeNode_s *left;
	struct treeNode_s *right;
} treeNode_t;

/***
	Struct of the state machine's nodes
***/
typedef struct graphNode_s {
	int id;
	vector<string> proprieties;
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

	while(N--) {
		cin >> g.id;
		cin >> quant;

		while(quant--) {
			cin >> prop;
			g.proprieties.push_back(prop);
		}
		cin >> quant;

		while (quant--) {
			cin >> state;
			g.next.push_back(state);
		}
		v.push_back(g);

		g.proprieties.clear();
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

		cout << "Proprieties: \n";
		for (int j = 0; j < (int)graph[i].proprieties.size(); ++j) {
			cout << graph[i].proprieties[j] << " ";
		}
		cout << "\n";

		cout << "States: \n";
		for (int j = 0; j < (int)graph[i].next.size(); ++j) {
			cout << graph[i].next[j] << " ";

		}
		cout << "\n\n\n";
	}
}

int main(int argc, char const *argv[]) {

	vector<graphNode_t> graph;

	graph = readInput();

	printGraph(graph);


	return 0;
}