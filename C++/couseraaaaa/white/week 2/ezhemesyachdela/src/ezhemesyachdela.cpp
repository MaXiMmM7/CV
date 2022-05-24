//============================================================================
// Name        : ezhemesyachdela.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	vector<int> days={31,28,31,30,31,30,31,31,30,31,30,31};
	vector<vector<string>> deals(31);
	int month=0;
int Q;
cin >> Q;
string s,name;
int j;
for(int ii=0;ii<Q;ii++){

	cin >> s;
	if(s=="ADD"){
		cin >>j >> name;
		deals[j-1].push_back(name);
	}
	else if(s=="DUMP"){
		cin >> j;
		cout << deals[j-1].size();
		for(string a:deals[j-1]){
			cout << " " << a ;
		}
		cout << endl;
	}
	else if(s=="NEXT"){
		if(month==11){
			month=0;
		}
		else{
			if(days[month+1]>days[month]){
				deals.resize(days[month+1]);
			}
			if (days[month+1]<days[month]){
				for(int k=(days[month+1]); k<days[month];k++){
					deals[days[month+1]-1].insert(end(deals[days[month+1]-1]),begin(deals[k]),end(deals[k]));
				}
				deals.resize(days[month+1]);
			}
			month++;
		}

	}


}

	return 0;
}
