#include "test_runner.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include <map>
#include <optional>
#include <unordered_set>

using namespace std;

struct HttpRequest {
  string method, path, body;
  map<string, string> get_params;
};

pair<string, string> SplitBy(const string& what, const string& by) {
  size_t pos = what.find(by);
  if (by.size() < what.size() && pos < what.size() - by.size()) {
    return {what.substr(0, pos), what.substr(pos + by.size())};
  } else {
    return {what, {}};
  }
}

template<typename T>
T FromString(const string& s) {
  T x;
  istringstream is(s);
  is >> x;
  return x;
}

pair<size_t, string> ParseIdAndContent(const string& body) {
  auto [id_string, content] = SplitBy(body, " ");
  return {FromString<size_t>(id_string), content};
}

struct LastCommentInfo {
  size_t user_id, consecutive_count;
};

///////////////////////////////
///////////////////////////////
//////////////////////////////
enum class HttpCode {
  Ok = 200,
  NotFound = 404,
  Found = 302,
};

class HttpResponse {
public:
  explicit HttpResponse(HttpCode code):Code(static_cast<int>(code)){}

  HttpResponse& AddHeader(string name, string value){
	  headers.insert(pair<string,string>(name,value));
	  return *this;
  }

  HttpResponse& SetContent(string a_content){
	  content=a_content;
	  return *this;
  }
  HttpResponse& SetCode(HttpCode a_code){
	  Code=static_cast<int>(a_code);
	  return *this;
  }

  const multimap<string,string>& GetHeaders() const{
	  return headers;
  }
  int GetCode() const{
	  return Code;
  }
  const string& GetContent() const{
	  return content;
  }

  size_t GetContentSize() const{
  	  return content.size();
    }

  bool IsEmptyContent() const{
    	  return content.empty();
      }
  friend ostream& operator << (ostream& output, const HttpResponse& resp){
	  output << "HTTP/1.1 ";
	  /*if(resp.GetCode()==static_cast<int>(HttpCode::NotFound)){
		   output << "404 Not found\n";
		  for(const auto&[key,value]:resp.GetHeaders()){
		  		  output << key << ": " << value << "\n";
		  	  }
		  return output << "\n";
	  }*/

	  output << resp.GetCode() << " ";
	  if(resp.GetCode()==static_cast<int>(HttpCode::Ok)){
		  output << "OK" << "\n";
	  }
	  else if(resp.GetCode()==static_cast<int>(HttpCode::Found)){
		  output << "Found" << "\n";
	  }
	  else{
		  output << "Not found\n";
	  }

	  for(const auto&[key,value]:resp.GetHeaders()){
		  output << key << ": " << value << "\n";
	  }

	  if(!resp.IsEmptyContent()){
		  output << "Content-Length: " << resp.GetContentSize() << "\n" << "\n";
		  output << resp.GetContent() ;//<< "\n";
	  }
	  else{
		  output << "\n";
	  }
	  return output;

  }
private:
  multimap<string,string> headers;
  int Code;
  string content;

};

///////////////////////////////////////
/////////////////////////////////////


class CommentServer {
private:
  vector<vector<string>> comments_;
  std::optional<LastCommentInfo> last_comment;
  unordered_set<size_t> banned_users;

public:

  HttpResponse ServeRequest(const HttpRequest& req){

    if (req.method == "POST") {
    	/////////////////////////////
      if (req.path == "/add_user") {
        comments_.emplace_back();
        auto response = to_string(comments_.size() - 1);
        return HttpResponse(HttpCode::Ok).SetContent(response);
      }

      ////////////////////////////////

      else if (req.path == "/add_comment") {
        auto [user_id, comment] = ParseIdAndContent(req.body);

        if (!last_comment || last_comment->user_id != user_id) {
          last_comment = LastCommentInfo {user_id, 1};
        } else if (++last_comment->consecutive_count > 3) {
          banned_users.insert(user_id);
        }

        if (banned_users.count(user_id) == 0) {
          comments_[user_id].push_back(string(comment));
          return HttpResponse(HttpCode::Ok);
        } else {
        	return HttpResponse(HttpCode::Found).AddHeader("Location","/captcha");
        }
      }
      /////////////////////////////////////
      else if (req.path == "/checkcaptcha") {
        if (auto [id, response] = ParseIdAndContent(req.body); response == "42") {
          banned_users.erase(id);
          if (last_comment && last_comment->user_id == id) {
            last_comment.reset();
          }
      	return HttpResponse(HttpCode::Ok);
        }
        else{
        	return HttpResponse(HttpCode::Found).AddHeader("Location","/captcha");
        }
      }
      ///////////////////////////////////////
 //     else {
   //     os << "HTTP/1.1 404 Not found\n\n";
     // }
    }


    else if (req.method == "GET") {
      if (req.path == "/user_comments") {
        auto user_id = FromString<size_t>(req.get_params.at("user_id"));
        string response;
        for (const string& c : comments_[user_id]) {
          response += c + '\n';
        }
    	return HttpResponse(HttpCode::Ok).SetContent(response);
      }
      ////////////////////////
      else if (req.path == "/captcha") {
    	  return HttpResponse(HttpCode::Ok).SetContent(
    			  "What's the answer for The Ultimate Question of Life, the Universe, and Everything?");
           }
      //else {
        //os << "HTTP/1.1 404 Not found\n\n";
      //}
    }

    return HttpResponse(HttpCode::NotFound);
  }


};

