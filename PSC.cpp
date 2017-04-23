#include "PSC.h"

void PSC::displayDebug() {
	for (unsigned int i = 0; i < domVars.size(); i++)
	{
		cout << "Domaine de la variable x" << i << ": ";
		for (unsigned int p = 0; p < domVars[i].size(); p++)
			cout << domVars[i][p] << ", ";
		cout << endl;
	}

	for (unsigned int i = 0; i < restrictions.size(); i++)
	{
		cout << "Contrainte " << i << ": ";
		for (unsigned int p = 0; p < restrictions[i].size(); p++)
			cout << restrictions[i][p] << ", ";
		cout << endl;
	}
}

bool PSC::isValid(vector<int> v) {
	bool valid = true;
	int sum = 0;

	cout << "Testing leave: ";
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	cout << endl;

	for (int i = 0; i < restrictions.size(); i++) {
		if (!valid) {
			return false;
			cout << "false" << endl;
		}
		cout << restrictions[i][0] << " ";

		switch (restrictions[i][0]) {
		case 1:
			valid = (v[restrictions[i][1]] == v[restrictions[i][2]]) && valid;
			break;
		case 2:
			valid = (v[restrictions[i][1]] != v[restrictions[i][2]]) && valid;
			break;
		case 3:
			valid = (v[restrictions[i][1]] <= v[restrictions[i][2]]) && valid;
			break;
		case 4:
			valid = (v[restrictions[i][1]] < v[restrictions[i][2]]) && valid;
			break;
		case 5:
			valid = (v[restrictions[i][1]] >= v[restrictions[i][2]]) && valid;
			break;
		case 6:
			valid = (v[restrictions[i][1]] > v[restrictions[i][2]]) && valid;
			break;
		case 7:
			sum = 0;
			cout << "size:" << restrictions[i].size();
			for (int p = 2; p < restrictions[i].size(); p++)
				sum += v[restrictions[i][p]];
			cout << " sum: " << sum << endl;
			valid = (sum == restrictions[i][1]) && valid;
			break;
		case 8:
			valid = valid;
			// TODO;
			break;
		case 9:
			sum = 0;
			for (int p = 1; p < restrictions[i].size(); p++)
				sum += v[restrictions[i][p]];
			valid = (sum == v[restrictions[i][restrictions[i].size() - 1]]) && valid;
			break;
		case 10:
			sum = 0;
			for (int p = 1; p < restrictions[i].size(); p++)
				sum += v[restrictions[i][p]];
			valid = (sum == restrictions[i][restrictions[i].size() - 1]) && valid;
			break;
		}
	}

	cout << endl;
	return valid;
}

/*
Tree* PSC::trivialTree(int var, int value) {
	Tree* node;

	if (var == 0) node = new Tree(var, value, domVars[0].size());
	else if (var < nbVar) node = new Tree(var, domVars[var][value], domVars[var].size());
	else node = new Tree(var, domVars[var][value], 0);

	if (var < nbVar) {
		for (int i = 0; i < domVars[var].size(); i++)
			node->children[i] = trivialTree(var+1, i);
	}

	return node;
	
}
*/

void PSC::trivialTree(Tree* b) {
	if (b->var == nbVar) return;
	for (int i = 0; i < domVars[b->var].size(); i++)
	{
		// cout << "Creating var " << b->var + 1 << " value " << domVars[b->var][i] << endl;
		Tree* c = new Tree(domVars[b->var][i], b->var + 1);
		b->children.push_back(c);
		trivialTree(b->children[i]);
	}
}

vector<int> PSC::trivialSolve(Tree* b, vector<int> values) {
	if (b->var == nbVar) { // Toute les valeurs ont été assignées, c'est une feuille.
		if (isValid(values)) return values;
		return vector<int>(0);
	}

	for (int i = 0; i < b->children.size(); i++) {
		values.push_back(b->children[i]->value);
		vector<int> result = trivialSolve(b->children[i], values);
		values.erase(values.end() - 1);
		if (result.size() != 0) return result;
	}

	return vector<int>(0);
}