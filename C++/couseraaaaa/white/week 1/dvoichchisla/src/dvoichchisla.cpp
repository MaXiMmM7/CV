//============================================================================
// Name        : dvoichchisla.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

int main() {
	int N;
	vector<int> d;
    cin>>N;

    while(N!=0){
    	d.push_back(N-2*(N/2));
    	N=N/2;
    }
    for (int i=d.size(); i!=0;i--){
    	cout << d[i-1];
    }
	return 0;
}
