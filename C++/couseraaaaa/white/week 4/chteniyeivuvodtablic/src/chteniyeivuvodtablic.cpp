//============================================================================
// Name        : chteniyeivuvodtablic.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;


void Print(const string& NameOfFile)
{
	string data;
	int N,M;
	ifstream input(NameOfFile);
	if(input){
	//	cout << setfill(' ');
		input >> N;
		input.ignore(1);
		input >> M;
		input.ignore(1);
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
		    if (j<M-1){getline(input,data,',');}
		    else{getline(input,data);}
				cout << setw(10) << data;
				if(j!=M-1){
					cout <<" ";
				}
			}
			if(i!=N-1){
				cout << endl;
			}
		}

	}

}
int main() {
	string NameOfFile="input.txt";

	Print(NameOfFile);

	return 0;
}
