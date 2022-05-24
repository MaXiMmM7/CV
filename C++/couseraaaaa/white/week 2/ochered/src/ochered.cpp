//============================================================================
// Name        : ochered.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
	int N;
	int count =0;
	cin >>N;
	vector<bool> people;
	string s;
	int j;
	for (int i=0; i<N; i++){
		cin >> s;
		if(s!="WORRY_COUNT"){
		cin >> j;
		if(s=="COME"){
			people.resize(people.size()+j);
			if(j>0){
				for(int k=(people.size()-1);k>(people.size()-j-1);k--){
					people[k]=0;
				}
			}

		}
		if(s=="WORRY"){
			people[j]=1;
		}
		if(s=="QUIET"){
			people[j]=0;
		}
		}
		else{
			for(auto a:people){
				if(a==1){
					count++;
				}
			}
			cout <<endl << count;
			count=0;
		}
	}


	return 0;
}
