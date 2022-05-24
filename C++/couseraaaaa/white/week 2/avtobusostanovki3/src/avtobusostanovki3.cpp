//============================================================================
// Name        : avtobusostanovki3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include<string>
#include <set>

using namespace std;

int main() {
	int Q;
	cin >> Q;

	int count;
	string s;
	int number =1;
	set<string> check;
	map<set<string>,int> stops;
	for(int i=0; i< Q;i++){
		cin >> count;
		for(int j=0; j<count;j++){
			 cin >> s;
			check.insert(s);
		}
		if(stops.count(check)!=0){
			cout << "Already exists for " << stops[check] << endl;
		}
		else{
			count = int(stops.size());
			stops[check]=++count;
			cout << "New bus "<< stops[check] << endl;
		}
		check.clear();
	}
	return 0;
}
