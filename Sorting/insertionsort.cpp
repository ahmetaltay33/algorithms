#include "insertionsort.h"
void InsertionSort(int* A, int r)
{
	int key, i;
	for (int j = 1; j < r; ++j)
	{
		key = A[j];
		i = j;
		while(i > 0 && A[i-1] > key)
		{
			A[i] = A[i-1];
			i--;
		}
		A[i] = key;
	}
}