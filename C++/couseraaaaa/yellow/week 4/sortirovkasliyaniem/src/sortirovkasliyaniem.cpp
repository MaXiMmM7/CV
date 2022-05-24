//============================================================================
// Name        : sortirovkasliyaniem.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
	if(range_end-range_begin<2){
		return;
	}/*
	vector<typename RandomIt::value_type> elements(range_begin, range_end);
	vector<typename RandomIt::value_type> first={range_begin ,range_begin+(range_end-range_begin)/2};
	vector<typename RandomIt::value_type> second={range_begin+(range_end-range_begin)/2,range_end};

	MergeSort(first.begin() ,first.end());
	MergeSort(second.begin() ,second.end());
	merge(first.begin() ,first.end(),
			second.begin() ,second.end(),range_begin);*/
	vector<typename RandomIt::value_type> elements(range_begin, range_end);
    MergeSort(elements.begin() ,elements.begin()+(elements.end()-elements.begin())/2 );
	MergeSort(elements.begin()+(elements.end()-elements.begin())/2,elements.end());
	//////
	/*cout << range_end-range_begin << endl;
	auto It=range_begin;
	while(It!=range_end){
		cout << *It << " ";
		It++;
	}
	cout << endl;*/
	//////////
	vector<typename RandomIt::value_type> helper;
		merge(elements.begin() ,elements.begin()+(elements.end()-elements.begin())/2 ,
				elements.begin()+(elements.end()-elements.begin())/2,elements.end(),range_begin);


}


int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(begin(v), end(v));


  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}

