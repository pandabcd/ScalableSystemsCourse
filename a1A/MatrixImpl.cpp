#include "IMatrix.h"
#include <iostream>
#include<cstring>

using namespace std;

/**
 * 2D Matrix Implementation usign Arrays
 */
class ArrayMatrix: public IMatrix
{  
	private: 
		float **arr;
		bool is_init;
		int row_num,row,col,nnz; //row = number of rows
   
	public:
	
	ArrayMatrix()
	{ 
		is_init = 0;
		row_num = 0;
		row, col = 0;
		nnz = 0;
	}
 	
	/** Override the init function defined in the IMatrix interface */
	void init (int N, int M)
 	{ 
		if(is_init){
 			throw logic_error("Matrix already initiated!");
 		}

 		// cout<<"Initialising with "<<N<<" rows and "<<M<<" columns."<<endl;
		is_init = true;

		row = N;
		col = M;

		// Defining 2-d array dynamically
		arr = (float**)malloc(row*sizeof(float *)) ;
		
		for (int i=0; i<N; i++){
	         arr[i] = (float *)malloc(col * sizeof(float)); 
		}

		// Initialising the array with 0
		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				arr[i][j] = 0;
			}
		}
		
	}
	
	/** Override the append function defined in the IMatrix interface */
   void append (float* row_vals)
	{ 
	    if(row_num>row){
	    	throw out_of_range("Appending more rows than initialised");
	    }

	    // Assuming no violations in number of elements of row as mailed by Simmhan sir
	    // Inserting values in the current row
	    for(int j=0;j<col;j++){
	    	arr[row_num][j] = row_vals[j];

	    	// Having a dynamic count of nnz
	    	if(row_vals[j]!=0){
	    		nnz++;
	    	}
	    }
		row_num++;
	}

	
	/** Override the get function defined in the IMatrix interface */
	float get(int i, int j)
	{ 
	    if(i<0 || j<0 || i>row || j>col){
	    	throw out_of_range("Index to get is out of range");
	    }
	    return arr[i][j];
	}

	
	int row_count()
	{
		return row;
	}
	
	int col_count() 
	{
		return col;
	}

	int nnz_count()
	{
		return nnz;
	}

};

/**
 * 2D Matrix Implementation usign CSR
 */
class CSRMatrix: public IMatrix
{  	
	private: 
		// TODO
		// IR = cumulative sum of number of elements in row
		// IC = Indices of column
		float *arr_vals, *IR, *IC;
		bool is_init;
		int num_rows, num_cols, nnz, row_ind;
   
	public:
   
   // Setting pointers to null and rest values to 0(false)
	CSRMatrix()
	{ 
		is_init = 0;
		num_rows = 0;
		num_cols = 0;
		row_ind = 0;
		nnz = 0;
		IC = NULL;
		arr_vals = NULL;
		IR = NULL;
	}
 
 	/** Override the init function defined in the IMatrix interface */
	void init (int N, int M)
 	{ 
		if(is_init){
 			throw logic_error("Matrix already initiated!");
 		}
 		// cout<<"Creating CSR with "<<N<<" rows and "<<M<<" columns."<<endl;
		is_init = true;

		// First element is not necessarily 0 in this implementation(it is no. of nnz in first row)
		num_rows = N;
		row_ind = 0;
		num_cols = M;
		
	}
	

	/** Override the append function defined in the IMatrix interface */
   void append (float* row_vals)
	{ 	
		// Count of non-zero in the input row(not total nnz)
	    int nz_count = 0;
	
	    for(int i=0;i<num_cols;i++){
	    	if(row_vals[i]!=0){
	    		// Incrementing total nnz and nnz in the current row as well
	    		nz_count++;
	    		nnz++;

	    		// make this better
	    		// Also handle realloc fails
	    		IC = (float*)realloc(IC, nnz*sizeof(float));
	    		arr_vals = (float*)realloc(arr_vals, nnz*sizeof(float));

	    		IC[nnz-1] = i;
	    		arr_vals[nnz-1] = row_vals[i];
	    	}
	    }

	    
	    row_ind++;
	    // Try to remove this line

	    IR = (float*)realloc(IR, num_rows*sizeof(float));
	    IR[row_ind-1] = IR[row_ind-2] + nz_count;
	}

	
	/** Override the get function defined in the IMatrix interface */
	float get(int i, int j)
	{ 
	    // First element is number of non-zeros in first row(in this implementation)
	    if(i==0){
			if(IR[0]==0)
				return 0;
			else{
				for(int x=0;x<IR[0];x++){
					if(IC[x]==j){
						return arr_vals[x];
					}
				}
			}
		}

		if(IR[i]-IR[i-1]==0){
			return 0;
		}
		// Standard algo. for finding element in csr
		for(int x=IR[i-1];x<IR[i];x++){
			if(IC[x]==j){
				return arr_vals[x];
			}
		}
		return 0;
	}

	int row_count()
	{
		return num_rows;
	}
	
	int col_count() 
	{
		return num_cols;
	}

	int nnz_count()
	{
		return nnz;
	}
	
};