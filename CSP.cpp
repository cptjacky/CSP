#include "CSP.h"

bool CSP::isIn(map<int, int> &affectation, vector<int> &v) {
    for (int i = 0; i < v.size(); i++) {
        if (!affectation.count(v[i])) return false;
    }
    return true;
}

int CSP::isValid(map<int, int> &affectation) {
    bool valid = true;
    int nValid = 0;

    for (int i = 0; i < constraints.size(); i++) {
        switch(constraints[i][0]) { 
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
    return (!nValid ? -1 : nValid);
}

vector<vector<int> > CSP::domainReduction(map<int, int>* af) {
	vector<vector<int> > tempvars;
	for (int i = 0; i < nbVars; i++) {
		if (af->count(i) > 0) tempvars.push_back(vector<int>(1, (*af)[i]));
		else tempvars.push_back(vars[i]);
	}

	for (int i = 0; i < constraints.size(); i++) {
		int opl = constraints[i][1], opr = constraints[i][2];

		for (int l = 0; l < tempvars[opl].size(); l++) {
			bool possible = false;
			for (int r = 0; r < tempvars[opr].size(); r++) {
				switch (constraints[i][0]) {
				case 4:
					possible = tempvars[opl][l] < tempvars[opr][r] || possible;
					break;
				case 6:
					possible = tempvars[opl][l] > tempvars[opr][r] || possible;
					break;
				}
			}
			if (!possible) tempvars[opl].erase(tempvars[opl].begin() + l);
		}

		for (int r = 0; r < tempvars[opr].size(); r++) {
			bool possible = false;
			for (int l = 0; l < tempvars[opl].size(); l++) {
				switch (constraints[i][0]) {
				case 4:
					possible = tempvars[opl][l] < tempvars[opr][r] || possible;
					break;
				case 6:
					possible = tempvars[opl][l] > tempvars[opr][r] || possible;
					break;
				}
			}
			if (!possible) tempvars[opr].erase(tempvars[opr].begin() + r);
		}
	}

	for (int i = 0; i < nbVars; i++)
		if (tempvars[i].size() == 0) return vector<vector<int> >(nbVars);

	return tempvars;
}

map<int, int>* CSP::solve() {
    vector<int> order;
    // This here until further improvements;
	order.push_back(4);
	order.push_back(5);
	order.push_back(20);
	order.push_back(43);
	for (int i = 0; i < nbVars; i++)
	if (i != 4 && i!= 5 && i != 20 && i!= 43) order.push_back(i);
    /*for (int i = 0; i < nbVars; i++)
        order.push_back(i);*/

    vector<map<int, int>* > pile;
    pile.push_back(new map<int, int>);

    map<int, int>* current;

    while (pile.size()) {
		/*current = pile[0];
		pile.erase(pile.begin());*/
		current = pile[pile.size() - 1];
		pile.erase(pile.begin() + pile.size() - 1);

        for (int i = 0; i < vars[order[current->size()]].size(); i++)
        {
            map<int, int>* t = new map<int, int>(*current);
            (*t)[order[current->size()]] = vars[order[current->size()]][i];

            int r = isValid(*t);

            if (r == nbConstraints) return t;
            if (r != 0) pile.push_back(t);
            if (r == 0) delete t;
        }
        delete current;
    }

    return new map<int, int>;
}

map<int, int>* CSP::solve2() {
	vector<int> order;
	// This here until further improvements;
	/*order.push_back(4);
	order.push_back(5);
	order.push_back(20);
	order.push_back(43);
	for (int i = 0; i < nbVars; i++)
		if (i != 4 && i!= 5 && i != 20 && i!= 43) order.push_back(i);*/
	for (int i = 0; i < nbVars; i++)
		order.push_back(i);

	vector<map<int, int>* > pile;
	pile.push_back(new map<int, int>);

	map<int, int>* current;

	while (pile.size()) {
		/*current = pile[0];
		pile.erase(pile.begin());*/
		current = pile[pile.size() -1];
		pile.erase(pile.begin() + pile.size() - 1);

		vector<vector<int> > tempvars = domainReduction(current);

		for (int i = 0; i < tempvars[order[current->size()]].size(); i++)
		{
			map<int, int>* t = new map<int, int>(*current);
			(*t)[order[current->size()]] = tempvars[order[current->size()]][i];

			int r = isValid(*t);

			if (r > 0) cout << r << endl;

			if (r == nbConstraints) return t;
			if (r != 0) pile.push_back(t);
			if (r == 0) delete t;
		}
		delete current;
	}

	return new map<int, int>;
}

void CSP::displayDebug() {
	for (int i = 0; i < vars.size(); i++) {
		cout << endl << "Var " << i << ": ";
		for (int y = 0; y < vars[i].size(); y++) {
			cout << vars[i][y] << " ";
		}
	}
}