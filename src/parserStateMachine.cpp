#include <parserStateMachine.h>

using namespace std;

/*** 
	Function to read the input
	output: the state machine
***/
vector<graphNode_t> readStateMachine() {

	graphNode_t g;
	vector<graphNode_t> v;
	int N;
	int quant;
	string prop;
	int state;

	cin >> N;
	v.resize(N);

	while(N--) {
		cin >> g.id;

		if (g.id > v.size()) {
			cout << "Malformed state machine!\n";
			exit (EXIT_FAILURE);
		}
		cin >> quant;

		while(quant--) {
			cin >> prop;
			g.properties[prop] = true;
		}
		cin >> quant;

		while (quant--) {
			cin >> state;

			if (state > v.size()) {
				cout << "Malformed state machine!\n";
				exit (EXIT_FAILURE);
			}

			g.next.push_back(state - 1);
		}
		
		v[g.id - 1] = g;

		g.properties.clear();
		g.next.clear();
	}

	return v;
}
