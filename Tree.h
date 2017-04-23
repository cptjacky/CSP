#include <iostream>
#include <vector>

using namespace std;

class Tree {
public:
    int value;
	int var;
    vector<Tree*> children;

    Tree(int val, int v);
    bool isLeaf();
};
