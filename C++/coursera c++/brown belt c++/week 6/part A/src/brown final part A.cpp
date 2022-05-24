#include <iostream>
#include "test_runner.h"
#include <iterator>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <system_error>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include <set>
#include <cmath>
#include <iomanip>

using namespace std;

/*
pair<string_view, optional<string_view>> SplitTwoStrict(string_view s, string_view delimiter = " ") {
  const size_t pos = s.find(delimiter);
  if (pos == s.npos) {
    return {s, nullopt};
  } else {
    return {s.substr(0, pos), s.substr(pos + delimiter.length())};
  }
}

pair<string_view, string_view> SplitTwo(string_view s, string_view delimiter = " ") {
  const auto [lhs, rhs_opt] = SplitTwoStrict(s, delimiter);
  return {lhs, rhs_opt.value_or("")};
}

string_view ReadToken(string_view& s, string_view delimiter = " ") {
  const auto [lhs, rhs] = SplitTwo(s, delimiter);
  s = rhs;
  return lhs;
}

int ConvertToInt(string_view str) {
  // use std::from_chars when available to git rid of string copy
  size_t pos;
  const int result = stoi(string(str), &pos);
  if (pos != str.length()) {
    std::stringstream error;
    error << "string " << str << " contains " << (str.length() - pos) << " trailing chars";
    throw invalid_argument(error.str());
  }
  return result;
}
*/

struct Coordinates{
	Coordinates(){}
	Coordinates(double lat,double lon):latitude(lat),longitude(lon){}
	double latitude = 0.0;
	double longitude = 0.0;
};

constexpr double pi = 3.1415926535;
constexpr double R =  6371000;


bool operator==(const Coordinates& l,const Coordinates& r){
	return (l.latitude==r.latitude)&&(l.longitude==r.longitude);
}
double Distance(const Coordinates& l, const Coordinates& r){
	if(l==r){return 0.;}
	double lat_r = r.latitude/180*pi;
	double lat_l = l.latitude/180*pi;
	double lon_r = r.longitude/180*pi;
	double lon_l = l.longitude/180*pi;// fi -shir
	return R*acos(sin(lat_l)*sin(lat_r)+cos(lat_l)*cos(lat_r)*cos(lon_l-lon_r));
}

//

//class Route;
//class Bus;
//
class Stop{
public:
	Stop(){}
	Stop(const string& name,const Coordinates& coords):name_(name),coords_(coords){}
	const string& GetName() const{
		return name_;
	}
	const Coordinates& GetCoordinates() const{
		return coords_;
	}
	void InsertBus(string name){
		buses_.insert(name);
	}
	const set<string>& GetBuses() const{
		return buses_;
	}

	bool HasBuses() const{
		return !buses_.empty();
	}
private:
	string name_;
	Coordinates coords_;
	set<string> buses_;
};

double Distance(const Stop& l, const Stop& r){
	return Distance(l.GetCoordinates(),r.GetCoordinates());
}

bool operator==(const Stop& l, const Stop& r){
	return (l.GetName()==r.GetName())&&(l.GetCoordinates()==r.GetCoordinates());
}

ostream& operator<<(ostream& output, const Stop& stop){
	return output << stop.GetName() << " " << stop.GetCoordinates().latitude << " " << stop.GetCoordinates().longitude;
}

using StopPtr = shared_ptr<Stop>;

class StopsDatabase{
public:
	void Insert(Stop stop){
		stops_[stop.GetName()]=make_shared<Stop>(stop);
	}
	optional<StopPtr> GetStop(const string& name) const{
		if(stops_.count(name)==0){
			return nullopt;
		}
		return stops_.at(name);
	}
private:
	unordered_map<string,StopPtr> stops_;
};

using _Route_=vector<shared_ptr<Stop>>;

