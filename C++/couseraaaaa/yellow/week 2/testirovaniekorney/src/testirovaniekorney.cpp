/*#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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



int GetDistinctRealRootCount(double a, double b, double c) {
	if(a!=0){
	double D=b*b-4*a*c;

	if(D==0){////////////////
		return 1;
	}
	else if (D>0){
		return 2;
	}}
	else if(b!=0){
		return 1;
	}
		return 0;
}


void TestAllNotZero(){
	AssertEqual(GetDistinctRealRootCount(2,4,1),2," 2 4 1"); // 16-8=8;
	AssertEqual(GetDistinctRealRootCount(4,4,1),1," 4 4 1"); // 16-16=0
	AssertEqual(GetDistinctRealRootCount(4,4,2),0," 4 4 2"); // 16-32<0

	AssertEqual(GetDistinctRealRootCount(-4,4,2),2," -4 4 2"); // 16+32>0  ;a<0
	AssertEqual(GetDistinctRealRootCount(4,4,-2),2," 4 4 -2"); // 16+32>0  ;c<0

	AssertEqual(GetDistinctRealRootCount(4,-4,2),0," 4 -4 2"); // 16-32<0  ;b<0
	AssertEqual(GetDistinctRealRootCount(4,-4,1),1," 4 -4 1"); // 16-16=0  ;b<0
	AssertEqual(GetDistinctRealRootCount(2,-4,1),2," 2 -4 1"); // 16-8>0  ;b<0

	AssertEqual(GetDistinctRealRootCount(-4,4,-2),0," -4 4 -2"); // 16-32<0  ;a,c<0
	AssertEqual(GetDistinctRealRootCount(-4,4,-1),1," -4 4 -1"); // 16-16=0  ;a,c<0
	AssertEqual(GetDistinctRealRootCount(-2,4,-1),2," -2 4 -1"); // 16-8>0   ;a,c<0

	AssertEqual(GetDistinctRealRootCount(-4,-4,2),2," -4 -4 2"); // 16+32>0  ;a,b<0
    AssertEqual(GetDistinctRealRootCount(-4,-4,1),2," -4 -4 1"); // 16+16>0  ;a,b<0
	AssertEqual(GetDistinctRealRootCount(-2,-4,1),2," -2 -4 1"); // 16+8>0   ;a,b<0

	AssertEqual(GetDistinctRealRootCount(4,-4,-2),2," 4 -4 -2"); // 16+32>0  ;c,b<0
	AssertEqual(GetDistinctRealRootCount(4,-4,-1),2," 4 -4 -1"); // 16+16>0  ;c,b<0
    AssertEqual(GetDistinctRealRootCount(2,-4,-1),2," 2 -4 -1"); // 16+8>0   ;c,b<0

	AssertEqual(GetDistinctRealRootCount(-4,-4,-2),0," -4 -4 -2"); // 16-32<0  ;a,b,c<0
	AssertEqual(GetDistinctRealRootCount(-4,-4,-1),1," -4 -4 -1"); // 16-16=0  ;a,b,c<0
	AssertEqual(GetDistinctRealRootCount(-2,-4,-1),2," -2 -4 -1"); // 16-8>0   ;a,b,c<0
}


void Test_B_IsZero(){
	AssertEqual(GetDistinctRealRootCount(1,0,1),0," 1 0 1"); // -4   ; a,c>0
	AssertEqual(GetDistinctRealRootCount(-1,0,1),2," -1 0 1"); // 4   ; a<0,c>0
	AssertEqual(GetDistinctRealRootCount(1,0,-1),2," 1 0 -1"); // 4   ; a>0,c<0
	AssertEqual(GetDistinctRealRootCount(-1,0,-1),0," -1 0 -1"); // -4   ; a<0,c<0
}

void Test_A_IsZero(){
	AssertEqual(GetDistinctRealRootCount(0,4,2),1," 0 4 2"); //  x<0 ; b,c>0
	AssertEqual(GetDistinctRealRootCount(0,-4,2),1," 0 -4 2"); //  x<0 ; b<0
	AssertEqual(GetDistinctRealRootCount(0,4,-2),1," 0 4 -2"); //  x<0 ; c<0
	AssertEqual(GetDistinctRealRootCount(0,-4,-2),1," 0 -4 -2"); //  x<0 ; b,c<0
}

void Test_C_IsZero(){
	AssertEqual(GetDistinctRealRootCount(1,1,0),2," 1 1 0"); //  1 ; b,a>0
	AssertEqual(GetDistinctRealRootCount(1,-1,0),2," 1 -1 0"); //  1 ; b<0,a>0
	AssertEqual(GetDistinctRealRootCount(-1,1,0),2," -1 1 0"); //  1 ; b>0,a<0
	AssertEqual(GetDistinctRealRootCount(-1,-1,0),2," -1 -1 0"); //  1 ; b,a<0
}

void Test_A_B_IsZero(){
	AssertEqual(GetDistinctRealRootCount(0,0,1),0," 0 0 1"); //  c>0
	AssertEqual(GetDistinctRealRootCount(0,0,-1),0," 0 0 -1"); //  c<0
}

void Test_A_C_IsZero(){
	AssertEqual(GetDistinctRealRootCount(0,1,0),1," 0 1 0"); //  b>0
	AssertEqual(GetDistinctRealRootCount(0,-1,0),1," 0 -1 0"); //  b<0
}

void Test_B_C_IsZero(){
	AssertEqual(GetDistinctRealRootCount(1,0,0),1," 1 0 0"); //  a>0
	AssertEqual(GetDistinctRealRootCount(-1,0,0),1," -1 0 0"); // a<0
}

void TestAll(){
	  TestRunner runner;
	  runner.RunTest(TestAllNotZero, "TestAllNotZero");
	  runner.RunTest(Test_B_IsZero,"Test_B_IsZero");
	  runner.RunTest(Test_A_IsZero,"Test_A_IsZero");
	  runner.RunTest(Test_C_IsZero,"Test_C_IsZero");
	  runner.RunTest(Test_A_B_IsZero,"Test_A_B_IsZero");
	  runner.RunTest(Test_A_C_IsZero,"Test_A_C_IsZero");
	  runner.RunTest(Test_B_C_IsZero,"Test_B_C_IsZero");
}
int main() {
  TestAll();
  //cout << GetDistinctRealRootCount(2,4,1) << endl;
  // добавьте сюда свои тесты
  return 0;
}*/
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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


