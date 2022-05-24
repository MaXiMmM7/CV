#include "test_runner.h"
#include "profile.h"
#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <string>
#include <cstdint>
using namespace std;


class Client{
public:
	Client(const int64_t& id,const int64_t& t):ID(id),time_(t){}
	int64_t GetID()const{return ID;}
	int64_t GetTime() const {return time_;}
private:
	unsigned int ID;
	int64_t time_;
};

bool operator <(const Client& l,const Client& r){
	return  l.GetTime()!=r.GetTime() ? l.GetTime()<r.GetTime() : l.GetID()<r.GetID();
}

/*
ostream& operator <<(ostream& stream,Client& cl){
	return stream << cl.GetID() << ": " << cl.GetTime();
}*/

class Booking{
public:
	void Book(const int64_t& t,const string& hotel,
			const int64_t& id, const int64_t& rooms ){
		current_time=t;
		Clear(hotel);
		time[hotel].push(t);
		hotels_rooms[hotel].push(rooms);
		hotels_count_of_rooms[hotel]+=rooms;
		if(hotels_clients[hotel].count(Client(id,clients_time[hotel][id]))!=0){
			hotels_clients[hotel].erase(Client(id,clients_time[hotel][id]));
		}
        hotels_clients[hotel].insert(Client(id,t));
		clients_time[hotel][id]=t;
		/*//
		cerr << hotel << ":" << hotels_clients[hotel].size() << endl;
		for(auto x:hotels_clients[hotel]){
			cerr << x << " , ";
		}
		cerr << endl;
		//*/

	}
	int64_t Clients(const string& hotel){
		Clear(hotel);
		return static_cast<int64_t>(hotels_clients[hotel].size());
	}

	//uint16_t Rooms(const string& hotel){
	int64_t Rooms(const string& hotel){
	Clear(hotel);
		return hotels_count_of_rooms[hotel];
	}
private:
	int64_t current_time; // текущее время
	map<string,queue<int64_t>> time; // отель - очередь из моментов времени когда там была бронь
    map<string,queue<int64_t>> hotels_rooms; // отель - очередь из комнат
	map<string,int64_t> hotels_count_of_rooms; // отель - общее число комнат
    map<string,set<Client>> hotels_clients; // отель - множество клиентов
    map<string,map<unsigned int,int64_t>> clients_time; // отель - клиент и  последнее время заказа в нем

