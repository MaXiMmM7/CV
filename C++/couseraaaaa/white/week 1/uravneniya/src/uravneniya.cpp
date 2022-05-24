//============================================================================
// Name        : uravneniya.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cmath>
using namespace std;

int main() {
double a,b,c;
cin >> a >> b >> c;
if(a!=0){
double D=b*b-4*a*c;
if(D==0){
	cout << -b/(2*a);
}
else if (D>0){
	cout << (1/(2*a))*(-b+sqrt(D)) << " " << (1/(2*a))*(-b-sqrt(D));
}}
else if(b!=0){
	cout << -c/b;
}
	return 0;
}
