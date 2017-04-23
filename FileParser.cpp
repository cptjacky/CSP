#include "FileParser.h"


/*
Prends une ligne comme entrée, et la divise en utilisant le caractère espace comme délimiteur.
Ex: Transforme "14 5 3" en un vector : [14, 5, 3].
*/
const vector<int> FileParser::split(const string & input)
{
	istringstream ss(input);
	string token;

	vector<int> output;
	while (getline(ss, token, ' '))
		output.push_back(stoi(token));

	return output;
}

/*
Constructeur: Prends en paramètre le chemin du fichier à parser et l'ouvre.
*/
FileParser::FileParser(string path)
{
	if (infile.is_open())
		infile.close();

	infile.open(path);

	if (!infile.good()) {
		cout << "[ERREUR] Impossible d'ouvrir le fichier de graphe! (" << path << ")" << endl;
		if (infile.is_open())
			infile.close();
		exit(0);
	}

	cout << "[INFO] Fichier ouvert avec succès, on continue. (" << path << ")" << endl;
}

/*
Destructeur: Ferme le fichier eventuellement ouvert.
*/
FileParser::~FileParser()
{
	if (infile.is_open())
		infile.close();
}

/*
Génère l'objet PSC;
*/
PSC& FileParser::generate()
{
	string line;

	int i = 0;
	int nv = 0;
	vector<int> tkk;

	vector<int> sommets;

	PSC* gg = new PSC();

	while (getline(infile, line))
	{
		if (i == 0) {
			// Line 1, nombre de variables;
			nv = stoi(line);
			cout << "[INFO] Nombre de variables trouvé: " << nv << endl;
			i++;

			gg->nbVar = nv;
		}
		else if (i > 0 && i < nv + 1) {
			// On remplit le tableau des domaines;
			tkk = split(line);
			cout << "[INFO] Domaine de la variable x" << tkk[0] << " trouvé." << endl;
			tkk.erase(tkk.begin());
			gg->domVars.push_back(tkk);

			i++;
		}
		else if (stoi(line) != -1) {
			// On remplit le tableau des contraintes;
			tkk = split(line);
			cout << "[INFO] Contrainte " << tkk[0] << " trouvée." << endl;
			gg->restrictions.push_back(tkk);

			i++;
		}
	}
	return *gg;
}
