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
#include <numeric>
#include "router.h"
#include "graph.h"
#include <iterator>
#include "profile.h"
#include <algorithm>

using namespace std;


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
	return R*acos(sin(lat_l)*sin(lat_r)+cos(lat_l)*cos(lat_r)*cos(abs(lon_l-lon_r)));
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

	const unordered_map<string,double>& GetMapOfDists() const{
		return distances_to_other_stops;
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
	const unordered_map<string,StopPtr>& GetStops() const{
			return stops_;
		}

	size_t Size() const{
		return stops_.size();
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

using Bus_shared=shared_ptr<Bus>;

class BusesDatabase{
public:
	void Insert(Bus bus){
		//
		//
		buses_[bus.GetName()]=make_shared<Bus>(bus);
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

	const unordered_map<string,Bus_shared>& GetBusPark(){
		return buses_;
	}

	size_t Size()const{
		return buses_.size();
	}
private:
	unordered_map<string,Bus_shared> buses_;
};



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

/*
struct Weight{
	Weight(double w = 0.,string b_f = "",string b_t = "", double w_t = 0., bool i_s = false):
		weight(w),bus_from(b_f),bus_to(b_t),wait_time(w_t),is_start(i_s){}
	double weight;
	string bus_from;
	string bus_to;
//	bool start = false;
	double wait_time = 0.;
	bool is_start = false;
};

Weight operator+(const Weight& l, const Weight& r){
	double w_helper = r.weight+l.weight;
	if(l.bus_to!=r.bus_from){
		w_helper+=r.wait_time;
	}
	bool b_helper=r.is_start ? true : false;
	return Weight({w_helper,l.bus_from,r.bus_to,r.wait_time,b_helper});
}
bool operator<(const Weight& l, const Weight& r){
	return l.weight<r.weight;
}
bool operator==(const Weight& l, const Weight& r){
	return 	l.weight==r.weight;
}
bool operator<=(const Weight& l, const Weight& r){
	return (l<r)||(l==r);
}
bool operator>(const Weight& l, const Weight& r){
	return !(l<=r);
}
bool operator>=(const Weight& l, const Weight& r){
	return !(l<r);
}

struct Hasher{
	size_t operator()(const Weight& w) const{
		size_t a = s_hasher(w.bus_from);
		size_t b = s_hasher(w.bus_to);
		size_t c = d_hasher(w.weight);
		size_t x = 997;
		return x*x*a+x*b+c;
	}
	hash<string> s_hasher;
	hash<double> d_hasher;
};
*/

struct Double_2{
	Double_2(double t = 0., int s_c = 0, string b = ""):time_(t),stop_count(s_c),bus(b){}
	double time_;
	int stop_count;
	string bus;
};

bool operator<(const Double_2& l, const Double_2& r){
	return l.time_<r.time_;
}
bool operator==(const Double_2& l, const Double_2& r){
	return l.time_==r.time_;
}
bool operator<=(const Double_2& l, const Double_2& r){
	return (l<r)||(l==r);
}
bool operator>=(const Double_2& l, const Double_2& r){
	return !(l<r);
}
bool operator>(const Double_2& l, const Double_2& r){
	return !(l<=r);
}

bool operator<(const Double_2& l, const int& r){
	return l.time_<r;
}
bool operator==(const Double_2& l, const int& r){
	return l.time_==r;
}
bool operator<=(const Double_2& l, const int& r){
	return (l<r)||(l==r);
}
bool operator>=(const Double_2& l, const int& r){
	return !(l<r);
}
bool operator>(const Double_2& l, const int& r){
	return !(l<=r);
}

Double_2 operator+(const Double_2& l, const Double_2& r){
	return {(l.time_+r.time_),(l.stop_count+r.stop_count)};
}

enum Type{
	wait,
	bus
};
struct Data{
	string stop_name;
	Type type;
};

bool operator==(const Data& l, const Data& r){
	return (l.stop_name==r.stop_name)&&(l.type==r.type);
}

struct Hasher{
	size_t operator()(const Data& obj)const{
		size_t a = s_hasher(obj.stop_name);
		size_t b = i_hasher(obj.type);
		size_t x = 997;
		return x*a+b;
	}
	hash<string> s_hasher;
	hash<int> i_hasher;
};

void ProcessJson(istream& input = cin,ostream& output = cout){
	LOG_DURATION("from the begin");

	auto Doc = Json::Load(input);
	auto root = Doc.GetRoot().AsMap();

	    StopsDatabase stops;
		BusesDatabase buses;

		//
		//
		//
		auto root_settings = root["routing_settings"].AsMap();
		double bus_velocity = (root_settings["bus_velocity"].AsDouble())*1000./60.;
		double wait_time = root_settings["bus_wait_time"].AsDouble();

		//
	//	cerr << bus_velocity << " " << wait_time << endl;
		//

		auto base_requests = root["base_requests"].AsArray();

		for(auto request: base_requests){
				auto map_request = request.AsMap();
				if(map_request["type"].AsString()=="Stop"){
					stops.Insert(Stop(map_request["name"].AsString(),
							Coordinates(map_request["latitude"].AsDouble(),map_request["longitude"].AsDouble())));
					if(map_request.count("road_distances") == 1 ){//&& !map_request["road_distances"].AsMap().empty()){
						for(auto [stop,dist]: map_request["road_distances"].AsMap()){
							stops.InsertDist(map_request["name"].AsString(),
									stop, dist.AsDouble());
						}
				}

				}
			}

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


		//////////////////CREATE GRAPH
		LOG_DURATION("from the graph creation");

		vector<Data> stop_by_id;
		unordered_map<Data,size_t,Hasher> id_by_stop;
		//Create vertexes and ids
		for(auto [stop_name,x]: stops.GetStops()){
			if(id_by_stop.count({stop_name,Type::wait}) == 0){
				stop_by_id.push_back({stop_name,Type::wait});
				id_by_stop[{stop_name,Type::wait}]=(stop_by_id.size()-1);
				stop_by_id.push_back({stop_name,Type::bus});
				id_by_stop[{stop_name,Type::bus}]=(stop_by_id.size()-1);
			}
		}



		//
	//	cerr << "Size" << stop_by_id.size() << endl;
//
		Graph::DirectedWeightedGraph<Double_2> graph(stop_by_id.size());
		/////////////////////////////////

		LOG_DURATION("from put edges");

		double dist,time,sum;

		auto buses_park = buses.GetBusPark();

		for(auto [bus,bus_ptr]: buses_park){

			vector<double> dists;
			auto stops_for_bus = bus_ptr->GetRoute();
			dists.reserve(stops_for_bus.size());

			for(int i = 0; i < static_cast<int>(stops_for_bus.size()); i++){

				//
		//		cerr << "\n STOP IS " << stops_for_bus[i]->GetName() << endl << endl;
				//
				graph.AddEdge({id_by_stop[{stops_for_bus[i]->GetName(),Type::wait}],
					id_by_stop[{stops_for_bus[i]->GetName(),Type::bus}], {wait_time, 0,bus}});
				//
			//	cerr << stops_for_bus[i]->GetName() << " wait - bus " << wait_time << endl;
				//

				if(i > 0){
					dist = stops.GetStop(stops_for_bus[i-1]->GetName()).value()->GetDistTo(stops_for_bus[i]->GetName()).value();
					time = dist/bus_velocity;
					dists.push_back(time);
					//
			//		cerr << " dist is " << dist << " bus_velocity is " << bus_velocity  << " time is " << time << endl;
					//


					for(int j = 0; j < i; j++){
						sum = 0.;
						auto it=dists.begin();
						advance(it,j);
						sum = accumulate(it,dists.end(),sum);
						//
				//							cerr << "from: " << stops_for_bus[j]->GetName() << " to: "
					//								<< stops_for_bus[i]->GetName() << " time: " <<   sum <<
						//							 " stops_count: " << (i-j) << endl;
											//
						//
						//cerr <<  "accumulate: " << accumulate(it,dists.end(),sum) << endl;
						//
						graph.AddEdge({id_by_stop[{stops_for_bus[j]->GetName(),Type::bus}],
							id_by_stop[{stops_for_bus[i]->GetName(),Type::wait}], {sum,(i-j),bus}});
					}

				}
			}
		}


		//
		cerr << " Vertex:  " << graph.GetVertexCount() << " Edge: " << graph.GetEdgeCount() << endl;
		//


			//////////////
			Graph::Router<Double_2> router(graph);

		//
		cerr << stop_by_id.size() << " " << id_by_stop.size() << endl;
		//for(auto x: stop_by_id){
			//cout << x << "  id_by_stop " << id_by_stop[x] << endl;
//		}

		//

		LOG_DURATION("stat_requests");

		///////////////////
		auto stat_requests = root["stat_requests"].AsArray();

		output << "[\n";
		for(int i = 0 ;i < static_cast<int>(stat_requests.size()); i++ ){
			auto request = stat_requests[i].AsMap();
			//
			//cerr << "id:  " << request["id"].AsDouble() << endl;
			//
			output << "{\n" << "\"request_id\": " << static_cast<int>(request["id"].AsDouble()) << ",\n";

			if(request["type"].AsString()=="Bus"){
				///////////////////////////
				auto bus = buses.GetBus(request["name"].AsString());
				if(bus.has_value()){
					output << "\"stop_count\": " << bus.value().GetNumberOfStops() << ",\n";
					output << "\"unique_stop_count\": " << bus.value().GetUniqueNumberOfStops() << ",\n " ;
					double len = bus.value().CalculateFullDistance();
					int len_int=static_cast<int>(len);
					output << "\"route_length\": "<< len_int << ",\n " <<
							"\"curvature\": " << fixed << setprecision(6)
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
			}else if(request["type"].AsString()=="Route"){

				auto from_ = request["from"].AsString();
				auto to_ = request["to"].AsString();

				if(from_ == to_){
					output << "\"total_time\": 0,\n\"items\": []\n";
				}else{

				//
			//	cerr << "hey 1 "   << from_ << "  " << to_<< endl;
				//

					auto built_route = router.BuildRoute(id_by_stop[{from_,Type::wait}],
							id_by_stop[{to_,Type::wait}]);
				//
			//	auto built_route = router.BuildRoute(id_by_stop[from_], id_by_stop[to_]);
				//
			//	cerr << "hey 2 " << built_route.has_value()  << endl;
				//

				if(built_route.has_value()){
					output << "\"items\": [";


					//
				//	cerr << "hey 3" << endl;
					//
					double total_time = built_route.value().weight.time_;

					//
				//	cerr << "hey 4    " << total_time << endl;
					//
					//double local_time = 0.;
					//int span_count = 0;

					//output << "\n{\n\"type\": \"Wait\",\n\"stop_name\": \"" << from_
						//<< "\",\n\"time\": " << wait_time  << "\n},";
					//total_time+=wait_time;

					//
					string str;
//					cerr << "hey 5 "  << endl;
					//
					for(int i = 0; i < static_cast<int>(built_route.value().edge_count); i++){
						auto edge = graph.GetEdge(router.GetRouteEdge(built_route.value().id, i));

						auto from_from = stop_by_id[edge.from];
						auto to_to = stop_by_id[edge.to];


						//
			/*			cerr << static_cast<int>(built_route.value().edge_count) << endl;
												cerr << "from bus " << from_from.bus << " " << "to bus " << to_to.bus <<
														"  from stop " << from_from.stop_name << "  to stop " << to_to.stop_name <<
														"  from " << from_from.type << " to  " << to_to.type <<
														"  stops_count: " << edge.weight.stop_count
														<< " time: "<< edge.weight.time_ << endl;
*/					 							//

						//if((from_from.bus!=to_to.bus) || (i+1 == static_cast<int>(built_route.value().edge_count))){
							if((from_from.type == Type::bus) && (to_to.type == Type::wait)){
					//		output << str;
						//	str.clear();

						//	span_count = (id_by_stop[{to_to.bus,to_to.stop_name,to_to.type}] -
							//		id_by_stop[{from_from.bus,from_from.stop_name,from_from.type}])/2;
/*							if((i+1 == static_cast<int>(built_route.value().edge_count))){
								local_time+=edge.weight;
								span_count++;
							}*/

							output << str;
							str.clear();
							output << "\n{\n\"type\": \"Bus\",\n" << "\"bus\": \"";
							output << edge.weight.bus;
							output << "\",\n\"span_count\": ";
							//output << (span_count);
							output << edge.weight.stop_count;
							output << (",\n\"time\": ");
							output << edge.weight.time_ << "\n}";
							str.append(",");
							//local_time = 0.;
							//span_count=0;
						//	continue;
							//continue;
							//continue;

						}else if(from_from.type==Type::wait && to_to.type==Type::bus){

							output << str;
							str.clear();
							output << "\n{\n\"type\": \"Wait\",\n\"stop_name\": \"";
							output << from_from.stop_name;
							output << "\",\n\"time\": ";
							output << edge.weight.time_;
							output << "\n}";
							//output << ",";
							str.append(",");
						//	span_count = 0;
							//local_time = 0.;
							//continue;
						}


						//local_time+=edge.weight;
						//span_count++;
						//intersect_was = intersect;
					}
					output << "\n],\n\"total_time\": " << total_time << "\n";
				}else{
					output << "\"error_message\": \"not found\"\n";
				}
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


void TestJson(){
	{
		ifstream input("test2.txt");
		ProcessJson(input);
	}
}



int main(){
	TestRunner tr;
	RUN_TEST(tr,TestStopsDatabase);
	//RUN_TEST(tr,TestRoute);
	RUN_TEST(tr,TestBus);
	RUN_TEST(tr,TestBusDatabase);
	RUN_TEST(tr,TestDistance);
	RUN_TEST(tr,TestJson);


	ProcessJson();

	//WorkWithData();!!!!!!!!!!!!!!!!!!!!!

	return 0;
}
