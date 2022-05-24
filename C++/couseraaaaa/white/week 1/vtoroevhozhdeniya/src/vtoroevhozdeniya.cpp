//============================================================================
// Name        : vtoroevhozdeniya.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
using namespace std;

int main() {
	string s;
	cin >>s;
	int check=0;
    for (int i=1; i<=s.size();i++){
    	if(s[i-1]=='f'){
    		check++;
    		if (check==2) {
    			cout << (i-1);
    			break;
    		}
    	}

    }
    if(check==1){cout << -1;}
    else if(check==0){cout <<-2;}

	return 0;
}
