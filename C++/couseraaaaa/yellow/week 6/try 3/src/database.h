
#pragma once
#include "date.h"
#include <algorithm>
#include <map>
#include <vector>
#include <utility>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <set>

using namespace std;


class Database{
public:
	void Add(const Date& date,const string& event);

	void Print(ostream& stream) const;

	template <typename Function>
		int RemoveIf(Function f){
		int count=0;
		for(auto It_x=begin(database),It_end=end(database);It_x!=It_end;){
						auto It=stable_partition(begin(It_x->second),end(It_x->second),
								[&](const pair<Date,string>& p){return !f(p.first,p.second);});

						count+=static_cast<int>(end(It_x->second)-It);


						It_x->second.erase(It,end(It_x->second));



					if(It_x->second.empty()){
						//
						database_helper.erase(It_x->first);
						//
						It_x=database.erase(It_x);
						It_end=database.end();


					}
					else{
						//

						database_helper.erase(It_x->first);
						database_helper[It_x->first].insert(
								begin(It_x->second),end(It_x->second));
						//
						It_x++;

					}

					}
			return count;
		}

	template <typename Function>
			vector<pair<Date,string>> FindIf(Function f) const {
			vector<pair<Date,string>> result;

			for(auto It_x=begin(database);It_x!=end(database);It_x++){
				auto It=begin(It_x->second);
				while(It!=end(It_x->second)){
	It=find_if(It,end(It_x->second),[&](const pair<Date,string>& p){return f(p.first,p.second);});
									if(It!=end(It_x->second)){
										result.push_back(*It);
										It++;
									}
				}
			}
				return result;
			}

		pair<Date,string> Last(const Date& date) const;

private:
	map<Date,vector<pair<Date,string>>> database;
	map<Date,set<pair<Date,string>>> database_helper;
};

template <class K, class V>
ostream& operator << (ostream& os, const pair<K, V>& p) {
  return os << p.first <<" " <<p.second;
}
