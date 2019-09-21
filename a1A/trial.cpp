#include <iostream>
#include<fstream>
#include<sstream>

using namespace std;

int main(){
	float a[16][16] = {0};

	ifstream fin("16.tsv");
	float x;
	fin>>x;
	cout<<x;
	// if(ifs.fail()){
	// 	cerr<<"Error in ifstream object creation.";
	// 	return -1;
	// }

	// string line;
	

	// while(getline(ifs, line)){
	
	// 	stringstream ss(line);

	// 	string temp;
	// 	while(getline(ss,temp,'\t')){
	// 		cout<<temp<<" ";
	// 	}
	// 	cout<<endl;
	// }
	return 0;	
}