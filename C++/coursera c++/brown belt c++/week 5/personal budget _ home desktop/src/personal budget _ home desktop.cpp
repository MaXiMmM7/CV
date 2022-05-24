#include "test_runner.h"
#include <iostream>
#include <ctime>
#include <utility>
#include <iomanip>
#include <sstream>
#include <map>


using namespace std;

const int SECONDS_IN_A_DAY=60*60*24;

class Date{
public:
	Date(int day = 0, int month = 0, int year = 0):
		day_(day),month_(month),year_(year){}

	time_t AsTimestamp() const;

	int GetDay() const{
		return day_;
	}

	int GetMonth() const{
		return month_;
	}

	int GetYear() const{
		return year_;
	}


	Date operator++(int){
		Date old=*this;

		tm t={};
		t.tm_year=year_-1900;
		t.tm_mon=month_-1;
		t.tm_mday=day_+1;
		mktime(&t);

		year_=t.tm_year+1900;
		month_=t.tm_mon+1;
		day_=t.tm_mday;

		return old;
	}

private:
	int day_;
	int month_;
	int year_;
};


time_t Date::AsTimestamp() const {
  std::tm t;
  t.tm_sec   = 0;
  t.tm_min   = 0;
  t.tm_hour  = 0;
  t.tm_mday  = day_;
  t.tm_mon   = month_ - 1;
  t.tm_year  = year_ - 1900;
  t.tm_isdst = 0;
  return mktime(&t);
}

int ComputeDaysDiff(const Date& date_to, const Date& date_from) {
  const time_t timestamp_to = date_to.AsTimestamp();
  const time_t timestamp_from = date_from.AsTimestamp();
  static const int SECONDS_IN_DAY = 60 * 60 * 24;
  return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
}




bool operator==(const Date& l,const Date& r){
	return (l.GetYear()==r.GetYear())&&(l.GetMonth()==r.GetMonth())&&(l.GetDay()==r.GetDay());
}

bool operator<(const Date& l,const Date& r){
	if(l.GetYear()==r.GetYear()){
		if(l.GetMonth()==r.GetMonth()){
			return l.GetDay()<r.GetDay();
		}
		else{
			return l.GetMonth()<r.GetMonth();
		}
	}
	return l.GetYear()<r.GetYear();
}


bool operator<=(const Date& l,const Date& r){
	return (l<r)||(l==r);
}

istream& operator>>(istream& input,Date& date){
	int day;
	int month;
	int year;
	input >> year;
	input.ignore(1);
	input >> month;
	input.ignore(1);
	input >> day;

	date=Date(move(day),move(month),move(year));
	return input;
}

ostream& operator<<(ostream& output,const Date& date){
	return (output << setw(4) << setfill('0') << date.GetYear()
			<< "-"<< setw(2) << setfill('0') << date.GetMonth()
			<< "-"<< setw(2) << setfill('0') << date.GetDay() );
}




class Budget{
public:

	void Earn(Date from,Date to,int money){
		double money_per_day=(double)money/(ComputeDaysDiff(to,from)+1);
		for(;from<=to;from++){
			dates[from]+=money_per_day;
		}
	}

	double ComputeIncome(Date from,Date to) const{
		double income=0;

		auto It_from = dates.lower_bound(from);
		auto It_to = dates.upper_bound(to);

		for(;It_from!=It_to;It_from++){
			income+=It_from->second;
		}
		return income;
	}

	void PayTax(Date from, Date to){
		auto It_from = dates.lower_bound(from);
		auto It_to = dates.upper_bound(to);

		for(;It_from!=It_to;It_from++){
			It_from->second*=0.87;
		}
	}

	const map<Date,double>& Get( ) const{
		return dates;
	}

private:
	map<Date,double> dates;
};

void ReadAndPerform(istream& input = cin, ostream& output = cout){
	Budget bd;
	Date from;
	Date to;
	int money;
	int Q;
	input >> Q;
	string command;
	for(int i = 0; i < Q; i++){

		input >> command >> from >> to;

		if(command=="Earn"){
			input  >> money;
			bd.Earn(move(from), move(to), move(money));
		}

		if(command=="ComputeIncome"){
			output.precision(25);
			output << bd.ComputeIncome(move(from), move(to)) << "\n";
		}

		if(command=="PayTax"){
			bd.PayTax(move(from), move(to));
		}
	}


}


