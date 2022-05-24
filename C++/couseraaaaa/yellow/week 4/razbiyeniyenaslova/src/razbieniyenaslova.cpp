//============================================================================
// Name        : razbieniyenaslova.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> SplitIntoWords(const string& s){

	auto It1=s.begin();
	auto It2=s.begin();
	vector<string> result;

	while(It2!=s.end()){
		It2=find_if(It1,s.end(),[](const char& x){return x==' ';});
		result.push_back({It1,It2});
		if(It2!=s.end()){
			It1=++It2;
		}
		}
return result;
}

int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;

  return 0;
}
