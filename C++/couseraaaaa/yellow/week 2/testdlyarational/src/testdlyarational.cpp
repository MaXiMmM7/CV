//============================================================================
// Name        : testdlyarational.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
/*
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>

using namespace std;



template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}


template <typename Key,typename Word>
ostream& operator << (ostream& stream, const pair<Key,Word>& p){
	return stream << "[" << p.first << " , " << p.second << "]";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};
/////////////////////////////////////////

/////////////////////////////////////////

/////////////////////////////////////////
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

/////////////////////////////////////

/////////////////////////////////////

///////////////////////////////////

void TestDefault(){
	{
		Rational num;
		AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(0,1)," Default");
	}
}

void TestOver(){
	{
		Rational num(1,2);
		AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(1,2)," 1,2");
	}
	{
			Rational num(2,4);
			AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(1,2)," 2,4");
	}

	{
			Rational num(4,2);
			AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(2,1)," 4,2");
	}
	{
			Rational num(-1,2);
			AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(-1,2)," -1,2");
    }
	{
				Rational num(1,-2);
				AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(-1, 2)," 1,-2");
	}
	{
					Rational num(-1,-2);
					AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(1,2)," -1, -2");
	}
	{
				Rational num(-2,4);
				AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(-1,2)," -2,4");
	}

	{
				Rational num(-4,2);
				AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(-2,1)," -4,2");
	}
	{
					Rational num(2,-4);
					AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(-1,2)," 2,-4");
		}

		{
					Rational num(4,-2);
					AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(-2,1)," 4,-2");
		}
		{
						Rational num(-2,-4);
						AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(1,2)," 2,4");
			}

			{
						Rational num(-4,-2);
						AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(2,1)," 4,2");
			}
	{
					Rational num(0,-2);
					AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(0,1)," 0,-2");
	}
	{
					Rational num(0,70);
					AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(0,1)," 0,70");
	}

}
void TestAll(){
	TestRunner runner;
	runner.RunTest(TestDefault,"TestDefault");
	runner.RunTest(TestOver,"TestOver");
}
int main() {
  TestAll();

  return 0;
}

*/

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>

using namespace std;



template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}


template <typename Key,typename Word>
ostream& operator << (ostream& stream, const pair<Key,Word>& p){
	return stream << "[" << p.first << " , " << p.second << "]";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

void TestDefault(){
	{
		Rational num;
		AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(0,1)," Default");
	}
}

void TestOver(){
	{
		Rational num(1,2);
		AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(1,2)," 1,2");
	}
	{
			Rational num(2,4);
			AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(1,2)," 2,4");
	}

	{
			Rational num(4,2);
			AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(2,1)," 4,2");
	}
	{
			Rational num(-1,2);
			AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(-1,2)," -1,2");
    }
	{
				Rational num(1,-2);
				AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(-1, 2)," 1,-2");
	}
	{
					Rational num(-1,-2);
					AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(1,2)," -1, -2");
	}
	{
				Rational num(-2,4);
				AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(-1,2)," -2,4");
	}

	{
				Rational num(-4,2);
				AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(-2,1)," -4,2");
	}
	{
					Rational num(2,-4);
					AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(-1,2)," 2,-4");
		}

		{
					Rational num(4,-2);
					AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(-2,1)," 4,-2");
		}
		{
						Rational num(-2,-4);
						AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(1,2)," 2,4");
			}

			{
						Rational num(-4,-2);
						AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(2,1)," 4,2");
			}
	{
					Rational num(0,-2);
					AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(0,1)," 0,-2");
	}
	{
					Rational num(0,70);
					AssertEqual(pair<int,int>(num.Numerator(),num.Denominator()),pair<int,int>(0,1)," 0,70");
	}

}
void TestAll(){
	TestRunner runner;
	runner.RunTest(TestDefault,"TestDefault");
	runner.RunTest(TestOver,"TestOver");
}
int main() {
  TestAll();

  return 0;
}

