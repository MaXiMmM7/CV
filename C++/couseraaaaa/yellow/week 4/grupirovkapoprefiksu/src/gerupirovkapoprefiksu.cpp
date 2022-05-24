//============================================================================
// Name        : gerupirovkapoprefiksu.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;


#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    const string& prefix){
	    string help=prefix;
		help[static_cast<int>(prefix.size())-1]=
				static_cast<char>((prefix[static_cast<int>(prefix.size())-1]+1));
		auto It1= lower_bound(range_begin,range_end, prefix);
		auto It2 =lower_bound(range_begin,range_end, help);
	    return {It1,It2};

}






int main() {
  const vector<string> sorted_strings = {};

  const auto mo_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "");
  for (auto it = mo_result.first; it != mo_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;

  const auto mt_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
  cout << (mt_result.first - begin(sorted_strings)) << " " <<
      (mt_result.second - begin(sorted_strings)) << endl;

  const auto na_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
  cout << (na_result.first - begin(sorted_strings)) << " " <<
      (na_result.second - begin(sorted_strings)) << endl;

  return 0;
}


