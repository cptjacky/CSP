#include "Tree.h"

const string rInfo[] = { "=", "!=", "<=", "<", ">=", ">", "Sum = value", "??", "Sum = var", "Sum < value" };

class PSC {
public:

    int nbVar;                          // Les variables vont de 1 à nbVar;
    vector<vector<int>> domVars;        // domVars.size = nbVar;
    vector<vector<int>> restrictions;

    Tree* t;

    void displayDebug();
	bool isValid(vector<int> v);

	//Tree* trivialTree(int i, int j);
	
	void trivialTree(Tree* b);
	vector<int> trivialSolve(Tree* b, vector<int> values);
};
