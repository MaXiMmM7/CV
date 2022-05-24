//============================================================================
// Name        : rabotasfailami.cpp
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
	string s;
	string Name("input.txt");
	ifstream input(Name);
	if(input){
		while(getline(input,s)){
			cout << s << endl;
		}
	}
	return 0;
}
