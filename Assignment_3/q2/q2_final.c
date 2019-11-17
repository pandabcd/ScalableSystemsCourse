#include <stdio.h>
#include<stdlib.h>
#include "mpi.h"

#define arr_size 1000000
#define query_size 50

int main(int argc, char **argv){
    int rank,size;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);    
    MPI_Status status[size];
    MPI_Request request_send[size], request_receive[query_size][size];

    FILE *fptr;
    char *filename = "q2-sample-input.txt";
    fptr = fopen(filename, "r");
    double *arr = (double *)malloc(arr_size*sizeof(double));
    double *query_arr = (double  *)malloc(query_size*sizeof(double));
    double *result_arr = (double *)malloc(query_size*sizeof(double));

    for(int i=0;i<arr_size;i++){
        fscanf(fptr,"%lf", &arr[i]);
    }
    for(int i=0;i<query_size;i++){
        fscanf(fptr,"%lf", &query_arr[i]);
        result_arr[i] = -1;
    }

    //************** Timing starts from here ***************//
    double start_time = MPI_Wtime();
    
    // Array containing the received signals(index) from each process
    int receive_store[query_size][size];
    for(int i=0;i<query_size;i++){
      for(int j=0;j<size;j++){
        receive_store[i][j] = -1;
      }
    }    

    // Receiving signals before sending so that there is no wait once signal is sent
    for(int q=0;q<query_size;q++){
      for(int j=0;j<size;j++){
          MPI_Irecv(&receive_store[q][j],1,MPI_DOUBLE,j,q,MPI_COMM_WORLD,&request_receive[q][j]);
      }
    }

    // Array containing the final result
    double final_result[query_size];
    for(int i=0;i<query_size;i++){
      final_result[i] = -1;
    }

    // Array having boolean value to signal whether query q has been executed by process p or not
    int done[query_size][size];
    for(int q=0;q<query_size;q++){
      for(int p=0;p<size;p++){
        done[q][p] = 0;
      }
    }

    int width = arr_size/size;      // Defining search region for each process
    int dummy = -1;                 //Dummy variable to be sent if element is not found
    
    for(int q=0;q<query_size;q++){
        int found = 0;
        // Every thread finds it part
        for(int i=rank*width;i<(rank+1)*width;i++){
          // Checking if some other process has found the answer regularly
          // How often this should be checked depends on the data distribution
          if(i%10000==0){
            for(int p=0;p<size;p++){
              MPI_Test(&request_receive[q][p], &done[q][p], &status[p]);
              if(done[q][p]){
                if(rank==0){
                  printf("Done!(Process %d) ... received %d index for query %d\n", rank, receive_store[q][p], q);

                }
                final_result[q] = receive_store[q][p];
                found = 1;
                break;  
              }
            }
          }

            // Found by other process in the if statement above
          if(found){
             break;
          }
            
          // If not found by other process, carry on with searching
          if(arr[i]==query_arr[q]){
            result_arr[q] = i;
            found = 1;
            // Send result to every processor if found
            for(int j=0;j<size;j++){
              MPI_Isend(&i,1,MPI_DOUBLE,j,q,MPI_COMM_WORLD,&request_send[j]);
              final_result[q] = i;
              }
              break;
            }
          }

        // Send -1 to everyone if not found
        if(!found){
          for(int j=0;j<size;j++){
            MPI_Isend(&dummy,1,MPI_DOUBLE,j,q,MPI_COMM_WORLD,&request_send[j]);
          }
        }
    }
   
  // Making sure that every process has sent and received the required signals
    MPI_Barrier(MPI_COMM_WORLD);

   //***************** Timing ends here ********************** 
    double total_time = MPI_Wtime() - start_time;
  

  // Process 0 printing the result
    if(rank==0){
      for(int q=0;q<query_size;q++){
        for(int j=0;j<size;j++){
          printf("%d ", receive_store[q][j]);
          // final_result[q] = final_result[q] > receive_store[q][j] ?  final_result[q] : receive_store[q][j];
        }
        printf("\n");
      }
    }
   
    // Writing to file
    FILE *wptr = fopen("output.txt", "w");
    if(rank==0){
      for(int q=0;q<query_size;q++){
        printf("%lf\n", final_result[q]);
        fprintf(wptr, "%lf\n", final_result[q]);
      }
      printf("Average time taken per query(for %d queries): %lf \n", query_size, total_time/query_size);
    }

    MPI_Finalize();

    return 0;
}



// Solve edge case of indices