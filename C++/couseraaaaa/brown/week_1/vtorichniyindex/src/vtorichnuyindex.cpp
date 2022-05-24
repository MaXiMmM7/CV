#include "test_runner.h"

#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <unordered_map>
#include <iterator>
#include <list>
#include <algorithm>

using namespace std;

struct Record {
  string id;
  string title;
  string user;
  int timestamp;
  int karma;
};

bool operator ==(const Record& l,const Record& r){
	return l.id==r.id&&l.karma==r.karma&&l.timestamp==r.timestamp&&
			l.title==r.title&&l.user==r.user;
}
bool operator != (const Record& l,const Record& r){
	return !(l==r);
}
// Реализуйте этот класс

/*
class Database {
public:
  bool Put(const Record& record){

	  if(map_id.find(record.id)==map_id.end()){
		  map_id.insert({record.id,record});
		  auto It=map_id.find(record.id);
		  {
		  map_timestap.insert({record.timestamp,It});
		  map_karma.insert({record.karma,It});
		  map_user.insert({record.user,It});
		  }

		   return true;
	  }
	  return false;
  }

  const Record* GetById(const string& id) const{
	  auto It=map_id.find(id);
	  if(It!=map_id.end()&&It->first==id){
		   return &(It->second);
	  }
	  return nullptr;
  }

  bool Erase(const string& id){
	  auto It=map_id.find(id);
	  	  if(It==map_id.end()||It->first!=id){
	  		  return false;
	  	  }
	 // auto copy=map_id[id];
	  //map_id.erase(id);


	  	  {
	  auto It1=map_timestap.lower_bound((It->second).timestamp);
	  while(It1->second!=It){
		  It1++;
	  }
	  map_timestap.erase(It1);
	  	  }
	  	  {
	  auto It1=map_karma.lower_bound((It->second).karma);
	  	  while(It1->second!=It){
	  		  It1++;
	  	  }
	  	  map_karma.erase(It1);
	  	  }
	  	  {
	  auto It1=map_user.lower_bound((It->second).user);
	  	  	  while(It1->second!=It){
	  	  		  It1++;
	  	  	  }
	  	  	  map_user.erase(It1);

	  	  }

	  map_id.erase(It);

	  return true;
  }

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const{
	   auto It1= map_timestap.lower_bound(low);
	  auto It2= map_timestap.upper_bound(high);
	  while(It1!=It2){
		if(!callback(It1->second->second)){
	  		break;
	  	}
		It1++;
	  }

	  }

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const{
	  auto It1= map_karma.lower_bound(low);
	  	  auto It2= map_karma.upper_bound(high);
	  	while(It1!=It2){
	  			if(!callback(It1->second->second)){
	  		  		break;
	  		  	}
	  			It1++;
	  		  }  }


  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const{
	  auto It1= map_user.lower_bound(user);
	  auto It2= map_user.upper_bound(user);
	  while(It1!=It2){
	  		if(!callback(It1->second->second)){
	  	  		break;
	  	  	}
	  		It1++;
	  	  }  }

private:
  unordered_map<string,Record> map_id;
  multimap<int,unordered_map<string,Record>::iterator> map_timestap;
  multimap<int,unordered_map<string,Record>::iterator> map_karma;
  multimap<string,unordered_map<string,Record>::iterator> map_user;

};
*/



class Database {
public:
  bool Put(const Record& record){

	  if(map_id.find(record.id)==map_id.end()){
		 auto [It,b]= map_id.insert({record.id,{record,{},{},{}}});
		  //auto It=map_id.find(record.id);
		  Record* t=&(((*It).second).record);
		  {
		  It->second.map_timestap_iter=map_timestap.insert({record.timestamp,t});
		  It->second.map_karma_iter=map_karma.insert({record.karma,t});
		  It->second.map_user_iter=map_user.insert({record.user,t});
		  }

		   return true;
	  }
	  return false;
  }

  const Record* GetById(const string& id) const{
	  auto It=map_id.find(id);
	  if(It!=map_id.end()&&It->first==id){
		   return &(It->second.record);
	  }
	  return nullptr;
  }

