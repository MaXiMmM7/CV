//============================================================================
// Name        : kolichestvounikalstrok.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
	int Q;
	cin >> Q;
	string s;
	set<string> stroks;
	for(int i=0;i<Q;i++){
		cin >> s;
		stroks.insert(s);
	}
	cout << stroks.size();
	return 0;
}
