#include<stdio.h>
#include<string.h>
#include "BinTreeImpl.cpp"
#include<fstream>
#include<sstream>
#include<time.h>
#include<chrono>

using namespace std;

// string output_1, output_2;

// *********************
// key_add = address of the key array
// val_add = address of the val array
// Function to get key, val pairs for insertions(returns insertion length)
int load_data(int** key_add, float** val_add, string data_file){
	// cout << "Prefetching data: " << data_file <<endl;

	// **** READING FILE ****
	// Have fin fail check
	ifstream fin(data_file);
	if(fin.fail()){
		cerr << "Unable to load file: " << data_file <<endl;
		exit(0);
  	}
	string s;
	char c;
	int len =0;

	// Initial size of the arrays
	int size = 10;
	*key_add = (int *)malloc(size*sizeof(int));
	*val_add = (float*)malloc(size*sizeof(float));


	int k;
	float v;

	// Checking if EOF is reached
	while(fin.peek() != EOF){
		// Realloc if memory is full
		if(len==size){
			size *=2;
			*key_add = (int*)realloc(*key_add, size*sizeof(int));
			*val_add = (float*)realloc(*val_add, size*sizeof(float));
		}

		// Get a string in 'key:value' format
		fin >> s;
		
		// s1 will have the int part(char array)
		// s2 will have the flt part(char array)
		char s1[s.length()],s2[s.length()];
		int i=0;
		while(s[i]!= ':'){
			s1[i]= s[i];
			i++;
		}

		s1[i] = '\0';
		i++;
		int j=0;
		while(i<s.length()){
			s2[j] = s[i];
			j++; i++ ;
		}

		// Converting char array to int and float respectively
		k = atoi(s1);
		v = atof(s2);
		(*key_add)[len] = k; 
		(*val_add)[len] = v;
		len ++ ;
		
	}
	len--;
	
	// cout << "Data loading succesful..." << endl;
	return len;
}

// Function to get queries in an array(returns query length)
// Passing address of the query array
int load_query(int** query_add, string query_file){
	// cout << "Loading queries: " << query_file << endl;
	float * ans = NULL;

	// Add fin fail
	ifstream fin(query_file);
	if(fin.fail()){
		cerr << "Failed to load query file: " << query_file << endl;
		exit(0);
	}
	
	int len =0;

	// Initial query size
	int size = 10;
	*query_add = (int *)malloc(size*sizeof(int));
	
	int q;

	// Reading till EOF is reached
	while(fin.peek() != EOF){
		int el;

		// Doubling memory if limit is reached
		if(len==size){
			size *=2;
			*query_add = (int*)realloc(*query_add, size*sizeof(int));
		}

		fin >> el;
		(*query_add)[len] = el;
		len++;
	}
	len--;
	
	return len;
}

// Chrono stuff referred from https://www.geeksforgeeks.org/chrono-in-c/
// Simple function to query a given tree from a given query array and returns the answer to the queries
float* query_tree(IBinTree* ibt, int * query,const int query_length){
	// cout << "Querying: " << query_length <<endl;

	float* ans = (float *)malloc(query_length*sizeof(float));
	
	std::chrono::time_point<std::chrono::system_clock> start, end; 
	chrono::duration<double> time_taken;

	double max_time = FLT_MIN, min_time = FLT_MAX, total_time = 0;

	for(int i=0;i<query_length;i++){
		start = chrono::system_clock::now();
		
		ans[i] = ibt->find(query[i]);
		
		end = chrono::system_clock::now();
		time_taken = end-start;
		long double time_taken_s = time_taken.count();
		// cout<< time_taken.count() <<endl;

		max_time = max(max_time, time_taken.count());
		min_time = min(min_time, time_taken.count());
		total_time += time_taken.count();
	}
	// cout<<(total_time/query_length)<<","<<min_time<<","<<max_time<<","<<total_time;
	// output_2 += to_string(query_length) + "," + to_string((float)total_time/(float)query_length) + "," + to_string(min_time) + "," + to_string(max_time) + "," + to_string(total_time);
	return ans;
}

// Funtion to print the output to a file
void print_output(float* ans,const int ans_length, string output_file ){
	ofstream fout(output_file);

	for(int i=0;i<ans_length;i++){
		fout << ans[i] << "\t" ;
	}
	// fout.close();
}

