//============================================================================
// Name        : raborasfailami2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {



	string InputName("input.txt");
	string OutputName("output.txt");
	ifstream input(InputName);
	ofstream output(OutputName);

	if(input){
		string s;
		while(getline(input,s)){
			output << s << endl;
		}
	}
	else {
		cout << "Fail" << endl;
	}

	return 0;
}
