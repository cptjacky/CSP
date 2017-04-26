#include "E2-CSP.h"

/* Cette fonction teste si toute les variables de v sont bien affectées. */
bool CSP::isIn(map<int, int> &affectation, vector<int> &v) {
	for (int i = 0; i < v.size(); i++) {
		if (!affectation.count(v[i])) return false;
	}
	return true;
}

/* Cette fonction teste toute les contraintes possible de tester avec les variables actuellement affectée, et retourne le nombre de tests effectués. (0 = Au moins un test faux!; -1 = Aucun test ne peut être effectué avec les variables assignées.*/
int CSP::isValid(map<int, int> &affectation) {
	bool valid = true;
	int nValid = 0;

	/* On parcoure toute les contraintes; */
	for (int i = 0; i < constraints.size(); i++) {
		switch (constraints[i][0]) {
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
			// La logique du 8 est implémentée à la lecture du fichier: séparation en contraintes binaires;
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


/* La fonction de réduction de domaine; Elle prends en argument les domaines de valeur des variables et la variable qui doit être assignée. On vérifie ensuite toute les conditions (binaires uniquement) liées à cette variable. */
vector<vector<int> >& CSP::domainReduction(vector<vector<int> > &doms, int x, int value) {

	doms[x] = vector<int>(1, value);

	// varConstraints[x] contient toute les contraintes qui affectent la variable x;
	for (int i = 0; i < varConstraints[x].size(); i++) {
		int opl = varConstraints[x][i][1], opr = varConstraints[x][i][2];

		for (int l = 0; l < doms[opl].size(); l++) {
			bool possible = false;
			for (int r = 0; r < doms[opr].size(); r++) {
				switch (varConstraints[x][i][0]) {
				case 1:
					possible = doms[opl][l] == doms[opr][r] || possible;
					break;
				case 2:
					possible = doms[opl][l] != doms[opr][r] || possible;
					break;
				case 3:
					possible = doms[opl][l] <= doms[opr][r] || possible;
					break;
				case 4:
					possible = doms[opl][l] < doms[opr][r] || possible;
					break;
				case 5:
					possible = doms[opl][l] >= doms[opr][r] || possible;
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
				case 1:
					possible = doms[opl][l] == doms[opr][r] || possible;
					break;
				case 2:
					possible = doms[opl][l] != doms[opr][r] || possible;
					break;
				case 3:
					possible = doms[opl][l] <= doms[opr][r] || possible;
					break;
				case 4:
					possible = doms[opl][l] < doms[opr][r] || possible;
					break;
				case 5:
					possible = doms[opl][l] >= doms[opr][r] || possible;
					break;
				case 6:
					possible = doms[opl][l] > doms[opr][r] || possible;
					break;
				}
			}
			if (!possible) doms[opr].erase(doms[opr].begin() + r);
		}
	}

	// Si au moins un des domaines est null, on vide complètement le tableau des domaines; L'état est bon à jeter!
	for (int i = 0; i < doms.size(); i++) {
		if (doms[i].size() == 0) {
			doms = vector<vector<int> >(0);
			break;
		}
	}

	return doms;
}

/* Génère le tableau des contraintes par variable */
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

/* Fonction utilisée pour générer l'ordre dans lequel on traîte les variables: du plus petit domaine au plus grand; */
bool CSP::sortOrder(int x, int y) {
	return (vars[x].size() < vars[y].size());
}


/* Fonction de résolution basique, fonctionelle avec tout type de conditions */
map<int, int>* CSP::solve() {
	totalNodes = 0;
	branchesIgnorees = 0;
	start = clock();

	// On initialise et trie le tableau des domaines;
	vector<int> order;
	for (int i = 0; i < nbVars; i++)
		order.push_back(i);
	sort(order.begin(), order.end(), [this](int l, int r) {return sortOrder(l, r); });

	// Pas de récursivité... mais une pile.
	vector<map<int, int>* > pile;
	pile.push_back(new map<int, int>);

	map<int, int>* current;

	while (pile.size()) {
		current = pile[pile.size() - 1];
		pile.erase(pile.begin() + pile.size() - 1);

		// Pour tout les enfants de l'état courant;
		for (int i = 0; i < vars[order[current->size()]].size(); i++)
		{
			totalNodes++;

			// On crée l'état enfant (donc l'affectation);
			map<int, int>* t = new map<int, int>(*current);
			(*t)[order[current->size()]] = vars[order[current->size()]][i];

			// On teste les contraintes sur l'état enfant;
			int r = isValid(*t);

			// Toute les contraintes sont respectées, SOLUTION!!
			if (r == nbConstraints) {
				duration = (clock() - start) / (double)CLOCKS_PER_SEC;
				return t;
			}
			if (r != 0)
				pile.push_back(t); 			// Aucun test faux, on ajoute l'état à la pile!
			if (r == 0) {					// Un test faux, l'état est à jeter.
				branchesIgnorees++;
				delete t;
			}
		}
		delete current;
	}

	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	return new map<int, int>;
}

/* Fonction de résolution par réduction de domaine */
map<int, int>* CSP::solve2() {
	totalNodes = 0;
	branchesIgnorees = 0;
	start = clock();

	// On initialise et trie le tableau des domaines;
	vector<int> order;
	for (int i = 0; i < nbVars; i++)
		order.push_back(i);
	sort(order.begin(), order.end(), [this](int l, int r) {return sortOrder(l, r); });

	// Pas de récursivité... mais une pile.
	vector<Node* > pile;
	pile.push_back(new Node(vars));

	Node* current;

	while (pile.size()) {
		current = pile[pile.size() - 1];
		pile.erase(pile.begin() + pile.size() - 1);

		/* Pour tout les enfants des sous domaine de l'état courrant */
		for (int i = 0; i < current->domains[order[current->assigned->size()]].size(); i++)
		{
			totalNodes++;
			// On crée l'état enfant, il possède l'affectation et les domaines de l'état courant;
			Node* t = new Node(current);

			int var = order[current->assigned->size()];
			int value = current->domains[order[current->assigned->size()]][i];

			// On assigne la valeur;
			(*t->assigned)[var] = value;

			// On réduit le domaine de l'enfant.
			t->domains = domainReduction(t->domains, var, value);

			if (t->assigned->size() == nbVars) {				// Toutes les variables sont là, grâce à la réduction de domaine, pas besoin de tester, c'est une solution!
				duration = (clock() - start) / (double)CLOCKS_PER_SEC;
				return t->assigned;
			}
			else if (t->domains.size() == 0) {				// Les domaines sont vides!
				delete t;
				branchesIgnorees++;
			}
			else												// Tout va bien, on ajoute à la pile;
				pile.push_back(t);

		}
		delete current;
	}
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	return new map<int, int>;
}

void CSP::displayDebug() {
	cout << "### STRUCTURE ###" << endl << endl;
	cout << "--- Domaines de valeurs ---" << endl;
	for (int i = 0; i < vars.size(); i++) {
		cout << "Var " << i << ": {";
		for (int y = 0; y < vars[i].size(); y++) {
			cout << vars[i][y] << "; ";
		}
		cout << "}" << endl;
	}

	cout << endl << "--- Contraintes ---" << endl;
	for (int i = 0; i < constraints.size(); i++) {
		if (constraints[i][0] < 7) {
			cout << "X" << constraints[i][1] << " " << rInfo[constraints[i][0] - 1] << " X" << constraints[i][2] << endl;
		}
		else if (constraints[i][0] == 9) {
			for (int y = 2; y < constraints[i].size(); y++)
				cout << "X" << constraints[i][y] << (y == constraints[i].size() - 1 ? "" : " + ");
			cout << " = X" << constraints[i][1] << endl;
		}
		else {
			for (int y = 2; y < constraints[i].size(); y++)
				cout << "X" << constraints[i][y] << (y == constraints[i].size() - 1 ? "" : " + ");
			cout << " = " << constraints[i][1] << endl;
		}
	}
}

void CSP::displayStats() {
	cout << "### Statistiques ###" << endl << endl;
	cout << "Nombre de noeuds créés: " << totalNodes << endl;
	cout << "Nombre de branches ignorées: " << branchesIgnorees << endl;
	cout << "Temps d'éxécution: " << duration << "s" << endl << endl;
}

/* Constructeur initial d'un noeud; Structure utilisée pour la réduction de domaine: passer une affectation & un domaine correspondant;*/
Node::Node(vector<vector<int> > p) {
	assigned = new map<int, int>;
	domains = p;
}

/* Constructeur de copie; */
Node::Node(Node* n) {
	assigned = new map<int, int>(*n->assigned);
	domains = vector<vector<int> >(n->domains);
}

/* Destructeur; */
Node::~Node() {
	delete assigned;
}