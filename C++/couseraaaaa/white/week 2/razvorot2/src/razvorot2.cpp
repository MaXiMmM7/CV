//============================================================================
// Name        : razvorot2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

vector<int> Reversed(const vector<int>& s){
	vector<int> v=s;
	int helper;
	int first=0;
	int last=v.size()-1;
	while(first<last){
		helper=v[first];
		v[first]=v[last];
		v[last]=helper;
		first++;
		last--;
	}
	return v;
}
int main() {
	vector <int> v(1);
	v.assign(1,0);
	cout << v.size();

	return 0;
}
