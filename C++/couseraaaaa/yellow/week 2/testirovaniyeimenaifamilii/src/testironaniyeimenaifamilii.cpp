/*#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};


/////////////////////////////
struct omg{
	string FirstName="0";
	string LastName="0";
};

string draw(const string& first_name, const string& last_name){
	if((first_name!="0")&&(last_name!="0")){
		return first_name + " " + last_name;
	}
	else if(first_name!="0"){
		return first_name + " with unknown last name";
	}
	return last_name + " with unknown first name";
}

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
  years[year].FirstName=first_name;
  string helper="0";
  for(auto& x: years){
	  if(x.first>year){
		  if((x.second.FirstName=="0")||(x.second.FirstName==helper)){
			  x.second.FirstName=first_name;
		  }

	  }
	  if(x.first<year){
	  helper=x.second.FirstName;
	  }
  }
  helper="0";
  if(years[year].LastName=="0"){
  for (auto& x:years){
	  if(x.first==year){
		  x.second.LastName=helper;
		  break;
	  }
	  helper=x.second.LastName;
  }
  }

  }
  void ChangeLastName(int year, const string& last_name) {
	  years[year].LastName=last_name;
	    string helper="0";
	    for(auto& x: years){
	  	  if(x.first>year){
	  		  if((x.second.LastName=="0")||(x.second.LastName==helper)){
	  			  x.second.LastName=last_name;
	  		  }

	  	  }
	  	  if(x.first<year){
	  	  helper=x.second.LastName;
	  	  }
	    }
	    helper="0";
	    if(years[year].FirstName=="0"){
	    for (auto& x:years){
	  	  if(x.first==year){
	  		  x.second.FirstName=helper;
	  		  break;
	  	  }
	  	  helper=x.second.FirstName;
	    }
	    }

  }
  string GetFullName(int year) {
	  int helper=0;
	  if(years.empty()){
		  return "Incognito";
	  }
	  for(const auto& x :years){
		  if((x.first>year)&&helper==0){
			  return "Incognito";
		  }
		  if(x.first>year){
			  return draw(years.at(helper).FirstName,years.at(helper).LastName);
		  }
		  helper=x.first;
	  }
	  return draw(years.at(helper).FirstName,years.at(helper).LastName);

  }
private:
  map<int,omg> years;
};
///////////////////

void TestEmpty(){
	{
		Person empty;
		for(int year : {0, 1}){
		AssertEqual(empty.GetFullName(year),"Incognito","empty in "+to_string(year));
		}

	}
	{
						Person empty;
						empty.GetFullName(1);
						AssertEqual(empty.GetFullName(1),"Incognito","double call empty in "+to_string(1));
				}
}

void TestChangeFirstName(){

	{
		Person person;
	    person.ChangeFirstName(1, "Max");
	    AssertEqual(person.GetFullName(0),"Incognito",
	   				  "One Name change in 1 fail in " + to_string(0));
	  for (int year : {1,2}) {
		  AssertEqual(person.GetFullName(year),"Max with unknown last name",
				  "One Name change in 1 fail in " + to_string(year));
	  }
	}
	{
			Person person;
		    person.ChangeFirstName(1, "Max");
		    person.GetFullName(0);
		    AssertEqual(person.GetFullName(0),"Incognito",
		   				  "double call One Name change in 1 fail in " + to_string(0));
		    person.GetFullName(1);
		   		    AssertEqual(person.GetFullName(1),"Max with unknown last name",
		   		   				  "double call One Name change in 1 fail in " + to_string(1));
		   		 person.GetFullName(2);
		   				    AssertEqual(person.GetFullName(2),"Max with unknown last name",
		   				   				  "double call One Name change in 1 fail in " + to_string(2));

		}

}

void TestChangeLastName(){
		{
			Person person;
		    person.ChangeLastName(1, "Volkov");
		    AssertEqual(person.GetFullName(0),"Incognito",
		   				  "One LastName change in 1 fail in " + to_string(0));
		  for (int year : {1,2}) {
			  AssertEqual(person.GetFullName(year),"Volkov with unknown first name",
					  "One LastName change in 1 fail in " + to_string(year));
		  }
		}

		{
				Person person;
			    person.ChangeLastName(1, "Volkov");
			    person.GetFullName(0);
			    AssertEqual(person.GetFullName(0),"Incognito",
			   				  "double call One LastName change in 1 fail in " + to_string(0));
			    person.GetFullName(1);
			   		    AssertEqual(person.GetFullName(1),"Volkov with unknown first name",
			   		   				  "double call LastOne Name change in 1 fail in " + to_string(1));
			   		 person.GetFullName(2);
			   				    AssertEqual(person.GetFullName(2),"Volkov with unknown first name",
			   				   				  "double call One LastName change in 1 fail in " + to_string(2));

			}


}

void TestChangeBothNames(){
	{Person person;
	    person.ChangeFirstName(1, "Max");
	    person.ChangeLastName(1, "Volkov");
	    AssertEqual(person.GetFullName(0),"Incognito",
	    					   				  "change in Name in 1 and LastName in 1 fail in " + to_string(0));
	    for (int year : {1,2}) {
	    					 					  AssertEqual(person.GetFullName(year),"Max Volkov",
	    					 							  "change in Name in 1 and LastName in 1 fail in  " + to_string(year));
	    					 				  }

		}
	{
				Person person;
					    person.ChangeFirstName(1, "Max");
					    person.ChangeLastName(3, "Volkov");
					    AssertEqual(person.GetFullName(0),"Incognito",
					   				  "change in Name in 1 and LastName in 3 fail in " + to_string(0));
					  for (int year : {1,2}) {
						  AssertEqual(person.GetFullName(year),"Max with unknown last name",
								  "change in Name in 1 and LastName in 3 fail in  " + to_string(year));
					  }
					  for (int year : {3,4}) {
					 					  AssertEqual(person.GetFullName(year),"Max Volkov",
					 							  "change in Name in 1 and LastName in 3 fail in  " + to_string(year));
					 				  }
	}
	{
					Person person;
						    person.ChangeFirstName(3, "Max");
						    person.ChangeLastName(1, "Volkov");
						    AssertEqual(person.GetFullName(0),"Incognito",
						   				  "change in Name in 3 and LastName in 1 fail in " + to_string(0));
						  for (int year : {1,2}) {
							  AssertEqual(person.GetFullName(year),"Volkov with unknown first name",
									  "change in Name in 3 and LastName in 1 fail in  " + to_string(year));
						  }
						  for (int year : {3,4}) {
						 					  AssertEqual(person.GetFullName(year),"Max Volkov",
						 							  "change in Name in 3 and LastName in 1 fail in  " + to_string(year));
						 				  }
		}


}

void TestChangeFirstNameMoreThanOneTime(){
	{
					Person person;
				    person.ChangeFirstName(1, "Max");
				    person.ChangeFirstName(3, "Maxim");
				   AssertEqual(person.GetFullName(0),"Incognito",
						   				  "change in Name in 1 and Name in 3 fail in " + to_string(0));
						  for (int year : {1,2}) {
							  AssertEqual(person.GetFullName(year),"Max with unknown last name",
									  "change in Name in 1 and Name in 3 fail in  " + to_string(year));
						  }
						  for (int year : {3,4}) {
						 					  AssertEqual(person.GetFullName(year),"Maxim with unknown last name",
						 							  "change in Name in 1 and Name in 3 fail in  " + to_string(year));
						 				  }
		}
	{
						Person person;
					    person.ChangeFirstName(1, "Max");
					    person.ChangeFirstName(5, "Maxim");
					    person.ChangeFirstName(3, "Maxon");

					   AssertEqual(person.GetFullName(0),"Incognito",
							   				  "change in Name in 1,3,5 fail in  " + to_string(0));
							  for (int year : {1,2}) {
								  AssertEqual(person.GetFullName(year),"Max with unknown last name",
										  "change in Name in 1,3,5 fail in  " + to_string(year));
							  }
							  for (int year : {3,4}) {
							 					  AssertEqual(person.GetFullName(year),"Maxon with unknown last name",
							 							  "change in Name in 1,3,5 fail in  " + to_string(year));
							 				  }
							  for (int year : {5,6}) {
							  							 					  AssertEqual(person.GetFullName(year),"Maxim with unknown last name",
							  							 							  "change in Name in 1,3,5 fail in  " + to_string(year));
							  							 				  }
			}
}

void TestChangeLastNameMoreThanOneTime(){
	{
					Person person;
				    person.ChangeLastName(1, "Max");
				    person.ChangeLastName(3, "Maxim");
				   AssertEqual(person.GetFullName(0),"Incognito",
						   				  "change in LastName in 1 and Name in 3 fail in " + to_string(0));
						  for (int year : {1,2}) {
							  AssertEqual(person.GetFullName(year),"Max with unknown first name",
									  "change in LastName in 1 and Name in 3 fail in  " + to_string(year));
						  }
						  for (int year : {3,4}) {
						 					  AssertEqual(person.GetFullName(year),"Maxim with unknown first name",
						 							  "change in LastName in 1 and Name in 3 fail in  " + to_string(year));
						 				  }
		}
	{
						Person person;
					    person.ChangeLastName(1, "Max");
					    person.ChangeLastName(5, "Maxim");
					    person.ChangeLastName(3, "Maxon");

					   AssertEqual(person.GetFullName(0),"Incognito",
							   				  "change in LastName in 1,3,5 fail in  " + to_string(0));
							  for (int year : {1,2}) {
								  AssertEqual(person.GetFullName(year),"Max with unknown first name",
										  "change in LastName in 1,3,5 fail in  " + to_string(year));
							  }
							  for (int year : {3,4}) {
							 					  AssertEqual(person.GetFullName(year),"Maxon with unknown first name",
							 							  "change in LastName in 1,3,5 fail in  " + to_string(year));
							 				  }
							  for (int year : {5,6}) {
							  							 					  AssertEqual(person.GetFullName(year),"Maxim with unknown first name",
							  							 							  "change in LastName in 1,3,5 fail in  " + to_string(year));
							  							 				  }
			}
}

void TestChangeBothNamesMoreThanOneTime(){
	{
		Person person;
		person.ChangeFirstName(1,"Max");
		person.ChangeLastName(2,"Volkov");
		person.ChangeFirstName(4,"Maxim");
		for (int year : {2,3}) {
	   AssertEqual(person.GetFullName(year),"Max Volkov",
	   "change in Name in 1,4; Last in 2 fail in  " + to_string(year));
		  }
		for (int year : {4,5}) {
			   AssertEqual(person.GetFullName(year),"Maxim Volkov",
			   "change in Name in 1,4; Last in 2 fail in  " + to_string(year));
				  }
	}
	{
			Person person;
			person.ChangeLastName(1,"Volkov");
			person.ChangeFirstName(2,"Max");
			person.ChangeLastName(4,"Volk");
			for (int year : {2,3}) {
		   AssertEqual(person.GetFullName(year),"Max Volkov",
		   "change in Last in 1,4; Name in 2 fail in  " + to_string(year));
			  }
			for (int year : {4,5}) {
				   AssertEqual(person.GetFullName(year),"Max Volk",
				   "change in Last in 1,4; Name in 2 fail in  " + to_string(year));
					  }
		}
	{
			Person person;
			person.ChangeFirstName(1,"Max");
			person.ChangeLastName(11,"Volkolak");
			person.ChangeFirstName(5,"Maxim");
			person.ChangeLastName(7,"Volk");
			person.ChangeLastName(3,"Volkov");
			person.ChangeFirstName(9,"Maxon");



			for (int year : {3,4}) {
		   AssertEqual(person.GetFullName(year),"Max Volkov",
		   "change in Name in 1,5,9 ; Last in 3,7,11 fail in  " + to_string(year));
			  }
			for (int year : {5,6}) {
					   AssertEqual(person.GetFullName(year),"Maxim Volkov",
					   "change in Name in 1,5,9 ; Last in 3,7,11 fail in  " + to_string(year));
						  }
			for (int year : {7,8}) {
					   AssertEqual(person.GetFullName(year),"Maxim Volk",
					   "change in Name in 1,5,9 ; Last in 3,7,11 fail in  " + to_string(year));
						  }
			for (int year : {9,10}) {
					   AssertEqual(person.GetFullName(year),"Maxon Volk",
					   "change in Name in 1,5,9 ; Last in 3,7,11 fail in  " + to_string(year));
						  }
			for (int year : {11,12}) {
					   AssertEqual(person.GetFullName(year),"Maxon Volkolak",
					   "change in Name in 1,5,9 ; Last in 3,7,11 fail in  " + to_string(year));
						  }
		}
}
void TestAll(){
	TestRunner runner;
	runner.RunTest(TestEmpty, "TestEmpty");
	runner.RunTest(TestChangeFirstName, "TestChangeFirstName");
	runner.RunTest(TestChangeLastName, "TestChangeLastName");
	runner.RunTest(TestChangeBothNames, "TestChangeBothNames");
	runner.RunTest(TestChangeFirstNameMoreThanOneTime, "TestChangeFirstNameMoreThanOneTime");
	runner.RunTest(TestChangeLastNameMoreThanOneTime, "TestChangeLastNameMoreThanOneTime");
	runner.RunTest(TestChangeBothNamesMoreThanOneTime, "TestChangeBothNamesMoreThanOneTime");
}
int main() {

	TestAll();

	Person person;

	  person.ChangeFirstName(1965, "Polina");
	  person.ChangeLastName(1967, "Sergeeva");
	  for (int year : {1900, 1965, 1990}) {
	    cout << person.GetFullName(year) << endl;
	  }

	  person.ChangeFirstName(1970, "Appolinaria");
	  for (int year : {1969, 1970}) {
	    cout << person.GetFullName(year) << endl;
	  }

	  person.ChangeLastName(1968, "Volkova");
	  for (int year : {1969, 1970}) {
	    cout << person.GetFullName(year) << endl;
	  }

  // добавьте сюда свои тесты
  return 0;
}*/
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};




