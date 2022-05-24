//============================================================================
// Name        : grupirovkaposimvolu.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "test_runner.h"
using namespace std;



template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith( RandomIt range_begin, RandomIt range_end, char prefix){
	string help;
	help.push_back(prefix);
	auto It1= lower_bound(range_begin,range_end, help);
    //auto It2 =upper_bound(range_begin,range_end, to_string(static_cast<char>(prefix+1)));
	help[0]=static_cast<char>(prefix+1);
	auto It2 =lower_bound(range_begin,range_end, help);
	//
	//cout <<to_string(prefix) << " " << prefix+1 << " " << to_string(static_cast<char>(prefix+1)) << " " << *It1 << " " << *It2 << endl;
	//
    return {It1,It2};
}


void Test(){
	{
		 /* const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

		  const auto m_result =
		      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
		  AssertEqual(pair<string,string> (*m_result.first,*m_result.second),pair<string,string> ("moscow", "murmansk"), "first test_1");
		 //
const auto p_result =
		      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
AssertEqual(pair<size_t,size_t> (p_result.first - begin(sorted_strings),
		p_result.second - begin(sorted_strings)),pair<size_t,size_t> (2, 2), "first test_2");
	//
 const auto z_result =
		      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
 AssertEqual(pair<size_t,size_t> (z_result.first - begin(sorted_strings),
		 z_result.second - begin(sorted_strings)),pair<size_t,size_t> (3, 3), "first test_3");*/
		}
}

void TestALl(){
	TestRunner runner;
	runner.RunTest(Test, " Test this ...");
}


int main() {



  return 0;
}
