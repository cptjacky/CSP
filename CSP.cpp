#include "CSP.h"
/*
bool isIn(map<int, int> &affectation, vector<int> &v) {
    for (int i = 0; i < v.size(); i++) {
        if (!affectation.count(v[i])) return false;
    }
    return true;
}

int CSP::isValid(map<int, int> *affectation) {
    bool valid = true;
    int nValid = 0;

    for (int i = 0; i < constraints.size(); i++) {
        switch(constraints[i][0]) {    for( MyMap::const_iterator it = my_map.begin(); it != my_map.end(); ++it )
    {
      int key = it->first;
      string value = it->second;
    }
        case 1:
            if (isIn(affectation, vector<int>(constraints[i].begin() + 1, constraints[i].end()))) {
                valid = (affectation[constraints[i][1]] == affectation[constraints[i][2]]) && valid;
                nValid += valid;
            }
			break;
        case 2:
            if (isIn(affectation, vector<int>(constraints[i].begin() + 1, constraints[i].end()))) {
                valid = (affectation[constraints[i][1]] != affectation[constraints[i][2]]) && valid;
			    nValid += valid;
            }
			break;
		case 3:
		    if (isIn(affectation, vector<int>(constraints[i].begin() + 1, constraints[i].end()))) {
                valid = (affectation[constraints[i][1]] <= affectation[constraints[i][2]]) && valid;
			    nValid += valid;
            }
			break;
		case 4:
		    if (isIn(affectation, vector<int>(constraints[i].begin() + 1, constraints[i].end()))) {
                valid = (affectation[constraints[i][1]] < affectation[constraints[i][2]]) && valid;
			    nValid += valid;
            }
			break;
		case 5:
		    if (isIn(affectation, vector<int>(constraints[i].begin() + 1, constraints[i].end()))) {
                valid = (affectation[constraints[i][1]] >= affectation[constraints[i][2]]) && valid;
			    nValid += valid;
            }
			break;
		case 6:
		    if (isIn(affectation, vector<int>(constraints[i].begin() + 1, constraints[i].end()))) {
                valid = (affectation[constraints[i][1]] > affectation[constraints[i][2]]) && valid;
			    nValid += valid;
            }
			break;
		case 7:
		    if (isIn(affectation, vector<int>(constraints[i].begin() + 2, constraints[i].end()))) {
                int sum = 0;
                for (int p = 2; p < constraints[i].size(); p++)
                    sum += affectation[constraints[i][p]];
                valid = (sum == constraints[i][1]) && valid;
			    nValid += valid;
            }
			break;
		case 8:
            valid = valid;
            // TODO;
			break;
		case 9:
		    if (isIn(affectation, vector<int>(constraints[i].begin() + 1, constraints[i].end()))) {
                int sum = 0;
                for (int p = 2; p < constraints[i].size(); p++)
                    sum += affectation[constraints[i][p]];
                valid = (sum == affectation[constraints[i][1]]) && valid;
                nValid += valid;
            }
			break;
		case 10:
		    if (isIn(affectation, vector<int>(constraints[i].begin() + 2, constraints[i].end()))) {
                int sum = 0;
                for (int p = 2; p < constraints[i].size(); p++)
                    sum += affectation[constraints[i][p]];
                valid = (sum < constraints[i][1]) && valid;
                nValid += valid;
            }
			break;
        }

        if (!valid) return 0;
    }
    return (!nValid ? return -1 : return nValid);
}

map<int, int>* CSP::solve() {
    vector<int> order;
    // This here until further improvements;
    for (int i = 0; i < nbVars; i++)
        order.push_back(i);

    vector<map<int, int>* > pile;
    pile.push_back(new map<int, int>);

    map<int, int>* current;

    while (pile.size()) {
        current = pile[0];
        pile.erase(pile.begin());

        for (int i = 0; i < vars[order[current->size()]].size(); i++)
        {
            map<int, int>* t = new map<int, int>(*current);
            t[order[current->size()]] = vars[order[current->size()]][i];

            int r = isValid(t);
            if (r == nbConstraints) return t;
            if (r != 0) pile.push_back(t);
            if (r == 0) delete t;
        }
        delete current;
    }

    return new map<int, int>;
}
*/
