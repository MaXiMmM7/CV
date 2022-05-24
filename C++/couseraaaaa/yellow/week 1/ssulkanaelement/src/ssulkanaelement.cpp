//============================================================================
// Name        : ssulkanaelement.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include <utility>
#include <exception>
#include <stdexcept>

using namespace std;

template<typename Key,typename Word>
Word& GetRefStrict(map<Key,Word>& m,const Key& key){
	if(m.count(key)==0){
		throw system_error();
	}
	return m[key];
}

int main() {
	try{
	map<int, string> m = {{0, "value"}};
	string& item = GetRefStrict(m, 0);
	item = "newvalue";
	cout << m[0] << endl; // выведет newvalue
	}catch(exception& ex){

	}
	return 0;
}
