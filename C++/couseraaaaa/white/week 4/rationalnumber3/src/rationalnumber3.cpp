//============================================================================
// Name        : rationalnumber3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================



#include <iostream>
#include <cmath>
using namespace std;

int Evklid( int a, int b){
	if(a>b){
		int n=a;
		a=b;
		b=n;
	}
	int helper,n;
	while(b%a!=0){
		n=b/a;
		helper=a;
		a=b-n*a;
		b=helper;

	}
return a;
}

class Rational {
public:
    Rational() {
       p=0;
       q=1;
    }

    Rational(int numerator, int denominator) {
    	p=numerator;
    	q=denominator;
    	if((numerator!=0)&&(denominator!=0)){
        p=p/Evklid(abs(numerator),abs(denominator));
        q=q/Evklid(abs(numerator),abs(denominator));
    	}
    	if(p*q<0){
    		p=-abs(p);
    		q=abs(q);
    	}
    	else{
    		p=abs(p);
    		q=abs(q);
    	}
    	if((p==0)&&(q!=1)){
    		q=1;
    	}
    }

    int Numerator() const {
        return p;
    }

    int Denominator() const {
        return q;
    }

private:
    int p;
    int q;
};


Rational operator+(const Rational& a,const Rational& b){
	int p=a.Numerator()*b.Denominator()+b.Numerator()*a.Denominator();
	int q=b.Denominator()*a.Denominator();
	return Rational(p,q);
}

Rational operator-(const Rational& a,const Rational& b){
	int p=a.Numerator()*b.Denominator()-b.Numerator()*a.Denominator();
	int q=b.Denominator()*a.Denominator();
	return Rational(p,q);
}

bool operator ==(const Rational& a,const Rational& b){
return a.Numerator()*b.Denominator()==b.Numerator()*a.Denominator();
}

Rational operator *(const Rational& a,const Rational& b){
	return Rational(a.Numerator()*b.Numerator(),a.Denominator()*b.Denominator());
}

Rational operator /(const Rational& a,const Rational& b){
	return Rational(a.Numerator()*b.Denominator(),a.Denominator()*b.Numerator());
}


int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}
