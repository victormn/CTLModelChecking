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
	vector<string> properties;
	vector<string> nodes;
	vector<int> next;
} graphNode_t;

/***
	Function to add a property from the tree on the graph
	input: graph and the property
***/
void opAdd (vector<graphNode_t> graph, string value) {

	for (int i = 0; i < (int)graph.size(); ++i) {
		for (int j = 0; j < (int)graph[i].properties.size(); ++j) {
			if(graph[i].properties[j] == value) {
				graph[i].nodes.push_back(value);
			}
		}
	}
}

/***
	Function to add a property of a & b oh the graph
	input: graph, a, b, and the property (a & b)
***/
void opAnd (vector<graphNode_t> &graph, string a, string b, string value) {

	bool hasA = false;
	bool hasB = false;
	
	for (int i = 0; i < (int)graph.size(); ++i) {
		for (int j = 0; j < (int)graph[i].properties.size(); ++j) {
			if (graph[i].properties[j] == a) {
				hasA = true;
			}
			
			if (graph[i].properties[j] == b) {
				hasB = true;
			}

			if (hasA && hasB) {
				graph[i].nodes.push_back(value);
				return;
			}
		}
	}
}