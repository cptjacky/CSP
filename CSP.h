#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;


class CSP {
public:
    int nbVars;
    int nbConstraints;

    vector<vector<int> > vars;
    vector<vector<int> > constraints;

	bool isIn(map<int, int> &affectation, vector<int> &v);

	vector<vector<int> > domainReduction(map<int, int>* af);
    int isValid(map<int, int> &affectation);

    map<int, int>* solve();
	map<int, int>* solve2();



	void displayDebug();
};