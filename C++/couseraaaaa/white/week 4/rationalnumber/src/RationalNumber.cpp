//============================================================================
// Name        : RationalNumber.cpp
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

int main() {
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    cout << "OK" << endl;
    return 0;
}
