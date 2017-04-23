#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "PSC.h"

using namespace std;

class FileParser {

private:
	ifstream infile;
	const vector<int> split(const string& l);

public:
	FileParser(string path);
	~FileParser();

	PSC& generate();
};
