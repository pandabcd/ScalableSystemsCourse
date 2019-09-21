#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include "MatrixImpl.cpp"
#include<time.h>

#include<fstream>
#include<sstream>

using namespace std;


/**
  * Runner code that serves as harness for invoking various functions required 
  * to be implemented for this assignment.
  * You may modify this code, but need to retain the input parameter signature and 
  * output requirements specified in the assignment.
  */  
  
/////////////////////////////////////////////////////////////////////////////
// Code for loading matrix from input_file into array impl and returning object
IMatrix* load_arr(char* input_file) 
{
	cout << "LOAD: ARRAY"  << endl;
	ifstream fin(input_file);

	if(fin.fail()){
		cerr<<"Fin failed!!"<<endl;
	}

	int num_rows, num_cols;
	fin>>num_rows>>num_cols;
		
	ArrayMatrix* array_matrix = new ArrayMatrix;
	
	array_matrix->init(num_rows, num_cols);

	for(int i=0;i<num_rows;i++){
		float curr_row[num_cols];
		for(int j=0;j<num_cols;j++){
			fin>>curr_row[j];
		}
		array_matrix->append(curr_row);
	}
	fin.close();
	return array_matrix;

}

// Code for loading matrix from input_file into CSR impl and returning object
// Exactly the same as above but with csr object
IMatrix* load_csr(char* input_file) 
{
	cout << "LOAD: CSR"  << endl;
	ifstream fin(input_file);

	if(fin.fail()){
		cerr<<"FIN failed!!"<<endl;
	}

	int num_rows, num_cols;
	fin>>num_rows>>num_cols;
		
	CSRMatrix* csr_matrix = new CSRMatrix;

	csr_matrix->init(num_rows, num_cols);

	for(int i=0;i<num_rows;i++){
		float curr_row[num_cols];
		for(int j=0;j<num_cols;j++){
			fin>>curr_row[j];
		}
		csr_matrix->append(curr_row);
	}
	fin.close();
	return csr_matrix;

}

// Code for initializing an empty matrix using array impl with rows and cols as 
	// dimensions, and returning the object
IMatrix* init_arr(int rows, int cols) 
{
	ArrayMatrix* array_matrix = new ArrayMatrix;
	array_matrix->init(rows, cols);
	return array_matrix;
}


// Code for initializing an empty matrix using CSR impl with rows and cols as 
	// dimensions, and returning the object
IMatrix* init_csr(int rows, int cols) 
{
	CSRMatrix* csr_matrix = new CSRMatrix;
	csr_matrix->init(rows,cols);
	return csr_matrix;
}

// prints matrix as TSV to output_file
void print_mat(IMatrix* mat, char* output_file) 
{
	cout<<"PRINTING to: "<<output_file  << endl;

	ofstream fout(output_file);

	// Writing row and column number
	cout<<mat->row_count()<<endl;
	if(fout.is_open()){
		fout << mat->row_count() << "\t" << mat->col_count() << "\n";
	}
	else{
		cout << "Unable to open file!";
		return;
	}

	// Writing individual elements
	for(int i=0;i<mat->row_count();i++){
		for(int j=0;j<mat->col_count();j++){
			fout << mat->get(i,j) << "\t";
		}
		fout<<"\n";
	}
	fout.close();
}

/////////////////////////////////////////////////////////////////////////////
// Simple function to load an input file and output the same to another file
void load(char* mat_type, char* input_file, char* output_file)
{
	IMatrix* mat1;

	clock_t start, end;
	start = clock();
	if (strcmp("array", mat_type)==0) 
    { 
		mat1 = load_arr(input_file);
    }  
	else if (strcmp("csr", mat_type)==0) // TODO: time this region and print "load,csr,output_file,time_millisec"
	{  
		mat1 = load_csr(input_file);
	}
	else
		cout << "[load] invalid matrix type input seen: " << mat_type << endl;
	end = clock();
	double time_used = ((double)end-start)/CLOCKS_PER_SEC;
	cout << "Time taken to load(in s): " << time_used << endl;

	// Timing the write method
	start = clock();
	// store the loaded matrix mat1 in output file given by output_file
	print_mat(mat1, output_file);
	end = clock();
	time_used = ((double)end-start)/CLOCKS_PER_SEC;
	cout << "Time taken to write(in s): " << time_used << endl;


	return;
}

