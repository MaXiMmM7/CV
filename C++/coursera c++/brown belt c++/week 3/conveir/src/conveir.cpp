#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>

using namespace std;



struct Email {
  string from;
  string to;
  string body;
};

istream& operator>>(istream& in,Email& e){
	getline(in,e.from);
	getline(in,e.to);
	getline(in,e.body);
	return in;
}
/*
struct Email {
  string from;
  string to;
  string body;
  Email(string f,string t, string b):from(f),to(t),body(b){}
  Email(){}
};*/


class Worker {
public:
  virtual ~Worker() = default;
  virtual void Process(unique_ptr<Email> email) = 0;
  virtual void Run() {
    // только первому worker-у в пайплайне нужно это имплементировать
    throw logic_error("Unimplemented");
  }

protected:
  unique_ptr<Worker> next_worker=nullptr;
  // реализации должны вызывать PassOn, чтобы передать объект дальше
  // по цепочке обработчиков
  void PassOn(unique_ptr<Email> email) const{
	  if(next_worker!=nullptr){
		  next_worker->Process(move(email));
	  }

  }

public:
  void SetNext(unique_ptr<Worker> next){
	  next_worker=move(next);
  }
};



class Reader : public Worker {
public:
	Reader(istream& in):stream(in){	}
	void Run() override{
		Email e;
		while(stream>>e){
			Process(move(make_unique<Email>(e)));
			}

	}

	void Process(unique_ptr<Email> email) override{
		PassOn(move(email));
	}
	private:
	istream& stream;
};


/*
class Reader : public Worker {
public:
  Reader(istream& s):stream(s){}

  void Run() override{
	  Email e;
	 while(stream){
		// Email e;
		 stream >> e;

    	 Process(move(make_unique<Email>(e)));
    	// if(stream.eof()){break;}

     }
   }

  void Process(unique_ptr<Email> email){
	  PassOn(move(email));
  }


protected:
   istream& stream;
};
*/

class Filter : public Worker {
public:
	using Function = function<bool(const Email&)>;
private:
	  Function f;
public:
  Filter(Function fun):f(fun){ }

  void Process(unique_ptr<Email> email) override{
	  if(f(*email)){
		  PassOn(move(email));
	  }
  	}
};


class Copier : public Worker {
private:
	string to;
public:
	Copier(const string& s):to(s){}
	void Process(unique_ptr<Email> email) override{
		if(to!=email->to){
			Email e;
			e.from=email->from;
			e.to=to;
			e.body=email->body;
			PassOn(move(email));
			PassOn(move(make_unique<Email>(e)));
		}
		else{
			PassOn(move(email));
		}
		}
};


class Sender : public Worker {
private:
	ostream& stream;
public:
	Sender(ostream& os):stream(os){}
	void Process(unique_ptr<Email> email) override{
		stream << email->from << "\n" << email->to << "\n" << email->body  << endl;
		PassOn(move(email));
	}
};


// реализуйте класс
class PipelineBuilder {
public:

	// добавляет в качестве первого обработчика Reader
  explicit PipelineBuilder(istream& in){
	  workers.push_back(make_unique<Reader>(in));
  }

  // добавляет новый обработчик Filter
  PipelineBuilder& FilterBy(Filter::Function filter){
	  workers.push_back(make_unique<Filter>(filter));
	  return *this;
  }

  // добавляет новый обработчик Copier
  PipelineBuilder& CopyTo(string recipient){
	  workers.push_back(make_unique<Copier>(recipient));
	  return *this;
  }

  // добавляет новый обработчик Sender
  PipelineBuilder& Send(ostream& out){
	  workers.push_back(make_unique<Sender>(out));
	  return *this;
  }


  // возвращает готовую цепочку обработчиков
  unique_ptr<Worker> Build(){
	  auto It=next(workers.rbegin());
	  while(It!=workers.rend()){
		  It->get()->SetNext(move(*prev(It)));
		  It++;
	  }
	  return move(*workers.begin());


  }

  vector<unique_ptr<Worker>> workers;
};


void TestSanity() {
  string input = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "ralph@example.com\n"
    "erich@example.com\n"
    "I do not make mistakes of that kind\n"
  );
  istringstream inStream(input);
  ostringstream outStream;

  PipelineBuilder builder(inStream);

  builder.FilterBy([](const Email& email) {
    return email.from == "erich@example.com";
  });
   builder.CopyTo("richard@example.com");
  builder.Send(outStream);
  auto pipeline = builder.Build();
   pipeline->Run();
  string expectedOutput = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "erich@example.com\n"
    "richard@example.com\n"
    "Are you sure you pressed the right button?\n"
  );

  ASSERT_EQUAL(expectedOutput, outStream.str());

}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSanity);
 // cerr << "\n\n\nyes\n\n\n" << endl;
  return 0;
}
