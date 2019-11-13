#include <stdio.h>
#include<stdlib.h>
#include "mpi.h"

#define arr_size 40
#define query_size 1

int main(int argc, char **argv){
    int rank,size;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    
    
    MPI_Status status[size];
    MPI_Request request_send[size], request_receive[size];

    
  	int recv;

    FILE *fptr;
    // char *filename = "q2-sample-input.txt";
    char *filename = "sample_input.txt";

    fptr = fopen(filename, "r");
    int *arr = (int *)malloc(arr_size*sizeof(int));
    int *query_arr = (int *)malloc(query_size*sizeof(int));

    for(int i=0;i<arr_size;i++){
        fscanf(fptr,"%d", &arr[i]);
    }
    // for(int i=0;i<query_size;i++){
    //     fscanf(fptr,"%d ", &query_arr[i]);
    // }

    query_arr[0] = arr[33];
    

    // for(int i=0;i<size;i++){
    //     if(i!=rank){
    //         MPI_Isend(&rank,1,MPI_INT,i,86,MPI_COMM_WORLD,&request);
    //     }
    // }

    // MPI_Irecv(&recv,1,MPI_INT,MPI_ANY_SOURCE,86,MPI_COMM_WORLD,&request);
    int dummy = 42;
    int width = arr_size/size;

    int not_found = -1;
    
    // printf("I am process %d and I am searching from %d to %d \n", rank, rank*width, (rank+1)*width);
    for(int i=rank*width;i<(rank+1)*width;i++){
        // if(rank==8){
        //     printf("%d %d\n", arr[i], query_arr[0]);
        // }
        if(arr[i]==query_arr[0]){
            printf("Element found by process %d at %d\n", rank, i);
            not_found = 0;
            for(int j=0;j<size;j++){
                // if(j!=rank){
                    MPI_Isend(&i,1,MPI_INT,j,0,MPI_COMM_WORLD,&request_send[j]);
                // }
            }
            break;
        }
    }

    if(not_found==-1){
        for(int j=0;j<size;j++){
            // if(j!=rank){
                MPI_Isend(&not_found,1,MPI_INT,j,0,MPI_COMM_WORLD,&request_send[j]);
            // }
        }
        printf("I am a useless thread. My id is %d (not found = %d)\n", rank, not_found);
    }

    int final_recv = -1;
    for(int j=0;j<size;j++){
        // if(j==rank){
        //     continue;
        // }
        int done = 0;
        MPI_Irecv(&recv,1,MPI_INT,j,0,MPI_COMM_WORLD,&request_receive[j]);
        while(!done){
            MPI_Test(&request_receive[j], &done, &status[j]);
        }
        if(recv!=-1){
            final_recv = recv;
        }
    }

    // if(rank==0)
        printf("Received %d(process %d)\n", final_recv, rank);

    // int done;
    // for(int j=0;j<size;j++){
    //     done = 0;
    //     if(j!=rank){
    //         while(!done){
    //             MPI_Test(&request_receive[j], &done, &status[j]);
        
    //             MPI_Irecv(&recv,1,MPI_INT,j,0,MPI_COMM_WORLD,&request_receive[j]);
    //             printf("Process %d received %d \n", rank, recv);
    //             if(recv!=-1){
    //                 printf("Element found bitch! @ (message by %d) %d \n", rank, recv);
    //             }
    //             done =1;
    //         }
    //     }
    // }


    // int done=0;
    // int local_done =0 ;
    // while(done!=size-1){
    //     done = 0;
    //     for(int i=0;i<size;i++){
    //         MPI_Test(&request[i],&local_done,&status[i]);
    //         if(local_done){
    //             done++;
    //         }
    //     }
    // }


    // printf("I am process %d and I received %d \n", rank, recv);

    MPI_Finalize();

	return 0;
}