#include "FileParser.h"
#include <locale>


int main() {
	locale::global(locale(""));
	
	FileParser* f = new FileParser("C:/Users/Nicolas/Desktop/CSP/E2-G7.txt");
	CSP m = f->generate();

	/*m.displayDebug();
	for (int i = 0; i <100; i++)
		m.domainReduction();
	m.displayDebug();*/

    map<int, int>* result = m.solve();
    cout << "Nombre de variables dans le resultat: " << result->size() << endl;

    for(map<int, int>::const_iterator it = result->begin(); it != result->end(); ++it )
    {
		cout << "Variable " << it->first << ": ";
		cout << it->second << endl;
    }
	system("pause");
}
