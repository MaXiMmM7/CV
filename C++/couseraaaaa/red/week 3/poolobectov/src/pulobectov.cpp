#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <exception>
#include <set>

using namespace std;


template <class T>
class ObjectPool {
public:
  T* Allocate(){
	  if(free.empty()){
		 T* var = new T;
		 alloc.insert(var);
		 return var;
	  }
	  auto result=free.front();
	  alloc.insert(result);
	  free.pop();
	  return result;
  }
  T* TryAllocate(){;
  if(free.empty()){return nullptr;}
  auto result=free.front();
 	  alloc.insert(result);
 	  free.pop();
 	  return result;

  }

  void Deallocate(T* object){;
  auto It=alloc.find(object);
  if(It==alloc.end()){ throw invalid_argument("OMG");}
  free.push(*It);
  alloc.erase(It);
  }

  ~ObjectPool(){;
  while(!alloc.empty()){
	  delete *alloc.begin();
	  alloc.erase(alloc.begin());
  }
  while(!free.empty()){
  	  delete free.front();
  	  free.pop();
    }
  }

  //

  bool EMPA(){
	  return alloc.empty();
  }
  bool EMPF(){
  	  return free.empty();
    }
  //
private:
  set<T*> alloc;
  queue<T*> free;
};

void TestObjectPool() {
	{ ObjectPool<string> pool;

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

	{

	}
}



int main() {
  TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
  cerr << "hello";
  return 0;
}
