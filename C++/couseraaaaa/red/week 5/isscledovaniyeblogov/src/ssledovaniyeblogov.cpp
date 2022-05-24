#include "test_runner.h"
#include "profile.h"

#include <map>
#include <vector>
#include <string>
#include <future>
#include <iostream>
#include <utility>
#include <algorithm>
#include <sstream>
#include <functional>
using namespace std;

/////////////////////////////////////////
////////////////////////////////////////
/////////////////////////////////////////

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other){
	  for(auto x:other.word_frequences){
		  if(word_frequences.count(x.first)==0){
			  word_frequences[x.first]=x.second;
		  }
		  else{
			  word_frequences[x.first]+=x.second;
		  }
  }
  }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
	Stats result;
	stringstream stream;
	stream << line;
	for(string s;getline(stream,s,' ');){
			if(key_words.count(s)==1){
				if(result.word_frequences.count(s)==0){
				result.word_frequences[move(s)]=1;
				}
				else{
					result.word_frequences[move(s)]++;
				}
			}
			while(stream.peek()==' '){
				stream.ignore(1);
			}
	}
	return result;
}

Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, istream& input
) {
  Stats result;
  for (string line; getline(input, line); ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
	LOG_DURATION("hey");
	vector<future<Stats>> stats;
	vector<stringstream> data;
string s;
int j=0;

	while(!input.eof()){
		stringstream stream;
		stream << (" " +s+"   ");
		while(getline(input,s)){
			stream << (" " +s+"   ");
				if(j==20000){
							data.push_back(move(stream));
							j=0;
							break;
						}
			j++;
		}
		if(!getline(input,s)){
			data.push_back(move(stream));
				}
	}

	for(auto& x:data){
		stats.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(x)));
	}

Stats result;
for (auto& f : stats) {
    result += f.get();
  }
	return result;
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

void TestTwo() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  for(int i=0;i<100000;i++){
	  ss << "this new yangle service really rocks\n";
	    ss << "It sucks when yangle isn't available\n";
	    ss << "10 reasons why yangle is the best IT company\n";
	    ss << "yangle rocks others suck\n";
	    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";
}


  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 600000},
    {"rocks", 200000},
    {"sucks", 100000}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}


int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
  RUN_TEST(tr, TestTwo);


return 0;
}
