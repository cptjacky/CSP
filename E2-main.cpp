#include "E2-FileParser.h"
#include <locale>


int main() {
	locale::global(locale(""));

	CSP m;
	map<int, int>* result;
	string filepath = "C:/Users/Nicolas/Desktop/CSP/E2-G6.txt";  // A r�gler selon l'ordinateur sur lequel on compile et le fichier que l'on souhaite lire!

	FileParser* f = new FileParser(filepath);
	m = f->generate(); // Lecture du fichier.
	m.computeVarConstraints();
	m.displayDebug();

	// R�solution traditionelle;
	result = m.solve();
	m.displayStats();

	// Ou r�solution par r�duction de domaine.. Il faut choisir!
	result = m.solve2();
	m.displayStats();


	/* Affichage du r�sultat; */
	cout << "Nombre de variables dans le resultat: " << result->size() << endl;
	for (map<int, int>::const_iterator it = result->begin(); it != result->end(); ++it)
	{
		cout << "Variable " << it->first << ": ";
		cout << it->second << endl;
	}

	system("pause");
}