/*
int GetDistinctRealRootCount(double a, double b, double c) {
	if(a!=0){
	double D=b*b-4*a*c;

	if(D==0){////////////////
		return 1;
	}
	else if (D>0){
		return 2;
	}}
	else if(b!=0){
		return 1;
	}
		return 0;
}
*/

void TestAllNotZero(){
	AssertEqual(GetDistinctRealRootCount(2,4,1),2," 2 4 1"); // 16-8=8;
	AssertEqual(GetDistinctRealRootCount(4,4,1),1," 4 4 1"); // 16-16=0
	AssertEqual(GetDistinctRealRootCount(4,4,2),0," 4 4 2"); // 16-32<0

	AssertEqual(GetDistinctRealRootCount(-4,4,2),2," -4 4 2"); // 16+32>0  ;a<0
	AssertEqual(GetDistinctRealRootCount(4,4,-2),2," 4 4 -2"); // 16+32>0  ;c<0

	AssertEqual(GetDistinctRealRootCount(4,-4,2),0," 4 -4 2"); // 16-32<0  ;b<0
	AssertEqual(GetDistinctRealRootCount(4,-4,1),1," 4 -4 1"); // 16-16=0  ;b<0
	AssertEqual(GetDistinctRealRootCount(2,-4,1),2," 2 -4 1"); // 16-8>0  ;b<0

	AssertEqual(GetDistinctRealRootCount(-4,4,-2),0," -4 4 -2"); // 16-32<0  ;a,c<0
	AssertEqual(GetDistinctRealRootCount(-4,4,-1),1," -4 4 -1"); // 16-16=0  ;a,c<0
	AssertEqual(GetDistinctRealRootCount(-2,4,-1),2," -2 4 -1"); // 16-8>0   ;a,c<0

	AssertEqual(GetDistinctRealRootCount(-4,-4,2),2," -4 -4 2"); // 16+32>0  ;a,b<0
    AssertEqual(GetDistinctRealRootCount(-4,-4,1),2," -4 -4 1"); // 16+16>0  ;a,b<0
	AssertEqual(GetDistinctRealRootCount(-2,-4,1),2," -2 -4 1"); // 16+8>0   ;a,b<0

	AssertEqual(GetDistinctRealRootCount(4,-4,-2),2," 4 -4 -2"); // 16+32>0  ;c,b<0
	AssertEqual(GetDistinctRealRootCount(4,-4,-1),2," 4 -4 -1"); // 16+16>0  ;c,b<0
    AssertEqual(GetDistinctRealRootCount(2,-4,-1),2," 2 -4 -1"); // 16+8>0   ;c,b<0

	AssertEqual(GetDistinctRealRootCount(-4,-4,-2),0," -4 -4 -2"); // 16-32<0  ;a,b,c<0
	AssertEqual(GetDistinctRealRootCount(-4,-4,-1),1," -4 -4 -1"); // 16-16=0  ;a,b,c<0
	AssertEqual(GetDistinctRealRootCount(-2,-4,-1),2," -2 -4 -1"); // 16-8>0   ;a,b,c<0
}


