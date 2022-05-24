//============================================================================
// Name        : razvorotposled.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

void Reverse(vector<int>& v){
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
}
int main() {

	return 0;
}
