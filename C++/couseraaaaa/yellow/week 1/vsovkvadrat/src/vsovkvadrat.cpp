//============================================================================
// Name        : vsovkvadrat.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <string>
using namespace std;




template <typename First,typename Second> pair<First,Second> operator *(const pair<First,Second> a,
		                                                                      const pair<First,Second> b);
template <typename T> vector<T> operator*(const vector<T>& a,const vector<T>& b);
template <typename Key,typename Value> map<Key,Value> operator *(const map<Key,Value>& a,const map<Key,Value>& b);
template <typename T> T Sqr(const T& x);


template <typename First,typename Second> pair<First,Second> operator *(const pair<First,Second> a,
		                                                                      const pair<First,Second> b){
	return pair<First,Second>(a.first*b.first,a.second*b.second);
}
template <typename T> vector<T> operator*(const vector<T>& a,const vector<T>& b){
	vector<T> c;
	for(size_t i=0;i<a.size();i++){
		c.push_back(a[i]*b[i]);
	}
	return c;
}
template <typename Key,typename Value> map<Key,Value> operator *(const map<Key,Value>& a,const map<Key,Value>& b){
	map<Key,Value> c=a;
	for(auto& x: c){
	x.second=x.second*x.second;
	}
	return c;
}


template <typename T>
T Sqr(const T& x){
	return x*x;
}



int main() {
	vector<int> v = {1, 2, 3};
	cout << "vector:";
	for (int x : Sqr(v)) {
	  cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
	  cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
}