void TestEmpty(){
	{
		Person empty;
		for(int year : {0, 1}){
		AssertEqual(empty.GetFullName(year),"Incognito","empty in "+to_string(year));
		}

	}
	{
						Person empty;
						empty.GetFullName(1);
						AssertEqual(empty.GetFullName(1),"Incognito","double call empty in "+to_string(1));
				}
}

void TestChangeFirstName(){

	{
		Person person;
	    person.ChangeFirstName(1, "Max");
	    AssertEqual(person.GetFullName(0),"Incognito",
	   				  "One Name change in 1 fail in " + to_string(0));
	  for (int year : {1,2}) {
		  AssertEqual(person.GetFullName(year),"Max with unknown last name",
				  "One Name change in 1 fail in " + to_string(year));
	  }
	}
	{
			Person person;
		    person.ChangeFirstName(1, "Max");
		    person.GetFullName(0);
		    AssertEqual(person.GetFullName(0),"Incognito",
		   				  "double call One Name change in 1 fail in " + to_string(0));
		    person.GetFullName(1);
		   		    AssertEqual(person.GetFullName(1),"Max with unknown last name",
		   		   				  "double call One Name change in 1 fail in " + to_string(1));
		   		 person.GetFullName(2);
		   				    AssertEqual(person.GetFullName(2),"Max with unknown last name",
		   				   				  "double call One Name change in 1 fail in " + to_string(2));

		}

}