struct HttpHeader {
  string name, value;
};

ostream& operator<<(ostream& output, const HttpHeader& h) {
  return output << h.name << ": " << h.value;
}

bool operator==(const HttpHeader& lhs, const HttpHeader& rhs) {
  return lhs.name == rhs.name && lhs.value == rhs.value;
}

struct ParsedResponse {
  int code;
  vector<HttpHeader> headers;
  string content;
};

istream& operator >>(istream& input, ParsedResponse& r) {
  string line;
  getline(input, line);

  {
    istringstream code_input(line);
    string dummy;
    code_input >> dummy >> r.code;
  }

  size_t content_length = 0;

  r.headers.clear();
  while (getline(input, line) && !line.empty()) {
    if (auto [name, value] = SplitBy(line, ": "); name == "Content-Length") {
      istringstream length_input(value);
      length_input >> content_length;
    } else {
      r.headers.push_back( {std::move(name), std::move(value)});
    }
  }

  r.content.resize(content_length);
  input.read(r.content.data(), r.content.size());
  return input;
}


void Test(CommentServer& srv, const HttpRequest& request, const ParsedResponse& expected) {
  stringstream ss;

  //srv.ServeRequest(request);
  /*cout << srv.ServeRequest(request) << endl;
  cout << "COde " <<  srv.ServeRequest(request).GetCode() << endl;
  cout << "Content  " <<srv.ServeRequest(request).GetContent() << endl;
  cout << "Content  " <<srv.ServeRequest(request).GetContent() << endl;
  cout << "Headers" << endl;
  auto v= srv.ServeRequest(request).GetHeaders();
  cout << v.empty() << endl;
  for (auto [key,value]: v){
	cout << key << " - " << value << endl;
  }
*/
  //
  ParsedResponse resp;
  ss << srv.ServeRequest(request);
  ss >> resp;

  ASSERT_EQUAL(resp.code, expected.code);
  ASSERT_EQUAL(resp.headers, expected.headers);
  ASSERT_EQUAL(resp.content, expected.content);
}

template <typename CommentServer>
void TestServer() {
  CommentServer cs;

  const ParsedResponse ok{200};
  const ParsedResponse redirect_to_captcha{302, {{"Location", "/captcha"}}, {}};
  const ParsedResponse not_found{404};


  Test(cs, {"POST", "/add_user"}, {200, {}, "0"});
  Test(cs, {"POST", "/add_user"}, {200, {}, "1"});
  Test(cs, {"POST", "/add_comment", "0 Hello"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Hi"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Buy my goods"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Enlarge"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Buy my goods"}, redirect_to_captcha);

    Test(cs, {"POST", "/add_comment", "0 What are you selling?"}, ok);
    Test(cs, {"POST", "/add_comment", "1 Buy my goods"}, redirect_to_captcha);
    Test(
    cs,
    {"GET", "/user_comments", "", {{"user_id", "0"}}},
    {200, {}, "Hello\nWhat are you selling?\n"}
  );
  Test(
    cs,
    {"GET", "/user_comments", "", {{"user_id", "1"}}},
    {200, {}, "Hi\nBuy my goods\nEnlarge\n"}
  );
  Test(
    cs,
    {"GET", "/captcha"},
    {200, {}, {"What's the answer for The Ultimate Question of Life, the Universe, and Everything?"}}
  );

  Test(cs, {"POST", "/checkcaptcha", "1 24"}, redirect_to_captcha);
  //hey1
  //    cerr << "hey23" << endl;
      //

  Test(cs, {"POST", "/checkcaptcha", "1 42"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Sorry! No spam any more"}, ok);
  Test(
    cs,
    {"GET", "/user_comments", "", {{"user_id", "1"}}},
    {200, {}, "Hi\nBuy my goods\nEnlarge\nSorry! No spam any more\n"}
  );

  Test(cs, {"GET", "/user_commntes"}, not_found);
  Test(cs, {"POST", "/add_uesr"}, not_found);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestServer<CommentServer>);
}
