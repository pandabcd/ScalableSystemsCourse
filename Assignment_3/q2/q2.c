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

    
    int recv;

    FILE *fptr;
    char *filename = "q2-sample-input.txt";
   
    fptr = fopen(filename, "r");
    int *arr = (int *)malloc(arr_size*sizeof(int));
    int *query_arr = (int *)malloc(query_size*sizeof(int));
    int *result_arr = (int *)malloc(query_size*sizeof(int));

    for(int i=0;i<arr_size;i++){
        fscanf(fptr,"%d", &arr[i]);
    }

    for(int i=0;i<query_size;i++){
        fscanf(fptr,"%d", &query_arr[i]);
        result_arr[i] = -1;
    }

    // for(int i=0;i<query_size;i++){
    //     printf("Query : %d (Process %d)\n", query_arr[i], rank);
    // }
    

  double start_time = MPI_Wtime();


int final_result[query_size];
    for(int i=0;i<query_size;i++){
      final_result[i] = -1;
    }
    
    int receive_store[query_size][size];
    for(int i=0;i<query_size;i++){
      for(int j=0;j<size;j++){
        receive_store[i][j] = 0;
      }
    }    

    for(int q=0;q<query_size;q++){
      for(int j=0;j<size;j++){
          MPI_Irecv(&receive_store[q][j],1,MPI_INT,j,q,MPI_COMM_WORLD,&request_receive[q][j]);
      }
    }


    int done[query_size];
    for(int q=0;q<query_size;q++){
      done[q] = 0;
    }

// while(!done){
//             MPI_Test(&request_receive[j], &done, &status[j]);
//             // printf("Not done\n");
//         }

    int width = arr_size/size;
    int not_found = -1;
    
    // For every query
    for(int q=0;q<query_size;q++){
        int found = 0;
        // Every thread finds it part
        for(int i=rank*width;i<(rank+1)*width;i++){
            // done[q] =1 only if some process has found the element, and not just after msg. is received
            
            // if(i%10000==0){

            //   for(int p=0;p<size;p++){
            //     MPI_Test(&request_receive[q][p], &done[p], &status[p]);
            //     if(done[p]){
            //       final_result[q] = receive_store[q][p];
            //       break;  
            //     }
            //   }
            // }

            


            if(arr[i]==query_arr[q]){
                result_arr[q] = i;
                found = 1;
                // Send result to every processor if found
                for(int j=0;j<size;j++){
                    MPI_Isend(&i,1,MPI_INT,j,q,MPI_COMM_WORLD,&request_send[j]);
                    final_result[q] = i;
                }
                break;
            }
        }
        if(!found){
          int dummy = -1;
          for(int j=0;j<size;j++){
            MPI_Isend(&dummy,1,MPI_INT,j,q,MPI_COMM_WORLD,&request_send[j]);
          }
        }
    }
   

   MPI_Barrier(MPI_COMM_WORLD);


  


    // if(rank==0){
    //     for(int q=0;q<query_size;q++){
    //       for(int j=0;j<size;j++){
    //         printf("%d ", receive_store[q][j]);
    //       }
    //         printf("\n");
    //       }
    // }
    
  double total_time = MPI_Wtime() - start_time;

  if(rank==0){
    for(int q=0;q<query_size;q++){
      printf("%d\n", final_result[q]);
    }
    printf("Total time taken: %lf \n", total_time);
  }
  
    MPI_Finalize();

  return 0;
}