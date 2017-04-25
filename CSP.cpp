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

vector<vector<int> > CSP::domainReduction(vector<vector<int> > &doms, int x, int value) {

	for (int i = 0; i < varConstraints[x].size(); i++) {
		int opl = varConstraints[x][i][1], opr = varConstraints[x][i][2];

		for (int l = 0; l < doms[opl].size(); l++) {
			bool possible = false;
			for (int r = 0; r < doms[opr].size(); r++) {
				switch (varConstraints[x][i][0]) {
				case 4:
					possible = doms[opl][l] < doms[opr][r] || possible;
					break;
				case 6:
					possible = doms[opl][l] > doms[opr][r] || possible;
					break;
				}
			}
			if (!possible) doms[opl].erase(doms[opl].begin() + l);
		}

		for (int r = 0; r < doms[opr].size(); r++) {
			bool possible = false;
			for (int l = 0; l < doms[opl].size(); l++) {
				switch (varConstraints[x][i][0]) {
				case 4:
					possible = doms[opl][l] < doms[opr][r] || possible;
					break;
				case 6:
					possible = doms[opl][l] > doms[opr][r] || possible;
					break;
				}
			}
			if (!possible) doms[opr].erase(doms[opr].begin() + r);
		}
	}

	for (int i = 0; i < nbVars; i++) {
		if (doms[i].size() == 0) doms = vector<vector<int> >(0);
	}

	return doms;
}

void CSP::computeVarConstraints() {
	for (int v = 0; v < nbVars; v++) {
		for (int i = 0; i < nbConstraints; i++) {
			if (constraints[i][0] == 7 || constraints[i][0] == 10) {
				for (int t = 2; t < constraints[i].size(); t++) {
					if (constraints[i][t] == v) varConstraints[v].push_back(constraints[i]);
				}
			}
			else {
				for (int t = 1; t < constraints[i].size(); t++) {
					if (constraints[i][t] == v) varConstraints[v].push_back(constraints[i]);
				}
			}
		}
	}
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

	// This here until further improvements;
	vector<int> order;
	for (int i = 0; i < nbVars; i++)
		order.push_back(i);

	vector<Node* > pile;
	pile.push_back(new Node(vars));

	Node* current;

	while (pile.size()) {
		current = pile[pile.size() -1];
		pile.erase(pile.begin() + pile.size() - 1);

		for (int i = 0; i < current->domains[order[current->assigned->size()]].size(); i++)
		{
			Node* t = new Node(current);

			int var = order[current->assigned->size()];
			int value = current->domains[order[current->assigned->size()]][i];

			(*t->assigned)[var] = value;

			t->domains = domainReduction(t->domains, var, value);

			// cout << t->domains.size() << endl;

			if (t->assigned->size() == nbVars)
				return t->assigned;
			else if (t->domains.size() == 0)
				delete t;
			else
				pile.push_back(t);

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


Node::Node(vector<vector<int> > p) {
	assigned = new map<int, int>;
	domains = p;
}

Node::Node(Node* n) {
	assigned = new map<int, int>(*n->assigned);
	domains = vector<vector<int> >(n->domains);
}

Node::~Node() {
	delete assigned;
}