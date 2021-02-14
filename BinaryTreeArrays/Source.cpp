
#include "Tree.h"


int main() {
	Tree tree;

	//tree.generateRandomTree(10, 1, 10);

	//tree.printTreeGraphic();

	//cout << tree.heightRec();

	tree.addNode(100);
	tree.addNode(70);
	tree.addNode(90);
	tree.addNode(150);
	tree.addNode(140);
	tree.addNode(200);
	tree.addNode(210);
	tree.addNode(68);
	tree.addNode(46);

	tree.addNode(89);
	tree.addNode(95);
	tree.addNode(70);


	tree.addNode(20);
	tree.addNode(29);
	tree.addNode(43);
	tree.addNode(89);
	tree.printTreeGraphic();
	cout << tree.heightRec();
	cout << tree.getTreeHeight();
	
	//tree.deleteNode(62);
	//cout << endl << "------------------------------------------------------------------" << endl;
	//tree.printTreeGraphic();
	//tree.deleteNode(89);
	//cout << endl << "------------------------------------------------------------------" << endl;
	//tree.printTreeGraphic();
	//tree.deleteNode(43);
	//cout << endl << "------------------------------------------------------------------" << endl;
	//tree.printTreeGraphic();
	//tree.deleteNode(95);
	//cout << endl << "------------------------------------------------------------------" << endl;
	//tree.printTreeGraphic();
	//tree.deleteNode(89);
	//cout << endl << "------------------------------------------------------------------" << endl;
	//tree.printTreeGraphic();


	return 0;
}