void TestChangeLastName(){
		{
			Person person;
		    person.ChangeLastName(1, "Volkov");
		    AssertEqual(person.GetFullName(0),"Incognito",
		   				  "One LastName change in 1 fail in " + to_string(0));
		  for (int year : {1,2}) {
			  AssertEqual(person.GetFullName(year),"Volkov with unknown first name",
					  "One LastName change in 1 fail in " + to_string(year));
		  }
		}

		{
				Person person;
			    person.ChangeLastName(1, "Volkov");
			    person.GetFullName(0);
			    AssertEqual(person.GetFullName(0),"Incognito",
			   				  "double call One LastName change in 1 fail in " + to_string(0));
			    person.GetFullName(1);
			   		    AssertEqual(person.GetFullName(1),"Volkov with unknown first name",
			   		   				  "double call LastOne Name change in 1 fail in " + to_string(1));
			   		 person.GetFullName(2);
			   				    AssertEqual(person.GetFullName(2),"Volkov with unknown first name",
			   				   				  "double call One LastName change in 1 fail in " + to_string(2));

			}


}

void TestChangeBothNames(){
	{Person person;
	    person.ChangeFirstName(1, "Max");
	    person.ChangeLastName(1, "Volkov");
	    AssertEqual(person.GetFullName(0),"Incognito",
	    					   				  "change in Name in 1 and LastName in 1 fail in " + to_string(0));
	    for (int year : {1,2}) {
	    					 					  AssertEqual(person.GetFullName(year),"Max Volkov",
	    					 							  "change in Name in 1 and LastName in 1 fail in  " + to_string(year));
	    					 				  }

		}
	{
				Person person;
					    person.ChangeFirstName(1, "Max");
					    person.ChangeLastName(3, "Volkov");
					    AssertEqual(person.GetFullName(0),"Incognito",
					   				  "change in Name in 1 and LastName in 3 fail in " + to_string(0));
					  for (int year : {1,2}) {
						  AssertEqual(person.GetFullName(year),"Max with unknown last name",
								  "change in Name in 1 and LastName in 3 fail in  " + to_string(year));
					  }
					  for (int year : {3,4}) {
					 					  AssertEqual(person.GetFullName(year),"Max Volkov",
					 							  "change in Name in 1 and LastName in 3 fail in  " + to_string(year));
					 				  }
	}
	{
					Person person;
						    person.ChangeFirstName(3, "Max");
						    person.ChangeLastName(1, "Volkov");
						    AssertEqual(person.GetFullName(0),"Incognito",
						   				  "change in Name in 3 and LastName in 1 fail in " + to_string(0));
						  for (int year : {1,2}) {
							  AssertEqual(person.GetFullName(year),"Volkov with unknown first name",
									  "change in Name in 3 and LastName in 1 fail in  " + to_string(year));
						  }
						  for (int year : {3,4}) {
						 					  AssertEqual(person.GetFullName(year),"Max Volkov",
						 							  "change in Name in 3 and LastName in 1 fail in  " + to_string(year));
						 				  }
		}


}

