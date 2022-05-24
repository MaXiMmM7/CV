#include <iomanip>
#include <iostream>
#include <vector>
#include "profile.h"
#include <utility>
#include <algorithm>
#include <utility>
#include <iterator>
#include <set>
#include <map>

using namespace std;


/*class ReadingManager {
public:

  void Read(int user_id, int page_count) {
 	  if(users.count(user_id)!=0){ //logQ         P=10^3  M=10^5  Q=10^6
	  int  helper=users[user_id];// logQ
	  pages.erase(pages.lower_bound(helper));//logQ

   }
	  users[user_id]=page_count; //logQ
      pages.insert(page_count); // logQ
  }

//5*logQ

  double Cheer(int user_id) const {
  if(users.count(user_id)==0){return 0*1.0;} //logQ
  if(pages.size()==1){return 1;}//const
 // return (1.0*distance(pages.begin(),pages.lower_bound(users.at(user_id))))/(pages.size()-1);//Q
  return *pages.lower_bound(users.at(user_id));//Q

  }
//Q

//Q



private:

  map<int,int> users; //
  multiset<int> pages;
};*/

class ReadingManager {
public:

  void Read(int user_id, int page_count) {
 	  if(users.count(user_id)!=0){ //logQ         P=10^3  M=10^5  Q=10^6
	  int  helper=users[user_id];// logQ
	  pages.at(helper).erase(user_id);//logQ
	  if(pages.at(helper).size()==0){
		  pages.erase(helper);
	  }

   }
	  users[user_id]=page_count; //logQ
      pages[page_count].insert(user_id); // logQ
  }

//5*logQ

  double Cheer(int user_id) const {
  if(users.count(user_id)==0){return 0*1.0;} //logQ
  if(users.size()==1){return 1;}//const
  double result=0;
  auto It1=pages.lower_bound(users.at(user_id));
  for(auto It=pages.begin();It!=It1;It++){
	  result+=(*It).second.size();
  }
  return result/(users.size()-1);
 // return (1.0*distance(pages.begin(),pages.lower_bound(users.at(user_id))))/(pages.size()-1);//Q
  }
//Q

//Q



private:

  map<int,int> users; //
  map<int,set<int>> pages;
};

/*
void TestAll(){
	LOG_DURATION("Tester");
	  ReadingManager manager;
	  int user_id=0;
	  int page=0;
	  for(int i=0;i<100000;i++){
		  manager.Read(user_id,page);
		  user_id++;
		  page++;
		  if(page>1000){
			  page=0;
		  }
	  }

	  LOG_DURATION("Cheer");

	  user_id=0;
	  for(int i=0;i<900000;i++){
	  		  manager.Cheer(user_id);
	  		  user_id++;

	  		  if(page>100000){
	  			  user_id=0;
	  		  }
	  	  }
}
*/
int main() {

//
	//TestAll();

	///
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;
  {LOG_DURATION("TestALl");
  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }
  }
  return 0;
}
