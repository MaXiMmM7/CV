//============================================================================
// Name        : realizclas.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "phone_number.h"
#include "test_runner.h"
#include <string>
#include <sstream>
#include <exception>
using namespace std;

  /* Принимает строку в формате +XXX-YYY-ZZZZZZ
     Часть от '+' до первого '-' - это код страны.
     Часть между первым и вторым символами '-' - код города
     Всё, что идёт после второго символа '-' - местный номер.
     Код страны, код города и местный номер не должны быть пустыми.
     Если строка не соответствует этому формату, нужно выбросить исключение invalid_argument. Проверять, что номер содержит только цифры, не нужно.

     Примеры:
     * +7-495-111-22-33
     * +7-495-1112233
     * +323-22-460002
     * +1-2-coursera-cpp
     * 1-2-333 - некорректный номер - не начинается на '+'
     * +7-1233 - некорректный номер - есть только код страны и города
  */
  PhoneNumber::PhoneNumber(const string &international_number){
	  stringstream stream;
	  stream << international_number;
	  string country,city,local;
	  if(stream.peek()!='+'){
		  throw invalid_argument("hello");
	  }
	  stream.ignore(1);
	  getline(stream,country,'-');
	  getline(stream,city,'-');
	  stream >> local;
	  if(stream){
	       country_code_=country;
	       city_code_=city;
	       local_number_=local;
	  }
	  else{
		  throw invalid_argument("hello");
	  }
  }

  string PhoneNumber::GetCountryCode() const{
	  return country_code_;
  }
  string PhoneNumber::GetCityCode() const {
  	  return city_code_;
    }
  string PhoneNumber::GetLocalNumber() const {
  	  return local_number_;
    }
  string PhoneNumber::GetInternationalNumber() const{
	  return "+"+country_code_+"-"+city_code_+"-"+local_number_;
  }

/*
  void Test(){
	  {
		  PhoneNumber num("+7-937-3");
		  AssertEqual(num.GetCountryCode(),"7", "country code");
		  AssertEqual(num.GetCityCode(),"937", "city code");
		  AssertEqual(num.GetLocalNumber(),"3", "localcode");
		  AssertEqual(num.GetInternationalNumber(),"+7-937-3", "full");
	  }
	  {
	 		  PhoneNumber num("+1-2");

	 	  }
  }
  void TestAll(){
	  TestRunner runner;
	  runner.RunTest(Test, "Test");
  }
  int main(){
	  TestAll();
	  return 0;
  }
*/
