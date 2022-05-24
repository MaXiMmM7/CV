//============================================================================
// Name        : spisokstudentov.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Name{
	string name;
	explicit Name(const string& s){
		name=s;
	}
};

struct Surname{
	string surname;
	explicit Surname(const string& s){
		surname=s;
	}
};

struct Day{
	int day;
	explicit Day(const int& val){
		day=val;
	}
};

struct Month{
	int month;
	explicit Month(const int& val){
		month=val;
	}
};

struct Year{
	int year;
	explicit Year(const int& val){
		year=val;
	}
};

struct Student {
	string name;
	string surname;
	int day;
	int month;
	int year;
Student (Name n,Surname s,Day d,Month m,Year y){
		name=n.name;
		surname=s.surname;
		day=d.day;
		month=m.month;
		year=y.year;
	}
/*Student(){
	name="0";
	surname="0";
	day=0;
	month=0;
	year=0;
}*/
};

void Helper(const vector<Student>& students,const string& s,const int& number){
	if((number>0)&&(number<=(int)students.size())){
		if(s=="name"){
			cout << students[number-1].name<<" "<<students[number-1].surname<< endl;
			return;
		}
		if(s=="date"){
		    cout <<  students[number-1].day << "."<<students[number-1].month<<"."<<students[number-1].year<< endl;
		    return;
		}
	}
	cout << "bad request" << endl;
}

int main() {
	int N;
	cin>> N;
vector<Student> students;
for(int i=0; i<N;i++){
	string n,s;
	int d,m,y;
	cin >> n >> s >> d >> m>> y;
	students.push_back(Student(Name(n),Surname(s),Day(d),Month(m),Year(y)));
}
int M;
cin >> M;
string s;
int k;
for(int i=0;i<M;i++){
	cin >> s >> k;
	 Helper(students,s,k);
}
	return 0;
}
