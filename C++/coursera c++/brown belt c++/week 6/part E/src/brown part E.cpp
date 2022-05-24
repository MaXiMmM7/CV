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
#include "router.h"
#include "graph.h"
#include <iterator>
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
//	bool is_round_trip;
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

	size_t Size() const{
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


struct BusStop{
	BusStop(string b, string s, int n = 1 ):bus(b),stop(s),number(n){}
	string bus;
	string stop;
	int number;
};

bool operator==(const BusStop& l, const BusStop& r){
	return (l.bus==r.bus)&&(l.stop==r.stop)&&(l.number==r.number);
}

struct BusStopHasher{
	size_t operator()(const BusStop& obj) const{
		size_t a = hasher(obj.stop);
		size_t b = hasher(obj.bus);
		size_t c = int_hasher(obj.number);
		size_t x = 997;
		return c*x*x+a*x+b;
	}

	hash<string> hasher;
	hash<int> int_hasher;
};

void ProcessJson(istream& input = cin,ostream& output = cout){

	auto Doc = Json::Load(input);
	auto root = Doc.GetRoot().AsMap();

	    StopsDatabase stops;
		BusesDatabase buses;

		//
		//
		//
		double bus_velocity,wait_time;
		if(root.count("routing_settings") == 1){
		auto root_settings = root["routing_settings"].AsMap();
		 bus_velocity = (root_settings["bus_velocity"].AsDouble())*1000./60.;
		wait_time = root_settings["bus_wait_time"].AsDouble();

		cerr << bus_velocity << " " << wait_time << endl;
		//
		}

		auto base_requests = root["base_requests"].AsArray();

		for(auto request: base_requests){
				auto map_request = request.AsMap();
				if(map_request["type"].AsString()=="Stop"){
					//
					cerr << map_request["name"].AsString() << endl;
					//
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
					//
					cerr <<  map_request["name"].AsString() << endl;
					//
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
		Graph::DirectedWeightedGraph<double> graph(stops.Size()*buses.Size()*10);
		vector<BusStop> stop_by_id;
		unordered_map<BusStop,size_t,BusStopHasher> id_by_stop;


		//
		cerr << "buse size: " << buses.Size() << " stops size: " << stops.Size() << endl;
		cerr << "helper 1" << endl;
		//
		double dist,time;
		size_t helper_id(0);
		auto buses_park = buses.GetBusPark();
		for(auto [bus,bus_ptr]: buses_park){
			auto stops_for_bus = bus_ptr->GetRoute();
			unordered_map<string,int> count_of_copies;
			for(int i = 0; i < static_cast<int>(stops_for_bus.size()); i++){

				//if(i+1!=static_cast<int>(stops_for_bus.size())){
				count_of_copies[stops_for_bus[i]->GetName()]++;
				//}

				if(id_by_stop.count({bus,stops_for_bus[i]->GetName(),count_of_copies[stops_for_bus[i]->GetName()]}) == 0){

					stop_by_id.push_back({bus,stops_for_bus[i]->GetName(),count_of_copies[stops_for_bus[i]->GetName()]});
					id_by_stop[{bus,stops_for_bus[i]->GetName(),count_of_copies[stops_for_bus[i]->GetName()]}]=helper_id++;
					for(int j = 1; j < count_of_copies[stops_for_bus[i]->GetName()]; j++){
						//
						cerr << stop_by_id[id_by_stop[{bus,stops_for_bus[i]->GetName(),count_of_copies[stops_for_bus[i]->GetName()]}]].number  << "  " <<
							stop_by_id[id_by_stop[{bus,stops_for_bus[i]->GetName(),j}]].number << endl;

						//
						graph.AddEdge({id_by_stop[{bus,stops_for_bus[i]->GetName(),
							count_of_copies[stops_for_bus[i]->GetName()]}],
							id_by_stop[{bus,stops_for_bus[i]->GetName(),j}], wait_time});
						graph.AddEdge({id_by_stop[{bus,stops_for_bus[i]->GetName(),j}],
							id_by_stop[{bus,stops_for_bus[i]->GetName(),
							count_of_copies[stops_for_bus[i]->GetName()]}], wait_time});
					}
				}




				//
			cerr <<"i = " << i << " bus "  << bus << " name" << stops_for_bus[i]->GetName()
						<< " with id: " <<  id_by_stop[{bus,stops_for_bus[i]->GetName(),
					count_of_copies[stops_for_bus[i]->GetName()]}]
			   << " number: " << stop_by_id[id_by_stop[{bus,stops_for_bus[i]->GetName(),count_of_copies[stops_for_bus[i]->GetName()]}]].number <<
													   endl;
							//

				if(i > 0){
					dist = stops.GetStop(stops_for_bus[i-1]->GetName()).value()->GetDistTo(stops_for_bus[i]->GetName()).value();
					time = dist/bus_velocity;
					size_t id1 = id_by_stop[{bus,stops_for_bus[i-1]->GetName(),
						count_of_copies[stops_for_bus[i-1]->GetName()]}];
					size_t id2;
					id2 = id_by_stop[{bus,stops_for_bus[i]->GetName(),
						count_of_copies[stops_for_bus[i]->GetName()]}];
					graph.AddEdge({id1,id2, time});
					}
				}
			}


		auto stops_helper = stops.GetStops();
		for(auto [stop_name,stop_ptr]: stops_helper){
			vector<string> stop_buses_book(stop_ptr->GetBuses().begin(),stop_ptr->GetBuses().end());
			for(int i = 0; i+1 < static_cast<int>(stop_buses_book.size()); i++){
				for(int j = i+1; j < static_cast<int>(stop_buses_book.size()); j++){
					int i_start = 1;
					while(id_by_stop.count({stop_buses_book[i],stop_name,i_start})==1){
						int j_start =1;
						while(id_by_stop.count({stop_buses_book[j],stop_name,j_start}) == 1){
							graph.AddEdge({(id_by_stop[{stop_buses_book[i],stop_name,i_start}]),
								id_by_stop[{stop_buses_book[j],stop_name,j_start}], wait_time});
							graph.AddEdge({(id_by_stop[{stop_buses_book[j],stop_name,j_start}]),
								id_by_stop[{stop_buses_book[i],stop_name,i_start}], wait_time});
							j_start++;
						}
						i_start++;
					}
					//
				//	cerr << "stop: " << stop_name << "  bus1: " << stop_buses_book[i] <<
					//		" bus2: " << stop_buses_book[j] << endl;
					//
				}
			}
		}

		Graph::Router<double> router(graph);

		//
		cerr <<"Sizes: " << stop_by_id.size() << " " << id_by_stop.size() << endl;
		//for(auto x: stop_by_id){
			//cout << x << "  id_by_stop " << id_by_stop[x] << endl;
//		}

		//

		///////////////////
		auto stat_requests = root["stat_requests"].AsArray();

		output << "[\n";
		for(int i = 0 ;i < static_cast<int>(stat_requests.size()); i++ ){
			auto request = stat_requests[i].AsMap();
			//
		//	cerr << "id:  " << request["id"].AsDouble() << endl;
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


				auto book_from = stops.GetStop(from_).value()->GetBuses();
				auto book_to = stops.GetStop(to_).value()->GetBuses();

				if((!book_from.empty())&&(!book_to.empty())){

					auto built_route = router.BuildRoute(id_by_stop[{*book_from.begin(),from_}],
							id_by_stop[{*book_to.begin(),to_}]);

				for(auto from_bus: book_from){
					for(auto to_bus: book_to){
						int i_start=1;
						while(id_by_stop.count({from_bus,from_,i_start}) == 1){
							int j_start = 1;
							while(id_by_stop.count({to_bus,to_,j_start}) == 1){
								auto helper = router.BuildRoute(id_by_stop[{from_bus,from_,i_start}],
										id_by_stop[{to_bus,to_,j_start}]);
								if(helper.has_value()){
									if(built_route.has_value()){
										if(helper.value().weight < built_route.value().weight){
											built_route = helper;
										}
									}else{
										built_route = helper;
									}
								}
								j_start++;
							}
							i_start++;

						}
					}
				}




				if(built_route.has_value()){


					output << "\"items\": [";

					double total_time = built_route.value().weight;

					double local_time = 0.;
					int span_count = 0;

					output << "\n{\n\"type\": \"Wait\",\n\"stop_name\": \"" << from_
							<< "\",\n\"time\": " << wait_time  << "\n},";
					total_time+=wait_time;



					for(int i = 0; i < static_cast<int>(built_route.value().edge_count); i++){
						auto edge = graph.GetEdge(router.GetRouteEdge(built_route.value().id, i));

						//
					/*	cerr << "edge:  " << stop_by_id[edge.from].bus << " " << stop_by_id[edge.from].number <<
								" " << stop_by_id[edge.from].stop << " to:  " <<
								stop_by_id[edge.to].bus << " " <<  stop_by_id[edge.to].number << " " <<
								stop_by_id[edge.from].stop << " weight: " << edge.weight << endl;
					*/
						//
						cerr << "i is  " << i << endl;
						//
						if((stop_by_id[edge.from].bus!=stop_by_id[edge.to].bus) ||
								((stop_by_id[edge.from].stop == stop_by_id[edge.to].stop) &&
										(stop_by_id[edge.from].number!=stop_by_id[edge.to].number))){

							//
							//
							if(i != 0){
					//		output << str;
						//	str.clear();
							output << "\n{\n\"type\": \"Bus\",\n" << "\"bus\": \"";
							output << stop_by_id[edge.from].bus;
							output << "\",\n\"span_count\": ";
							output << (span_count);
							span_count=0;
							output << (",\n\"time\": ");
							output << local_time << "\n}";
							local_time = 0.;


							output << ",\n{\n\"type\": \"Wait\",\n\"stop_name\": \"";
							output << stop_by_id[edge.from].stop;
							output << "\",\n\"time\": ";
							output << wait_time;
							output << "\n}";
							output << ",";

							if(i+1 != static_cast<int>(built_route.value().edge_count)){
							continue;
							}
							}else{
								total_time-=wait_time;
							}
						//	total_time+=wait_time;
						}

						if(i+1 == static_cast<int>(built_route.value().edge_count)){
//							output << str;
	//						str.clear();
							output << "\n{\n\"type\": \"Bus\",\n" << "\"bus\": \"";
							output << stop_by_id[edge.from].bus;
							output << "\",\n\"span_count\": ";
							output << (span_count+1);
							span_count=0;
							output << (",\n\"time\": ");
							output << (local_time+edge.weight) << "\n}";
							break;
						}

						local_time+=edge.weight;
						span_count++;
						//intersect_was = intersect;


					}
					output << "\n],\n\"total_time\": " << total_time << "\n";
				}else{
					output << "\"error_message\": \"not found\"\n";
				}
				}
				else{
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
		ifstream input("test3.txt");
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
	//RUN_TEST(tr,TestJson);


	ProcessJson();

	//WorkWithData();!!!!!!!!!!!!!!!!!!!!!

	return 0;
}
