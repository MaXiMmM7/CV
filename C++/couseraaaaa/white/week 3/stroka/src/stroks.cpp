//============================================================================
// Name        : stroks.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
using namespace std;

class ReversibleString{
public:
	ReversibleString(){}
	ReversibleString(const string& v){
		s=v;
	}
	void Reverse(){
		int t=s.size()-1;
		for(int i=0;i<=t/2;i++){
			int tmp=s[i];
			s[i]=s[t-i];
			s[t-i]=tmp;

		}
	}
	string ToString() const{
		return s;
	}
private:
	string s;
};

int main() {

	  ReversibleString s("live");
	  s.Reverse();
	  cout << s.ToString() << endl;

	  s.Reverse();
	  const ReversibleString& s_ref = s;
	  string tmp = s_ref.ToString();
	  cout << tmp << endl;

	  ReversibleString empty;
	  cout << '"' << empty.ToString() << '"' << endl;

	return 0;
}
