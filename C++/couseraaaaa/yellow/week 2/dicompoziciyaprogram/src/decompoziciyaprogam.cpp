//============================================================================
// Name        : decompoziciyaprogam.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
/*
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  string check;
  is >> check;
  if(check=="NEW_BUS"){
	  q.type=QueryType::NewBus;
	is >> q.bus;
	int N;
	is >> N;
	for(int i=0;i<N;i++){
		is >> q.stop;
		q.stops.push_back(q.stop);
	}
  }
  if(check=="BUSES_FOR_STOP"){
	  q.type=QueryType::BusesForStop;
	  is >> q.stop;
   }
  if(check=="STOPS_FOR_BUS"){
	  q.type=QueryType::StopsForBus;
	  is >> q.bus;
   }
  if(check=="ALL_BUSES "){
	  q.type=QueryType::AllBuses;
   }
  return is;
}

struct BusesForStopResponse {
    bool existence;
	string stop;
    vector<string> Buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	if(!r.existence){
		  os << "No Stop";
		  return os;
	  }
	  for(auto x: r.Buses){
		  os << x << " ";
	  }
  return os;
}

struct StopsForBusResponse {
  bool existence;
  string bus;
  vector<BusesForStopResponse> stops;
   };

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	if(!r.existence){
		  os << "No bus";
		  return os;
	  }
	size_t N=r.stops.size();
	  for(size_t i=0;i < N;i++){
		  os << "Stop " << r.stops[i].stop << ": ";
		  if(r.stops[i].Buses.size()>1){

			  for(auto z:r.stops[i].Buses){
			  os << z << " ";
			  }
		  }
		  else{
			  os << "no interchange";
		  }
		  if(i!=N-1){
			  os << endl;
		  }
	  }
  return os;
}

struct AllBusesResponse {
	bool existence;
  map<string,vector<string>> AllBuses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if(!r.existence){
	  os << "No buses";
	  return os;
  }
  size_t N=r.AllBuses.size();
  size_t i=1;
  for(auto x: r.AllBuses){
	  os << "Bus " << x.first << ":";
	  for(const auto& y: x.second){
		  os << " " << y;
	  }
	  if(i!=N){
		  os << endl;
	  }
	  i++;
  }

  return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
	  buses_to_stops[bus]=stops;
	       for (auto x:stops) {
	        stops_to_buses[x].push_back(bus);
	       }

  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
	  BusesForStopResponse result;
	  if(stops_to_buses.count(stop)==0){
		  result.existence=0;
		  return  result;
	  }
	  result.existence=1;
	  result.stop=stop;
	  result.Buses=stops_to_buses.at(stop);
	  return result;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
	  StopsForBusResponse result;
    if(buses_to_stops.count(bus)==0){
    	result.existence=0;
    	return result;
    }
    result.bus=bus;
    BusesForStopResponse helper;
    helper.existence=1;
    for(auto x:buses_to_stops.at(bus)){
    	helper.stop=x;
    	helper.Buses=stops_to_buses.at(x);
    	result.stops.push_back(helper);
    }
    return result;
  }

  AllBusesResponse GetAllBuses() const {
	  AllBusesResponse result;
	  if(buses_to_stops.size()==0){
		  result.existence=0;
		  return result;
	  }
	  result.AllBuses=buses_to_stops;
	  return result;
  }
private:
  map<string, vector<string>> buses_to_stops;
  map<string, vector<string>> stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
*/

#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  string check;
  is >> check;
  if(check=="NEW_BUS"){
	  q.type=QueryType::NewBus;
	is >> q.bus;
	q.stops.clear();
	int N;
	is >> N;
	for(int i=0;i<N;i++){
		is >> q.stop;
		q.stops.push_back(q.stop);
	}
  }
  if(check=="BUSES_FOR_STOP"){
	  q.type=QueryType::BusesForStop;
	  is >> q.stop;
   }
  if(check=="STOPS_FOR_BUS"){
	  q.type=QueryType::StopsForBus;
	  is >> q.bus;
   }
  if(check=="ALL_BUSES"){
	  q.type=QueryType::AllBuses;
   }
  return is;
}

struct BusesForStopResponse {
  string stop;
  vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if(r.buses.empty()){
	  os << "No stop";
	  return os;
  }

  size_t N=r.buses.size();
  for(size_t i=0;i<N;i++){
	  os << r.buses[i];
	  if(i!=(N-1)){
		  os << " ";
	  }
  }
  return os;
}

struct StopsForBusResponse {
  string bus;
  vector<string> array;
  map<string,vector<string>> stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	 if(r.stops.empty()){
		  os << "No bus";
		  return os;
	  }
	  size_t N=r.stops.size();
	  size_t i=1;
	 for (const auto& x: r.array){
		 os << "Stop " << x <<":";
		 if(r.stops.at(x).size()>1){
		 for(const auto& y: r.stops.at(x)){
			 if(y!=r.bus){
			 os << " " << y;
			 }
		 }
		 }
		 else{
			 os << " no interchange";
		 }
		 if(i!=N){
			 os << endl;
		 }
		 i++;
	 }

  return os;
}

struct AllBusesResponse {
	map<string, vector<string>> Buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {

	if(r.Buses.empty()){
		  os << "No buses";
		  return os;
	  }
	  size_t N=r.Buses.size();
	  size_t i=1;
	  for(const auto& x: r.Buses){
		  os << "Bus " << x.first << ":";
				  for(const auto& y: x.second){
					  os << " " << y;
				  }
				   if(i!=N){
				 			 os << endl;
				 		 }
				 		 i++;
	  }
  return os;

}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
   Buses[bus]=stops;
   for(auto& x: stops){
	   Stops[x].push_back(bus);
   }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
   BusesForStopResponse result;
   if(Stops.count(stop)==0){
  	   return result;
     }

   result.stop=stop;
   result.buses=Stops.at(stop);
   return result;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
	  StopsForBusResponse result;
	  if(Buses.count(bus)==0){
	 	   return result;
	    }

	  result.bus=bus;
	  for(auto x: Buses.at(bus)){
		  result.stops[x]=Stops.at(x);
	  }
	  result.array=Buses.at(bus);
    return result;
  }

  AllBusesResponse GetAllBuses() const {
	  AllBusesResponse result;
	  result.Buses=Buses;
	  return result;
  }

private:
  map<string, vector<string>> Buses;
  map<string, vector<string>> Stops;

};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
