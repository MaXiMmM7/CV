//============================================================================
// Name        : imenaifamilii4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "test_runner.h"
using namespace std;



/////////////////////////////
#include <map>
#include <string>

// Возвращает пустую строку, если имя неизвестно
string FindNameByYear(const map<int, string>& names, int year) {
  auto iter_after = names.upper_bound(year);
  string name;
  if (iter_after != names.begin()) {
    name = (--iter_after)->second;
  }
  return name;
}

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    last_names[year] = last_name;
  }
  string GetFullName(int year) {
    const string first_name = FindNameByYear(first_names, year);
    const string last_name = FindNameByYear(last_names, year);
    if (first_name.empty() && last_name.empty()) {
      return "Incognito";
    } else if (first_name.empty()) {
      return last_name + " with unknown first name";
    } else if (last_name.empty()) {
      return first_name + " with unknown last name";
    } else {
      return first_name + " " + last_name;
    }
  }
private:
  map<int, string> first_names;
  map<int, string> last_names;
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
}