class Route{
public:
	Route(){}
	Route(_Route_ stops):route_(move(stops)){
	if(GetNumberOfStops()>1){
		for(size_t i=0; i+2<GetNumberOfStops();i++){
			length+=Distance(route_[i]->GetCoordinates(),route_[i+1]->GetCoordinates());
		}
	}
	}
	void push_back(StopPtr stop){
		route_.push_back(stop);
		if(GetNumberOfStops()>1){
			length+=Distance(route_[GetNumberOfStops()-2]->GetCoordinates(),route_[GetNumberOfStops()-1]->GetCoordinates());
		}
	}
	const _Route_& GetRoute() const{
		return route_;
	}
	size_t GetNumberOfStops() const{
		return route_.size();
	}
    size_t GetUniqueNumberOfStops() const{
		return set(route_.begin(),route_.end(),[](StopPtr l, StopPtr r){
			return l->GetName()<r->GetName();
		}).size();
	}
	bool Empty() const{
		return route_.empty();
	}
	double GetLength() const{
		return length;
	}
	//   int GetNumberOfStops
protected:
	_Route_ route_;
	double length = 0.;
};

class Bus: public Route{
public:
	Bus(){}
	Bus(string name):name_(move(name)){}
	Bus(Route rt,string name):Route(move(rt)),name_(move(name)){}
	string GetName() const{
		return name_;
	}
	void push_back(StopPtr stop){
		Route::push_back(stop);
		route_.back()->InsertBus(name_);
	}
private:
	string name_;
};

using Bus_unique=unique_ptr<Bus>;

class BusesDatabase{
public:
	void Insert(Bus bus){
		//
		//
		buses_[bus.GetName()]=make_unique<Bus>(bus);
	}

	optional<Bus> GetBus(const string& name) const{
		//
		//cout << name << endl;
		//
		if(buses_.count(name)==0){
			//
		//	cout << name << "  case 0"<< endl;
			//
			return nullopt;
		}
		//
	//				cout << name << "  case 1"<< endl;
					//
		return *buses_.at(name);
	}

private:
	unordered_map<string,Bus_unique> buses_;
};




void ParseName(string& s){
	while(s.front()==' '){
		s.erase(0,1);
	}
	while(s.back()==' '){
		s.pop_back();
	}
}

vector<string> ParseNames(string s){
	//
//	cout << s << endl;
	//
	vector<string> result;
	string helper;
	size_t pose;
	if(s.find("-")!=s.npos){
		pose=s.find("-");
		helper=s.substr(0,pose);
		while(!helper.empty()){
			ParseName(helper);
			//
	//		cout << helper << endl;
			//
			result.push_back(move(helper));
			if(pose!=helper.npos){
				s.erase(0,pose+1);
			}else{
				break;
			}
			//
	//		cout << s << endl;
			//
			pose=s.find("-");
			helper=s.substr(0,pose);
		}
		auto copy = result;
		//
	//	cout << "COPY : " << copy << endl;
		//
		for (auto It=next(copy.rbegin()); It!=copy.rend();It++){
			result.push_back(*It);
		}
	}
	else if(s.find('>')!=s.npos){
		pose=s.find('>');
		helper=s.substr(0,pose);
		while(!helper.empty()){
		//	cout << helper << " " << pose <<endl;
			ParseName(helper);
			result.push_back(move(helper));
			if(pose!=helper.npos){
				s.erase(0,pose+1);
			}else{
				break;
			}
			pose=s.find(">");
			helper=s.substr(0,pose);
		}}
	else{
		ParseName(s);
		result.push_back(s);
	}

		return result;
}





