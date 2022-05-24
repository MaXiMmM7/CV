//============================================================================
// Name        : vuvodstochostu.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
	string NameOfFile("input.txt");
	ifstream input(NameOfFile);
	if(input){
		double number;
		cout << fixed << setprecision(3);
		while(input >> number){
			cout << number << endl;
		}

	}else{
		cout << "problems" << endl;
	}

	return 0;
}
