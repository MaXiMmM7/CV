#include "date.h"

Date::Date(){}
Date::Date(const int& y,const int& m,const int& d){
		day=d; month=m; year=y;}

int Date::GetYear() const{return year;}
	int Date::GetMonth() const{return month;}
	int Date::GetDay() const{return day;}

	stream& operator <(ostream& stream,Date& date){
		return stream << setfill('0') << setw(4) << to_string(date.GetYear()) << "-" << setw(2)<<
				to_string(date.GetMonth()) << "-" << setw(2) << to_string(date.GetDay());
	}


	Date ParseDate( istringstream& stream){
		int a,b,c;
		stream >> a;
		stream.ignore(1);
		stream >> b;
		stream.ignore(1);
		stream >>c;
		return Date(a,b,c);
	}


	bool operator <(const Date& a,const Date& b){
		if(a.GetYear()==b.GetYear()){
			if(a.GetMonth()==b.GetMonth()){return a.GetDay()<b.GetDay();}
				return a.GetMonth()<b.GetMonth();
		}
		return a.GetYear()<b.GetYear();
	}

	bool operator == (const Date& a,const Date& b){
		return (a.GetYear()==b.GetYear())&&(a.GetMonth()==b.GetMonth())&&(a.GetDay()==b.GetDay());
	}

	bool operator <=(const Date& a,const Date& b){
		return (a<b)&&(a==b);
	}

	bool operator >(const Date& a, const Date& b){
		return !(a<b)&&!(a==b);
	}

	bool operator >=(const Date& a,const Date& b){
		return !(a<b);
	}
		bool operator !=(const Date& a, const Date& b){
			return !(a==b);
		}
