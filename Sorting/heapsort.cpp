#include "heapsort.h"

void Exchange(int* A, int i, int j)
{
	const int e = A[i];
	A[i] = A[j];
	A[j] = e;
}

int Parent(int i)
{
	return i / 2;
}

int Left(int i)
{
	return (i * 2) + 1;
}

int Right(int i)
{
	return (i * 2) + 2;
}

int Leafs(int n)
{
	return n / 2;
}

void MaxHeapify(int* A, int n, int i)
{
	const int l = Left(i);
	const int r = Right(i);
	int largest = i;
	if (l < n && A[l] > A[largest])
		largest = l;
	if (r < n && A[r] > A[largest])
		largest = r;
	if (largest != i)
	{
		Exchange(A, i, largest);
		MaxHeapify(A, n, largest);
	}
}

void BuildMaxHeap(int* A, int n)
{
	const int s = Leafs(n);
	for (int i = s - 1; i >= 0; i--)
	{
		MaxHeapify(A, n, i);
	}
}

void HeapSort(int* A, int n)
{
	BuildMaxHeap(A, n);
	for (int i = n -1 ; i >= 0; i--)
	{
		Exchange(A, 0, i);
		MaxHeapify(A, i, 0);
	}
}