void WorkWithData(istream& input = cin,ostream& output = cout){
	StopsDatabase stops;
	BusesDatabase buses;
	int Q;
	string name;
	string helper;
	double num_1,num_2;
	input >> Q;
	vector<pair<string,string>> bus_requests;
	for(int i = 0; i < Q; i++){
		input >> helper;
		if(helper == "Stop"){
			getline(input,name,':');
			ParseName(name);
			getline(input,helper,',');
			num_1 = stod(helper);
			getline(input,helper);
			num_2 = stod(helper);

			//
		//	cout << "__" << name << "__" << endl;
			//
			stops.Insert(Stop(move(name),Coordinates(num_1,num_2)));
		}else if(helper == "Bus"){
			getline(input,name,':');
			ParseName(name);
			//Bus bus(name);
			getline(input,helper);
			bus_requests.push_back(make_pair(name,helper));
/*			for(auto x: ParseNames(helper)){
				//
				cout << x << endl;
				//
				bus.push_back(stops.GetStop(string(x)).value());
			}
			buses.Insert(move(bus));
			*/
		}
	}

	for(auto x: bus_requests){
		Bus bus(x.first);
		//
	/*	cout <<"ok  " <<  x.first << "______" << x.second << endl;
		for(auto z: ParseNames(x.second)){
			cout << "__" << z << "__" ;
		}
		cout << endl <<endl<<endl;*/
		//

		for(auto y: ParseNames(x.second)){
			//
		//	cout << "y:_" << y <<"_" << endl;

			//
			bus.push_back(stops.GetStop(string(y)).value());
		}
		buses.Insert(move(bus));
	}

	input >> Q;

	for(int i = 0; i < Q; i++){
		input >> helper;
		if(helper == "Bus"){
			getline(input,name);
			ParseName(name);
			output << "Bus " << name << ": ";
			auto bus = buses.GetBus(name);
			if(bus.has_value()){
				output << bus.value().GetNumberOfStops() << " stops on route, " <<
						bus.value().GetUniqueNumberOfStops() << " unique stops, " <<
						fixed << setprecision(6) << bus.value().GetLength() << " route length\n";

			}
			else{
				output << "not found\n";
			}
		}else if(helper == "Stop"){
			getline(input,name);
			ParseName(name);
			output << "Stop " << name << ": ";
			auto stop = stops.GetStop(name);
			if(stop.has_value()){
				if(stop.value()->HasBuses()){
					output << "buses ";
				for(auto x:stop.value()->GetBuses()){
					output << x << " ";
				}
				output << "\n";
			}else{
				output << "no buses\n";

			}
			}
			else{
				output << "not found\n";
			}

		}
	}
}

/////////////////////////////////////
void TestStopsDatabase(){
	{
		StopsDatabase db;
		ASSERT_EQUAL(false,db.GetStop("cat").has_value());
		ASSERT_EQUAL(false,db.GetStop("dog").has_value());
		db.Insert(Stop("cat", Coordinates(5.5,6.5)));
		ASSERT_EQUAL(true,db.GetStop("cat").has_value());
		ASSERT_EQUAL(false,db.GetStop("dog").has_value());
		ASSERT_EQUAL(Coordinates(5.5,6.5).latitude,db.GetStop("cat").value()->GetCoordinates().latitude);
		ASSERT_EQUAL(Coordinates(5.5,6.5).longitude,db.GetStop("cat").value()->GetCoordinates().longitude);
	}

}
/*
void TestRoute(){
	{
		StopsDatabase db;
		db.Insert(Stop("cat", Coordinates(1,1)));
		db.Insert(Stop("dog", Coordinates(2,2)));
		db.Insert(Stop("frog", Coordinates(3,3)));

		Route route;
		ASSERT_EQUAL(true,route.Get().empty());
		route.push_back(*db.GetStop("cat"));
		ASSERT_EQUAL(static_cast<size_t>(1),route.Get().size());
		vector<Stop> helper;
		for(auto x: route.Get()){
			helper.push_back(*x);
		}
		vector<Stop> checker({Stop("cat", Coordinates(1,1))});
		ASSERT_EQUAL(helper,checker);
		route.push_back(*db.GetStop("dog"));
		route.push_back(*db.GetStop("frog"));
		ASSERT_EQUAL(static_cast<size_t>(3),route.Get().size());
		checker = vector<Stop>({Stop("cat", Coordinates(1,1)),Stop("dog", Coordinates(2,2)),Stop("frog", Coordinates(3,3))});
        helper.clear();
    	for(auto x: route.Get()){
    		helper.push_back(*x);
    	}
    	ASSERT_EQUAL(helper,checker);

	}
}*/

