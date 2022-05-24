//============================================================================
// Name        : peremesheniyastrok.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>
using namespace std;

 void MoveStrings(vector<string>& source, vector<string>& destination){
	 for (auto s:source){
		 destination.push_back(s);
	 }
	 source.clear();
 }

int main() {

	return 0;
}
