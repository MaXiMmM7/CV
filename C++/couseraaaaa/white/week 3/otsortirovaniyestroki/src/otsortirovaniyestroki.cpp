//============================================================================
// Name        : otsortirovaniyestroki.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class SortedStrings{
public:
	void AddString(const string& s){
		strings.push_back(s);
		sort(begin(strings),end(strings));
	}
	vector<string> GetSortedStrings(){
		return strings;
	}
private:
	vector<string> strings;
};

void PrintSortedStrings(SortedStrings& s){
	for(const string& x: s.GetSortedStrings()){
		cout << x << " ";
	}
	cout << endl;
}
int main() {
	SortedStrings strings;

	  strings.AddString("first");
	  strings.AddString("third");
	  strings.AddString("second");
	  PrintSortedStrings(strings);

	  strings.AddString("second");
	  PrintSortedStrings(strings);

	  return 0;

}
