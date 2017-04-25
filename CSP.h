#include <map>

using namespace std;

bool isIn(map<int, int> &affectation, vector<int> v);

class CSP {
public:
    int nbVars;
    int nbConstraints;

    vector<vector<int> > vars;
    vector<vector<int> > constraints;

    int isValid(map<int, int> &affectation);

    map<int, int>* solve();
};
