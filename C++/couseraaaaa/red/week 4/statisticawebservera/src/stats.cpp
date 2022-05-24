#include "stats.h"



	Stats::Stats(){
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

  void Stats::AddMethod(string_view method){
	  if(method_st.count(method)==1){
		  method_st[method]++;
		  return;
	  }
	  method_st["UNKNOWN"]++;
  }

  void Stats::AddUri(string_view uri){
	  if(uri_st.count(uri)==1){
	  		  uri_st[uri]++;
	  		  return;
	  	  }
	  	  uri_st["unknown"]++;
  }
  const map<string_view, int>& Stats::GetMethodStats() const{
	  return method_st;
  }
  const map<string_view, int>& Stats::GetUriStats() const{
	  return uri_st;
  }


HttpRequest ParseRequest(string_view line){
	HttpRequest result;

	size_t marker = line.find_first_not_of(' ');
	line.remove_prefix(marker);
	marker = line.find(' ', 0);
	result.method=line.substr(0,marker);
	line.remove_prefix(marker+1); //POST /order HTTP/1.1

	marker = line.find(' ', 0);
	result.uri=line.substr(0,marker);
	line.remove_prefix(marker+1);

	result.protocol=line.substr(0);

	return result;
}
