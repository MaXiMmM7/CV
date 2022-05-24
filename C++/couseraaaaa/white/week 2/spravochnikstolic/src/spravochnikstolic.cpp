//============================================================================
// Name        : spravochnikstolic.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
	int Q;
	cin >> Q;
	string s,country, capital;
	map<string,string> world;
	for (int i =0; i<Q; i++){
		cin >>s;
		if(s=="CHANGE_CAPITAL"){
			cin >> country >> capital;
			if(world.count(country)==0){
			world[country]=capital;
			cout << "Introduce new country " << country << " with capital " << capital << endl;
			}
			else{
				if(world[country]==capital){
					cout << "Country " << country << " hasn't changed its capital" << endl;
				}
				else{
					cout << "Country " <<  country << " has changed its capital from " << world[country]<< " to " << capital << endl;
					world[country]=capital;
				}
			}
		}
		if(s=="RENAME"){
			cin >> country >> capital;
	if((world.count(country)==0)||(country==capital)||(world.count(capital)!=0)){
		cout << "Incorrect rename, skip" << endl;
	}
	else{
		cout << "Country " << country << " with capital " << world[country] << " has been renamed to " << capital << endl;
		s=world[country];
			world.erase(country);
			world[capital]=s;
	}
		}
		if(s=="ABOUT"){

			cin >> country;
			if(world.count(country)==0){
				cout << "Country "<< country<< " doesn't exist"<< endl;
			}
			else{
			cout <<"Country " << country << " has capital " << world[country] << endl;
			}
		}
		if(s=="DUMP"){
			if(world.empty()){
				cout<< "There are no countries in the world" << endl;
			}
			else{
				for( auto x: world){
					cout << x.first << "/" << x.second << " ";
				}
				cout <<endl;
			}
		}
	}
	return 0;
}
