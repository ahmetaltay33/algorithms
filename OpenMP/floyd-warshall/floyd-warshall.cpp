// floyd-warshall.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include <string>

using namespace std;

float min(float a, float b)
{
	if (b < a)
		return b;
	return a;
}

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

void printArrayQube(int size, float*** w)
{
	for (int k = 0; k < size; ++k) // arrays
	{
		cout << "\n";
		printf("Array[%d]\n", k);
		for (int i = 0; i < size; ++i) // rows
		{
			string arrOut;
			for (int j = 0; j < size; ++j) // cols
			{
				if (!arrOut.empty())
					arrOut += ", ";
				arrOut += std::to_string(w[k][i][j]);
			}
			cout << arrOut + "\n";
		}
	}
	cout << "\n";
}

int main()
{
	cout << "En kisa yol probleminin Floyd-Warshall algoritmasi kullanilarak paralel programlama ile cozumu\n";

	float** yollar = new float*[4];

	yollar[0] = new float[4];
	yollar[0][0] = 0;
	yollar[0][1] = 3;
	yollar[0][2] = INFINITY;
	yollar[0][3] = 7;

	yollar[1] = new float[4];
	yollar[1][0] = 8;
	yollar[1][1] = 0;
	yollar[1][2] = 2;
	yollar[1][3] = INFINITY;

	yollar[2] = new float[4];
	yollar[2][0] = 5;
	yollar[2][1] = INFINITY;
	yollar[2][2] = 0;
	yollar[2][3] = 1;

	yollar[3] = new float[4];
	yollar[3][0] = 2;
	yollar[3][1] = INFINITY;
	yollar[3][2] = INFINITY;
	yollar[3][3] = 0;

	float*** sonuc = floyd_warshall(4, yollar);
	printArrayQube(4, sonuc);
	
	delete[] yollar;
	delete[] sonuc;
}