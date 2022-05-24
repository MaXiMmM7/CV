//============================================================================
// Name        : sortirovkacelchisla.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

bool helper(const int& a, const int& b){
	return (abs(a)<abs(b));
}

void print(const vector<int>& v){
	for(const auto& x: v){
		cout << x << " ";
	}
	cout << endl;
}

int main() {
int Q;
cin >> Q;
vector<int> v(Q);
for(int& j:v){
	cin>> j;
}
sort(begin(v),end(v),helper);
print(v);



	return 0;
}
