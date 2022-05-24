#include <algorithm>
#include <list>
#include <map>
#include "profile.h"
#include <iostream>
using namespace std;


int main() {

cin.tie(nullptr);
ios_base::sync_with_stdio(false);
list<int> sportsmen;
map<int,typename list<int> :: iterator> help;

int Q;
cin >> Q;
int before;
int current;
for(int i=0; i < Q; i++){
	cin >> current >> before;
	if(help.count(before)==1){
		help[current]=sportsmen.emplace(help[before],current);
	}
	else{
		sportsmen.emplace_back(current);
		help[current]=prev(sportsmen.end());
     }
}


for(auto x: sportsmen){
	cout << x << "\n";
}

	/*{
	LOG_DURATION("TestAll");
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	list<int> sportsmen;
	map<int,typename list<int> :: iterator> help;
	int Q=100000;
	int before;
	int current;
	for(int i=0; i < Q; i++){
		current=i;
		before=i/2;
	if(help.count(before)==1){
		help[current]=sportsmen.emplace(help[before],current);
	}
	else{

		help[current]=prev(sportsmen.end());

	}

	}

	for(auto x: sportsmen){
		cout << x << "\n";
	}
}
*/
return 0;
}