  bool Erase(const string& id){
	  auto It=map_id.find(id);
	  	  if(It==map_id.end()||It->first!=id){
	  		  return false;
	  	  }
	 // auto copy=map_id[id];
	  //map_id.erase(id);


	  	map_timestap.erase(It->second.map_timestap_iter);
	  	map_karma.erase(It->second.map_karma_iter);
	  	map_user.erase(It->second.map_user_iter);
	  	map_id.erase(It);

	  return true;
  }

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const{
	   auto It1= map_timestap.lower_bound(low);
	  auto It2= map_timestap.upper_bound(high);
	  while(It1!=It2){
		if(!callback(*(It1->second))){
	  		break;
	  	}
		It1++;
	  }

	  }

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const{
	  auto It1= map_karma.lower_bound(low);
	  	  auto It2= map_karma.upper_bound(high);
	  	while(It1!=It2){
	  			if(!callback(*(It1->second))){
	  		  		break;
	  		  	}
	  			It1++;
	  		  }  }


  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const{
	  auto It1= map_user.lower_bound(user);
	  auto It2= map_user.upper_bound(user);
	  while(It1!=It2){
	  		if(!callback(*(It1->second))){
	  	  		break;
	  	  	}
	  		It1++;
	  	  }  }

private:
  struct data{
	  Record record;
	  multimap<int, Record*>::iterator map_timestap_iter;
	  multimap<int, Record*>::iterator map_karma_iter;
	  multimap<string, Record*>::iterator map_user_iter;

  };
  unordered_map<string,data> map_id;
  multimap<int, Record*> map_timestap;
  multimap<int, Record*> map_karma;
  multimap<string, Record*> map_user;

};


void TestRangeBoundaries() {
  const int good_karma = 1000;
  const int bad_karma = -10;

  Database db;
  db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
  db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

  int count = 0;
  db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
    ++count;
    return true;
  });
  ASSERT_EQUAL(2, count);

  db.Put({"id3", "Hello there", "master", 1536107260, good_karma});
   db.Put({"id4", "O>>-<", "general2", 1536107260, bad_karma});
   db.Put({"id5", "Hello there", "master", 1536107260, 0});
   db.Put({"id7", "Hello there", "master", 1536107260, -1000});
   db.Put({"id6", "O>>-<", "general2", 1536107260, 0});
     db.Put({"id8", "O>>-<", "general2", 1536107260, 100000});
     db.Put({"id9", "O>>-<", "general2", 1536107260, 0});

      count = 0;
       db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
         ++count;
         return true;
       });
       ASSERT_EQUAL(7, count);



}

void TestSameUser() {
  Database db;
  db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
  db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

  int count = 0;
  db.AllByUser("master", [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);

 db.Erase("id1");
 count = 0;
   db.AllByUser("master", [&count](const Record&) {
     ++count;
     return true;
   });
   ASSERT_EQUAL(1, count);

   db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
   db.Put({"id3", "Rethink life", "master", 1536107260, 2000});
   db.Put({"id4", "Don't sell", "son", 1536107260, 1000});
   db.Put({"id5", "Rethink life", "master", 1536107260, 2000});
   db.Put({"id6", "Don't sell", "a", 1536107260, 1000});
   db.Put({"id7", "Rethink life", "z", 1536107260, 2000});

   count = 0;
      db.AllByUser("master", [&count](const Record&) {
        ++count;
        return true;
      });
      ASSERT_EQUAL(4, count);

}

void TestReplacement() {
  const string final_body = "Feeling sad";

  Database db;
  db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
  db.Erase("id");
  db.Put({"id", final_body, "not-master", 1536107260, -10});

  auto record = db.GetById("id");
  ASSERT(record != nullptr);
  ASSERT_EQUAL(final_body, record->title);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestRangeBoundaries);
  RUN_TEST(tr, TestSameUser);
  RUN_TEST(tr, TestReplacement);
  return 0;
}
