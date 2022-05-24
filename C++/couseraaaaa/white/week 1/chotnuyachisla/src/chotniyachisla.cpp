//============================================================================
// Name        : chotniyachisla.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
	int a,b,check;
	cin >>a >>b;
	if(a%2==0){
		 check=a;
	}
	else {check=a+1;}
	while(check<=b){
		cout << check << " ";
		check+=2;
	}
	return 0;
}
