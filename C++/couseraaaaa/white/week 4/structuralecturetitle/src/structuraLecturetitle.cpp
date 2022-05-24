//============================================================================
// Name        : structuraLecturetitle.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
using namespace std;


struct Specialization{
	string s;
	explicit Specialization(const string& a){
		s=a;
	}
};
struct Course{
	string s;
		explicit Course(const string& a){
			s=a;
		}
};
struct Week{
			string s;
				explicit Week(const string& a){
					s=a;
				}
};

struct LectureTitle {
  string specialization;
  string course;
  string week;

  LectureTitle(Specialization s,Course c, Week w){
	  specialization=s.s;
	  course=c.s;
	  week=w.s;
  }
};

int main() {

	return 0;
}