void Test_Date(){
	{
		Date d;
		istringstream input("2021-10-27");
		input >> d;
		ostringstream output;
		output << d;
		ASSERT_EQUAL(output.str(),string("2021-10-27"));
	}
	{
		Date d;
		istringstream input("2021-09-01");
		input >> d;
		ostringstream output;
		output << d;
		ASSERT_EQUAL(output.str(),string("2021-09-01"));
	}
	{
		Date d;
		istringstream input("1-1-1");
		input >> d;
		ostringstream output;
		output << d;
		ASSERT_EQUAL(output.str(),string("0001-01-01"));
	}
	{
		Date d1;
		Date d2;
		istringstream input("1-1-1 2020-02-25");
		input >> d1 >> d2;
		ostringstream output;
		output << d1 << " " << d2;
		ASSERT_EQUAL(output.str(),string("0001-01-01 2020-02-25"));
	}
	{
		Date d1;
		Date d2;
		istringstream input("2021-10-20 2021-10-27");
		input >> d1 >> d2;
		ASSERT_EQUAL(ComputeDaysDiff(d2,d1),7);
	}
	{
		Date d;
		istringstream input("2021-10-20");
		input >> d;
		ostringstream output;
		output << d;
		ASSERT_EQUAL(output.str(),string("2021-10-20"));
		output.str("");
		d++;
		output << d;
		ASSERT_EQUAL(output.str(),string("2021-10-21"));
		output.str("");
		for(int i=0;i<11;i++){
			d++;
		}
		output << d;
		ASSERT_EQUAL(output.str(),string("2021-11-01"));
	}
	{
		Date d1(2021,10,21);
		Date d2(2021,10,22);
		ASSERT_EQUAL((d1<d2),true);
		ASSERT_EQUAL((d2<d2),false);
		ASSERT_EQUAL((d2<d1),false);
		ASSERT_EQUAL((d1<=d2),true);
		ASSERT_EQUAL((d2<=d2),true);
		ASSERT_EQUAL((d2<=d1),false);
		ASSERT_EQUAL((Date(2020,10,15)<Date(2021,10,15)),true);
		ASSERT_EQUAL((Date(2021,10,15)<Date(2020,10,15)),false);
		ASSERT_EQUAL((Date(2021,10,15)<Date(2021,11,15)),true);
		ASSERT_EQUAL((Date(2021,11,15)<Date(2021,10,15)),false);
		ASSERT_EQUAL((Date(2021,11,15)<Date(2021,11,16)),true);
		ASSERT_EQUAL((Date(2021,11,16)<Date(2021,11,15)),false);
		ASSERT_EQUAL((Date(2021,11,16)<Date(2021,11,16)),false);
	}
}

void Test_Budget(){
	{
		Budget budget;
		ASSERT_EQUAL(budget.ComputeIncome(Date(25,10,2021), Date(27,10,2021)),0.);
		budget.PayTax(Date(20,10,2021), Date(27,11,2021));
		ASSERT_EQUAL(budget.ComputeIncome(Date(25,10,2021), Date(27,10,2021)),0.);
		ASSERT_EQUAL(budget.ComputeIncome(Date(1,1,2020), Date(27,10,2020)),0.);
		budget.Earn(Date(25,10,2021), Date(27,10,2021),15);
		ASSERT_EQUAL(budget.ComputeIncome(Date(25,10,2021), Date(27,10,2021)),15.)
		budget.PayTax(Date(25,10,2021), Date(25,10,2021));
		ASSERT_EQUAL(budget.ComputeIncome(Date(25,10,2021), Date(25,10,2021)),(5.*0.87));
		ASSERT_EQUAL(budget.ComputeIncome(Date(25,10,2021), Date(27,10,2021)),(5.*0.87+10.))
	}
	{
		Budget budget;
		budget.Earn(Date(1,1,2020), Date(1,1,2020), 10);
		ASSERT_EQUAL(budget.ComputeIncome(Date(25,10,2021), Date(25,10,2021)),0.);
		ASSERT_EQUAL(budget.ComputeIncome(Date(1,1,2020), Date(1,1,2020)),10.);
		ASSERT_EQUAL(budget.ComputeIncome(Date(1,1,2015), Date(1,1,2025)),10.);
	}
	{

		Budget budget_;
		istringstream input("8\nEarn 2000-01-02 2000-01-06 20\n"
				"ComputeIncome 2000-01-01 2001-01-01\n"
				"PayTax 2000-01-02 2000-01-03\n"
				"ComputeIncome 2000-01-01 2001-01-01\n"
				"Earn 2000-01-03 2000-01-03 10\n"
				"ComputeIncome 2000-01-01 2001-01-01\n"
				"PayTax 2000-01-03 2000-01-03\n"
				"ComputeIncome 2000-01-01 2001-01-01");
		ostringstream output;
		ReadAndPerform(input,output);

		string true_result("20\n18.96000000000000085265128\n28.96000000000000085265128\n27.20759999999999934061634\n");
		ASSERT_EQUAL(output.str(),true_result);
	}
}
int main(){

	TestRunner tr;
	RUN_TEST(tr,Test_Date);

	RUN_TEST(tr,Test_Budget);


	ReadAndPerform();

	return 0;
}






