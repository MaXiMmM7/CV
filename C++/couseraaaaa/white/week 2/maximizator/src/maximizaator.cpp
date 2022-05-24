//============================================================================
// Name        : maximizaator.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

void UpdateIfGreater (int first, int& second){
	if(second<first){
		second=first;
	}
}
int main() {
	int a=5;
	int b=7;
	UpdateIfGreater(9,b);
	cout << a << " " << b;
	return 0;
}
