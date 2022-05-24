#include "test_runner.h"
#include <iostream>
#include <ctime>
#include <utility>
#include <iomanip>
#include <sstream>
#include <set>


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

size_t HasherFromDateToSize_t(const Date& date){
	return static_cast<size_t>(ComputeDaysDiff(date,Date(1,1,2000)));
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
	//input.ignore(1);

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

	Budget(){
		dates.assign(static_cast<size_t>(ComputeDaysDiff(Date(31,12,2099),Date(1,1,2000))),0.);
	}

	void Earn(Date from,Date to,int money){
		// from      111from111000to//  000from11111to00 // 000from000to000
		size_t start=HasherFromDateToSize_t(from);
		size_t finish=HasherFromDateToSize_t(to);
	    ///
		indexes_start.insert(start);
		indexes_finish.insert(finish);
		///
		double money_per_day=double(money)/(ComputeDaysDiff(to,from)+1);

		for(;start<=finish;start++){
			dates[start]+=money_per_day;
		}

	}

	double ComputeIncome(Date from,Date to) const{
		double income = 0;
		if(indexes_start.empty()){
			return income;
		}

		size_t start=HasherFromDateToSize_t(from);
		size_t finish=HasherFromDateToSize_t(to);
		size_t checkpoint;
		PutNewCheckpoint(start,checkpoint,finish);


		while(start<=finish){
			if(start<=checkpoint){
			income+=dates[start];
				start++;
			}
			else{
			PutNewCheckpoint(start,checkpoint,finish);
			}
		}

		return income;
	}

	void PayTax(Date from, Date to){

		if(indexes_start.empty()){
			return;
		}

		size_t start=HasherFromDateToSize_t(from);
		size_t finish=HasherFromDateToSize_t(to);
		size_t checkpoint;
		PutNewCheckpoint(start,checkpoint,finish);

		while(start<=finish){
			if(start<=checkpoint){
				dates[start]*=0.87;
				start++;
			}
			else{
				PutNewCheckpoint(start,checkpoint,finish);
			}
		}
	}

	const vector<double>& Get( ) const{
		return dates;
	}

private:
	void PutNewCheckpoint(size_t& start,size_t& checkpoint,size_t finish) const{

		if(dates[start]==0){
			auto It=indexes_start.lower_bound(start);
			if(It!=indexes_start.end()&&*It<=finish){
				start=*It;
			}
			else{
				start=finish+1;
			}
		}
		auto It=indexes_finish.lower_bound(start);
		if(It!=indexes_finish.end()&&*It<=finish){
			checkpoint=*It;
		}
		else{
			checkpoint=finish;
		}


	}

	vector<double> dates;
	set<size_t> indexes_start;
	set<size_t> indexes_finish;
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

}

void Test_Hasher(){
	{
		ASSERT_EQUAL(HasherFromDateToSize_t(Date(1,1,2000)),static_cast<size_t>(0));
		ASSERT_EQUAL(HasherFromDateToSize_t(Date(2,1,2000)),static_cast<size_t>(1));
		ASSERT_EQUAL(HasherFromDateToSize_t(Date(31,12,2099)),
				static_cast<size_t>(ComputeDaysDiff(Date(31,12,2099),Date(1,1,2000))));
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
	RUN_TEST(tr,Test_Hasher);
	RUN_TEST(tr,Test_Budget);



    ReadAndPerform();

	return 0;
}

