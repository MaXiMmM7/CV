//============================================================================
// Name        : bazaregionov.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
/*
#include <iostream>
#include <map>
#include <tuple>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

enum class Lang {
  DE, FR, IT
};

struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};

auto RegionEqual(const Region& a){
	return tie(a.std_name,a.parent_std_name,a.names,a.population);
}
bool operator <(const Region& a,const Region& b){
	return RegionEqual(a)<RegionEqual(b);
}
bool operator ==(const Region& a,const Region& b){
	return RegionEqual(a)==RegionEqual(b);
}

int FindMaxRepetitionCount(const vector<Region>& regions){
	int N=static_cast<int>(regions.size());
	if(N==0){
		return 0;
	}
	map<Region,int> data;
for (int i=0;i<N;i++){
	if(data.count(regions[i])==0){
	data[regions[i]]=1;}
	else{
		data[regions[i]]++;
	}

}
int max=1;
for (auto x: data){
	if(x.second>max){
		max=x.second;
	}
}
return max;
}


int main() {

	vector <Region> reg;
	cout << FindMaxRepetitionCount(reg)<<endl;;
	cout << FindMaxRepetitionCount({
	      {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Russia",
	          "Eurasia",
	          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
	          89
	      }, {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Russia",
	          "Eurasia",
	          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
	          89
	      },
	  }) << endl;
	 cout << FindMaxRepetitionCount({
	      {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Russia",
	          "Eurasia",
	          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
	          89
	      }, {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Moscow",
	          "Toulouse",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          31
	      },
	  }) << endl;


	return 0;
}*/





#include <iostream>
#include <map>
#include <tuple>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;



auto RegionEqual(const Region& a){
	return tie(a.std_name,a.parent_std_name,a.names,a.population);
}
bool operator <(const Region& a,const Region& b){
	return RegionEqual(a)<RegionEqual(b);
}
bool operator ==(const Region& a,const Region& b){
	return RegionEqual(a)==RegionEqual(b);
}

int FindMaxRepetitionCount(const vector<Region>& regions){
	int N=static_cast<int>(regions.size());
	if(N==0){
		return 0;
	}
	map<Region,int> data;
for (int i=0;i<N;i++){
	if(data.count(regions[i])==0){
	data[regions[i]]=1;}
	else{
		data[regions[i]]++;
	}

}
int max=1;
for (auto x: data){
	if(x.second>max){
		max=x.second;
	}
}
return max;
}


