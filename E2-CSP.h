#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

const string rInfo[] = { "=", "!=", "<=", "<", ">=", ">", "Sum = value", "??", "Sum = var", "Sum < value" };

class CSP {
public:
	int nbVars;
	int nbConstraints;

	vector<vector<int> > vars;
	vector<vector<int> > constraints;
	map<int, vector<vector<int> >> varConstraints;

	int totalNodes;
	int branchesIgnorees;
	clock_t start;
	double duration;

	bool sortOrder(int x, int y);
	bool isIn(map<int, int> &affectation, vector<int> &v);
	int isValid(map<int, int> &affectation);
	vector<vector<int> >& domainReduction(vector<vector<int> > &doms, int x, int value);

	void computeVarConstraints();

	map<int, int>* solve();
	map<int, int>* solve2();

	void displayDebug();
	void displayStats();
};

class Node {
public:
	map<int, int>* assigned;
	vector<vector<int> > domains;

	Node(vector<vector<int> > p);
	Node(Node* n);

	~Node();
};