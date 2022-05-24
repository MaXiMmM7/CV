


#include "date.h"


#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;



	Date::Date():year(0),month(0),day(0){}

	Date:: Date(const int& y,const int& m,const int& d):
			year(y),month(m),day(d){}

	int Date::GetYear() const {return year;}
	int Date::GetMonth() const {return month;}
	int Date::GetDay() const {return day;}


istringstream& operator >>(istringstream& stream,Date& date){
	if(stream){
		int y,m,d;
		char a,b;
		stream >> y >>a >> m>>b>>d;
		if((stream)&&(a=='-')&&(b=='-')&&(stream.peek()==' ')){
			date=Date(y,m,d);
		}
	}
	return stream;
}

ostream& operator <<(ostream& stream,const Date& date){
	stream << setfill('0') << setw(4) << to_string(date.GetYear()) << "-" << setw(2)<<
			to_string(date.GetMonth()) << "-" << setw(2) << to_string(date.GetDay());
			return stream;
}

bool operator <(const Date& a,const Date& b){
	if(a.GetYear()==b.GetYear()){
		if(a.GetMonth()==b.GetMonth()){
			return a.GetDay() <b.GetDay();
		}
		return a.GetMonth()<b.GetMonth();
	}
	return a.GetYear()<b.GetYear();
}

bool operator ==(const Date& a,const Date& b){
	return (a.GetYear()==b.GetYear())&&(a.GetMonth()==b.GetMonth())&&(a.GetDay()==b.GetDay());
}

bool operator >(const Date& a,const Date& b){
	return (!(a==b))&&(!(a<b));
}

bool operator >=(const Date& a,const Date& b){
	return !(a<b);
}
bool operator <=(const Date& a,const Date& b){
	return (a<b)||(a==b);
}
bool operator !=(const Date& a,const Date&b){
	return !(a==b);
}

Date ParseDate(istringstream& stream){
	Date date;
	stream >> date;
	return date;
}
