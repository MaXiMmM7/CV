//============================================================================
// Name        : Calculatordrobey.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <exception>
#include <istream>
using namespace std;

// один из способов вычисления наибольшего общего делителя (НОД) — рекурсивный:
// вместо цикла функция будет вызывать себя же, но с другими аргументами
int GreatestCommonDivisor(int a, int b) {
  if (b == 0) {
    return a;
  } else {
    return GreatestCommonDivisor(b, a % b);
  }
}

class Rational {
public:
  Rational() {  // дробь по умолчанию — 0/1
    numerator = 0;
    denominator = 1;
  }
  Rational(int new_numerator, int new_denominator) {
	  if(new_denominator==0){
	 		  throw invalid_argument("Invalid argument");
	 	  }
    const int gcd = GreatestCommonDivisor(new_numerator, new_denominator);
    // сократим дробь, разделив числитель и знаменатель на их НОД
    numerator = new_numerator / gcd;
    denominator = new_denominator / gcd;
    // знаменатель должен быть положительным
    if (denominator < 0) {
      denominator = -denominator;
      numerator = -numerator;
    }
  }

  int Numerator() const {
      return numerator;
    }

    int Denominator() const {
      return denominator;
    }

  private:
    int numerator;
    int denominator;
  };

  // поскольку дроби сокращены, достаточно сравнить числители и знаменатели
  bool operator == (const Rational& lhs, const Rational& rhs) {
    return lhs.Numerator() == rhs.Numerator() &&
        lhs.Denominator() == rhs.Denominator();
  }

  // используем обычную формулу сложения дробей, основанную на приведении слагаемых к общему знаменателю
  Rational operator + (const Rational& lhs, const Rational& rhs) {
    return {
        lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
        lhs.Denominator() * rhs.Denominator()
    };
  }

  Rational operator - (const Rational& lhs, const Rational& rhs) {
    return {
        lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
        lhs.Denominator() * rhs.Denominator()
    };
  }

  Rational operator * (const Rational& lhs, const Rational& rhs) {
    return {
        lhs.Numerator() * rhs.Numerator(),
        lhs.Denominator() * rhs.Denominator()
    };
  }

  // деление равносильно умножению на обратную («перевёрнутую») дробь
  Rational operator / (const Rational& lhs, const Rational& rhs) {
	  if(rhs.Numerator()==0){
	 			  throw domain_error("Division by zero");
	 		  }
    return lhs * Rational(rhs.Denominator(), rhs.Numerator());
  }

  istream& operator >> (istream& is, Rational& r) {
    int n, d;
    char c;

    if (is) {
        is >> n >> c >> d;
        if (is && c == '/') {
            r = Rational(n, d);
        }
       /* else{
  	 		  throw invalid_argument("Invalid argument");
  	 	  }*/
        }


    return is;
  }

  ostream& operator << (ostream& os, const Rational& r) {
    return os << r.Numerator() << '/' << r.Denominator();
  }


  bool operator < (const Rational& lhs, const Rational& rhs) {
    return (lhs - rhs).Numerator() < 0;
  }




int main() {
	Rational r1,r2;
	char c;
	try{
	cin >> r1 >>c >>r2;
	if (c=='/'){
		cout << r1/r2;
	}
	else if(c=='*'){
		cout << r1*r2;
	}
	else if(c=='-'){
		cout << r1 - r2;
	}
	else if(c=='+'){
		cout << r1+r2;
	}
	}catch (exception& ex){
		cout << ex.what();
	}

	return 0;
}