void Test_B_IsZero(){
	AssertEqual(GetDistinctRealRootCount(1,0,1),0," 1 0 1"); // -4   ; a,c>0
	AssertEqual(GetDistinctRealRootCount(-1,0,1),2," -1 0 1"); // 4   ; a<0,c>0
	AssertEqual(GetDistinctRealRootCount(1,0,-1),2," 1 0 -1"); // 4   ; a>0,c<0
	AssertEqual(GetDistinctRealRootCount(-1,0,-1),0," -1 0 -1"); // -4   ; a<0,c<0
}

void Test_A_IsZero(){
	AssertEqual(GetDistinctRealRootCount(0,4,2),1," 0 4 2"); //  x<0 ; b,c>0
	AssertEqual(GetDistinctRealRootCount(0,-4,2),1," 0 -4 2"); //  x<0 ; b<0
	AssertEqual(GetDistinctRealRootCount(0,4,-2),1," 0 4 -2"); //  x<0 ; c<0
	AssertEqual(GetDistinctRealRootCount(0,-4,-2),1," 0 -4 -2"); //  x<0 ; b,c<0
}

void Test_C_IsZero(){
	AssertEqual(GetDistinctRealRootCount(1,1,0),2," 1 1 0"); //  1 ; b,a>0
	AssertEqual(GetDistinctRealRootCount(1,-1,0),2," 1 -1 0"); //  1 ; b<0,a>0
	AssertEqual(GetDistinctRealRootCount(-1,1,0),2," -1 1 0"); //  1 ; b>0,a<0
	AssertEqual(GetDistinctRealRootCount(-1,-1,0),2," -1 -1 0"); //  1 ; b,a<0
}

void Test_A_B_IsZero(){
	AssertEqual(GetDistinctRealRootCount(0,0,1),0," 0 0 1"); //  c>0
	AssertEqual(GetDistinctRealRootCount(0,0,-1),0," 0 0 -1"); //  c<0
}

void Test_A_C_IsZero(){
	AssertEqual(GetDistinctRealRootCount(0,1,0),1," 0 1 0"); //  b>0
	AssertEqual(GetDistinctRealRootCount(0,-1,0),1," 0 -1 0"); //  b<0
}

void Test_B_C_IsZero(){
	AssertEqual(GetDistinctRealRootCount(1,0,0),1," 1 0 0"); //  a>0
	AssertEqual(GetDistinctRealRootCount(-1,0,0),1," -1 0 0"); // a<0
}

void TestAll(){
	  TestRunner runner;
	  runner.RunTest(TestAllNotZero, "TestAllNotZero");
	  runner.RunTest(Test_B_IsZero,"Test_B_IsZero");
	  runner.RunTest(Test_A_IsZero,"Test_A_IsZero");
	  runner.RunTest(Test_C_IsZero,"Test_C_IsZero");
	  runner.RunTest(Test_A_B_IsZero,"Test_A_B_IsZero");
	  runner.RunTest(Test_A_C_IsZero,"Test_A_C_IsZero");
	  runner.RunTest(Test_B_C_IsZero,"Test_B_C_IsZero");
}
int main() {
  TestAll();
  //cout << GetDistinctRealRootCount(2,4,1) << endl;
  // добавьте сюда свои тесты
  return 0;
}

