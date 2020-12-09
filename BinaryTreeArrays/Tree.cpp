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

    //элемент не найден
    return -1;
}

void Tree::addNode(int x)
{
	if (tree.data[0] != -1) {			//Если он не инициализирован,
		addNode(0, x);		//то вызовется рекурсивная функция для добавления элемента.
	}
	else				                //Иначе Функция поместит новое значение:
	{
		tree.data[0] = x;		        //инициализируется корневой элемент      
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

    if (x < tree.data[rootIndex])  	//Если новое ключевое значение меньше чем //ключевое значение в узле
    {
        if (tree.left[rootIndex] != -1)		     //И если левый указатель узла инициализирован
            addNode(tree.left[rootIndex], x);    //Функция вызывает саму себя, для левого //узла потомка
        //Иначе (если левый потомок не //инициализирован)
        else		
        {
            tree.data[size] = x;               
            tree.parent[size] = rootIndex;
            tree.left[rootIndex] = size;		
        }
    }
    else if (x > tree.data[rootIndex])		//Иначе Если новое ключевое значение не //меньше ключевого значения в узле 
    {
        if (tree.right[rootIndex] != -1)		//И если правый указатель инициализирован,
            addNode(tree.right[rootIndex], x);		//То функция вызывает саму себя, для правого //потомка
        else		//Иначе(если правый потомок не //инициализирован)
        {
            tree.data[size] = x;
            tree.parent[size] = rootIndex;
            tree.right[rootIndex] = size;
        }
    }
    else {
        //т.к. метод addNode увеличивает размер дерева на 1, в случае добавления повторного элемента нужно сделать обратное действие в противовес
        size--;
    }
}

void Tree::deleteNode(int key, int rootTree)
{
    int searchedNodeIndex = findNodeIndex(key);

    

    //удаляемый элемент - корень
    if (searchedNodeIndex == 0) {
        if ((tree.left[searchedNodeIndex] != -1 && tree.right[searchedNodeIndex] == -1) ||
            (tree.left[searchedNodeIndex] == -1 && tree.right[searchedNodeIndex] != -1)) {
            //сместить массив влево
            //shiftArray(searchedNodeIndex);
            deleteColumn(searchedNodeIndex);
            //убрать потомка
            tree.parent[searchedNodeIndex] = -1;
            
        }
        else if (tree.left[searchedNodeIndex] != -1 && tree.right[searchedNodeIndex] != -1) {
            int minElemIndex = searchMin(tree.right[searchedNodeIndex]); //ищем минимальный элемент в левом 
            int min = tree.data[minElemIndex];
            deleteNode(min, rootTree); //удалим найденный элемент из поддерева, функция не уйдет в рекурсию, т.к.
                                                            //если у минимального элемента не может быть двух потомков
            tree.data[searchedNodeIndex] = min;//ставим его на место удаляемого узла
        }

    }
    //если найденный элемент без потомков
    else if (tree.left[searchedNodeIndex] == -1 && tree.right[searchedNodeIndex] == -1) {
        
        if (tree.left[tree.parent[searchedNodeIndex]] == searchedNodeIndex) {
            //убрать из потомка
            tree.left[tree.parent[searchedNodeIndex]] = -1;
        }
        else {
            tree.right[tree.parent[searchedNodeIndex]] = -1;
        }
        //shiftArray(searchedNodeIndex);
        deleteColumn(searchedNodeIndex);
    }
    //элемент имеет только одного потомка слева
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
    //элемент имеет только одного потомка справа
    else if (tree.left[searchedNodeIndex] == -1 && tree.right[searchedNodeIndex] != -1)
    {
        //понять с какой стороны этот узел у потомка
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
    //элемент имеет два потомка
    else {
        int minElemIndex = searchMin(tree.right[searchedNodeIndex]); //ищем минимальный элемент в правом 
        int min = tree.data[minElemIndex];
        deleteNode(min, rootTree); //удалим найденный элемент из поддерева, функция не уйдет в рекурсию, т.к.
                                                        //если у минимального элемента не может быть двух потомков
        tree.data[searchedNodeIndex] = min;//ставим его на место удаляемого узла
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