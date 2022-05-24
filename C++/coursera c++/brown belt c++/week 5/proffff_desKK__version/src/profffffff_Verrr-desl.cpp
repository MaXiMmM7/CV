#include "test_runner.h"
#include <iostream>
#include <ctime>
#include <utility>
#include <iomanip>
#include <sstream>
#include <set>
#include <random>


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
	input.ignore(1);

	date = Date(move(day),move(month),move(year));
	return input;
}

ostream& operator<<(ostream& output,const Date& date){
	return (output << setw(4) << setfill('0') << date.GetYear()
			<< "-"<< setw(2) << setfill('0') << date.GetMonth()
			<< "-"<< setw(2) << setfill('0') << date.GetDay() );
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



class Budget{
public:

	Budget(){
		dates.assign(static_cast<size_t>(ComputeDaysDiff(Date(1,1,2100),Date(1,1,2000))),0.);
		dates_spend.assign(static_cast<size_t>(ComputeDaysDiff(Date(1,1,2100),Date(1,1,2000))),0.);
	}

	void Earn(Date from,Date to,int money){
		DoSomethingWithMoney(move(from),move(to),move(money),dates,indexes_start,indexes_finish);
	}

	void Spend(Date from,Date to,int money){
		DoSomethingWithMoney(move(from),move(to),move(money),dates_spend,indexes_start_spend,indexes_finish_spend);
	}


	double ComputeIncome(Date from,Date to) const{
		double sum = 0.;
		sum+=ComputeSomething(move(from),move(to),dates,indexes_start,indexes_finish);
		sum-=ComputeSomething(move(from),move(to),dates_spend,indexes_start_spend,indexes_finish_spend);
		return sum;
	}

	void PayTax(Date from, Date to, int percentage){

		if(indexes_start.empty()){
			return;
		}

		size_t start=HasherFromDateToSize_t(from);
		size_t finish=HasherFromDateToSize_t(to);
		size_t checkpoint;
		PutNewCheckpoint(start,checkpoint,finish,dates,indexes_start,indexes_finish);

		while(start<=finish){
			if(start<=checkpoint){
				dates[start]*=((100.- percentage)/100.);
				start++;
			}
			else{
				PutNewCheckpoint(start,checkpoint,finish,dates,indexes_start,indexes_finish);
			}
		}
	}

	const vector<double>& GetDates( ) const{
		return dates;
	}

	const vector<double>& GetDatesSpend( ) const{
		return dates_spend;
	}

private:

	void DoSomethingWithMoney(Date from,Date to,int money,
			vector<double>& d ,set<size_t>& s,set<size_t>& f){

		size_t start=HasherFromDateToSize_t(from);
		size_t finish=HasherFromDateToSize_t(to);

		s.insert(start);
		f.insert(finish);
		double money_per_day=double(money)/(ComputeDaysDiff(to,from)+1);

		for(;start<=finish;start++){
			d[start]+=money_per_day;
		}
	}

	double ComputeSomething(Date from,Date to,
			const vector<double>& d ,const set<size_t>& s,const set<size_t>& f) const{

		double sum = 0;

		if(d.empty()){
			return sum;
		}

		size_t start=HasherFromDateToSize_t(from);
		size_t finish=HasherFromDateToSize_t(to);
		size_t checkpoint;
		PutNewCheckpoint(start,checkpoint,finish,d,s,f);

		while(start<=finish){
			if(start<=checkpoint){
				sum+=d[start];
				start++;
			}
			else{
				PutNewCheckpoint(start,checkpoint,finish,d,s,f);
			}
		}

		return sum;

	}

	void PutNewCheckpoint(size_t& start,size_t& checkpoint,size_t finish,
			const vector<double>& d,const set<size_t>& s,const set<size_t>& f) const{

		if(d[start]==0){
			auto It=s.lower_bound(start);
			if(It!=s.end()&&*It<=finish){
				start=*It;
			}
			else{
				start=finish+1;
			}
		}
		auto It=f.lower_bound(start);
		if(It!=f.end()&&*It<=finish){
			checkpoint=*It;
		}
		else{
			checkpoint=finish;
		}
	}

	vector<double> dates;
	set<size_t> indexes_start;
	set<size_t> indexes_finish;

	vector<double> dates_spend;
	set<size_t> indexes_start_spend;
	set<size_t> indexes_finish_spend;

};


void ReadAndPerform(istream& input = cin, ostream& output = cout){
	Budget bd;
	Date from;
	Date to;
	int money;
	int Q;
	input >> Q;
	string command;
	int percentage;

	//
	//cerr << "\n\nHello\n\n" << endl;
	//
	for(int i = 0; i < Q; i++){

		input >> command >> from >> to;

		//
//		cerr <<  command  <<" " << from  << " " <<  to;
		//
		if(command=="Earn"){
			input  >> money;
			//
	//		cerr << "  " << money;
			//
			bd.Earn(move(from), move(to), move(money));
		}

		if(command=="ComputeIncome"){
			//output.precision(25);
			output <<fixed << setprecision(25) << setw(25) <<  bd.ComputeIncome(move(from), move(to)) << "\n";
		}

		if(command=="PayTax"){
			input >> percentage;
			//
//						cerr << "  " << percentage;
						//
			bd.PayTax(move(from), move(to),move(percentage));
		}
		if(command=="Spend"){
			input  >> money;
			//
	//					cerr << "  " << money;
						//
			bd.Spend(move(from), move(to), move(money));
		}
		///
//		cerr << "\n";
		///
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
		budget.PayTax(Date(20,10,2021), Date(27,11,2021),13);
		ASSERT_EQUAL(budget.ComputeIncome(Date(25,10,2021), Date(27,10,2021)),0.);
		ASSERT_EQUAL(budget.ComputeIncome(Date(1,1,2020), Date(27,10,2020)),0.);
		budget.Earn(Date(25,10,2021), Date(27,10,2021),15);

		ASSERT_EQUAL(budget.ComputeIncome(Date(25,10,2021), Date(27,10,2021)),15.)
		budget.PayTax(Date(25,10,2021), Date(25,10,2021),13);
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
				"PayTax 2000-01-02 2000-01-03 13\n"
				"ComputeIncome 2000-01-01 2001-01-01\n"
				"Spend 2000-12-30 2001-01-02 14\n"
				"ComputeIncome 2000-01-01 2001-01-01\n"
				"PayTax 2000-12-30 2000-12-30 13\n"
				"ComputeIncome 2000-01-01 2001-01-01");
		ostringstream output;
		ReadAndPerform(input,output);

		string true_result("20\n18.96000000000000085265128\n8.460000000000000852651283\n8.460000000000000852651283\n");
		ASSERT_EQUAL(output.str(),true_result);
	}
	{

		//
	//	cout << "\n\n\nWe are Here \n\n\n" << endl;
		//

		Budget budget_;
		istringstream input("39\n"
				"ComputeIncome 2000-01-01 2001-01-05\n"
				"ComputeIncome 2000-01-01 2099-01-05\n"
				"ComputeIncome 2000-01-01 2000-01-01\n"
				"PayTax 2000-01-01 2000-01-05 0\n"
				"ComputeIncome 2000-01-01 2001-01-05\n"
				"ComputeIncome 2000-01-01 2099-01-05\n"
				"ComputeIncome 2000-01-01 2000-01-01\n"
				"Earn 2000-01-01 2000-01-05 1000\n"     //
				"Spend 2000-01-01 2000-01-05 1000\n"
				"ComputeIncome 2000-01-01 2001-01-05\n"
				"ComputeIncome 2000-01-01 2099-01-05\n"
				"ComputeIncome 2000-01-01 2000-01-01\n"
				"Earn 2000-01-01 2000-01-05 1000\n"
				"ComputeIncome 2000-01-01 2001-01-05\n"
				"PayTax 2000-01-01 2000-01-05 5\n"
				"ComputeIncome 2000-01-01 2000-01-05\n"
				"ComputeIncome 2000-01-01 2000-01-01\n"
				"ComputeIncome 2000-01-01 2099-01-05\n"
				"PayTax 2000-01-01 2000-01-05 0\n"
				"ComputeIncome 2000-01-01 2000-01-05\n"
				"ComputeIncome 2000-01-01 2000-01-01\n"
				"ComputeIncome 2000-01-01 2099-01-05\n"
				"PayTax 2000-01-01 2000-01-05 100\n"
				"ComputeIncome 2000-01-01 2000-01-05\n"
				"ComputeIncome 2000-01-01 2000-01-01\n"
				"ComputeIncome 2000-01-01 2099-01-05\n" //
				"Spend 2000-02-01 2000-02-05 1000\n"
				"ComputeIncome 2000-01-01 2000-01-05\n"
				"ComputeIncome 2000-01-01 2000-01-01\n"
				"ComputeIncome 2000-01-01 2099-01-05\n"
				"ComputeIncome 2000-02-01 2000-02-05\n"
				"ComputeIncome 2000-02-01 2000-02-01\n"
				"ComputeIncome 2000-02-01 2099-01-05\n"
				"ComputeIncome 2000-01-01 2099-01-05\n"//
				"Earn 2000-01-04 2000-01-05 1000\n"
				"ComputeIncome 2000-01-04 2000-01-05\n" /////////600
				"ComputeIncome 2000-01-01 2000-01-05\n"/////////////////0
				"ComputeIncome 2000-01-05 2000-01-05\n"////////////////////300
				"ComputeIncome 2000-01-01 2099-01-05\n"///////////////////-1000
		);
		ostringstream output;
		ReadAndPerform(input,output);
//600 0 300 -1000
		string true_result("0\n0\n0\n0\n0\n0\n0\n0\n0\n1000\n900\n180\n900\n900\n180\n900\n-1000\n-200\n-1000\n"
				"-1000\n-200\n-2000\n-1000\n-200\n-1000\n-2000\n600\n0\n300\n-1000\n");
		ASSERT_EQUAL(output.str(),true_result);

	}
	{

		Budget budget_;
		istringstream input("11\n"
				"ComputeIncome 2000-01-01 2001-01-05\n"
				"ComputeIncome 2000-01-01 2099-01-05\n"
				"Spend 2000-01-01 2000-01-05 1000\n"
				"ComputeIncome 2000-01-01 2001-01-05\n"
				"ComputeIncome 2000-01-01 2099-01-05\n"
				"PayTax 2000-01-01 2000-01-05 95\n"
				"ComputeIncome 2000-01-01 2001-01-05\n"
				"ComputeIncome 2000-01-01 2099-01-05\n"
				"Earn 2000-01-01 2000-01-05 1000\n"
				"ComputeIncome 2000-01-01 2001-01-05\n"
				"ComputeIncome 2000-01-01 2099-01-05\n"
				);
		ostringstream output;
		ReadAndPerform(input,output);

		string true_result("0\n0\n-1000\n-1000\n-1000\n-1000\n0\n0\n");
		ASSERT_EQUAL(output.str(),true_result);

	}

	{
		//Test
		Budget budget;
		budget.Earn(Date(1,1,2000), Date(1,1,2000), 100);
		ASSERT_EQUAL(budget.GetDates()[0],100.);
		ASSERT_EQUAL(budget.GetDatesSpend()[0],0.);
		budget.Earn(Date(31,12,2099), Date(31,12,2099), 100);
		ASSERT_EQUAL(budget.GetDates().back(),100.);
		ASSERT_EQUAL(budget.GetDatesSpend().back(),0.);
		ASSERT_EQUAL(budget.ComputeIncome(Date(1,1,2000),Date(31,12,2099)),200.);
		budget.PayTax(Date(31,12,2099),Date(31,12,2099),50);
		ASSERT_EQUAL(budget.ComputeIncome(Date(1,1,2000),Date(31,12,2099)),150.);
		budget.PayTax(Date(1,1,2000),Date(31,12,2099),50);
		ASSERT_EQUAL(budget.ComputeIncome(Date(1,1,2000),Date(31,12,2099)),75.);
		budget.Spend(Date(31,12,2099),Date(31,12,2099),100);
		ASSERT_EQUAL(budget.GetDatesSpend().back(),100.);
		ASSERT_EQUAL(budget.ComputeIncome(Date(1,1,2000),Date(31,12,2099)),-25.);
		ASSERT_EQUAL(budget.ComputeIncome(Date(1,1,2000),Date(31,12,2055)),50.);
		budget.Earn(Date(1,1,2050),Date(20,1,2050),20000);
		ASSERT_EQUAL(budget.ComputeIncome(Date(1,1,2001),Date(31,12,2055)),20000.);
		ASSERT_EQUAL(budget.ComputeIncome(Date(1,1,2050),Date(5,1,2050)),5000.);
		ASSERT_EQUAL(budget.ComputeIncome(Date(7,1,2050),Date(11,1,2050)),5000.);
		ASSERT_EQUAL(budget.ComputeIncome(Date(10,1,2050),Date(16,1,2050)),7000.);
		ASSERT_EQUAL(budget.ComputeIncome(Date(1,1,2000),Date(31,1,2055)),20050.);
		budget.Spend(Date(6,1,2050),Date(15,1,2050),1000);
		ASSERT_EQUAL(budget.ComputeIncome(Date(1,1,2001),Date(31,12,2055)),19000.);
		ASSERT_EQUAL(budget.ComputeIncome(Date(1,1,2050),Date(20,1,2050)),19000.);
		ASSERT_EQUAL(budget.ComputeIncome(Date(6,1,2050),Date(15,1,2050)),9000.);//
		ASSERT_EQUAL(budget.ComputeIncome(Date(1,1,2050),Date(5,1,2050)),5000.);
		budget.Earn(Date(6,1,2050),Date(10,1,2050),5000);
		ASSERT_EQUAL(budget.ComputeIncome(Date(1,1,2001),Date(31,12,2055)),24000.);
		ASSERT_EQUAL(budget.ComputeIncome(Date(5,1,2050),Date(15,1,2050)),15000.);
		ASSERT_EQUAL(budget.ComputeIncome(Date(1,1,2050),Date(5,1,2050)),5000.);
		budget.Spend(Date(7,1,2050),Date(8,1,2050),2000);
		ASSERT_EQUAL(budget.ComputeIncome(Date(1,1,2001),Date(31,12,2055)),22000.);
		ASSERT_EQUAL(budget.ComputeIncome(Date(6,1,2050),Date(15,1,2050)),12000.);
		ASSERT_EQUAL(budget.ComputeIncome(Date(7,1,2050),Date(8,1,2050)),1800.);
		budget.Spend(Date(20,1,2050),Date(24,1,2050),5000);
		ASSERT_EQUAL(budget.ComputeIncome(Date(1,1,2001),Date(31,12,2055)),17000.);
		ASSERT_EQUAL(budget.ComputeIncome(Date(1,1,2050),Date(20,1,2050)),21000.);
		ASSERT_EQUAL(budget.ComputeIncome(Date(20,1,2050),Date(20,1,2050)),0.);





	}

	{
		random_device rd;   // non-deterministic generator
		mt19937 gen(rd());  // to seed mersenne twister.

		uniform_int_distribution<> dist_year(2000,2099); // distribute results between 1 and 6 inclusive.
	    uniform_int_distribution<> dist_month(1,12); // distribute results between 1 and 6 inclusive.
	    uniform_int_distribution<> dist_day(1,28); // distribute results between 1 and 6 inclusive.
	    uniform_int_distribution<> dist_values(0,1000000); // distribute results between 1 and 6 inclusive.
	    uniform_int_distribution<> dist_percentage(0,100); // distribute results between 1 and 6 inclusive.

		    //int Q=1000;
		int Q=1;
	    double res1,res2;
		    double sum_ = 0.;
		    int year_from,month_from,day_from,year_to,month_to,day_to,money;
		    Date d1,d2;

		    {
		 //   cerr << "first test" << endl;
		    	Budget budget;

		    	for(int i = 0; i < Q;i++){

		    		year_from=dist_year(gen);
		    		month_from=dist_month(gen);
		    		day_from=dist_day(gen);
		    		year_to=dist_year(gen);
		    		month_to=dist_month(gen);
		    		day_to=dist_day(gen);
		    		money=dist_values(gen);

		    		d1=Date(day_from,month_from,year_from);
		    		d2=Date(day_to,month_to,year_to);
		    		if(d2 < d1){
		    			Date d =d2;
		    			d2=d1;
		    			d1=d;
		    		}

		    		money=dist_values(gen);

		    		sum_+=money;

		    		stringstream stream1;
		    		stringstream stream2;

		    	budget.Earn(d1,d2,money);
	///	    	cout << "Day from: " << d1 << "  Day to:  " << d2
		//    			<< " money : " << money << "  income:  " << sum_ << "  i =  " << i << endl;


		    	stream1 <<fixed <<   setprecision(25) << budget.ComputeIncome(Date(1,1,2000),Date(31,12,2099));
		    	stream2 <<fixed <<    setprecision(25) << sum_;
		    	stream1 >> res1;
		    	stream2 >> res2;
	//	    	cout << fixed <<  setprecision(25) << "res1:  " <<setw(10)<< res1 << "  res2:  " << setw(26) << res2<< endl;

	//	    ASSERT_EQUAL(((res1-res2)<std::numeric_limits<double>::epsilon()),true);
		 	ASSERT_EQUAL(((res1-res2)<0.001),true);
		    	}

		    }
		    {
	//	    	cerr << "second test with spend" << endl;

		    	sum_ = 0.;
		    	int i=0;
		    	Budget budget;

		    	for(; i < Q/2;i++){

		    		year_from=dist_year(gen);
		    		month_from=dist_month(gen);
		    		day_from=dist_day(gen);
		    		year_to=dist_year(gen);
		    		month_to=dist_month(gen);
		    		day_to=dist_day(gen);

		    		money=dist_values(gen);

		    		d1=Date(day_from,month_from,year_from);
		    		d2=Date(day_to,month_to,year_to);
		    			    		if(d2 < d1){
		    			    			Date d =d2;
		    			    			d2=d1;
		    			    			d1=d;
		    			    		}

		    			    		money=dist_values(gen);

		    			    		sum_+=money;

		    			    		stringstream stream1;
		    			    		stringstream stream2;

		    			    	budget.Earn(d1,d2,money);
///		    			    	cout << "Day from: " << d1 << "  Day to:  " << d2
	//	    			    			<< " money : " << money << "  income:  " << sum_ << "  i =  " << i << endl;


		    			    	stream1 <<fixed <<   setprecision(25) << budget.ComputeIncome(Date(1,1,2000),Date(31,12,2099));
		    			    	stream2 <<fixed <<    setprecision(25) << sum_;
		    			    	stream1 >> res1;
		    			    	stream2 >> res2;
//		    			    	cout << fixed  << setprecision(25) << "res1:  " << res1 << "  res:2  " << res2<< endl;

		    			    	//ASSERT_EQUAL(((res1-res2)<std::numeric_limits<double>::epsilon()),true);
		    			    	ASSERT_EQUAL(((res1-res2)<0.001),true);



		    	}
		    			    	for(; i < Q;i++){

		    			    			    		year_from=dist_year(gen);
		    			    			    		month_from=dist_month(gen);
		    			    			    		day_from=dist_day(gen);
		    			    			    		year_to=dist_year(gen);
		    			    			    		month_to=dist_month(gen);
		    			    			    		day_to=dist_day(gen);

		    			    			    		money=dist_values(gen);

		    			    			    		d1=Date(day_from,month_from,year_from);
		    			    			    		d2=Date(day_to,month_to,year_to);
		    			    			    			    		if(d2 < d1){
		    			    			    			    			Date d =d2;
		    			    			    			    			d2=d1;
		    			    			    			    			d1=d;
		    			    			    			    		}

		    			    			    			    		money=dist_values(gen);

		    			    			    			    		sum_-=money;

		    			    			    			    		stringstream stream1;
		    			    			    			    		stringstream stream2;

		    			    			    			    	budget.Spend(d1,d2,money);
//		    			    			    			    	cout << "Day from: " << d1 << "  Day to:  " << d2
	//	    			    			    			    			<< " money : " << money << "  income:  " << sum_ << "  i =  " << i << endl;


		    			    			    			    	stream1 <<fixed <<   setprecision(25) << budget.ComputeIncome(Date(1,1,2000),Date(31,12,2099));
		    			    			    			    	stream2 <<fixed <<    setprecision(25) << sum_;
		    			    			    			    	stream1 >> res1;
		    			    			    			    	stream2 >> res2;
		    			    			 //   			    	cout << fixed  << setprecision(25) << "res1:  " << res1 << "  res:2  " << res2<< endl;

		    			    			    			    	//ASSERT_EQUAL(((res1-res2)<std::numeric_limits<double>::epsilon()),true);
		    			    			    			    	ASSERT_EQUAL(((res1-res2)<0.001),true);
		    	}
		    }

		    {
//		    cerr << "Test with spend and paytax"  << endl;

		    sum_ = 0.;
		    		    	int i=0;
		    		    	Budget budget;
		    		    	int percentage;

		    		    	for(; i < Q/2;i++){

		    		    		year_from=dist_year(gen);
		    		    		month_from=dist_month(gen);
		    		    		day_from=dist_day(gen);
		    		    		year_to=dist_year(gen);
		    		    		month_to=dist_month(gen);
		    		    		day_to=dist_day(gen);
		    		    		percentage=dist_percentage(gen);

		    		    		money=dist_values(gen);

		    		    		d1=Date(day_from,month_from,year_from);
		    		    		d2=Date(day_to,month_to,year_to);
		    		    			    		if(d2 < d1){
		    		    			    			Date d =d2;
		    		    			    			d2=d1;
		    		    			    			d1=d;
		    		    			    		}

		    		    			    		money=dist_values(gen);

		    		    			    		sum_+=money;
		    		    			    		sum_*=((100.-percentage)/100.);

		    		    			    		stringstream stream1;
		    		    			    		stringstream stream2;

		    		    			    	budget.Earn(d1,d2,money);
		    		    			    	budget.PayTax(Date(1,1,2000),Date(31,12,2099),percentage);

//		    		    			    	cout << "Day from: " << d1 << "  Day to:  " << d2
	//	    		    			    			<< " money : " << money << "  income:  " << sum_
		//											<< "  i =  " << i << "  percentage:  " << percentage <<  endl;


		    		    			    	stream1 <<fixed <<   setprecision(25) << budget.ComputeIncome(Date(1,1,2000),Date(31,12,2099));
		    		    			    	stream2 <<fixed <<    setprecision(25) << sum_;
		    		    			    	stream1 >> res1;
		    		    			    	stream2 >> res2;
//		    		    			    	cout << fixed  << setprecision(25) << "res1:  " << res1 << "  res:2  " << res2<< endl;

		    		    			    	//ASSERT_EQUAL(((res1-res2)<std::numeric_limits<double>::epsilon()),true);
		    		    			    	ASSERT_EQUAL(((res1-res2)<0.001),true);



		    		    	}
		    		    			    	for(; i < Q;i++){

		    		    			    			    		year_from=dist_year(gen);
		    		    			    			    		month_from=dist_month(gen);
		    		    			    			    		day_from=dist_day(gen);
		    		    			    			    		year_to=dist_year(gen);
		    		    			    			    		month_to=dist_month(gen);
		    		    			    			    		day_to=dist_day(gen);

		    		    			    			    		money=dist_values(gen);

		    		    			    			    		d1=Date(day_from,month_from,year_from);
		    		    			    			    		d2=Date(day_to,month_to,year_to);
		    		    			    			    			    		if(d2 < d1){
		    		    			    			    			    			Date d =d2;
		    		    			    			    			    			d2=d1;
		    		    			    			    			    			d1=d;
		    		    			    			    			    		}

		    		    			    			    			    		money=dist_values(gen);

		    		    			    			    			    		sum_-=money;

		    		    			    			    			    		stringstream stream1;
		    		    			    			    			    		stringstream stream2;

		    		    			    			    			    	budget.Spend(d1,d2,money);
//		    		    			    			    			    	cout << "Day from: " << d1 << "  Day to:  " << d2
	//	    		    			    			    			    			<< " money : " << money << "  income:  " << sum_ << "  i =  " << i << endl;


		    		    			    			    			    	stream1 <<fixed <<   setprecision(25) << budget.ComputeIncome(Date(1,1,2000),Date(31,12,2099));
		    		    			    			    			    	stream2 <<fixed <<    setprecision(25) << sum_;
		    		    			    			    			    	stream1 >> res1;
		    		    			    			    			    	stream2 >> res2;
//		    		    			    			    			    	cout << fixed  << setprecision(25) << "res1:  " << res1 << "  res:2  " << res2<< endl;

		    		    			    			    			    	//ASSERT_EQUAL(((res1-res2)<std::numeric_limits<double>::epsilon()),true);
		    		    			    			    			    	ASSERT_EQUAL(((res1-res2)<0.001),true);
		    		    	}

		    }

	}
}

int main(){

	TestRunner tr;
	RUN_TEST(tr,Test_Date);
	RUN_TEST(tr,Test_Hasher);
	//RUN_TEST(tr,Test_Budget);



    ReadAndPerform();

	return 0;
}

