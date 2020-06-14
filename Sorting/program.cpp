#include <iostream>
#include <array>
#include <string>


#include "binarytree.h"
#include "heapsort.h"
#include "mergesort.h"
#include "insertionsort.h"

using namespace std;

void printArray(int* A, int r)
{
	string arrOut;
	for (int i = 0; i < r; ++i) // rows
	{
		if (!arrOut.empty())
			arrOut += ", ";
		arrOut += to_string(A[i]);
	}
	cout << "{ " + arrOut + " }\n";
}

int main()
{
	cout << "Sort-Algorithms\n\n";
	int* A;
	
	cout << "Insertion-Sort\n";
	A = new int[10] { 5, 4, 8, 3, 6, 7, 9, 2, 1, 0 };
	printArray(A, 10);
	InsertionSort(A, 10);
	printArray(A, 10);
	delete[] A;
	cout << "\n";

	cout << "Merge-Sort\n";
	A = new int[21] { 5, 4, 8, 3, 6, 7, 9, 2, 1, 0, 20, 18, 17, 19, 15, 16, 14, 10, 13, 12, 11};
	printArray(A, 21);
	MergeSort(A, 0, 21-1);
	printArray(A, 21);
	delete[] A;
	cout << "\n";

	cout << "Heap-Sort\n";
	A = new int[10]{ 16, 14, 10, 8, 7, 9, 3, 2, 4, 1 };
	printArray(A, 10);
	HeapSort(A, 10);
	printArray(A, 10);
	delete[] A;
	cout << "\n";

	cout << "Binary-Tree\n";
	cout << "{ 15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9 }\n";
	node* root = nullptr;
	root = TreeInsert(root, 15);
	TreeInsert(root, 6);
	TreeInsert(root, 18);
	TreeInsert(root, 3);
	TreeInsert(root, 7);
	TreeInsert(root, 17);
	TreeInsert(root, 20);
	TreeInsert(root, 2);
	TreeInsert(root, 4);
	TreeInsert(root, 13);
	TreeInsert(root, 9);

	string treeOut;
	TreePrint(root, treeOut);
	cout << "{ " + treeOut + " }\n";

	cout << "Delete 7\n";
	TreeDelete(root, 7);
	treeOut = "";
	TreePrint(root, treeOut);
	cout << "{ " + treeOut + " }\n";

	cout << "Delete 6\n";
	TreeDelete(root, 6);
	treeOut = "";
	TreePrint(root, treeOut);
	cout << "{ " + treeOut + " }\n";
	
	return 1;
}
