#pragma once

#include <iostream>
using namespace std;

const int maxSize = 256;

struct treeArray {
	int data[maxSize];
	int parent[maxSize];
	int left[maxSize];
	int right[maxSize];
};

//9 3 0 5 24 17 11 22 30 40

class Tree
{
private:
	treeArray tree;


	int size = 0;
	int treeHeight = 0;
	//конструктор инициализирует дерево нулями

	int findNodeIndex(int x);
	void addNode(int rootTree, int x);
	void deleteNode(int key, int rootTree);
	void shiftArray(int start);
	void deleteColumn(int n);
	int searchMin(int rootIndex);
	void printRec(int node, int h);
	void recPreOrderCalculateHeight(int node, int tempSize);
	int __heightRec(int node);
public:
	Tree();
	void addNode(int x);
	void deleteNode(int x);
	bool searchNode(int x);
	void printTreeGraphic();
	int getTreeHeight();
	void generateRandomTree(int numberOfNodes, int minKey, int maxKey);
	int heightRec(); // вычисление высоты дерева
};

