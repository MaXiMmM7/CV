//============================================================================
// Name        : avtonusniyaostanovki2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

int main() {
	int Q;
	cin >> Q;
	map <vector<string>,int> ways;
	vector <string> stops;
	string name;
	int number=0;
	int helper;

	for(int i=0;i<Q;i++){
		cin >> helper;
		for(int j=0; j<helper; j++){
			cin >> name;
			stops.push_back(name);
		}
		if(ways.count(stops)==0){
			ways[stops]=++number;
			cout << "New bus "<< ways[stops] <<endl;
		}
		else{
			cout << "Already exists for " << ways[stops] <<endl;
		}
		stops.clear();
	}
	return 0;
}
