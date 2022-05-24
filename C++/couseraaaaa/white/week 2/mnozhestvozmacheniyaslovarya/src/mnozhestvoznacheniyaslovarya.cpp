//============================================================================
// Name        : mnozhestvoznacheniyaslovarya.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include <string>
#include <set>
using namespace std;

set<string> BuildMapValuesSet(const map<int,string>& m){
	set<string> result;
	for(auto x: m){
		result.insert(x.second);
	}
	return result;
}

