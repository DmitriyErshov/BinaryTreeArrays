#include "Tree.h"

Tree::Tree() {
	for (int i = 0; i < maxSize; i++)
	{
		tree.data[i] = -1;
		tree.parent[i] = -1;
		tree.left[i] = -1;
		tree.right[i] = -1;
	}
}

int Tree::findNodeIndex(int x)
{
    int i = 0;

    while (tree.data[i] != -1) {
        if (tree.data[i] == x) {
            return i;
        }
        i++;
    }

    //������� �� ������
    return -1;
}

void Tree::addNode(int x)
{
	if (tree.data[0] != -1) {			//���� �� �� ���������������,
		addNode(0, x);		//�� ��������� ����������� ������� ��� ���������� ��������.
	}
	else				                //����� ������� �������� ����� ��������:
	{
		tree.data[0] = x;		        //���������������� �������� �������      
	}

	size++;
}

void Tree::deleteNode(int x)
{
    deleteNode(x, 0);
    size--;
}

bool Tree::searchNode(int x)
{
    for (int i = 0; i < size; i++)
    {
        if (tree.data[i] == x) {
            return true;
        }
    }
    return false;
}

void Tree::addNode(int rootIndex, int x)
{
    //int rootIndex = findNodeIndex(rootIndex);

    if (x < tree.data[rootIndex])  	//���� ����� �������� �������� ������ ��� //�������� �������� � ����
    {
        if (tree.left[rootIndex] != -1)		     //� ���� ����� ��������� ���� ���������������
            addNode(tree.left[rootIndex], x);    //������� �������� ���� ����, ��� ������ //���� �������
        //����� (���� ����� ������� �� //���������������)
        else		
        {
            tree.data[size] = x;               
            tree.parent[size] = rootIndex;
            tree.left[rootIndex] = size;		
        }
    }
    else if (x > tree.data[rootIndex])		//����� ���� ����� �������� �������� �� //������ ��������� �������� � ���� 
    {
        if (tree.right[rootIndex] != -1)		//� ���� ������ ��������� ���������������,
            addNode(tree.right[rootIndex], x);		//�� ������� �������� ���� ����, ��� ������� //�������
        else		//�����(���� ������ ������� �� //���������������)
        {
            tree.data[size] = x;
            tree.parent[size] = rootIndex;
            tree.right[rootIndex] = size;
        }
    }
    else {
        //�.�. ����� addNode ����������� ������ ������ �� 1, � ������ ���������� ���������� �������� ����� ������� �������� �������� � ����������
        size--;
    }
}

