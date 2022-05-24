#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <map>
#include <list>
#include <vector>

using namespace std;

/*

template <typename T>
bool operator <(const pair<T,int>& l,const pair<T,int>& r){
	return l.second <r.second;
}



template <typename T>
class PriorityCollection {
public:
  using Id = typename list<T>::iterator;

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object){
	  container.push_back(move(object));
	  priority.insert(pair<Id,int>((--container.end()),0));
	  table[(--container.end())]=0;
	  return (--container.end());
  }
  //set

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...) map<int,Id>, map int,priority
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin){

	  container.insert(next(ids_begin),range_begin,range_end);
	  auto It=ids_begin++;
	  for(int i=0;i<range_begin-range_end;i++){
		  priority.insert(pair<Id,int>(It,0));
		   table[It]==0;
		   It++;
	  }
	  }
  //list

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const{
	  return table.count(id);
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const{
	  priority.erase(pair<Id,int>(id,table[id]));
	  table.erase(id);
	  return move(id);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id){
	  priority.erase(priority.find(make_pair(id,table[id])));
	  table[id]++;
	  priority.insert(make_pair(id,table[id]));
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const{
	  auto It=prev(priority.end());
	  auto helper=(*It).first;
	  pair<const T&,int> rez((helper),table[helper]);


      return rez;
  }

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax(){
	  auto It=prev(priority.end());
	  auto helper=(*It).first;
	  pair< T,int> rez(move(*helper),table[helper]);
	  table.erase((*It).first);
	  container.erase(It->first);
	  priority.erase(It);

      return rez;

  }

private:
  list<T> container;
  set<pair<Id,int>> priority;
  map<Id,int> table;
  // Приватные поля и методы
};
*/
int current_time=0;


template <typename T>
class MyClass{
public:
	MyClass(){};
	MyClass(typename list<T>::iterator It_,int prior_,int time_):
		It(It_),
		prior(prior_),
		time(time_)
	{}
	typename list<T>::iterator It;
	int prior=0;
	int time=0;

};

template <typename T>
bool operator <(const MyClass<T>& l,const MyClass<T>& r){
	return l.prior!=r.prior ?  l.prior <r.prior  : l.time <r.time;
}


template <typename T>
class PriorityCollection {
public:
 // using Id = typename list<T>::iterator;
	 using Id = int;
  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object){
	  container.push_back(move(object));
	  auto result =MyClass<T>(--container.end(),0,current_time++);
	  priority.insert(result);
	  book[result.time]=result;
	  return result.time;
  }
  //set

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...) map<int,Id>, map int,priority
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin){
	  auto It=prev(container.end());
	  container.insert(container.end(), //!!!!!!!!!!!!!!!!!!!!!!!!!
			  make_move_iterator(range_begin),
			  make_move_iterator(range_end));
	 It++;
	  for(auto It1=range_begin;It1!=range_end;It1++){
		  auto result =MyClass<T>(It++,0,current_time++);
		  priority.insert(result);
		  book[result.time]=result;

          *(ids_begin++)=result.time;
	  }
	  }
  //list

  ///////////////////////////////////////
  ///////////////////////////////////////
  ///////////////////////////////////////
  int GetPrior(Id id){
	  return book[id].prior;
  }
  ///////////////////////////////////////
  ///////////////////////////////////////
  ///////////////////////////////////////

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const{
	  return book.count(id);
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const{
	  //priority.erase(pair<Id,int>(id,table[id]));
	  //table.erase(id);

	  return (*book.at(id).It);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id){
	auto rez=book[id];
	priority.erase(priority.find(rez));
	rez.prior++;
	priority.insert(rez);
	book[id]=rez;
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const{
	  auto It=prev(priority.end());
	  auto helper=(*It);
      return pair<const T&, int>(*helper.It,helper.prior);
  }

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax(){
	  auto It=prev(priority.end());
	 	  auto helper=(*It);
	 	  auto rez=pair< T, int>(move(*helper.It),helper.prior);
	 	  container.erase(helper.It);
	 	  priority.erase(helper);
	 	  book.erase(helper.time);
	 	  return rez;
  }

private:
  list<T> container;
  set<MyClass<T>> priority;
  map<int,MyClass<T>> book;
  //int current_time=0;

  // Приватные поля и методы
};


class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

void MoreTests(){

	PriorityCollection<StringNonCopyable> contain;

		vector<StringNonCopyable> words;
		words.push_back("red");
		words.push_back("blue");
		words.push_back("green");
		words.push_back("yellow");
		words.push_back("white");

		vector<PriorityCollection<StringNonCopyable>::Id> check(words.size());

		contain.Add(words.begin(),words.end(), check.begin());

		//Проверка добавления вектора
		ASSERT_EQUAL(contain.Get(check[0]),"red");
		ASSERT_EQUAL(contain.Get(check[4]),"white");


		//Проверка валидности
		PriorityCollection<StringNonCopyable> spy;
		auto bomb = spy.Add({"joke"});

		ASSERT(!contain.IsValid(bomb));
		ASSERT(contain.IsValid(check[0]));

		contain.Promote(check[0]);				//red++
		contain.PopMax();                     //del red
		ASSERT(!contain.IsValid(check[0]));

		//Проверка GetMax()
		contain.Promote(check[4]);				//white++
		auto check_max = contain.GetMax();
		ASSERT_EQUAL(check_max.first,StringNonCopyable({"white"}));
		auto check_max_copy = contain.GetMax();
		ASSERT_EQUAL(check_max.first,check_max_copy.first);

		//Проверка извлечения максимума PopMax();

		ASSERT_EQUAL(check_max.first,"white");
		auto item = contain.PopMax();			//del white
		ASSERT_EQUAL(item.first,StringNonCopyable({"white"}));
		ASSERT_EQUAL(item.second,1);
		ASSERT(!contain.IsValid(check[4]));

		//проверка GetMax() по очередности добавления
		auto new_item = contain.Add({"new"});
		contain.Promote(check[3]);	// yellow++
		contain.Promote(new_item);
		contain.Promote(check[2]);	// green++
		auto x = contain.GetMax();

		ASSERT_EQUAL(x.second, 1);
		ASSERT_EQUAL(x.first, "new");
}

void AddTest(){
	PriorityCollection<StringNonCopyable> s;
	const auto white_id = s.Add("white");
	s.Promote(white_id);
	const auto yellow_id = s.Add("yellow");
	ASSERT_EQUAL(s.Get(yellow_id), "yellow");
	ASSERT_EQUAL(s.GetPrior(yellow_id), 0);
}

int main() {

  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  RUN_TEST(tr, MoreTests);
  RUN_TEST(tr, AddTest);

  return 0;
}
