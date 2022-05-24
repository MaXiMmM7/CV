#include "Common.h"
#include <deque>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <exception>
#include <mutex>
#include <iostream>
#include <future>
#include <thread>
#include <sstream>

using namespace std;
///  using BookPtr = std::shared_ptr<const IBook>;
class LruCache : public ICache {
public:
  LruCache(
      shared_ptr<IBooksUnpacker> books_unpacker,
      const Settings& settings
  ):unpacker_(books_unpacker),settings_(settings) {
	  current=0;
  }

  BookPtr GetBook(const string& book_name) override {

	  {lock_guard<mutex> g(m);
//	  stringstream ss;
	  //m.lock();

	 //  ss << "The thread number is  "  << this_thread::get_id()<< endl;
//	   ss << "The book is  "  << book_name<< "   " <<current << endl;
	  auto It=find(books.begin(),books.end(),book_name);
	  if(It!=books.end()){
		  //if(It!=books.begin()){
			  books.erase(It);
		  //}
	//	  ss << "OLD BOOK" << endl;

	  }
	  else{
		  BookPtr ptr=unpacker_->UnpackBook(book_name);
		  current+=ptr->GetContent().size();

//		  ss << "Its a new book ...." << current << endl;

		  if(ptr->GetContent().size()<=settings_.max_memory){

			  while(current>settings_.max_memory){
				  current-=dict[books.back()]->GetContent().size();
				  dict.erase(books.back());
				  books.pop_back();
			  }

		  }
		  else{
			  current=0;
			  books.clear();
			  dict.clear();
			  return (ptr);
		  }
//		  ss << "ANd now current is " << current << endl;
		  dict[book_name]=move(ptr);
	  }
	  books.push_front(book_name);
/*
	  int i=0;
	  for(auto a: books){
		  ss<<a << " " <<i++ << "|| ";
	  }
	  ss << endl;
	  i=0;
	  for(auto a: dict){
	  		  ss<<a.first << " " <<i++ << "|| ";
	  	  }
	  	  ss << endl;
		  ss << endl << endl;
	  	  cout << ss.str();
	  	  */

	  return dict[books.front()];
	  }
  }

private:
  shared_ptr<IBooksUnpacker> unpacker_;
  const Settings& settings_;
  size_t current;
  deque<string> books;
  unordered_map<string,BookPtr> dict;
  mutex m;
};


unique_ptr<ICache> MakeCache(
    shared_ptr<IBooksUnpacker> books_unpacker,
    const ICache::Settings& settings
) {
  return make_unique<LruCache>(move(books_unpacker),settings);
}
