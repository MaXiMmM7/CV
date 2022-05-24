//============================================================================
// Name        : annagramu.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include <string>
using namespace std;

string BuildCharCounters(const string& a, const string& b){
	map <char,int> check1;
	map <char,int> check2;
	for (const char& helper: a){
		check1[helper]++;
	}
	for (const char& helper: b){
		check2[helper]++;
	}
	if(check1.size()==check2.size()){
	for(auto g: check1){
		if(g.second!=check2[g.first]){
			return "NO";
		}
	}
	return "YES";}
	return "NO";
}

int main() {
	int N;
	string a,b;
	cin>>N;
	for(int i=0;i<N;i++){
	cin>> a >>b;
	cout << BuildCharCounters(a,b) << endl;
	}
	return 0;
}
