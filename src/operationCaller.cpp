#include <operationCaller.h>

using namespace std;

/***
	Function to add a property from the tree on the graph
	input: graph and the property
***/
void opAdd (vector<graphNode_t> &graph, string value) {

	for (int i = 0; i < (int)graph.size(); ++i) {
		if(graph[i].properties.count(value)) {
			graph[i].nodes[value] = true;
		}
	}
}

/***
	Function to add a property of a & b oh the graph
	input: graph, a, b, and the property (a & b)
***/
void opAnd (vector<graphNode_t> &graph, string a, string b, string value) {
	
	for (int i = 0; i < (int)graph.size(); ++i) {
		if (graph[i].nodes.count(a) && graph[i].nodes.count(b)) {
			graph[i].nodes[value] = true;
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
			if (graph[i].nodes.count(a) || graph[i].nodes.count(b)) {
				graph[i].nodes[value] = true;
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

	for (int i = 0; i < (int)graph.size(); ++i) {
		if (graph[i].nodes.count(a) == 0) {
			graph[i].nodes[value] = true;
		}
	}
}

/*** Function to add a property of EX(a) on the graph
	input: graph, a and the property EX(a)

	Search for nodes that have a next node with the property a 
		and insert the property value on these nodes
***/
void opEX (vector<graphNode_t> &graph, string a, string value) {

	for (int i = 0; i < (int)graph.size(); ++i) {
		if (graph[i].nodes.count(value) == 0) {
			for (int j = 0; j < (int)graph[i].next.size(); ++j) {
				if (graph[graph[i].next[j]].nodes.count(a)) {
					graph[i].nodes[value] = true;
					break;
				}
			}
		}
	}
}

/***
	Function to add a property of EU(a, b) oh the graph
	input: graph, a, b and the property EU(a, b)

	Search for nodes that has the property b 
		and insert the property value on these nodes

	Then search for nodes that have the property a and a next node with the property value
		and insert the property value on these nodes, recursively
***/
void opEU (vector<graphNode_t> &graph, string a, string b, string value) {

	for (int i = 0; i < (int)graph.size(); ++i) {
		if (graph[i].nodes.count(b)) {
			graph[i].nodes[value] = true;
		}
	}

	bool hasChanged = true;
	while (hasChanged) {
		hasChanged = false;
		for (int i = 0; i < (int)graph.size(); ++i) {
			if ((graph[i].nodes.count(a) || a == "TRUE") && !graph[i].nodes.count(value)) {
				for (int j = 0; j < (int)graph[i].next.size(); ++j) {
					if (graph[graph[i].next[j]].nodes.count(value)) {
						graph[i].nodes[value] = true;
						hasChanged = true;
						break;
					}
				}
			}
		}
	}
}


/***
	Function to add a property of AF(a) oh the graph
	input: graph, a and the property AF(a)

	Search for nodes that has the property a 
		and insert the property value on these nodes

	Then search for nodes that have all the nexts nodes with the property value
		and insert the property value on these nodes, recursively
***/
void opAF (vector<graphNode_t> &graph, string a, string value) {

	for (int i = 0; i < (int)graph.size(); ++i) {
		if (graph[i].nodes.count(a)) {
			graph[i].nodes[value] = true;
		}
	}

	bool hasChanged = true;
	bool allNextHave;
	while (hasChanged) {
		hasChanged = false;
		for (int i = 0; i < (int)graph.size(); ++i) {
			if (!graph[i].nodes.count(value)) {
				allNextHave = true;
				for (int j = 0; j < (int)graph[i].next.size(); ++j) {
					if (!graph[graph[i].next[j]].nodes.count(value)) {
						allNextHave = false;
						break;
					}
				}
				if (allNextHave && graph[i].next.size() != 0) {
					graph[i].nodes[value] = true;
					hasChanged = true;
				}
			}
		}
	}
}

void callOperation(treeNode_t *node, vector<graphNode_t> &graph){

	stack<treeNode_t*> origNodes;
    origNodes.push(node);
 
    stack<treeNode_t*> postNodes; 
    treeNode_t* aux;
   
    while (!origNodes.empty())
    {
        treeNode_t *current = origNodes.top();
        origNodes.pop();
 
        postNodes.push(current); 
        
        if (current->left)
            origNodes.push(current->left);
 
        if (current->right)
            origNodes.push(current->right);
    }
 
    while (!postNodes.empty())
    {		
	    aux = postNodes.top();  

		if(aux->type == "function"){

			if(aux->op == "EX"){
				opEX(graph, aux->left->content, aux->content);
			}
			else if(aux->op == "AF"){
				opAF(graph, aux->left->content, aux->content);
			}
			else if(aux->op == "EU"){
				opEU(graph, aux->left->content, aux->right->content, aux->content);
			}
			else if(aux->op == "!"){
				opNot(graph, aux->left->content, aux->content);
			}
			else if(aux->op == "&"){
				opAnd(graph, aux->left->content, aux->right->content, aux->content);
			}
			else if(aux->op == "|"){
				opOr(graph, aux->left->content, aux->right->content, aux->content);
			}
			else printf("Error while calling the algorithms!");

		}
		else{
			opAdd(graph, aux->content);
		}	

	    postNodes.pop();    	
    }	
}