// floyd-warshall.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// ReSharper disable IdentifierTypo
// ReSharper disable StringLiteralTypo
// ReSharper disable CommentTypo
#include <iostream>
#include <mpi.h>
#include <random>
#include <string>
#include <Windows.h>
#include <ctime>

using namespace std;

const int MASTER = 0;
const int PATH_SIZE = 20;
float** paths;

float*** floyd_warshall(const int start, const int end, float** w)
{
	const int size = end - start;
	const int ksize = size + 1;
	float*** a = new float** [ksize];
	a[0] = w;
	for (int k = 1; k < ksize; ++k) // arrays
	{
		a[k] = new float* [size];
		for (int i = start; i < end; ++i) // rows
		{
			a[k][i] = new float[size];
			for (int j = start; j < end; ++j) // cols
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

void deleteArray(int size, float** w)
{
	for (int i = 0; i < size; ++i)
		delete[] w[i];
}

void deleteArray(int size, int size2, float*** w)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size2; ++j)
		{
			delete[] w[i][j];
		}
		delete[] w[i];
	}
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

	float*** sortestPaths = floyd_warshall(0, 3, testInput);
	print3DArray(5, 4, 4, sortestPaths);

	bool isSuccess = checkArrayEquality(4, 4, sortestPaths[4], expectedResult);

	if (isSuccess)
		cout << "Floyd-Warshall algoritmasi calisiyor. Dogrulama testi gecildi.\n";
	else
		cout << "Floyd-Warshall algoritmasi calismiyor. Dogrulama basarisiz!\n";

	deleteArray(5, 4, sortestPaths);
}

int main(int argc, char *argv[])
{
	int task_id, num_tasks, chunksize, leftover, tag2, tag1, offset,
		dest, i, source, j;
	float ***mysum, ***sum;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &task_id);
	MPI_Comm_size(MPI_COMM_WORLD, &num_tasks);
	printf("MPI task %d has started...\n", task_id);
	chunksize = (PATH_SIZE / num_tasks); // 1001 / 4 = 250
	leftover = (PATH_SIZE % num_tasks); // 1001 % 4 = 1
	tag2 = 1;
	tag1 = 2;
	
	if(task_id == MASTER) // Master Thread
	{
		paths = generateRandomPath(PATH_SIZE);
		printf("Yollar olusturuldu. Matris boyutu: %d        \n", PATH_SIZE);
		printf("Task ID: %d, Number of Tasks: %d\n", task_id, num_tasks);

		/* Send each task its portion of the array - master keeps 1st part plus leftover elements */
		offset = chunksize + leftover;
		for (dest = 1; dest < num_tasks; dest++) {
			MPI_Send(&offset, 1, MPI_INT, dest, tag1, MPI_COMM_WORLD);
			MPI_Send(&paths[offset], chunksize, MPI_DOUBLE, dest, tag2, MPI_COMM_WORLD);
			printf("Sent %d elements to task %d offset= %d\n", chunksize, dest, offset);
			offset += chunksize;
		}

		/* Master does its part of the work */
		offset = 0;
		mysum = floyd_warshall(offset, chunksize + leftover, paths);

		/* Wait to receive results from each task */
		for (i = 1; i < num_tasks; i++) {
			source = i;
			MPI_Recv(&offset, 1, MPI_INT, source, tag1, MPI_COMM_WORLD, &status);
			MPI_Recv(&paths[offset], chunksize, MPI_DOUBLE, source, tag2, MPI_COMM_WORLD, &status);
		}

		/* Get final sum and print sample results */
		MPI_Reduce(&mysum, &sum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);

		print3DArray(PATH_SIZE + 1, 10, 10, sum);

	}  /* end of master section */
	else // Slave Threads
	{
		/* Receive my portion of array from the master task */
		source = MASTER;
		MPI_Recv(&offset, 1, MPI_INT, source, tag1, MPI_COMM_WORLD, &status);
		MPI_Recv(&paths[offset], chunksize, MPI_DOUBLE, source, tag2, MPI_COMM_WORLD, &status);

		/* Do my part of the work */
		mysum = floyd_warshall(offset, chunksize, paths);

		/* Send my results back to the master task */
		dest = MASTER;
		MPI_Send(&offset, 1, MPI_INT, dest, tag1, MPI_COMM_WORLD);
		MPI_Send(&paths[offset], chunksize, MPI_DOUBLE, MASTER, tag2, MPI_COMM_WORLD);

		/* Use sum reduction operation to obtain final sum */
		MPI_Reduce(&mysum, &sum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);

	}  /* end of slaves */
	
	MPI_Finalize();

	return 0;
}