//============================================================================
// Name        : rationalnumber4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <sstream>
#include <cmath>
#include <typeinfo>
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

    void Rebuild(const int& a,const int& b){
    	/*if(b==0){
    		p=Rational().p;
    		q=Rational().q;
    		return;
    	}*/
    	p=Rational(a,b).p;
    	q=Rational(a,b).q;
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

ostream& operator << (ostream& output,const Rational& num){
	output << num.Numerator() << "/" << num.Denominator();
	return output;
}

/*istream& operator >>(istream& stream, Rational& num){
	if(!stream.eof()){

	int a,b;
	cout << a << " " << b << endl;
	char c;
	stream >> a >> c >> b;
	if((c=='/')){
	num.Rebuild(a,b);
	}
	}
	return stream;
}*/

istream& operator >>(istream& stream, Rational& num){
	int a;
	if(stream >>a){
   // stream >> num.Numerator().p;
	int b;
	//cout << a << " " << b << endl;
	char c;
	stream >> c >> b;
	if((c=='/')&&(b!=0)){
	num.Rebuild(a,b);
	a=b=0;
	}
	}
	return stream;
}

int main() {
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 3;
        }



        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 4;
        }
    }

   /* istringstream input1("f /4 6/4");
   Rational r11, r22;
    input1 >> r11 >> r22;
  cout << r11 <<  ' ' << r22 << endl;

    istringstream input2("6/4 6/f");
    Rational r12, r21;
    input2 >> r12 >> r21;
    cout << r12 <<  ' ' << r21 << endl;

    istringstream input3("+5 /-4 as/ ffff");
       Rational r13, r23;
       input3 >> r13 >> r23 ;
       cout << r13 <<  ' ' << r23 << endl;
*/
    cout << "OK" << endl;
    return 0;
}
