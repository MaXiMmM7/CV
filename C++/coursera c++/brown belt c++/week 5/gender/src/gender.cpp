// Это пример функции, его не нужно отправлять вместе с функцией PrintStats
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
/*
enum class Gender {
  FEMALE,
  MALE
};

struct Person {
  int age;  // возраст
  Gender gender;  // пол
  bool is_employed;  // имеет ли работу
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
      begin(range_copy), middle, end(range_copy),
      [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
      }
  );
  return middle->age;
}
*/
void PrintStats(vector<Person> persons){
	//Median Age
	cout << "Median age = " << ComputeMedianAge(persons.begin(),persons.end()) << endl;

	//Median age for females = 40
	auto It_gender=partition(persons.begin(),persons.end(),[](Person& p){
		return p.gender==Gender::FEMALE;
	});
	cout <<"Median age for females = " << ComputeMedianAge(persons.begin(),It_gender) << endl;
	//Median age for males = 55
	cout <<"Median age for males = " << ComputeMedianAge(It_gender,persons.end()) << endl;
	//Median age for employed females = 40
	auto It_employe_fem=partition(persons.begin(),It_gender,[](Person& p){
		return p.is_employed==true;
	});
	cout <<"Median age for employed females = " << ComputeMedianAge(persons.begin(),It_employe_fem) << endl;
	//Median age for unemployed females = 80
	cout <<"Median age for unemployed females =  " << ComputeMedianAge(It_employe_fem,It_gender) << endl;
	//Median age for employed males = 55
	auto It_employe_m=partition(It_gender,persons.end(),[](Person& p){
			return p.is_employed==true;
		});
		cout <<"Median age for employed males = " << ComputeMedianAge(It_gender,It_employe_m) << endl;

	//Median age for unemployed males = 78
		cout <<"Median age for unemployed males =  " << ComputeMedianAge(It_employe_m,persons.end()) << endl;
}

int main() {
  vector<Person> persons = {
      {31, Gender::MALE, false},
      {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},
      {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false},
      {78, Gender::MALE, false},
      {10, Gender::FEMALE, false},
      {55, Gender::MALE, true},
  };
  PrintStats(persons);
  return 0;
}