/////////////////////////////////////////////////////////////////////////////
// Code for finding the transpose of mat1 and storing in a new matrix mat2
void transpose(IMatrix* mat1, IMatrix* mat2) 
{	
	for(int i=0;i<mat1->col_count();i++){

		float dummy_row[mat1->row_count()];
		for(int j=0;j<mat1->row_count();j++){
			dummy_row[j] = mat1->get(j,i);
		}
		mat2->append(dummy_row);
	}
	return;
}


void transpose(char* mat_type, char* input_file, char* output_file)
{ 
	IMatrix* mat1, *mat2;
	
	if (strcmp("array", mat_type)==0) 
    { 
    	cout << "TRASNPOSE: ARRAY" << endl;
		mat1 = load_arr(input_file);		
		mat2 = init_arr(mat1->col_count(), mat1->row_count());
    }  
	else if (strcmp("csr", mat_type)==0)
	{
		cout<<"TRASNPOSE: CSR"<< endl;	
		mat1 = load_csr(input_file);
		mat2 = init_csr(mat1->col_count(), mat1->row_count());
	}
	else {
		cout << "[transpose] invalid matrix type input seen: " << mat_type << endl;
		return;
	}
	
	// Timing the transpose method
	clock_t start = clock();
	transpose(mat1, mat2);
	clock_t end = clock();
	double time_used = ((double)end-start)/CLOCKS_PER_SEC;
	cout << "Time taken to transpose(in s): " << time_used << endl;

	// storing output matrix mat2 in file given by output_file
	print_mat(mat2, output_file);
	return;
}



/////////////////////////////////////////////////////////////////////////////
// Code for multiplying the mat1 and mat2 and storing in a third matrix mat3
void multiply(IMatrix* mat1, IMatrix* mat2, IMatrix* mat3) 
{	
	if(mat1->col_count()!=mat2->row_count()){
		cout<<"Error! Check compatibility of multiplication";
		throw logic_error("Incompatible matrices for multiplication");
		return;
	}

	int l = mat1->row_count(), m = mat1->col_count(), n = mat2->col_count();

	// Normal matrix multiplication where we call append after computing every row
	for(int i=0;i<l;i++){
		float dummy_row[n] ={0};
		for(int j=0;j<n;j++){
			for(int k=0;k<m;k++){
				dummy_row[j] += mat1->get(i,k)*mat2->get(k,j);
			}
		}
		mat3->append(dummy_row);
	}
	return;
}

void multiply(char* mat_type, char* input_file1, char* input_file2, char* output_file)
{
	IMatrix* mat1, *mat2, *mat3;

	if (strcmp("array", mat_type)==0) 
    { 
    	cout << "MULTIPLY ARRAY: " << endl;
		mat1 = load_arr(input_file1);
		mat2 = load_arr(input_file2);

		int r1 = mat1->row_count(), c1 = mat1->col_count(), r2 = mat2->row_count(), c2 = mat2->col_count();
		if(c1!=r2){
			cout << "Incompatible matrix multiplication. Check dimensions!!";
			throw logic_error("Incompatible matrices for multiplication");
			return;
		}
		mat3 = init_arr(mat1->row_count(), mat2->col_count());
	}  

	else if (strcmp("csr", mat_type)==0)
	{
		cout << "MULTIPLY CSR: " << endl;
		mat1 = load_csr(input_file1);
		mat2 = load_csr(input_file2);

		int r1 = mat1->row_count(), c1 = mat1->col_count(), r2 = mat2->row_count(), c2 = mat2->col_count();
		if(c1!=r2){
			cout << "Incompatible matrix multiplication. Check dimensions!!";
			return;
		}
		mat3 = init_csr(mat1->row_count(), mat2->col_count());
	}
	else {
		cout <<"[multiply] invalid matrix type input seen: " << mat_type << endl;
		return;
	}
	
	// TODO: time this method and print "multiply,mat_type,output_file,time_millisec"
	
	clock_t start = clock();
	// Multiply matrices
	multiply(mat1, mat2, mat3);
	clock_t end = clock();
	double time_used = ((double)end-start)/CLOCKS_PER_SEC;
	cout << "Time taken to multiply(in s): " << time_used << endl;

	// store output matrix mat3 in file given by output_file
	print_mat(mat3, output_file);

	return;
}