void TestChangeFirstNameMoreThanOneTime(){
	{
					Person person;
				    person.ChangeFirstName(1, "Max");
				    person.ChangeFirstName(3, "Maxim");
				   AssertEqual(person.GetFullName(0),"Incognito",
						   				  "change in Name in 1 and Name in 3 fail in " + to_string(0));
						  for (int year : {1,2}) {
							  AssertEqual(person.GetFullName(year),"Max with unknown last name",
									  "change in Name in 1 and Name in 3 fail in  " + to_string(year));
						  }
						  for (int year : {3,4}) {
						 					  AssertEqual(person.GetFullName(year),"Maxim with unknown last name",
						 							  "change in Name in 1 and Name in 3 fail in  " + to_string(year));
						 				  }
		}
	{
						Person person;
					    person.ChangeFirstName(1, "Max");
					    person.ChangeFirstName(5, "Maxim");
					    person.ChangeFirstName(3, "Maxon");

					   AssertEqual(person.GetFullName(0),"Incognito",
							   				  "change in Name in 1,3,5 fail in  " + to_string(0));
							  for (int year : {1,2}) {
								  AssertEqual(person.GetFullName(year),"Max with unknown last name",
										  "change in Name in 1,3,5 fail in  " + to_string(year));
							  }
							  for (int year : {3,4}) {
							 					  AssertEqual(person.GetFullName(year),"Maxon with unknown last name",
							 							  "change in Name in 1,3,5 fail in  " + to_string(year));
							 				  }
							  for (int year : {5,6}) {
							  							 					  AssertEqual(person.GetFullName(year),"Maxim with unknown last name",
							  							 							  "change in Name in 1,3,5 fail in  " + to_string(year));
							  							 				  }
			}
}

