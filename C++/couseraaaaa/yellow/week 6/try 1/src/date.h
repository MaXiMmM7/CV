#pragma once




#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;
class Date{
public:
	Date();

	Date(const int& y,const int& m,const int& d);

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
private:
	 int year;
	 int month;
	 int day;
};


istringstream& operator >>(istringstream& stream,Date& date);

ostream& operator <<(ostream& stream,const Date& date);

bool operator <(const Date& a,const Date& b);

bool operator ==(const Date& a,const Date& b);

bool operator >(const Date& a,const Date& b);

bool operator >=(const Date& a,const Date& b);

bool operator <=(const Date& a,const Date& b);

bool operator !=(const Date& a,const Date&b);

Date ParseDate(istringstream& stream);