// *************** Specific insert functions *******************
// Adds data in tree and returns the tree
LinkedBinSearchTree* insert_lbst(const int* key, const float* val, const int insert_len){
	// cout << "Adding data to lbst..." << endl;
	// output_1 += insert_len + ",";
	LinkedBinSearchTree* lbst = new LinkedBinSearchTree;
	
	for(int i=0;i<insert_len;i++){
		lbst->insert(key[i], val[i]);
	}

	return lbst;
}

// Adds data in tree and returns the tree
ArrayBinSearchTree* insert_abst(const int* key, const float* val, const int insert_len){
	// cout << "Adding data to abst..." << endl;
	// output_1 += insert_len + ",";
	ArrayBinSearchTree* abst = new ArrayBinSearchTree;

	for(int i=0;i<insert_len;i++){
		abst->insert(key[i], val[i]);
	}

	return abst;
}

// Adds data in tree and returns the tree
LinkedBinTree* insert_lbt(const int* key, const float* val, const int insert_len){
	// cout << "Adding data to lbt..." << endl;
	// output_1 += insert_len + ",";
	LinkedBinTree* lbt = new LinkedBinTree;

	for(int i=0;i<insert_len;i++){
		lbt->insert(key[i], val[i]);
	}

	return lbt;
}

// Adds data in tree and returns the tree
ArrayBinTree* insert_abt(const int* key, const float* val, const int insert_len){
	// cout << "Adding data to abt..." << endl;
	// output_1 += insert_len + ",";
	ArrayBinTree* abt = new ArrayBinTree;

	for(int i=0;i<insert_len;i++){
		abt->insert(key[i], val[i]);
	}

	return abt;
}
// *******************************************

void solve(string type,string data_file, string query_file, string output_file)
{
			IBinTree *ibt ;

			int *key;
			float *val;

			// Loading data in respective array and setting the length
			int insert_len = load_data(&key, &val, data_file);

			// Clocking the insertion time
			clock_t start, end;
			// start = clock();
			if(type=="lbst"){
				ibt = insert_lbst(key, val, insert_len);
				end = clock();		
				// cout<<"lbst,"<<data_file<<","<<query_file<<",";
			}
			else if(type=="abst"){
				ibt = insert_abst(key, val, insert_len);
				end = clock();
				// cout<<"abst,"<<data_file<<","<<query_file<<",";
			}
			else if(type=="lbt"){
				ibt = insert_lbt(key, val, insert_len);
				end = clock();
				// cout<<"lbt,"<<data_file<<","<<query_file<<",";
			}
			else if(type=="abt"){
				ibt = insert_abt(key, val, insert_len);
				end = clock();
				// cout<<"abt,"<<data_file<<","<<query_file<<",";
			}

			double time_used = ((double)end-start)/CLOCKS_PER_SEC;
			// cout << "Time taken to insert(in s): " << time_used*1000 << endl;
			// cout << time_used*1000<<endl;

			// Loading the queries and getting query length
			int* query;
			int query_length = load_query(&query,query_file);

			// cout << "Query length: " <<query_length;

			// start = clock();
			float* ans = query_tree(ibt, query, query_length);
			// end = clock() ;
			// time_used = ((double)end-start)/CLOCKS_PER_SEC;
			// cout << "Time taken to query(in s): " << time_used*1000 << endl;
			// cout<<"CPS:" <<CLOCKS_PER_SEC;
			// cout << time_used*1000 << endl;

			// print results in a file
			print_output(ans,query_length, output_file);

}


int main(int n, char *argv[])
{
	if(n<7){
		cout<<"Invalid input parameters. Correct format is ./a.out [-abt|lbt|abst|lbst] -data datafile.tsv -query querykey.txt -output outvals.txt";
	}

	// cout << scientific;
    
    // output_1 = string(argv[3]) + "," + string(argv[5]) + "." + string(argv[7]) + ",";
    // output_2 = string(argv[3]) + "," + string(argv[5]) + "." + string(argv[7]) + ",";

    solve(argv[1], argv[3], argv[5], argv[7]);
	
    // cout<<output_1<<endl;
    // cout<<output_2<<endl;
	return 0;
}
