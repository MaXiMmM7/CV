//============================================================================
// Name        : imenaifamilii3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//=====


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
	int blockname=0;
	int blocklast=0;
};

string draw( map<int,omg> years,  int helper){
	if((years[helper].FirstName!="0")&&(years[helper].LastName!="0")){
		return years[helper].FirstName + " " + years[helper].LastName;
	}
	else if(years[helper].FirstName!="0"){
		return years[helper].FirstName + " with unknown last name";
	}
	return years[helper].LastName + " with unknown first name";
}

string drawWithHistory(const vector<string>& names,const vector<string>& lastnames ){

	int end1=names.size()-1;
	int end2=lastnames.size()-1;


     string helperName,helperLast;
	if((names[end1]!="0")&&(lastnames[end2]!="0")){


		for(int i=end1-1;i>=1;i--){
			if(i==(end1-1)){
				helperName+="(";
			}
			if(names[i]!="0"){
			helperName+=names[i];
			if(i!=1){
				helperName+=", ";
			}}
			if(i==1){
							helperName+=")";
						}
		}
		for(int i=end2-1;i>=1;i--){
			if(i==(end2-1)){
							helperLast+="(";
						}
			if(lastnames[i]!="0"){
				helperLast+=lastnames[i];
				if(i!=1){
					helperLast+=", ";
				}}
			if(i==1){
										helperLast+=")";
									}
			}
		if((!helperName.empty())&&(!helperLast.empty())){
					return names[end1] + " "+ helperName + " " + lastnames[end2] +" "+ helperLast ;
		}
				if((helperName.empty())&&(!helperLast.empty())){
							return names[end1] + " " + lastnames[end2] +" "+ helperLast ;
				}
			if((!helperName.empty())&&(helperLast.empty())){
						return names[end1] + " "+ helperName + " " + lastnames[end2]  ;
			}
			if((helperName.empty())&&(helperLast.empty())){
						return names[end1] + " "+ lastnames[end2] ;
			}

	}
		else if(names[end1]!="0"){


			for(int i=end1-1;i>=1;i--){
				if(i==(end1-1)){
								helperName+="(";
							}
				if(names[i]!="0"){
						helperName+=names[i];
						if(i!=1){
							helperName+=", ";
						}}
				if(i==1){
											helperName+=")";
										}
					}


			if(!(helperName.empty())){
			return names[end1] + " "+ helperName  + " with unknown last name";
			}
			else{
				return names[end1]  + " with unknown last name";
			}


		}
	for(int i=end2-1;i>=1;i--){
		if(lastnames[i]!="0"){
			if(i==(end2-1)){
										helperLast+="(";
									}
					helperLast+=lastnames[i];
					if(i!=1){
						helperLast+=", ";
					}}
		if(i==1){
												helperLast+=")";
											}
				}

	if(!(helperLast.empty())){
			return lastnames[end2] +" "+ helperLast +  " with unknown first name";
	}
		return lastnames[end2] + " with unknown first name";

}

class Person {
public:
	Person(const string& name,const string& lastname,const int& year){
		years[year].FirstName=name;
		years[year].LastName=lastname;
		birth=year;
	}
  void ChangeFirstName(int year, const string& first_name) {
	  if(year<birth){
		  return;
	  }
  years[year].FirstName=first_name;
  years[year].blockname=1;
  string helper="0";
  for(auto& x: years){
	  if(x.first>year){
		  if(((x.second.FirstName=="0")||(x.second.FirstName==helper))&&(x.second.blockname==0)){
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
	  if(year<birth){
			  return;
		  }
	  years[year].LastName=last_name;
	  years[year].blocklast=1;
	    string helper="0";
	    for(auto& x: years){
	  	  if(x.first>year){
	  		  if(((x.second.LastName=="0")||(x.second.LastName==helper))&&(x.second.blocklast==0)){
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
  string GetFullName(int year) const{
	  if(year<birth){
			  return "No person";
		  }
	  int helper=0;
	  for(const auto& x :years){
		  if((x.first>year)&&helper==0){
			  return "Incognito";
		  }
		  if(x.first>year){
			  return draw(years,helper);
		  }
		  helper=x.first;
	  }
	  return draw(years,helper);

  }
  string GetFullNameWithHistory(int year) const{
	  if(year<birth){
				  return "No person";
			  }
	 string HelpFirst="0";
	 string HelpSecond="0";
	 vector<string> Names,LastNames;
	 Names.push_back("0");
	 LastNames.push_back("0");

	 int helper=0;

	 	  for(const auto& x :years){
	 		  if((x.first>year)&&helper==0){
	 			  return "Incognito";
	 		  }
	 		  if(x.first>year){

	 			  return drawWithHistory(Names,LastNames);
	 		  }
	 		  if(x.second.FirstName!=HelpFirst){
	 			  Names.push_back(x.second.FirstName);
	 		  }
	 		  if(x.second.LastName!=HelpSecond){
	 			  LastNames.push_back(x.second.LastName);
	 		  }
	 		  helper=year;
	 		  HelpFirst=x.second.FirstName;
	 		  HelpSecond=x.second.LastName;

	 	  }
	 	  return drawWithHistory(Names,LastNames);

  }
private:
  map<int,omg> years;
  int birth;
};


int main(){
	 Person person("Polina", "Sergeeva", 1960);
	  for (int year : {1959, 1960}) {
	    cout << person.GetFullNameWithHistory(year) << endl;
	  }

	  person.ChangeFirstName(1965, "Appolinaria");
	  person.ChangeLastName(1967, "Ivanova");
	  for (int year : {1965, 1967}) {
	    cout << person.GetFullNameWithHistory(year) << endl;
	  }

	  return 0;
}
