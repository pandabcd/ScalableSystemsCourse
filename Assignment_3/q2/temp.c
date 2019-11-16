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
    MPI_Request request_send[size], request_receive[size];

    
  	int recv;

    FILE *fptr;
    char *filename = "q2-sample-input.txt";
    // char *filename = "sample_input.txt";

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

    for(int i=0;i<query_size;i++){
        printf("Query : %d (Process %d)\n", query_arr[i], rank);
    }
    

    
    int dummy = 42;
    int width = arr_size/size;
    int not_found = -1;
    

    for(int q=0;q<query_size;q++){
        for(int i=rank*width;i<(rank+1)*width;i++){
            if(arr[i]==query_arr[q]){
                result_arr[q] = i;
                // remove this break
                // break;
            }
        }
    }

    // printf("Sending the following result (Process %d)\n", rank);
    for(int i=0;i<size;i++){
        MPI_Isend(result_arr,query_size,MPI_INT,i,0,MPI_COMM_WORLD,&request_send[i]);
        // for(int q=0;q<query_size;q++)
        //     printf("%d (Process %d)\n", result_arr[q], rank);
    }
    // if(not_found==-1){
    //     for(int j=0;j<size;j++){
    //             MPI_Isend(&not_found,1,MPI_INT,j,0,MPI_COMM_WORLD,&request_send[j]);
           
    //     }
    //     printf("I am a useless thread. My id is %d (not found = %d)\n", rank, not_found);
    // }


    int receive_result[query_size] = {0};

    int final_recv = -1;
    for(int j=0;j<size;j++){
        // int *receive_result = NULL;
        // receive_result = (int *)realloc(receive_result, query_size*sizeof(int));
        // for(int i=0;i<query_size;i++){
        //     receive_result[i] =22222222;
        //     printf("Receive results %d (Process %d)\n", receive_result[i], rank);
        // }
        int done = 0;

        MPI_Irecv(receive_result,query_size,MPI_INT,j,0,MPI_COMM_WORLD,&request_receive[j]);
        while(!done){
            MPI_Test(&request_receive[j], &done, &status[j]);
            // printf("Not done\n");
        }

        

        // printf("Printing Result (Process %d)\n", rank);
        // for(int q=0;q<query_size;q++){
        //     printf("%d %d (Process %d)\n",q, receive_result[q], rank);
        // }

        for(int q=0;q<query_size;q++){
            result_arr[q] = result_arr[q] > receive_result[q] ? result_arr[q] : receive_result[q]; 
        }

        // if(recv!=-1){
        //     final_recv = recv;
        // }
    }


    if(rank==0){
        for(int q=0;q<query_size;q++){
            printf("%d\n", result_arr[q]);
        }
    }

  
    MPI_Finalize();

	return 0;
}