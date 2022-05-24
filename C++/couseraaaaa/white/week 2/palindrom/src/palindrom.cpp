//============================================================================
// Name        : palindrom.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
using namespace std;

bool IsPalindrom(string s){
	if(s.empty()){return 1;}
	int first=0;
	int last=s.size()-1;
	while(first<last){
		if(s[first]!=s[last]){
			return 0;
		}
		first++;
		last--;
	}
		return 1;


}

int main() {
	cout << IsPalindrom("");
	return 0;
}
