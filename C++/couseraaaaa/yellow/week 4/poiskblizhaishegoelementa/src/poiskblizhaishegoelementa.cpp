//============================================================================
// Name        : poiskblizhaishegoelementa.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <set>
using namespace std;

set<int>::const_iterator FindNearestElement(
    const set<int>& numbers,
    int border){
	if(numbers.empty()){
		return begin(numbers);
	}
	auto It=numbers.lower_bound(border);
    if(It!=begin(numbers)&&It!=end(numbers)){
		if((*It-border)>=(border - *(prev(It)))){
			return prev(It);
		}
		else{
			return It;
		}
	}
    else if(It==end(numbers)){
       	return prev(It);
       }
	return It;
}

// set<int>::const_iterator —
// тип итераторов для константного множества целых чисел


int main() {
  set<int> numbers = {1, 4, 6};
  cout <<
      *FindNearestElement(numbers, 0) << " " <<  //1
	  *FindNearestElement(numbers, 1) << " " << //1
	  *FindNearestElement(numbers, 2) << " " << // 1
      *FindNearestElement(numbers, 3) << " " << // 4
      *FindNearestElement(numbers, 5) << " " <<   //4
      *FindNearestElement(numbers, 6) << " " <<  /// 6
      *FindNearestElement(numbers, 100) << endl; /// 6

  set<int> empty_set;

  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
  return 0;
}
