//============================================================================
// Name        : WhiteFinalProject.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include <set>
#include <exception>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>
using namespace std;

struct Year{
	int year;
	explicit Year(const int& y){
		year=y;
	}
	int GetYear() const{
			return year;
		}
};
struct Month{
	int month;
	explicit Month(const int& m){
		if((m<1)||(m>12)){
			throw invalid_argument("Month value is invalid: "+to_string(m));
		}
		month=m;
	}
	int GetMonth() const {
				return month;
			}
};
struct Day {
	int day;
	explicit Day(const int& d){
		if((d<1)||(d>31)){
			throw invalid_argument("Day value is invalid: " + to_string(d));
		}
		day=d;
	}
	int GetDay() const{
				return day;
			}
};

class Date {
public:
  int GetYear() const{
	  return year;
  }
  int GetMonth() const{
	  return month;
  }
  int GetDay() const{
	  return day;
  }
  Date(){}
  Date (const Year& y, const Month& m,const Day& d){
	  year=y.year;
	  month=m.month;
	  day=d.day;
  }

 /* Date (const Year& y,const Day& d, const Month& m){
 	  year=y.year;
 	  month=m.month;
 	  day=d.day;
  }*/
private:
  int year;
  int month;
  int day;
};



bool operator<(const Date& lhs, const Date& rhs){
	if(lhs.GetYear()==rhs.GetYear()){
		if(lhs.GetMonth()==rhs.GetMonth()){
		   return (lhs.GetDay() < rhs.GetDay());
		}
		return (lhs.GetMonth()<rhs.GetMonth());
	}
	return (lhs.GetYear() < rhs.GetYear());
}

ostream& operator <<(ostream& stream,const Date& date){
	cout << date.GetYear() << "-" << date.GetMonth() << "-" <<  date.GetDay();
			return stream;
}
istream& operator >>(istream& stream1, Date& date){
	if(stream1){
       string helper;
       stream1 >> helper;
       stringstream stream;
       stream << helper;
      // string check=to_string(stream1.peek());
		int a,b,c;
	    char t1,t2;
	   stream >> a >> t1 >> b >> t2 >> c;
	   //
	   //cout << endl << char(stream.peek()) << endl;
	   //
	   if(stream&&((t1=='-')&&(t2='-'))&&(stream.eof())){
		  date=Date(Year(a),Month(b),Day(c));
		  // date=Date(Year(a),Day(c),Month(b));
	   }
	   else{
		  throw invalid_argument("Wrong date format: "+helper);
	   }
	   return stream1;
	}
	return stream1;
}


void PrintTrue(const Date& d,const string s){
	cout << setfill('0') << setw(4) << to_string(d.GetYear()) <<"-" << setw(2)
			<< to_string(d.GetMonth())<<"-"   << setw(2) <<to_string(d.GetDay());
	cout << " " << s << endl;

}
void FindWritter(map<Date,set<string>> base,const Date& date){
	  for(const string& x: base[date]){
				  cout << x  << endl;
	  }
}

class Database {
public:
  void AddEvent(const Date& date, const string& event){
	  base[date].insert(event);
  }

  bool DeleteEvent(const Date& date, const string& event){
	  if(base.count(date)>0){
		  if (base[date].count(event)>0){
			  base[date].erase(event);
			  if(base[date].size()<1){
				  base.erase(date);///////////////////////////////////////
			  }
			return 1;

		  }
	  }
			 return 0;

  }

  int  DeleteDate(const Date& date){
	  if(base.count(date)>0){
		  int N= base[date].size();
		 base[date].clear();
		 return N;
	  }
	 return 0;
  }

  void  Find(const Date& date) const{
	  if(base.count(date)>0){
		  FindWritter(base,date);
	  }
	  else{
		  return;
	  }
  }

  void Print() const{
	  for(const auto& x: base){
		  for(const auto& y: x.second){
			  PrintTrue(x.first,y);
		  }
	  }
  }
private:
  map<Date,set<string>> base;
};


void Process(Database& database,const string& ss){
    stringstream stream;
    stream << ss;
	string s;
	stream >> s;
	Date date;
	try{
	if(s=="Add"){
		string event;

		stream >> date >> event;
		database.AddEvent(date,event);
		}

	else if(s=="Del"){

		string event;
       //    try{
           stream >> date >> event;
           if(event != ""){
        	   if(database.DeleteEvent(date,event)){
        		   cout << "Deleted successfully" << endl;
           }
           else{
        	   cout << "Event not found" << endl;
           }
	}else{
		cout << "Deleted " << database.DeleteDate(date) << " events" << endl;
	}
         /*  }catch(exception& ex){
        	   stream >> event;
        	   if(event!=""){
        		   cout << "Event not found" << endl;
        	   }
        	   else{
        		   cout << "Deleted 0 events" << endl;
        	   }
           }*/
	}
	else if(s=="Find"){
        stream>> date;
        database.Find(date);
	}
	else if(s=="Print"){
           database.Print();
	}
	else if(s==""){
			return;
		}
	else{
		throw invalid_argument("Unknown command: "+s);
	}

	}catch(exception& ex){
		cout << ex.what() << endl;
	}
	}




int main() {



  Database db;

  string command;
  while (getline(cin, command)) {
	  Process(db,command);
  }

  return 0;
}
