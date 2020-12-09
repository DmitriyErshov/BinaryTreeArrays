
#include "Tree.h"


int main() {
	Tree tree;

	tree.addNode(9);
	tree.addNode(3);
	tree.addNode(24);
	tree.addNode(0);
	tree.addNode(5);
	tree.addNode(17);
	tree.addNode(11);
	tree.addNode(30);
	tree.addNode(40);

	//tree.deleteNode(9);

	tree.printTreeGraphic();
	return 0;
}