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

bool IsPalindrom(string s){
	if(s.empty()){return 1;}
	int first=0;
	int last=s.size()-1;
	while(first<last){
		if(s[first]!=s[last]){
			return 0;
		}
		first++;
		last--;
	}
		return 1;
}

void TestPalindroms()
{
	Assert(IsPalindrom(""),"empty");
	Assert(IsPalindrom("a"),"one symbol");
	Assert(!IsPalindrom(" a"),"two symbols");
	Assert(!IsPalindrom("a "),"two symbols");
	Assert(IsPalindrom("  "),"two symbols");
	Assert(IsPalindrom("aaa"),"yes");
	Assert(IsPalindrom("abcba"),"yes");
	Assert(!IsPalindrom("abcdbc"),"no");
	Assert(!IsPalindrom(" hah"),"no");
	Assert(!IsPalindrom("aha "),"no");
	Assert(!IsPalindrom("a aa"),"no");
	Assert(!IsPalindrom("abbac"),"no");
	Assert(!IsPalindrom("avdvac"),"no");
	Assert(!IsPalindrom("caba"),"no");
	Assert(!IsPalindrom("cabba"),"no");
	Assert(IsPalindrom("abba"),"yes");

}

void TestAll(){
	TestRunner runner;
	runner.RunTest(TestPalindroms,"TestPalindroms");
}

int main() {
  TestAll();

  return 0;
}