void TestBus(){
	StopsDatabase db;
	db.Insert(Stop("cat", Coordinates(1,1)));
	db.Insert(Stop("dog", Coordinates(2,2)));
	db.Insert(Stop("frog", Coordinates(3,3)));


	Route route;
	route.push_back(*db.GetStop("cat"));
	route.push_back(*db.GetStop("dog"));
	route.push_back(*db.GetStop("frog"));

	Route route_2 = route;

	Bus bus(move(route),"777");
	ASSERT_EQUAL(true,route.Empty());
	ASSERT_EQUAL("777",bus.GetName());

    vector<Stop> checker({Stop("cat", Coordinates(1,1)),Stop("dog", Coordinates(2,2)),Stop("frog", Coordinates(3,3))});

    vector<Stop> helper;
    for(auto x: bus.GetRoute()){
    	helper.push_back(*x);
    }
	ASSERT_EQUAL(helper,checker);
}


void TestBusDatabase(){
	{
		StopsDatabase db;
		db.Insert(Stop("cat", Coordinates(1,1)));
		db.Insert(Stop("dog", Coordinates(2,2)));
		db.Insert(Stop("frog", Coordinates(3,3)));


		Route route;
		route.push_back(*db.GetStop("cat"));
		route.push_back(*db.GetStop("dog"));
		route.push_back(*db.GetStop("frog"));

		Route route_2 = route;

		Bus bus(move(route),"777");

		BusesDatabase bus_db;
		bus_db.Insert(bus);
		//ASSERT_EQUAL(true,bus.GetRoute().Get().empty());
		ASSERT_EQUAL(false,bus_db.GetBus("man").has_value());
		ASSERT_EQUAL(true,bus_db.GetBus("777").has_value());
		ASSERT_EQUAL("777",bus_db.GetBus("777").value().GetName());
		ASSERT_EQUAL(static_cast<size_t>(3),bus_db.GetBus("777").value().GetNumberOfStops());

		vector<Stop> checker({Stop("cat", Coordinates(1,1)),Stop("dog", Coordinates(2,2)),Stop("frog", Coordinates(3,3))});

//	    cout << "we are herer  "<<bus_db.GetBus("777").value().GetName() << endl;
	//    cout << *bus_db.GetBus("777").value().GetRoute().Get()[0] << endl;
	    vector<Stop> helper;

	    auto v=bus_db.GetBus("777").value().GetRoute();  //!!!!!!!!!!!!!!
	    for(auto x: v){
	  //  	cout <<"dsds  " <<  *x << endl;
	    	helper.push_back(*x);
	    }
		ASSERT_EQUAL(checker,helper);


	}
}




void TestDistance(){
	{
		Coordinates Tura(64.28,100.22);
		Coordinates New_York(40.71,-44.01);
		Coordinates Sydney(-33.874,151.213);

		//ASSERT_EQUAL(0.,Distance(Tura,Tura));
		//ASSERT_EQUAL(8335000.,Distance(Tura,New_York));
		//ASSERT_EQUAL(11780000.,Distance(Tura,Sydney));
	}
}
int main(){
	TestRunner tr;
	RUN_TEST(tr,TestStopsDatabase);
	//RUN_TEST(tr,TestRoute);
	RUN_TEST(tr,TestBus);
	RUN_TEST(tr,TestBusDatabase);
	RUN_TEST(tr,TestDistance);

	WorkWithData();
	//cout << "Hello" << endl;
	return 0;
}
