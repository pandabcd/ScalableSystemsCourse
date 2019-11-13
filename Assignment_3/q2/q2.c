#include <stdio.h>
#include<stdlib.h>
#include "mpi.h"

#define array_size 1000000
#define query_size 50

int main(int argc, char** argv){
  MPI_Status status;
  MPI_Request request;

  int rank,size;
  int done,myfound,nvalues;
  // Do we need to take double?
  int *b = (int *)malloc(array_size*sizeof(int));

  int i,j,dummy;
  FILE *infile;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  
  myfound=0;
  if (rank==0) {
    infile=fopen("data","r");
    for(i=0;i<size;++i) {
      fscanf(infile,"%d",&b[i]);
    }
  }

  MPI_Bcast(b,size,MPI_INT,0,MPI_COMM_WORLD);
  MPI_Irecv(&dummy,1,MPI_INT,MPI_ANY_SOURCE,86,MPI_COMM_WORLD,&request);
  MPI_Test(&request,&done,&status);
  
  nvalues=array_size/size;
  int low = rank*nvalues;
  int high = (rank +1)*nvalues;
  i=low;
  
  printf("Searching in %d and %d\n", low, high);
  // while(!done && i>=low && i<high) {
  //     if (b[i]==11) {
  //       dummy=123;
  //       for(j=0;j<size;++j) {
  //         MPI_Send(&dummy,1,MPI_INT,j,86,MPI_COMM_WORLD);
  //       }
  //       printf("P:%d found it at global index %d\n",rank,i);
  //       myfound=1;
  //     }
  //     MPI_Test(&request,&done,&status);
  //     ++i;
  // }
  // if (!myfound) {
  //   printf("P:%d stopped at global index %d\n",rank,i-1);
  // }
  MPI_Finalize();
}
