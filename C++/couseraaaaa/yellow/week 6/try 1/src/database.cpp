
#include "database.h"


#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#include <exception>
//#include <iomanip>
#include <sstream>

using namespace std;

bool operator < (const pair<Date,string>& a,const pair<Date,string>& b){
	return a.first<b.first;
}


	void Database::Add(const Date& date,const string& event){
		auto new_pair=make_pair(date,event);
		auto Its=equal_range(events.begin(),events.end(),new_pair);
		if(count(Its.first,Its.second,new_pair)==0){
			events.insert(Its.second,new_pair);
		}
	}
	void Database::Print(ostream& stream) const{
		size_t N=events.size();
		for(size_t i=0; i<N;i++){
			stream << events[i];
			if(i+1!=N){
				cout << endl;
			}
		}
	}


	pair<Date,string> Database::Last(const Date& date) const{
		if(date < begin(events)->first){
			throw invalid_argument("");
		}
		auto check =make_pair(date,"a");
		auto It=upper_bound(begin(events),end(events),check);
		return *prev(It);
	}


string ParseEvents(istringstream& stream){
	string event;
	while(stream.peek()==' '){
		stream.ignore(1);
	}
	getline(stream,event);
	return event;
}