/////////////////////////////////////////////////////////////////////////////
// Code for multiplying using block matrix multiplication
// the matrices mat1 and mat2 and storing in a third matrix mat3
	
void bmultiply(IMatrix* mat1, IMatrix* mat2, IMatrix* mat3) 
{	
	int r1 = mat1->row_count(), c1 = mat1->col_count(), r2 = mat2->row_count(), c2 = mat2->col_count();
	float dummy[r1][c2] = {0};

	// Defining the box in first three for loops
	for(int i=0;i<r1;i+=block_size){
		for(int j=0;j<c2;j+=block_size){
			for(int k=0;k<c1;k+=block_size){

				// Doing the actual multiplications here
				for(int ii=0;ii<block_size;ii++){
					for(int jj=0;jj<block_size;jj++){
						for(int kk=0;kk<block_size;kk+){
							dummy[i+ii][j+jj] += mat1->get(i+ii,k+kk)*mat2->get(k+kk,j+jj);
						}
					}
				}
			}
		}
	}

	float dummy_row[c2];
	for(int i=0;i<r1;i++){
		for(int j=0;j<c2;j++){
			dummy_row[j] = dummy[i][j];
		}
		mat3->append(dummy_row);
	}
	return;
}

void bmultiply(char* mat_type, char* input_file1, char* input_file2, char* output_file)
{
	IMatrix* mat1, *mat2, *mat3;

	if (strcmp("array", mat_type)==0) 
    { 
		mat1 = load_arr(input_file1);
		mat2 = load_arr(input_file2);

		int r1 = mat1->row_count(), c1 = mat1->col_count(), r2 = mat2->row_count(), c2 = mat2->col_count();
		if(c1!=r2){
			cout << "Incompatible matrix multiplication. Check dimensions!!";
			return;
		}
		if(r1!=c1 || r1!=r2 || r1!=c2){
			cout << "BMULTIPLY : Not square matrices with dimensions in power of 2(as mentioned in mail).";
			return;
		}
		mat3 = init_arr(mat1->row_count(), mat2->col_count());
	}  

	else if (strcmp("csr", mat_type)==0)
	{
		mat1 = load_csr(input_file1);
		mat2 = load_csr(input_file2);
		int r1 = mat1->row_count(), c1 = mat1->col_count(), r2 = mat2->row_count(), c2 = mat2->col_count();		
		if(c1!=r2){
			cout << "Incompatible matrix multiplication. Check dimensions!!";
			return;
		}
		if(r1!=c1 || r1!=r2 || r1!=c2){
			cout << "BMULTIPLY : Not square matrices with dimensions in power of 2(as mentioned in mail).";
			return;
		}
		mat3 = init_csr(mat1->row_count(), mat2->col_count());
	}
	else {
		cout << "[bmultiply] invalid matrix type input seen: " << mat_type << endl;
		return;
	}
	
	// TODO: time this method and print "bmultiply,mat_type,output_file,time_millisec"
	bmultiply(mat1, mat2, mat3);
	
	// store output matrix mat3 in file given by output_file
	print_mat(mat3, output_file);

	return;
}


/////////////////////////////////////////////////////////////////////////////

int main(int n, char *argv[])
{

	if(strcmp("load", argv[1])==0)
	{
		load(argv[2], argv[3], argv[4]);
	}
    else if( strcmp("transpose", argv[1])==0)
	{
		transpose(argv[2], argv[3], argv[4]);
	}
    else if(strcmp("multiply", argv[1])==0 )
	{
        multiply(argv[2], argv[3], argv[4], argv[5]);
	}
    else if(strcmp("bmultiply", argv[1])==0)
	{
        bmultiply(argv[2], argv[3], argv[4],argv[5]);
	} else 
		cout << "[main] invalid input parameters. Valid usage is..." << endl;

	return 0;
}