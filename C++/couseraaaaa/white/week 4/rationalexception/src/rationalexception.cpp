//============================================================================
// Name        : rationalexception.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <exception>
using namespace std;

int Evklid(int a, int b) {
  if (b == 0) {
    return a;
  } else {
    return Evklid(b, a % b);
  }
}

class Rational {
public:
  Rational(){
	  p=0;
	  q=1;
  }
  Rational(int numerator, int denominator){
	  if(denominator==0){
		  throw invalid_argument("Incorrect argument");
	  }
	  int d=Evklid(numerator,denominator);
	  p=numerator/d;
	  q=denominator/d;
	  if(q<0){
		  p=-p;
		  q=-q;
	  }

  }

  int Numerator() const{
	  return p;
  }
  int Denominator() const{
	  return q;
  }
private:
  int p;
  int q;

};

Rational operator /(const Rational& a,const Rational& b){
	 if(b.Numerator()==0){
			  throw domain_error("Error");
		  }
	return Rational(a.Numerator()*b.Denominator(),a.Denominator()*b.Numerator());
}

int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}
