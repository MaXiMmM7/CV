#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include "profile.h"
#include <sstream>
using namespace std;

class Learner {
 private:
  set<string> dict;

 public:
  int Learn(const vector<string>& words) {
    int before=static_cast<int>(dict.size());
    for (const auto& word : words) {
     dict.insert(word);
      }
    return static_cast<int>(dict.size())-before;
  }

  vector<string> KnownWords() {
	  vector<string> result;
	  result.insert(result.end(),dict.begin(),dict.end());
    return result;
  }
};


int main() {
  Learner learner;
  string line;
 /* while (getline(cin, line)) {
    vector<string> words;
    stringstream ss(line);
    string word;
    while (ss >> word) {
      words.push_back(word);
    }
    LOG_DURATION("Learn");
    cout << learner.Learn(words) << "\n";
  }*/
  getline(cin, line);
  vector<string> words;
     stringstream ss(line);
     string word;
     while (ss >> word) {
       words.push_back(word);
     }
     LOG_DURATION("Learn");
     cout << learner.Learn(words) << "\n";


  cout << "=== known words ===\n";
  LOG_DURATION("Knowwords");
  for (auto word : learner.KnownWords()) {
    cout << word << "\n";
  }
}
