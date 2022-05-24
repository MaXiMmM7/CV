//============================================================================
// Name        : sinonims.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <set>
#include<map>
using namespace std;

int main() {
	int Q;
	string s,s1,s2;
	cin >> Q;
	map<string,set<string>> sinonims;
	for(int i=0; i<Q;i++){
		cin>> s;
		if (s=="ADD"){
			cin>>s1>>s2;
			sinonims[s1].insert(s2);
			sinonims[s2].insert(s1);
		}
		else if(s=="COUNT"){
			cin >>s;
			if(sinonims.count(s)==0){
				cout << 0 << endl;
			}
			else{
				cout << sinonims[s].size() << endl;
			}
		}
		else if(s=="CHECK"){
			cin >>s1>>s2;
			if(sinonims[s1].count(s2)){
				cout << "YES" << endl;
			}
			else{
				cout << "NO" << endl;
			}
		}
	}
	return 0;
}
