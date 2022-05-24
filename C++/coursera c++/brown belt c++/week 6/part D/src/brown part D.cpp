#include <iostream>
#include "test_runner.h"
#include "json.h"
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
#include <utility>
#include <fstream>
#include <sstream>

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
	void SetCoordinates(Coordinates coords){
		coords_=coords;
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

	void InsertDist(string stop, double dist, bool flag){
		if(distances_to_other_stops.count(stop)==0 || flag){
			distances_to_other_stops[stop] = dist;
		}
	}

	optional<double> GetDistTo(string stop_to) const{
		if(distances_to_other_stops.count(stop_to)==0){
			return nullopt;
		}
		return distances_to_other_stops.at(stop_to);
	}
private:
	string name_;
	Coordinates coords_;
	set<string> buses_;
	unordered_map<string,double> distances_to_other_stops;
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
		if(stops_.count(stop.GetName())==0){
			stops_[stop.GetName()]=make_shared<Stop>(stop);
		}else{
			stops_[stop.GetName()]->SetCoordinates(stop.GetCoordinates());
		}
	}

	void InsertDist(string stop_from, string stop_to, double dist){
		stops_[stop_from]->InsertDist(stop_to, dist, true);
		if(stops_.count(stop_to)==0){
			stops_[stop_to]=make_shared<Stop>(Stop(stop_to,Coordinates()));
		}
		stops_[stop_to]->InsertDist(stop_from, dist, false);
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
	double CalculateFullDistance(){
		double result = 0.;
		for(int i = 0; i+1 < static_cast<int>(route_.size()); i++){
			auto dist = route_[i]->GetDistTo(route_[i+1]->GetName());
			if(dist.has_value()){
				//
				//cout << "WE ARE HERE" << endl;
				//
				result+=dist.value();
			}else{
				result+=Distance(route_[i]->GetCoordinates(),route_[i+1]->GetCoordinates());
			}
		}
		return result;
	}
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
	size_t pose;
	vector<pair<string,string>> bus_requests;
	for(int i = 0; i < Q; i++){
		input >> helper;
		if(helper == "Stop"){
			getline(input,name,':');
			ParseName(name);
			getline(input,helper,',');
			num_1 = stod(helper);
		//	cout << "Hello1" << endl;
			getline(input,helper);
			pose=helper.find(',');
			if(pose==helper.npos){
				num_2 = stod(move(helper));
				helper.clear();
			}else{
				num_2 = stod(helper.substr(0, pose));
				helper.erase(0,pose+1);
			}

			//
			//cout << "Hello2" << endl;
	//	cout << num_1 << " " << num_2 << "  " << helper.empty() << " " << helper <<  endl;
			//
		//	cout << "__" << name << "__" << endl;
			//
			stops.Insert(Stop(move(name),Coordinates(num_1,num_2)));

			while(!helper.empty()){
				string new_helper;//Stop X: latitude, longitude, D1m to stop1, D2m to stop2,

				pose = helper.find('m');
				num_1 = stod(helper.substr(0, pose));
				//
			//	cout << " num_1 " << num_1  << " helper: " << helper << endl;
				//
				helper.erase(0,pose+1);

				pose = helper.find('o');
				helper.erase(0,pose+1);

				pose = helper.find(',');
				new_helper = helper.substr(0, pose);
				ParseName(new_helper);

				//
			//	cout << new_helper << endl;
				//

				stops.InsertDist(name, new_helper, num_1);
				if(pose!=helper.npos){
					helper.erase(0,pose+1);
				}else{
					break;
				}
			}

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
						bus.value().GetUniqueNumberOfStops() << " unique stops, " ;
				double len = bus.value().CalculateFullDistance();
				//
				//cout << "\n\n\n" << len << "  "  << bus.value().GetLength() <<"\n\n\n" << endl;
				//
				int len_int=static_cast<int>(len);
				output << len_int << " route length, "<< fixed << setprecision(6)
						<< (len/bus.value().GetLength()) << " curvature\n";

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

void ProcessJson(istream& input = cin,ostream& output = cout){


	auto Doc = Json::Load(input);
	auto root = Doc.GetRoot().AsMap();
	/*
	cout << root.size() << " " << root.begin()->first << endl;
	cout << root.begin()->second.AsArray().size();
	cout << "\n\n\n\n\n";
	auto arr = root["base_requests"].AsArray();
	auto dict_1 = arr[0].AsMap();
	cout << "dict_1:  " << dict_1.size() << endl;
	for(auto x: dict_1){
		cout << x.first << " ";
	}
	cout << endl;
	for(auto x: arr){
		auto b = x.AsMap();
		cout << b["name"].AsString() << "  ";
	}
	cout << endl;

	auto arr_0 = root["stat_requests"].AsArray();
	cout << "arr_0 size: " << arr_0.size() << endl;

*/
	cerr << "okey 0" << endl;
	    StopsDatabase stops;
		BusesDatabase buses;

		auto base_requests = root["base_requests"].AsArray();
//
		cerr << "okey 1" << endl;
	//
		for(auto request: base_requests){
				auto map_request = request.AsMap();
				//
						cerr << "okey 1_" << endl;
					//
				if(map_request["type"].AsString()=="Stop"){
					//
											cerr << "okey 1_!" << endl;
										//
					stops.Insert(Stop(map_request["name"].AsString(),
							Coordinates(map_request["latitude"].AsDouble(),map_request["longitude"].AsDouble())));
					//
					for(auto [key,val]: map_request["road_distances"].AsMap()){
						cerr << key  << endl;
					}
					//
					if(!map_request["road_distances"].AsMap().empty()){
						//
												cerr << "okey 1_!!" << endl;
											//
						for(auto [stop,dist]: map_request["road_distances"].AsMap()){
							stops.InsertDist(map_request["name"].AsString(),
									stop, (dist.AsInt()+0.));
						}
					}
				}
			}
			cerr << "okey 2" << endl;
			for(auto request: base_requests){
				auto map_request = request.AsMap();
				if(map_request["type"].AsString()=="Bus"){
					Bus bus(map_request["name"].AsString());
					auto stops_ = map_request["stops"].AsArray();
					for(auto stop: stops_){
						bus.push_back(stops.GetStop(stop.AsString()).value());
					}
					if(!map_request["is_roundtrip"].AsBool()){
						for(int i = (static_cast<int>(stops_.size())-2); i >=0 ; i--){
							bus.push_back(stops.GetStop(stops_[i].AsString()).value());
						}
					}
					buses.Insert(move(bus));
				}
			}

			cerr << "okey 3" << endl;
		auto stat_requests = root["stat_requests"].AsArray();

		output << "[\n";
		for(int i = 0 ;i < static_cast<int>(stat_requests.size()); i++ ){
			auto request = stat_requests[i].AsMap();
			output << "{\n" << "\"request_id\": " << request["id"].AsInt() << ",\n";

			if(request["type"].AsString()=="Bus"){
				///////////////////////////
				auto bus = buses.GetBus(request["name"].AsString());
				if(bus.has_value()){
					output << "\"stop_count\": " << bus.value().GetNumberOfStops() << ",\n";
					output << "\"unique_stop_count\": " << bus.value().GetUniqueNumberOfStops() << ",\n " ;
					double len = bus.value().CalculateFullDistance();
					int len_int=static_cast<int>(len);
					output << "\"route_length\": "<< len_int << ",\n " <<
							"\"curvature\": " << fixed << setprecision(10)
							<< (len/bus.value().GetLength()) << "\n ";
				}
				else{
					output << "\"error_message\": \"not found\"\n";
				}

				////////////////////
			}else if(request["type"].AsString()=="Stop"){
				auto stop = stops.GetStop(request["name"].AsString());

				if(stop.has_value()){
					output << "\"buses\": [";
					if(stop.value()->HasBuses()){
						string str_;
						for(auto bs: stop.value()->GetBuses()){
							str_.append("\n\"");
							str_.append(bs);
							str_.append("\"");
							str_.append(",");
						}
						str_.pop_back();
						output << str_ <<  "\n";
					}
						output << "]\n";
				}
				else{
					output << "\"error_message\": \"not found\"\n";
				}
			}

			output << "}";
			if(i < (static_cast<int>(stat_requests.size()) - 1)){
				output << ",";
			}
			output << "\n";
		}
		output << "]\n";




}


/*void TestJson(){
	{
		ifstream input("json.txt");
		ProcessJson(input);
	}
}
*/


int main(){
	TestRunner tr;
	RUN_TEST(tr,TestStopsDatabase);
	//RUN_TEST(tr,TestRoute);
	RUN_TEST(tr,TestBus);
	RUN_TEST(tr,TestBusDatabase);
	RUN_TEST(tr,TestDistance);
	//RUN_TEST(tr,TestJson);



	ProcessJson();

	//WorkWithData();!!!!!!!!!!!!!!!!!!!!!

	return 0;
}
