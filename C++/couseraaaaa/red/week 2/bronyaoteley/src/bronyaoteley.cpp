#include "profile.h"
#include "test_runner.h"
#include <string>
#include <queue>
#include <iostream>
#include <map>
#include <set>
using namespace std;

class Client{
public:
	Client(const unsigned int& id,const int64_t& t):id_(id),t_(t){}
	int64_t GetTime() const {return t_;}
	unsigned int GetId() const {return id_;}
private:
	unsigned int id_;
    int64_t t_;
   };

bool operator <(const Client& l,const Client& r){
	return l.GetTime()<r.GetTime();
}



class Booking{
public:
	void Book(const int64_t& time,const string& hotel,const unsigned int& name,const int& count){
		current_time = time;
		Do(hotel);
		time_[hotel].push(time);
		hotels_rooms_[hotel].push(count);
		hotels_ROOMS_[hotel]+=count;
		if(hotels_clients_[hotel].count(Client(name,clients[hotel][name]))==0){
			hotels_CLIENTS_[hotel]++;
		}
		else{
			hotels_clients_[hotel].erase(Client(name,clients[hotel][name]));
			}
		hotels_clients_[hotel].insert(Client(name,time));
		clients[hotel][name]=time;
}
	int Clients(const string& hotel) {
		Do(hotel);
		return hotels_CLIENTS_[hotel];
	}
	int Rooms(const string& hotel) {
		Do(hotel);
		return hotels_ROOMS_[hotel];
				}
	private:
	int64_t current_time=0;
   map<string,int> hotels_ROOMS_;//для количества мест
   map<string,queue<int>>  hotels_rooms_;  //комнаты в отеле
   map<string,queue<int64_t>> time_;
   map<string,set<Client>> hotels_clients_;
   map<string,int> hotels_CLIENTS_;
   map<string,map<unsigned int,int64_t>> clients;
   void Do(const string& hotel){
	   while(!time_[hotel].empty() && time_[hotel].front() <= (current_time - 86400)) {
		   time_[hotel].pop();
		   hotels_ROOMS_[hotel]-=hotels_rooms_[hotel].front();
		   hotels_rooms_[hotel].pop();
   }
	   while(!hotels_clients_[hotel].empty() && (*hotels_clients_[hotel].begin()).GetTime() <= current_time - 86400){
		   hotels_clients_[hotel].erase(hotels_clients_[hotel].begin());
		   hotels_CLIENTS_[hotel]--;
	   }
   }
};

void Test(){
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
}
void TestAll(){
	TestRunner tr;
	RUN_TEST(tr,Test);
}

int main() {
	TestAll();
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
int Q;
cin >> Q;
Booking book;
string command,hotel;
int n,r;
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
