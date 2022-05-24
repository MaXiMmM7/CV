//============================================================================
// Name        : minimalnaya_stroka.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
using namespace std;

int main() {
	string a,b,c;
	cin >> a >> b >> c;
	if (a>=b){
		if(c>=a){
			cout << b;
		}
		else{
			if(b>=c){
				cout << c;
			}
			else {
				cout <<b;
			}
		}
	}
	else{
		if(c>=b){
			cout << a;
		}
		else{
			if(c>=a){
							cout << a;
						}
						else {
							cout <<c;
						}
		}
	}
	return 0;
}
