#include "E2-CSP.h"

class FileParser {

private:
	ifstream infile;
	const vector<int> split(const string& l);

public:
	FileParser(string path);
	~FileParser();

	CSP& generate();
};
