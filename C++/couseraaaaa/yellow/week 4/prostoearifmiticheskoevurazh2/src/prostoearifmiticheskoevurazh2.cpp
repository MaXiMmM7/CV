//============================================================================
// Name        : prostoearifmiticheskoevurazh2.cpp
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
	char a='*';
	char b='/';
	char prev;
	int N;
	deque<string> q;
	cin >> N;
	q.push_back(to_string(N));
	cin >> N;
	string data;
	getline(cin,data);
	for(int i=0;i<N;i++){
		getline(cin,data);
		if((data[0]==a||data[0]==b)&&(i!=0)&&(prev!=a&&prev!=b)){
        q.push_front("(");
        q.push_back(")");
		}
        q.push_back(" ");
        q.push_back(data);
        prev=data[0];

	}
	for(const auto& x: q){
		cout <<x;
	}

	return 0;
}
