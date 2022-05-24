#include "database.h"

void Database::Add(const Date& date,const string& event){
		if(count(begin(database[date]),end(database[date]),make_pair(date,event))==0){
			database[date].push_back(make_pair(date,event));
		}
	}

void Database::Print(ostream& stream) const{
		for(auto x: database){
			size_t N=x.second.size();
			for(size_t i=0;i<N;i++){
				stream << x.second[i].first << " " << x.second[i].second;
				if(i+1!=N){
					stream << endl;
				}
			}
		}
	}



		pair<Date,string> Database::Last(const Date& date){
		if(*begin(database).first>date){
		throw invalid_argument();
		}
		auto It=database.upper_bound(date);
		if(It!=begin(*It.second)){
			return *prev(It).second[static_cast<int>(*prev(It).second.size())-1];
		}
		return *It.second[0];
		}
