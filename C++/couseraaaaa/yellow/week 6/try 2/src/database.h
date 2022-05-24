#pragma once
#include "date.h"
#include <algorithm>
#include <map>
#include <vector>
#include <utility>
#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;


class Database{
public:
	void Add(const Date& date,const string& event);

	void Print(ostream& stream) const;

	template <typename Function>
		int RemoveIf(Function f){
		int count=0;
			for(auto x: database){
				auto It=stable_partition(begin(x.second),end(x.second),f);
				count+=static_cast<int>(end(x.second)-It);
				x.second.erase(It,end(x.second));
			if(database[x.first].empty){
				database.erase(x.first);
			}
			}
			return count;
		}

	template <typename Function>
			int FindIf(Function f) const {
			vector<pair<Date,string>> result;
				for(auto x: database){
					auto It=begin(x.second);
				while(It!=end(x.second)){
					It=find_if(It,end(x.second),f);
					if(It!=end(x,second)){
						result.push_back(*It);
					}
				}
				}
				return result;
			}

		pair<Date,string> Last(const Date& date);

private:
	map<Date,vector<pair<Date,string>>> database;
};