	void Clear(const string& hotel){
		while(!time[hotel].empty()&&time[hotel].front() <= current_time - 86400){
			time[hotel].pop();
			hotels_count_of_rooms[hotel]-=hotels_rooms[hotel].front();
			hotels_rooms[hotel].pop();
		}
		while(!hotels_clients[hotel].empty()&&
				(*hotels_clients[hotel].begin()).GetTime() <= current_time - 86400){
				hotels_clients[hotel].erase(hotels_clients[hotel].begin());
	}
	}
};

	void Test(){

		LOG_DURATION("Test");
		{
			Booking book;
			ASSERT_EQUAL(book.Rooms("Marriott"), 0);
			ASSERT_EQUAL(book.Clients("Marriott"), 0);
			book.Book(10,"FourSeasons",1,2);
			book.Book(10,"Marriott",1,1);
			book.Book( 86409, "FourSeasons", 2, 1);
			ASSERT_EQUAL(book.Clients("FourSeasons"), 2);
			ASSERT_EQUAL(book.Rooms("FourSeasons"), 3);
			ASSERT_EQUAL(book.Clients("Marriott"), 1);
	        book.Book(86410, "Marriott" ,2, 10);
			ASSERT_EQUAL(book.Rooms("FourSeasons"), 1);
			ASSERT_EQUAL(book.Rooms("Marriott"), 10);
		}
		{
			Booking b;
			b.Book(0, "a", 0, 1);
			b.Book(1, "a", 1, 2);
			b.Book(86400, "a", 1, 3);
			ASSERT_EQUAL(b.Clients("a"), 1);
			ASSERT_EQUAL(b.Rooms("a"), 5);

		}
		{
			//just one client
			Booking b;
			b.Book(0, "a", 0, 1);
			b.Book(1, "a", 0, 2);
			b.Book(2, "a", 0, 1);
			b.Book(3, "b", 0, 1);
			ASSERT_EQUAL(b.Clients("a"), 1);
			ASSERT_EQUAL(b.Rooms("a"), 4);
			ASSERT_EQUAL(b.Clients("b"), 1);
			ASSERT_EQUAL(b.Rooms("b"), 1);
		}
		{
			Booking b;
			b.Book(0, "a", 0, 1);
					b.Book(86400, "a", 1, 2);
					b.Book(86401, "a", 0, 1);
					ASSERT_EQUAL(b.Clients("a"), 2);
			     	ASSERT_EQUAL(b.Rooms("a"), 3);

					b.Book(86400*2, "a", 0, 1);
					ASSERT_EQUAL(b.Clients("a"), 1);
					ASSERT_EQUAL(b.Rooms("a"), 2);
					ASSERT_EQUAL(b.Clients("b"), 0);
							     	ASSERT_EQUAL(b.Rooms("b"), 0);

		}
		{
			//negative
			Booking b;
					b.Book(-86400*2, "a", 0, 1);
							b.Book(-86401, "a", 1, 2);
							b.Book(-86400, "a", 0, 1);
							ASSERT_EQUAL(b.Clients("a"), 2);
					     	ASSERT_EQUAL(b.Rooms("a"), 3);

							b.Book(0, "a", 0, 1);
							ASSERT_EQUAL(b.Clients("a"), 1);
							ASSERT_EQUAL(b.Rooms("a"), 1);
							ASSERT_EQUAL(b.Clients("b"), 0);
									     	ASSERT_EQUAL(b.Rooms("b"), 0);
		}
		{
			//at the same time
			Booking b;
			b.Book(10, "FourSeasons", 1, 2);
			b.Book(10, "FourSeasons", 1, 4);
			ASSERT_EQUAL(b.Clients("FourSeasons"), 1);
			ASSERT_EQUAL(b.Rooms("FourSeasons"), 6);

		}
		{
			Booking b;
			b.Book(0, "a", 0, 1);
			b.Book(1, "a", 1, 2);
			b.Book(86400, "a", 1, 3);
			ASSERT_EQUAL(b.Clients("a"), 1);
			ASSERT_EQUAL(b.Rooms("a"), 5);
		}

		{
					Booking b;
					b.Book(0, "a", 0, 1);
					b.Book(1, "a", 1, 2);
					b.Book(86401, "B", 1, 3);
					ASSERT_EQUAL(b.Clients("a"), 0);
					ASSERT_EQUAL(b.Rooms("a"), 0);
					ASSERT_EQUAL(b.Clients("B"), 1);
				    ASSERT_EQUAL(b.Rooms("B"), 3);

				}

		{
			Booking b;

			ASSERT_EQUAL(b.Rooms("a"),0);
			ASSERT_EQUAL(b.Clients("a"),0);

			ASSERT_EQUAL(b.Rooms("b"),0);
			ASSERT_EQUAL(b.Clients("c"),0);

			b.Book(-100000,"a",100000,1000);
			b.Book(-100000,"a",100003,1000);
			b.Book(-100000,"b",100002,1000);
			ASSERT_EQUAL(b.Rooms("a"),2000);
			ASSERT_EQUAL(b.Clients("a"),2);

			b.Book(-10000,"a",100002,1000);
			ASSERT_EQUAL(b.Rooms("a"),1000);
			ASSERT_EQUAL(b.Clients("a"),1);
			ASSERT_EQUAL(b.Rooms("b"),0);
			ASSERT_EQUAL(b.Clients("b"),0);

		}

	}
	void TestAll(){
		TestRunner tr;
		RUN_TEST(tr,Test);
	}


	void TestTime(){
		//q 10^5 time 2*10^18, hotels 10^9,client 10^9 , room 1000
		{
			LOG_DURATION("Q=10^5 1 hotel");
			Booking book;
			int k=1;
			for (int i=0;i<30000;i++){
				book.Book(i,"a",i*1000,k);
				if(k==1000){k=0;}
				k++;
			}
			for (int i=0;i<30000;i++){
							book.Clients("a");
						}

			for (int i=0;i<30000;i++){
							book.Rooms("a");
						}
		}

		{
					LOG_DURATION("Q=10^5 10 hotel");
					Booking book;
					int k=1;
					for (int i=0;i<10000;i++){
						book.Book(i,"a",i*1000,k);
						if(k==1000){k=0;}
						k++;
					}
					for (int i=0;i<10000;i++){
											book.Book(i,"b",i*1000,k);
											if(k==1000){k=0;}
											k++;
										}
					for (int i=0;i<10000;i++){
											book.Book(i,"c",i*1000,k);
											if(k==1000){k=0;}
											k++;
										}
					for (int i=0;i<10000;i++){
											book.Book(i,"d",i*1000,k);
											if(k==1000){k=0;}
											k++;
										}
					for (int i=0;i<10000;i++){
											book.Book(i,"r",i*1000,k);
											if(k==1000){k=0;}
											k++;
										}
					for (int i=0;i<10000;i++){
											book.Book(i,"m",i*1000,k);
											if(k==1000){k=0;}
											k++;
										}
					for (int i=0;i<10000;i++){
											book.Book(i,"q",i*1000,k);
											if(k==1000){k=0;}
											k++;
										}
					for (int i=0;i<10000;i++){
											book.Book(i,"p",i*1000,k);
											if(k==1000){k=0;}
											k++;
										}
					for (int i=0;i<10000;i++){
											book.Book(i,"l",i*1000,k);
											if(k==1000){k=0;}
											k++;
										}
					for (int i=0;i<10000;i++){
											book.Book(i,"k",i*1000,k);
											if(k==1000){k=0;}
											k++;
										}
		}
	}
	int main() {
		ios_base::sync_with_stdio(false);
		cin.tie(nullptr);

		TestAll();
        TestTime();
	int Q;
	cin >> Q;
	Booking book;
	string command,hotel;
	int64_t n;
	int64_t r;
	int64_t t;
	for(int i=0;i<Q;i++){
		cin >> command;
		if(command=="BOOK"){
			cin >> t >> hotel >> n >> r;
			book.Book(t,hotel,n,r);
		}
		else if(command=="CLIENTS"){
			cin >> hotel;
			cout << book.Clients(hotel) << "\n";
		}
		else if(command=="ROOMS"){
			cin >> hotel;
			cout << book.Rooms(hotel) << "\n";
		}
	}
		return 0;
	}
