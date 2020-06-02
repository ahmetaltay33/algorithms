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
const int PATH_SIZE = 10;
float** allPaths;
float** tmpPaths;

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

float** floyd_warshall(int offset, int chunk, float** w)
{
	const int size = chunk;
	const int ksize = size + 1;
	float*** a = new float** [ksize];
	a[0] = w;
	for (int k = 1; k < ksize; ++k) // arrays
	{
		a[k] = new float* [size];
		for (int i = offset; i < offset + chunk; ++i) // rows
		{
			a[k][i] = new float[size];
			for (int j = offset; j < offset + chunk; ++j) // cols
			{
				a[k][i][j] = min(a[k - 1][i][j], (a[k - 1][i][k - 1] + a[k - 1][k - 1][j]));
			}
		}
	}
	float** na = new float* [size];
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			na[i][j] = a[size][i][j];
		}
	}
	deleteArray(ksize, size, a);
	return na;
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

int main(int argc, char *argv[])
{
	int task_id, num_tasks, chunksize, leftover, tag2, tag1, offset,
		dest, i, source, j;
	float **myShortestPath, **shortestPath;
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
		allPaths = generateRandomPath(PATH_SIZE);
		printf("Yollar olusturuldu. Matris boyutu: %d        \n", PATH_SIZE);
		printf("Task ID: %d, Number of Tasks: %d\n", task_id, num_tasks);

		/* Send each task its portion of the array - master keeps 1st part plus leftover elements */
		offset = chunksize + leftover;
		for (dest = 1; dest < num_tasks; dest++) {
			MPI_Send(&offset, 1, MPI_INT, dest, tag1, MPI_COMM_WORLD);
			MPI_Send(&allPaths[offset], chunksize, MPI_DOUBLE, dest, tag2, MPI_COMM_WORLD);
			printf("Sent %d elements to task %d offset= %d\n", chunksize, dest, offset);
			offset += chunksize;
		}

		/* Master does its part of the work */
		offset = 0;
		myShortestPath = floyd_warshall(offset, chunksize + leftover, allPaths);

		/* Wait to receive results from each task */
		for (i = 1; i < num_tasks; i++) {
			source = i;
			MPI_Recv(&offset, 1, MPI_INT, source, tag1, MPI_COMM_WORLD, &status);
			MPI_Recv(&tmpPaths[offset], chunksize, MPI_FLOAT, source, tag2, MPI_COMM_WORLD, &status);
			
		}

		print2DArray(PATH_SIZE, PATH_SIZE, shortestPath);

	}  /* end of master section */
	else // Slave Threads
	{
		/* Receive my portion of array from the master task */
		source = MASTER;
		MPI_Recv(&offset, 1, MPI_INT, source, tag1, MPI_COMM_WORLD, &status);
		MPI_Recv(&tmpPaths[offset], chunksize, MPI_FLOAT, source, tag2, MPI_COMM_WORLD, &status);

		/* Do my part of the work */
		myShortestPath = floyd_warshall(offset, chunksize, tmpPaths);

		/* Send my results back to the master task */
		dest = MASTER;
		offset = 0;
		MPI_Send(&offset, 1, MPI_INT, dest, tag1, MPI_COMM_WORLD);
		MPI_Send(&myShortestPath[offset], chunksize, MPI_FLOAT, dest, tag2, MPI_COMM_WORLD);

	}  /* end of slaves */
	
	MPI_Finalize();

	return 0;
}