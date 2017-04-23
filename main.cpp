#include "FileParser.h"

int main() {
	FileParser* f = new FileParser("C:/Users/Nicolas/Desktop/AD/x64/Release/E2-G1.txt");
	PSC m = f->generate();
	m.displayDebug();
	m.t = new Tree(0, 0);
	m.trivialTree(m.t);
	vector<int> result = m.trivialSolve(m.t, vector<int>(0));
	cout << "Size of result: " << result.size();

	system("pause");
}