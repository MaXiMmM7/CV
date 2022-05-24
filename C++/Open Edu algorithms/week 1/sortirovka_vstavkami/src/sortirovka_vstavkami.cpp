//============================================================================
// Name        : sortirovka_vstavkami.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void SortInsertion(vector<int>& v, ofstream& out){
	int i,helper;
	out << 1 << " ";
	for( int j = 1; j < static_cast<int>(v.size()); j++){
		i = j - 1;
		while (i >= 0 && v[i] > v[i+1]){
			helper = v[i];
			v[i] = v[i+1];
			v[i+1] = helper;
			i = i -1;
		}
		out << (i+2) << " ";
	}

	out << "\n";
}

void PrintVectorInFile(const vector<int>& v,ofstream& out){
	for(auto x: v){
		out << x << " ";
	}
	out << "\n";
}

int main() {
	int N;
	ifstream input("input.txt");
	input >> N;
	vector<int> data(N);

	for(int i = 0; i < N; i++){
		input >> data[i];
	}

	ofstream output("output.txt");

	SortInsertion(data,output);

	PrintVectorInFile(data,output);

	return 0;
}
