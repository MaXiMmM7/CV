
#include "database.h"

void Database::Add(const Date& date,const string& event){
		if(database_helper[date].count(make_pair(date,event))==0){
			database[date].push_back(make_pair(date,event));
			database_helper[date].insert(make_pair(date,event));

		}

	}

void Database::Print(ostream& stream) const{
		for(auto x: database){
			size_t N=x.second.size();
			for(size_t i=0;i<N;i++){
				stream << x.second[i].first << " " << x.second[i].second<< endl;
			}
		}
	}



		pair<Date,string> Database::Last(const Date& date) const{

		if(database.empty()){
		throw 0;
			//throw invalid_argument("ok");
		}

		if(begin(database)->first>date){
		throw invalid_argument("ok");
		}

		auto It=database.upper_bound(date);
			return *prev((prev(It)->second).end());

		}



