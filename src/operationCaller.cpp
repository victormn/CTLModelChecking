#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

typedef struct treeNode_s {
	string content;
	string type;
	string op;	
	struct treeNode_s *left;
	struct treeNode_s *right;
} treeNode_t;

void callOperation(treeNode_t *node, vector<graphNode_t> &graph){

	stack<treeNode_t> origNodes;
    origNodes.push(node);
 
    stack<treeNode_t> postNodes; 
    treeNode_t aux;
   
    while (!origNodes.empty())
    {
        Node *current = origNodes.top();
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
		    switch(aux->op){
				case 'EX':
					opEX(&graph, aux->left, aux->content);
				case 'AF':
					opAF(&graph, aux->left, aux->content);
				case 'EU':
					opEU(&graph, aux->left, aux->right, aux->content);
				case '!':
					opNot(&graph, aux->left, aux->content);						
				case '&':
					opAnd(&graph, aux->left, aux->right, aux->content);
				case '|':
					opOr(&graph, aux->left, aux->right, aux->content);

				default:
					printf("Error while calling the algorithms!");
			}
		}
		else{
			opAdd(&graph, aux->content);
		}	

	    postNodes.pop();    	
    }	
}








