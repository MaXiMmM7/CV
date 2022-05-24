//============================================================================
// Name        : realizfunccii.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
//#include <test_runner.h>
#include <sum_reverse_sort.h>
#include <algorithm>
//#include <test_runner.h>


using namespace std;

/*
 *
 * #pragma once
#include <string>
#include <vector>

using namespace std;

int Sum(int x, int y);
string Reverse(string s);
void Sort(vector<int>& nums);
 *
 *
 *
 */
int Sum (int x, int y){
	return x+y;
}
string Reverse(string s){
int N=static_cast<int>(s.size());
char helper;
for(int i=0; i<N/2;i++){
	helper=s[i];
	s[i]=s[N-1-i];
	s[N-i-1]=helper;
}
return s;
}

void Sort(vector<int>& nums){
	sort(nums.begin(),nums.end());
}
/*
void TestAll(){
	TestRunner runner;
}*/
