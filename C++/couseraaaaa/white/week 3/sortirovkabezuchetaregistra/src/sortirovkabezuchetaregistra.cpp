//============================================================================
// Name        : sortirovkabezuchetaregistra.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

int main() {

	int N;
	cin >> N;
	vector<string> v(N);
	for(string& x: v){
		cin >> x;
	}

	sort(begin(v),end(v),[](string a,string b){
		string a1,b1;
		for(const auto& x: a){
			a1+=tolower(x);
		}
		for(const auto& x: b){
					b1+=tolower(x);
				}
		return (a1<b1);
	});
	for(const auto& x:v){
		cout << x << " ";
	}
	cout << endl;

	{
	    vector<string> w;
	    w.push_back("One");
	    {
	        w.push_back("Two");
	        {
	            w.push_back("Three");
	        }
	    }
	    for (auto s : w) {
	        cout << s;
	    }
	}
	return 0;
}
