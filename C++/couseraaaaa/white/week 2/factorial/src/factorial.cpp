//============================================================================
// Name        : factorial.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int Factorial(int n){
	int answer=1;
	if(n>0){
		for (int i=1;i<=n;i++){
			answer*=i;
		}
		return answer;
	}
	else {return 1;}
}

int main() {
	cout << Factorial(3);
	return 0;
}
