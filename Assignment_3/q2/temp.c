#include <stdio.h>
#include<stdlib.h>
#include "mpi.h"

#define arr_size 1000000
#define query_size 50

int main(int argc, char **argv){
	MPI_Status status;
	MPI_Request request;

    int rank,size;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
  
    
  	int recv;

    FILE *fptr;
    char *filename = "q2-sample-input.txt";
    fptr = fopen(filename, "r");
    int *arr = (int *)malloc(arr_size*sizeof(int));
    int *query_arr = (int *)malloc(query_size*sizeof(int));
    for(int i=0;i<size;i++){
        fscanf(fptr,"%d ", &arr[i]);
    }
    for(int i=0;i<query_size;i++){
        fscanf(fptr,"%d ", &query_arr[i]);
    }

    

    for(int i=0;i<size;i++){
        if(i!=rank){
            MPI_Isend(&rank,1,MPI_INT,i,86,MPI_COMM_WORLD,&request);
        }
    }

    MPI_Irecv(&recv,1,MPI_INT,MPI_ANY_SOURCE,86,MPI_COMM_WORLD,&request);
    
    int done=0;

    while(!done){
        printf("Not done!\n");
        MPI_Test(&request,&done,&status);
    }


    printf("I am process %d and I received from %d \n", rank, recv);

    MPI_Finalize();

	return 0;
}