//============================================================================
// Name        : avtobusostanovki1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

int main() {
	int Q;
	cin >> Q;
	map<string,vector<string>> ways;
	map<string,vector<string>> stop_buses;
	string s,name,stop;
	int count;

	for(int i=0; i<Q;i++){
		cin >> s;
		if(s=="NEW_BUS"){
			cin >> name >> count;
			for(int j=0;j<count;j++){
				cin >> stop;
				ways[name].push_back(stop);
				stop_buses[stop].push_back(name);
			}
		}
		else if(s=="BUSES_FOR_STOP"){
			cin >> name;
			if(stop_buses.count(name)==0){
				cout << "No stop" << endl;
			}
			else{
				for(auto x: stop_buses[name]){
					cout << x << " ";
				}
				cout << endl;
			}
		}
		else if(s=="STOPS_FOR_BUS"){
			cin >> name;
			if(ways.count(name)==0){
				cout << "No bus" << endl;
			}
			else{
			for(auto x: ways[name] ){
				cout << "Stop " << x <<": ";
				if(stop_buses[x].size()<=1){
					cout << "no interchange";
				}
				else{
				for(auto y: stop_buses[x]){
					if(y!=name){
					cout << y <<" ";
					}
				}
				}
				cout << endl;
			}
			}
		}
		else if(s=="ALL_BUSES"){
			if(ways.empty()){
				cout << "No buses" << endl;
			}
			else{
				for(auto x:ways){
					cout << "Bus " << x.first <<": ";
					for(auto y: x.second){
						cout << y << " ";
					}
					cout << endl;
				}
			}
		}
	}

	return 0;
}
