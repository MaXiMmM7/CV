//============================================================================
// Name        : otborpalindromov.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool IsPalindrom(string s){
	if(s.empty()){return 1;}
	int first=0;
	int last=s.size()-1;
	while(first<last){
		if(s[first]!=s[last]){
			return 0;
		}
		first++;
		last--;
	}
		return 1;


}

vector<string>  PalindromFilter(vector<string> words, int minLength){
	vector<string> answer;
	for(auto s:words){
		if(IsPalindrom(s) && (s.size()>=minLength)){
			answer.push_back(s);
		}
	}
	return answer;
}
int main() {
	vector<string> answer=PalindromFilter({"bro","weew","sfwefgwerfgwefe"},4);
	for (auto s:answer){
		cout << s << " ";
	}
	return 0;
}
