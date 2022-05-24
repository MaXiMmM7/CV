//============================================================================
// Name        : sortirovkasliyaniem2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
	if(range_end-range_begin<2){
		return;
	}
	/*vector<typename RandomIt::value_type> elements(range_begin, range_end);
	vector<typename RandomIt::value_type> first={range_begin,range_begin+(range_end-range_begin)/3};
	vector<typename RandomIt::value_type> second={range_begin+(range_end-range_begin)/3,range_begin+2*(range_end-range_begin)/3};
	vector<typename RandomIt::value_type> third={range_begin+2*(range_end-range_begin)/3,range_end};

	MergeSort(first.begin(),first.end());
	MergeSort(second.begin(),second.end());
	MergeSort(third.begin(),third.end());
	vector<typename RandomIt::value_type> helper;
	merge(first.begin(),first.end(),second.begin(),second.end(),back_inserter(helper));
	merge(helper.begin(),helper.end(),third.begin(),third.end(),range_begin);*/
	vector<typename RandomIt::value_type> elements(range_begin, range_end);

	MergeSort(elements.begin(),elements.begin()+(elements.end()-elements.begin())/3);
	MergeSort(elements.begin()+(elements.end()-elements.begin())/3,elements.begin()+2*(elements.end()-elements.begin())/3);
	MergeSort(elements.begin()+2*(elements.end()-elements.begin())/3,elements.end());
	vector<typename RandomIt::value_type> helper;
	merge(elements.begin(),elements.begin()+(elements.end()-elements.begin())/3,
			elements.begin()+(elements.end()-elements.begin())/3,elements.begin()+2*(elements.end()-elements.begin())/3,
			back_inserter(helper));
	merge(helper.begin(),helper.end(),elements.begin()+2*(elements.end()-elements.begin())/3,elements.end(),
			range_begin);
}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}

