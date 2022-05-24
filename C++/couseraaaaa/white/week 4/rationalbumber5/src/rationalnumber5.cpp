//============================================================================
// Name        : rationalnumber5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <sstream>
#include <cmath>
#include <typeinfo>
#include <map>
#include <set>
#include <vector>
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

bool operator <(const Rational& a,const Rational& b){
	return a.Numerator()*b.Denominator()<b.Numerator()*a.Denominator();
}


	int main() {
	    {
	        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
	        if (rs.size() != 3) {
	            cout << "Wrong amount of items in the set" << endl;
	            return 1;
	        }

	        vector<Rational> v;
	        for (auto x : rs) {
	            v.push_back(x);
	        }
	        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
	            cout << "Rationals comparison works incorrectly" << endl;
	            return 2;
	        }
	    }

	    {
	        map<Rational, int> count;
	        ++count[{1, 2}];
	        ++count[{1, 2}];

	        ++count[{2, 3}];

	        if (count.size() != 2) {
	            cout << "Wrong amount of items in the map" << endl;
	            return 3;
	        }
	    }

	    cout << "OK" << endl;
	    return 0;
	}

