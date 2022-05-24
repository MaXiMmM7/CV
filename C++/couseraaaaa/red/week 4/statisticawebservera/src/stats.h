
#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
using namespace std;

class Stats {
public:
	Stats();

  void AddMethod(string_view method);
  void AddUri(string_view uri);
  const map<string_view, int>& GetMethodStats() const;
  const map<string_view, int>& GetUriStats() const;
private:
  map<string_view, int> method_st;
  map<string_view, int> uri_st;
};

HttpRequest ParseRequest(string_view line);

/*
#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
using namespace std;

class Stats {
public:
	Stats(){
		method_st["GET"]=0;
		method_st["POST"]=0;
		method_st["PUT"]=0;
		method_st["DELETE"]=0;
		method_st["UNKNOWN"]=0; //«GET», «POST», «PUT», «DELETE»

		uri_st["/"]=0;
		uri_st["/order"]=0;
		uri_st["/product"]=0;
		uri_st["/basket"]=0;
		uri_st["/help"]=0;//«/», «/order», «/product», «/basket», «/help».
		uri_st["unknown"]=0;
}

  void AddMethod(string_view method){
	  if(method_st.count(method)==1){
		  method_st[method]++;
		  return;
	  }
	  method_st["UNKNOWN"]++;
  }
  void AddUri(string_view uri){
	  if(uri_st.count(uri)==1){
	  		  uri_st[uri]++;
	  		  return;
	  	  }
	  	  uri_st["unknown"]++;
  }
  const map<string_view, int>& GetMethodStats() const{
	  return method_st;
  }
  const map<string_view, int>& GetUriStats() const{
	  return uri_st;
  }
private:
  map<string_view, int> method_st;
  map<string_view, int> uri_st;
};

HttpRequest ParseRequest(string_view line){
	HttpRequest result;

	size_t marker = line.find_first_not_of(' ');
	line.remove_prefix(marker);
	marker = line.find('/', 0);
	result.method=line.substr(0,marker-1);
	line.remove_prefix(marker);

	marker = line.find(' ', 0);
	result.uri=line.substr(0,marker);
	line.remove_prefix(marker+1);

	result.protocol=line.substr(0);

	return result;
}
*/
