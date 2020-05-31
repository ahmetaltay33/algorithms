// floyd-warshall.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// ReSharper disable CommentTypo
// ReSharper disable StringLiteralTypo
#include <iostream>
#include <random>
#include <string>
#include <Windows.h>
#include <ctime>

using namespace std;

float*** floyd_warshall(int n, float** w)
{
	float*** a = new float**[n+1];
	a[0] = w;
	for (int k = 1; k < n + 1; ++k) // arrays
	{
		a[k] = new float*[n];
		for (int i = 0; i < n; ++i) // rows
		{
			a[k][i] = new float[n];
			for (int j = 0; j < n; ++j) // cols
			{
				a[k][i][j] = min(a[k - 1][i][j], (a[k - 1][i][k - 1] + a[k - 1][k - 1][j]));
			}
		}
	}
	return a;
}

void print2DArray(int col, int row, float** w)
{
	for (int i = 0; i < row; ++i) // rows
	{
		string arrOut;
		for (int j = 0; j < col; ++j) // cols
		{
			if (!arrOut.empty())
				arrOut += ", ";
			arrOut += std::to_string(w[i][j]);
		}
		cout << arrOut + "\n";
	}
	cout << "\n";
}

void print3DArray(int deep, int row, int col, float*** w)
{
	for (int k = 0; k < deep; ++k) // arrays
	{
		cout << "\n";
		printf("Array[%d]\n", k);
		print2DArray(row, col, w[k]);
	}
	cout << "\n";
}

bool checkArrayEquality(int row, int col, float** a1, float** a2)
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			if (a1[i][j] != a2[i][j])
				return false;
		}
	}
	return true;
}

float** generateRandomPath(int size)
{
	std::mt19937 gen;
	std::uniform_real_distribution<float> dis(0, 1);
	float** a = new float* [size];
	for (int i = 0; i < size; ++i)
	{
		a[i] = new float[size];
		for (int j = 0; j < size; ++j)
		{
			a[i][j] = dis(gen);
		}
	}
	return a;
}

void testSequentialLoad(int size)
{
	printf("Sirali test %dx%d boyutlu dizi baslatiliyor...\n", size, size);
	
	//Test verileri olusturuluyor...
	float** randomPaths = generateRandomPath(size);

	//Test verileri içinden en kýsa yolun bulunmasý için algoritma çalýþtýrýyor...
	clock_t timeBegin = clock();
	float*** randomSortestPaths = floyd_warshall(size, randomPaths);
	clock_t timeEnd = clock();

	//Algoritmanýn calisma suresi yazdiriliyor.
	const auto elapsedTime = timeEnd - timeBegin;
	printf("Sirali test %dx%d boyutlu dizi icin calistirildi, Gecen sure: %ldms\n", size, size, elapsedTime);

	delete[] randomSortestPaths;
}

void testFloydWarshallAlgorithm()
{
	float** testInput = new float* [4];

	testInput[0] = new float[4];
	testInput[0][0] = 0;
	testInput[0][1] = 3;
	testInput[0][2] = INFINITY;
	testInput[0][3] = 7;

	testInput[1] = new float[4];
	testInput[1][0] = 8;
	testInput[1][1] = 0;
	testInput[1][2] = 2;
	testInput[1][3] = INFINITY;

	testInput[2] = new float[4];
	testInput[2][0] = 5;
	testInput[2][1] = INFINITY;
	testInput[2][2] = 0;
	testInput[2][3] = 1;

	testInput[3] = new float[4];
	testInput[3][0] = 2;
	testInput[3][1] = INFINITY;
	testInput[3][2] = INFINITY;
	testInput[3][3] = 0;

	float** expectedResult = new float* [4];

	expectedResult[0] = new float[4];
	expectedResult[0][0] = 0;
	expectedResult[0][1] = 3;
	expectedResult[0][2] = 5;
	expectedResult[0][3] = 6;

	expectedResult[1] = new float[4];
	expectedResult[1][0] = 5;
	expectedResult[1][1] = 0;
	expectedResult[1][2] = 2;
	expectedResult[1][3] = 3;

	expectedResult[2] = new float[4];
	expectedResult[2][0] = 3;
	expectedResult[2][1] = 6;
	expectedResult[2][2] = 0;
	expectedResult[2][3] = 1;

	expectedResult[3] = new float[4];
	expectedResult[3][0] = 2;
	expectedResult[3][1] = 5;
	expectedResult[3][2] = 7;
	expectedResult[3][3] = 0;

	float*** sortestPaths = floyd_warshall(4, testInput);
	print3DArray(5, 4, 4, sortestPaths);

	bool isSuccess = checkArrayEquality(4, 4, sortestPaths[4], expectedResult);

	if (isSuccess)
		cout << "Floyd-Warshall algoritmasi calisiyor. Dogrulama testi gecildi.\n\n";
	else
		cout << "Floyd-Warshall algoritmasi calismiyor. Dogrulama basarisiz!\n\n";

	delete[] sortestPaths;
}

int main()
{
	cout << "En kisa yol probleminin Floyd-Warshall algoritmasi kullanilarak paralel programlama ile cozumu\n";

	testFloydWarshallAlgorithm();
	testSequentialLoad(1000);

	cout << "Tum islemler tamamlandi cikmak icin bir tusa basiniz...";
	getchar();
}