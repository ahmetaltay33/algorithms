// test-app.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#define  ARRAYSIZE	10
#define  MASTER		0

int data[ARRAYSIZE];

int main(int argc, char* argv[])
{
  int   numtasks, taskid, rc, dest, offset, i, j, tag1,
    tag2, source, chunksize, leftover;
  MPI_Status status;
  void printArr(int myoffset, int chunk, int myid);

  /***** Initializations *****/
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
  printf("MPI task %d has started...\n", taskid);
  chunksize = (ARRAYSIZE / numtasks);
  leftover = (ARRAYSIZE % numtasks);
  tag2 = 1;
  tag1 = 2;

  /***** Master task only ******/
  if (taskid == MASTER) {

    /* Initialize the array */
    for (i = 0; i < ARRAYSIZE; i++) {
      data[i] = i;
    }
  	
    printf("Initialized array\n");
    printf("numtasks= %d  chunksize= %d  leftover= %d\n", numtasks, chunksize, leftover);

    /* Send each task its portion of the array - master keeps 1st part plus leftover elements */
    offset = chunksize + leftover;
    for (dest = 1; dest < numtasks; dest++) {
      MPI_Send(&offset, 1, MPI_INT, dest, tag1, MPI_COMM_WORLD);
      MPI_Send(&data[offset], chunksize, MPI_DOUBLE, dest, tag2, MPI_COMM_WORLD);
      printf("Sent %d elements to task %d offset= %d\n", chunksize, dest, offset);
      offset = offset + chunksize;
    }

    /* Master does its part of the work */
    offset = 0;
    printArr(offset, chunksize + leftover, taskid);

    /* Wait to receive results from each task */
    for (i = 1; i < numtasks; i++) {
      source = i;
      MPI_Recv(&offset, 1, MPI_INT, source, tag1, MPI_COMM_WORLD, &status);
      MPI_Recv(&data[offset], chunksize, MPI_DOUBLE, source, tag2,
        MPI_COMM_WORLD, &status);
    }

    /* Get final sum and print sample results */
    //MPI_Reduce(&mysum, &sum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);

    printArr(0, ARRAYSIZE, taskid);

  }  /* end of master section */



/***** Non-master tasks only *****/

  if (taskid > MASTER) {

    /* Receive my portion of array from the master task */
    source = MASTER;
    MPI_Recv(&offset, 1, MPI_INT, source, tag1, MPI_COMM_WORLD, &status);
    MPI_Recv(&data[offset], chunksize, MPI_DOUBLE, source, tag2,
      MPI_COMM_WORLD, &status);

    /* Do my part of the work */
    printArr(offset, chunksize, taskid);
    printf("Slave task: %d, offset: %d, chunk: %d\n", taskid, offset, chunksize);
  	
    /* Send my results back to the master task */
    dest = MASTER;
    MPI_Send(&offset, 1, MPI_INT, dest, tag1, MPI_COMM_WORLD);
    MPI_Send(&data[offset], chunksize, MPI_DOUBLE, MASTER, tag2, MPI_COMM_WORLD);

    /* Use sum reduction operation to obtain final sum */
    //MPI_Reduce(&mysum, &sum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);

  } /* end of non-master */


  MPI_Finalize();

}   /* end of main */


void printArr(int myoffset, int chunk, int myid) {
  int i;
  printf("Task ID: %d, Array: {", myid);
  std::string arr;
  for (i = myoffset; i < myoffset + chunk; i++) {
    if (!arr.empty())
      arr += ", ";
    arr += std::to_string(data[i]);
  }
  std::cout << arr;
  printf(" }\n");
}
