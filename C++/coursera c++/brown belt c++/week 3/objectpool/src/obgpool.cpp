#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
#include <unordered_set>
#include <queue>
#include <utility>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate(){
	  T* ptr=TryAllocate();
	  if(ptr==nullptr){
		  ptr=new T;
		  dedicated.insert(ptr);
	  }
	  return ptr;
  }
  T* TryAllocate(){
	  if(free.empty()){
		  return nullptr;
	  }
	  T* ptr=free.front();
	  free.pop();
	  return *dedicated.insert(ptr).first;
  }

  void Deallocate(T* object){
	  if(dedicated.count(object)==0){
		  throw invalid_argument("Sorry,bro");
	  }
	  free.push(object);
	  dedicated.erase(object);
  }

  ~ObjectPool(){
	auto It=dedicated.begin();
	while(It!=dedicated.end()){
		T* ptr=*It;
		It=dedicated.erase(It);
		delete ptr;
	}
	  /*  while(!dedicated.empty()){
		  delete *dedicated.begin();
		  dedicated.erase(dedicated.begin());
	  }*/
	 /* while(!free.empty()){
		  delete free.front();
		  free.pop();
	  }
	  */
	size_t N=free.size();
	  for(size_t i=0;i<N;i++){
		  delete free.front();
		 		  free.pop();
	  }

  }

private:
  set<T*> dedicated;
  queue<T*> free;
};

void TestObjectPool() {

  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
