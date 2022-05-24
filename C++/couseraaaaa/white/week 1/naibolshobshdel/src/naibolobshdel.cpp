//============================================================================
// Name        : naibolobshdel.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
int a,b,n,helper;
cin >> a >> b;
if(a>b){
	n=a;
	a=b;
	b=n;
}
while(b%a!=0){
	n=b/a;
	helper=a;
	a=b-n*a;
	b=helper;

}
cout << a;
	return 0;
}