void TestChangeLastNameMoreThanOneTime(){
	{
					Person person;
				    person.ChangeLastName(1, "Max");
				    person.ChangeLastName(3, "Maxim");
				   AssertEqual(person.GetFullName(0),"Incognito",
						   				  "change in LastName in 1 and Name in 3 fail in " + to_string(0));
						  for (int year : {1,2}) {
							  AssertEqual(person.GetFullName(year),"Max with unknown first name",
									  "change in LastName in 1 and Name in 3 fail in  " + to_string(year));
						  }
						  for (int year : {3,4}) {
						 					  AssertEqual(person.GetFullName(year),"Maxim with unknown first name",
						 							  "change in LastName in 1 and Name in 3 fail in  " + to_string(year));
						 				  }
		}
	{
						Person person;
					    person.ChangeLastName(1, "Max");
					    person.ChangeLastName(5, "Maxim");
					    person.ChangeLastName(3, "Maxon");

					   AssertEqual(person.GetFullName(0),"Incognito",
							   				  "change in LastName in 1,3,5 fail in  " + to_string(0));
							  for (int year : {1,2}) {
								  AssertEqual(person.GetFullName(year),"Max with unknown first name",
										  "change in LastName in 1,3,5 fail in  " + to_string(year));
							  }
							  for (int year : {3,4}) {
							 					  AssertEqual(person.GetFullName(year),"Maxon with unknown first name",
							 							  "change in LastName in 1,3,5 fail in  " + to_string(year));
							 				  }
							  for (int year : {5,6}) {
							  							 					  AssertEqual(person.GetFullName(year),"Maxim with unknown first name",
							  							 							  "change in LastName in 1,3,5 fail in  " + to_string(year));
							  							 				  }
			}
}

