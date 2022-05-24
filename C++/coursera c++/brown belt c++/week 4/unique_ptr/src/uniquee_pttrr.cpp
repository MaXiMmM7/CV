#include "test_runner.h"
#include <utility>
#include <cstddef>  // нужно для nullptr_t

using namespace std;



// Реализуйте шаблон класса UniquePtr

template <typename T>
class UniquePtr {
private:
  T* object;
public:
  UniquePtr():object(nullptr){} //1

  UniquePtr(T * ptr):object(ptr){} //2

  UniquePtr(const UniquePtr&) = delete; //because unique

  UniquePtr(UniquePtr&& other){
	// if(this!=&other){
	  //delete object;
	  object=move(other.object);
//	  delete other.object;
	  other.object=nullptr;
	 //}
  }

  UniquePtr& operator = (const UniquePtr&) = delete;//because unique

  UniquePtr& operator = (nullptr_t){  //4
	  delete object;
	  object=nullptr;
	  return *this;
  }

  UniquePtr& operator = (UniquePtr&& other){//5
	  if(this!=&other){
		  delete object;
		  object=move(other.object);
		 // delete other.object;
		  other.object=nullptr;

	  }
	  return *this;
  }

  ~UniquePtr(){
	  delete object;
	  cerr << "Destructor" << endl;
  }

  T& operator * () const{
	  return *object;
  }

  T * operator -> () const{
	  return object;
  }

  T * Release(){
	  auto helper=move(object);
	  object=nullptr;
	  return helper;
  }

  void Reset(T * ptr){
	  delete object;
	  object=ptr;
  }

  void Swap(UniquePtr& other){
	  auto helper=move(other.object);
	  other.object=move(object);
	  object=move(helper);
  }

  T * Get() const{  //12
	  return object;
  }
};

/*
template<typename T>
bool operator!=(const UniquePtr<T>& l,const UniquePtr<T>& r){
	return (l.Get()!=r.Get());
}
*/
/*
template <typename T>
class UniquePtr {
private:
  T* object;
  void Clean(){
	  if(object!=nullptr){
		  object->~T();
	  }
  }
public:
  UniquePtr():object(nullptr){} //1

  UniquePtr(T * ptr):object(ptr){} //2

  UniquePtr(const UniquePtr&) = delete; //because unique

  UniquePtr(UniquePtr&& other){
	 if(*this!=other){
	  object=move(other.object);
	 other.object=nullptr;
	 }
  }

  UniquePtr& operator = (const UniquePtr&) = delete;//because unique

  UniquePtr& operator = (nullptr_t){  //4
	  Clean();
	  object=nullptr;
	  return *this;
  }

  UniquePtr& operator = (UniquePtr&& other){//5
	  if(*this!=other){
		  object=move(other.object);
		  other.object=nullptr;

	  }
	  return *this;
  }

  ~UniquePtr(){
	  Clean();
	  cerr << "Destructor" << endl;
  }

  T& operator * () const{
	  return *object;
  }

  T * operator -> () const{
	  return object;
  }

  T * Release(){
	  auto helper=object;
	  object=nullptr;
	  return helper;
  }

  void Reset(T * ptr){
	  Clean();
	  object=ptr;
  }

  void Swap(UniquePtr& other){
	  auto helper=move(other.object);
	  other.object=move(object);
	  object=move(helper);
  }

  T * Get() const{  //12
	  return object;
  }
};

template<typename T>
bool operator!=(const UniquePtr<T>& l,const UniquePtr<T>& r){
	return (l.Get()!=r.Get());
}
*/
struct Item {
  static int counter;
  int value;
  Item(int v = 0): value(v) {
    ++counter;
  }
  Item(const Item& other): value(other.value) {
    ++counter;
  }
  ~Item() {
    --counter;
    cerr << "Item destructured"  << endl;
  }
};

int Item::counter = 0;


void TestLifetime() {
	//
	//cerr << "We are here" << endl;
	//
  Item::counter = 0;
  {
    UniquePtr<Item> ptr(new Item);
    ASSERT_EQUAL(Item::counter, 1);

    ptr.Reset(new Item);
    ASSERT_EQUAL(Item::counter, 1);
  }
  ASSERT_EQUAL(Item::counter, 0);
  //
  ASSERT_EQUAL(Item::counter, 0);
  //
  {
    UniquePtr<Item> ptr(new Item);
    ASSERT_EQUAL(Item::counter, 1);

    auto rawPtr = ptr.Release();
    ASSERT_EQUAL(Item::counter, 1);

    //
 //   cerr << "1"  << endl;
    //
    delete rawPtr;
    //
      //  cerr << "2"  << endl;
        //
    ASSERT_EQUAL(Item::counter, 0);
   // cerr <<"dsfsdfsdcf  " <<  (ptr.Get()==nullptr) << endl;
  }
  ASSERT_EQUAL(Item::counter, 0);
  UniquePtr<Item> ptr1(new Item);
  UniquePtr<Item> ptr2(new Item);
  ptr2=move(ptr1);
  ASSERT_EQUAL(Item::counter, 1);
  UniquePtr<Item> ptr3(move(ptr2));
  ASSERT_EQUAL(Item::counter, 1);

}

void TestGetters() {
  UniquePtr<Item> ptr(new Item(42));
  ASSERT_EQUAL(ptr.Get()->value, 42);
  ASSERT_EQUAL((*ptr).value, 42);
  ASSERT_EQUAL(ptr->value, 42);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLifetime);
  RUN_TEST(tr, TestGetters);
}
