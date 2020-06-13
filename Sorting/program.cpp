#include <iostream>
#include <array>
#include <string>

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
	
	return 1;
}