
#pragma once
#include <iostream>
#include <iomanip>
#include <string>
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
	int year,month,day;
};

ostream& operator <<(ostream& stream,const Date& date);

Date ParseDate(istream& stream);
//Date ParseDate( istringstream& stream);


bool operator <(const Date& a,const Date& b);

bool operator == (const Date& a,const Date& b);

bool operator <=(const Date& a,const Date& b);

bool operator >(const Date& a, const Date& b);

bool operator >=(const Date& a,const Date& b);

bool operator !=(const Date& a, const Date& b);
