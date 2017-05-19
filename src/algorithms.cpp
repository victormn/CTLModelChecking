/***
	Function to add a property from the tree on the graph
	input: graph and the property
***/
void opAdd (vector<graphNode_t> &graph, string value) {

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

	bool hasA;
	bool hasB;
	
	for (int i = 0; i < (int)graph.size(); ++i) {
		hasA = false;
		hasB = false;
		for (int j = 0; j < (int)graph[i].nodes.size(); ++j) {
			if (graph[i].nodes[j] == a) {
				hasA = true;
			}
			
			if (graph[i].nodes[j] == b) {
				hasB = true;
			}

			if (hasA && hasB) {
				graph[i].nodes.push_back(value);
				break;
			}
		}
	}
}

/***
	Function to add a property of a | b on the graph
	input: graph, a, b and the property (a | b)
***/
void opOr (vector<graphNode_t> &graph, string a, string b, string value) {

	for (int i = 0; i < (int)graph.size(); ++i) {
		for (int j = 0; j < (int)graph[i].nodes.size(); ++j) {
			if (graph[i].nodes[j] == a || graph[i].nodes[j] == b) {
				graph[i].nodes.push_back(value);
				break;
			}
		}
	}
}

/***
	Function to add a property of !a on the graph
	input: graph, a and the property !a
***/
void opNot (vector<graphNode_t> &graph, string a, string value) {

	bool hasA;
	for (int i = 0; i < (int)graph.size(); ++i) {
		hasA = false;
		for (int j = 0; j < (int)graph[i].nodes.size(); ++j) {
			if (graph[i].nodes[j] == a) {
				hasA = true;
				break;
			}
		}

		if (!hasA) {
			graph[i].nodes.push_back(value);
		}
	}
}

/*** Function to add a property of EX(a) on the graph
	input: graph, a and the property EX(a)

	Search for nodes that have a next node with the property a 
		and insert the property value on these nodes
***/
void opEX (vector<graphNode_t> &graph, string a, string value) {

	bool hasA;
	for (int i = 0; i < (int)graph.size(); ++i) {
		hasA = false;
		for (int j = 0; j < (int)graph[i].next.size(); ++j) {
			for (int k = 0; k < (int)graph[graph[i].next[j]].nodes.size(); ++k) {
				if (graph[graph[i].next[j]].nodes[k] == a) {
					graph[i].nodes.push_back(value);
					hasA = true;
					break;
				}
			}
			if (hasA) {
				break;
			}
		}
	}
}


/***
	Function to verify if a graphNode_t has a property a
	input: graphNode_t and the property a
	output: a boolean that represents if the node has the property
***/
bool hasProp (graphNode_t &node, string a) {

	for (int i = 0; i < (int)node.nodes.size(); ++i) {
		if (node.nodes[i] == a) {
			return true;
		}
	}
	return false;
}

/***
	Function to add a property of EU(a, b) oh the graph
	input: graph, a, b and the property EU(a, b)

	Search for nodes that has the property b 
		and insert the property value on these nodes

	Then search for nodes that have a next node with the property value
		and insert the property value on these nodes recursively
***/
void opEU(vector<graphNode_t> &graph, string a, string b, string value) {

	for (int i = 0; i < (int)graph.size(); ++i) {
		for (int j = 0; j < (int)graph[i].nodes.size(); ++j) {
			if (graph[i].nodes[j] == b) {
				graph[i].nodes.push_back(value);
				break;
			}
		}
	}


	bool hasChanged = true;
	bool alreadyHasValue;
	while (hasChanged) {
		hasChanged = false;
		for (int i = 0; i < (int)graph.size(); ++i) {
			alreadyHasValue = false;
			// Verify if the node has the property a and if it don't the property value yet
			if (hasProp(graph[i], a) && graph[i].nodes.size() != 0 && graph[i].nodes[graph[i].nodes.size() - 1] != value) {
				for (int j = 0; j < (int)graph[i].next.size(); ++j) {
					for (int k = 0; k < (int)graph[graph[i].next[j]].nodes.size(); ++k) {
						if (graph[graph[i].next[j]].nodes[k] == value) {
							graph[i].nodes.push_back(value);
							hasChanged = true;
							alreadyHasValue = true;
							break;
						}
					}

					if (alreadyHasValue) {
						break;
					}
				}
			}
		}
	}
}