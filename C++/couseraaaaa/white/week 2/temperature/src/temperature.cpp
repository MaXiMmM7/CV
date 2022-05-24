//============================================================================
// Name        : temperature.cpp
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
	int m=0;
	int K=0;
	cin >> N;
	vector<int> v(N);
	for (int i=0;i<N;i++){
		cin >> v[i];
		m+=v[i];
	}
	m/=N;
	vector<int> answer;
	for (int i=0;i<N;i++){
		if(v[i]>m){
			K++;
			answer.push_back(i);
		}
	}
	cout << K <<endl;
	for (int a:answer){
			cout << a << " ";
		}
	return 0;
}