void TestChangeBothNamesMoreThanOneTime(){
	{
		Person person;
		person.ChangeFirstName(1,"Max");
		person.ChangeLastName(2,"Volkov");
		person.ChangeFirstName(4,"Maxim");
		for (int year : {2,3}) {
	   AssertEqual(person.GetFullName(year),"Max Volkov",
	   "change in Name in 1,4; Last in 2 fail in  " + to_string(year));
		  }
		for (int year : {4,5}) {
			   AssertEqual(person.GetFullName(year),"Maxim Volkov",
			   "change in Name in 1,4; Last in 2 fail in  " + to_string(year));
				  }
	}
	{
			Person person;
			person.ChangeLastName(1,"Volkov");
			person.ChangeFirstName(2,"Max");
			person.ChangeLastName(4,"Volk");
			for (int year : {2,3}) {
		   AssertEqual(person.GetFullName(year),"Max Volkov",
		   "change in Last in 1,4; Name in 2 fail in  " + to_string(year));
			  }
			for (int year : {4,5}) {
				   AssertEqual(person.GetFullName(year),"Max Volk",
				   "change in Last in 1,4; Name in 2 fail in  " + to_string(year));
					  }
		}
	{
			Person person;
			person.ChangeFirstName(1,"Max");
			person.ChangeLastName(11,"Volkolak");
			person.ChangeFirstName(5,"Maxim");
			person.ChangeLastName(7,"Volk");
			person.ChangeLastName(3,"Volkov");
			person.ChangeFirstName(9,"Maxon");



			for (int year : {3,4}) {
		   AssertEqual(person.GetFullName(year),"Max Volkov",
		   "change in Name in 1,5,9 ; Last in 3,7,11 fail in  " + to_string(year));
			  }
			for (int year : {5,6}) {
					   AssertEqual(person.GetFullName(year),"Maxim Volkov",
					   "change in Name in 1,5,9 ; Last in 3,7,11 fail in  " + to_string(year));
						  }
			for (int year : {7,8}) {
					   AssertEqual(person.GetFullName(year),"Maxim Volk",
					   "change in Name in 1,5,9 ; Last in 3,7,11 fail in  " + to_string(year));
						  }
			for (int year : {9,10}) {
					   AssertEqual(person.GetFullName(year),"Maxon Volk",
					   "change in Name in 1,5,9 ; Last in 3,7,11 fail in  " + to_string(year));
						  }
			for (int year : {11,12}) {
					   AssertEqual(person.GetFullName(year),"Maxon Volkolak",
					   "change in Name in 1,5,9 ; Last in 3,7,11 fail in  " + to_string(year));
						  }
		}
}
void TestAll(){
	TestRunner runner;
	runner.RunTest(TestEmpty, "TestEmpty");
	runner.RunTest(TestChangeFirstName, "TestChangeFirstName");
	runner.RunTest(TestChangeLastName, "TestChangeLastName");
	runner.RunTest(TestChangeBothNames, "TestChangeBothNames");
	runner.RunTest(TestChangeFirstNameMoreThanOneTime, "TestChangeFirstNameMoreThanOneTime");
	runner.RunTest(TestChangeLastNameMoreThanOneTime, "TestChangeLastNameMoreThanOneTime");
	runner.RunTest(TestChangeBothNamesMoreThanOneTime, "TestChangeBothNamesMoreThanOneTime");
}
int main() {

	TestAll();


  return 0;
}