void Tree::deleteNode(int key, int rootTree)
{
    int searchedNodeIndex = findNodeIndex(key);

    

    //��������� ������� - ������
    if (searchedNodeIndex == 0) {
        if ((tree.left[searchedNodeIndex] != -1 && tree.right[searchedNodeIndex] == -1) ||
            (tree.left[searchedNodeIndex] == -1 && tree.right[searchedNodeIndex] != -1)) {
            //�������� ������ �����
            //shiftArray(searchedNodeIndex);
            deleteColumn(searchedNodeIndex);
            //������ �������
            tree.parent[searchedNodeIndex] = -1;
            
        }
        else if (tree.left[searchedNodeIndex] != -1 && tree.right[searchedNodeIndex] != -1) {
            int minElemIndex = searchMin(tree.right[searchedNodeIndex]); //���� ����������� ������� � ����� 
            int min = tree.data[minElemIndex];
            deleteNode(min, rootTree); //������ ��������� ������� �� ���������, ������� �� ����� � ��������, �.�.
                                                            //���� � ������������ �������� �� ����� ���� ���� ��������
            tree.data[searchedNodeIndex] = min;//������ ��� �� ����� ���������� ����
        }

    }
    //���� ��������� ������� ��� ��������
    else if (tree.left[searchedNodeIndex] == -1 && tree.right[searchedNodeIndex] == -1) {
        
        if (tree.left[tree.parent[searchedNodeIndex]] == searchedNodeIndex) {
            //������ �� �������
            tree.left[tree.parent[searchedNodeIndex]] = -1;
        }
        else {
            tree.right[tree.parent[searchedNodeIndex]] = -1;
        }
        //shiftArray(searchedNodeIndex);
        deleteColumn(searchedNodeIndex);
    }
    //������� ����� ������ ������ ������� �����
    else if (tree.left[searchedNodeIndex] != -1 && tree.right[searchedNodeIndex] == -1) {
        if (tree.left[tree.parent[searchedNodeIndex]] == searchedNodeIndex) {
            tree.left[tree.parent[searchedNodeIndex]] = tree.left[searchedNodeIndex];
        }
        else {
            tree.right[tree.parent[searchedNodeIndex]] = tree.left[tree.parent[searchedNodeIndex]];
        }
        tree.parent[tree.right[searchedNodeIndex]] = tree.parent[searchedNodeIndex];
        //shiftArray(searchedNodeIndex);
        deleteColumn(searchedNodeIndex);
    }
    //������� ����� ������ ������ ������� ������
    else if (tree.left[searchedNodeIndex] == -1 && tree.right[searchedNodeIndex] != -1)
    {
        //������ � ����� ������� ���� ���� � �������
        if (tree.right[tree.parent[searchedNodeIndex]] == searchedNodeIndex) {
            tree.right[tree.parent[searchedNodeIndex]] = tree.right[searchedNodeIndex];
        }
        else {
            tree.left[tree.parent[searchedNodeIndex]] = tree.right[searchedNodeIndex];
        }
        tree.parent[tree.right[searchedNodeIndex]] = tree.parent[searchedNodeIndex];
        //shiftArray(searchedNodeIndex);
        deleteColumn(searchedNodeIndex);
    }
    //������� ����� ��� �������
    else {
        int minElemIndex = searchMin(tree.right[searchedNodeIndex]); //���� ����������� ������� � ������ 
        int min = tree.data[minElemIndex];
        deleteNode(min, rootTree); //������ ��������� ������� �� ���������, ������� �� ����� � ��������, �.�.
                                                        //���� � ������������ �������� �� ����� ���� ���� ��������
        tree.data[searchedNodeIndex] = min;//������ ��� �� ����� ���������� ����
    }
}

//void Tree::shiftArray(int start)
//{
//    for (int i = start; i < size; i++)
//    {
//        tree.data[i] = tree.data[i + 1];
//        tree.parent[i] = tree.parent[i + 1];
//        tree.left[i] = tree.left[i + 1];
//        tree.right[i] = tree.right[i + 1];
//    }
//}

void Tree::deleteColumn(int n)
{
    tree.data[n] = -1;
    tree.parent[n] = -1;
    tree.left[n] = -1;
    tree.right[n] = -1;
}

int Tree::searchMin(int rootIndex)
{
    while (tree.left[rootIndex] != -1) {
        rootIndex = tree.left[rootIndex];
    }

    return rootIndex;
}



void Tree::recPreOrderCalculateHeight(int node, int tempSize)
{
    if (node != -1) {
        tempSize++;
        recPreOrderCalculateHeight(tree.left[node], tempSize);
        recPreOrderCalculateHeight(tree.right[node], tempSize);
    }
    else {
        if (tempSize > treeHeight) {
            treeHeight = tempSize;
        }
    }
}



int Tree::getTreeHeight()
{
    recPreOrderCalculateHeight(0, 0);
    return treeHeight;
}

void Tree::printRec(int node, int h)
{
    if (node != -1)
    {
        printRec(tree.left[node], h + 1);

        for (int i = 1; i <= h; i++)
            cout << "\t";

        cout << tree.data[node] << endl;

        printRec(tree.right[node], h + 1);
    }
}

void Tree::printTreeGraphic()
{
    printRec(0, treeHeight);
}