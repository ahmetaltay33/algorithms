// floyd-warshall.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int sira, boyut;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &sira);
	MPI_Comm_size(MPI_COMM_WORLD, &boyut);
	printf("Merhaba dunya %d. islem: Toplam %d islem var.\n", sira, boyut);
	MPI_Finalize();
	return 0;
}