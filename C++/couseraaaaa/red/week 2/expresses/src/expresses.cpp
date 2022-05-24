#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include "profile.h"
using namespace std;

class RouteManager {
public:
  void AddRoute(const int& start,const int& finish) {
	 reachable_lists_[start].insert(finish);
    reachable_lists_[finish].insert(start);
  }
  int FindNearestFinish(const int& start, const int& finish) const {
	 int result = abs(start - finish);
    if (reachable_lists_.count(start) < 1) {
        return result;
    }
   auto It=reachable_lists_.at(start).lower_bound(finish);
   int result1;
   if(It!=reachable_lists_.at(start).begin()&&It!=reachable_lists_.at(start).end()){
	    result1=min(abs(*It-finish),abs(*prev(It)-finish));
	  }
   if(It==reachable_lists_.at(start).begin()){
	   result1=abs(*It-finish);
   };
  if (It==reachable_lists_.at(start).end()) {
	   result1=abs(*prev(It)-finish);
   }
   return result<result1 ? result: result1;

  }
private:
  map<int, set<int>> reachable_lists_;
};


/*
void TestAdd(){
	LOG_DURATION("TestAdd");
	RouteManager routes;
	int base=-100000;
			while(base<10000){
				routes.AddRoute(base, base+10);
				base++;
			}
}

void TestFindExist(){

	RouteManager routes;
		int base=-100000;
				while(base<10000){
					routes.AddRoute(base, base+10);
					base++;
				}

				//////////////////////////////////////

	 base=-100000;
	 LOG_DURATION("TestFindExist");

				while(base<10000){
					routes.FindNearestFinish(base, base+10);
				base++;
				}
}

void TestFindNonExist(){
	RouteManager routes;
			int base=-100000;
					while(base<10000){
						routes.AddRoute(base, base+10);

						base++;}

					//////////////////////////////////////

		 base=-100000;
		 LOG_DURATION("TestFindNonExist");

					while(base<10000){
					routes.FindNearestFinish(base, base+5);
					base++;
					}
}

void TestAll(){
	LOG_DURATION("TestALl");

	RouteManager routes;
				int base=-100000;
						while(base<10000){
							routes.AddRoute(base, base+10);
							base++;
						}

						//////////////////////////////////////

					base=-100000;
						while(base<0){
						routes.FindNearestFinish(base, base+5);
						base++;
						}
						while(base<10000){
						routes.FindNearestFinish(base, base+5);
						base++;
						}
}
*/

int main() {

	/*
	TestAdd();
	TestFindExist();
	TestFindNonExist();
	TestAll();
*/

	//
	/*
	 * 7
ADD -2 5
ADD 10 4
ADD 5 8
GO 4 10
GO 4 -2
GO 5 0
GO 5 100
	 */

  RouteManager routes;

  int query_count;
  cin >> query_count;
  LOG_DURATION("Full program");
  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int start, finish;
    cin >> start >> finish;
    if (query_type == "ADD") {
      routes.AddRoute(start, finish);
    } else if (query_type == "GO") {
      cout << routes.FindNearestFinish(start, finish) << "\n";
    }
  }

  return 0;
}
