//============================================================================
// Name        : edaleniyepovtorov.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

template <typename T>
void RemoveDuplicates(vector<T>& elements){
	sort(begin(elements),end(elements));
	typename vector<T>::iterator It=unique(begin(elements),end(elements));
	elements.erase(It,end(elements));
}

int main() {
  vector<int> v1 = {6, 4, 7, 6, 4, 4, 0, 1};
  RemoveDuplicates(v1);
  for (int x : v1) {
    cout << x << " ";
  }
  cout << endl;

  vector<string> v2 = {"C", "C++", "C++", "C", "C++"};
  RemoveDuplicates(v2);
  for (const string& s : v2) {
    cout << s << " ";
  }
  cout << endl;
  return 0;
}
