//============================================================================
// Name        : prostoearifmitischeskoevurazh.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <deque>
using namespace std;




int main() {
	int N;
	deque<string> q;
	cin >> N;
	q.push_back(to_string(N));
	cin >> N;
	string data;
	getline(cin,data);
	for(int i=0;i<N;i++){
		getline(cin,data);
        q.push_front("(");
        q.push_back(") ");
        q.push_back(data);
	}
	for(const auto& x: q){
		cout <<x;
	}

	return 0;
}
