#include "heapsort.h"

void Exchange(int* A, int i, int j)
{
	const int e = A[i];
	A[i] = A[j];
	A[j] = e;
}

int RootValue(const int* A)
{
	return A[0];
}

int Parent(int i)
{
	return i / 2;
}

int ParentValue(const int* A, int i)
{
	const int p = Parent(i);
	return A[p];
}

int Left(int i)
{
	return (i * 2) + 1;
}

int LeftValue(const int* A, int i)
{
	const int l = Left(i);
	return A[l];
}

int Right(int i)
{
	return (i * 2) + 2;
}

int RightValue(const int* A, int i)
{
	const int r = Right(i);
	return A[r];
}

int GetLeafsStartIndex(int n)
{
	return n / 2;
}

int* GetLeafValues(const int* A, int n)
{
	const int s = GetLeafsStartIndex(n);
	const int c = (n - s);
	int* W = new int[c];
	for (int i = 0; i < c; ++i)
	{
		W[i] = A[s + i];
	}
	return W;
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
	const int s = GetLeafsStartIndex(n);
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