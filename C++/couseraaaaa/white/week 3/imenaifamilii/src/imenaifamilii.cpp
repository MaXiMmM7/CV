//============================================================================
// Name        : imenaifamilii.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
using namespace std;

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
	  for(const auto& x :years){
		  if((x.first>year)&&helper==0){
			  return "Incognito";
		  }
		  if(x.first>year){
			  return draw(years[helper].FirstName,years[helper].LastName);
		  }
		  helper=x.first;
	  }
	  return draw(years[helper].FirstName,years[helper].LastName);

  }
private:
  map<int,omg> years;
};


int main(){
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
	return 0;
}
