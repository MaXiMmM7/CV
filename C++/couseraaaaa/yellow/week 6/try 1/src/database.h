#pragma once



#include "node.h"


#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#include <exception>
//#include <iomanip>
#include <sstream>

using namespace std;

bool operator < (const pair<Date,string>& a,const pair<Date,string>& b);


template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& s) {
  return os << s.first << " " << s.second;
}

class Database{
public:
	void Add(const Date& date,const string& event);

	void Print(ostream& stream) const;

	template <typename T>
	int RemoveIf(T predicate){
		auto It=remove_if(begin(events),end(events),predicate);
		int distance=end(events)-It;
		events.erase(It,end(events));
		return distance;
	}

	template <typename T>
		vector<pair<Date,string>> FindIf(T predicate) {
		auto It=begin(events);
		vector<pair<Date,string>> result;
		while(It!=end(events)){
			It=find(It,end(events),predicate);
			if(It!=end(events)){
				result.push_back(*It);
				It++;
			}
		}
		return result;
		}

	pair<Date,string> Last(const Date& date) const ;

private:
	vector<pair<Date,string>> events;
};


string ParseEvents(istringstream& stream);

