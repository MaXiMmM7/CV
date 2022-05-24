#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using namespace std;


struct Email {
  string from;
  string to;
  string body;
  Email(string f,string t, string b):from(f),to(t),body(b){}
  Email(){}
};


class Worker {
public:
  virtual ~Worker() = default;
  virtual void Process(unique_ptr<Email> email) = 0;
  virtual void Run() {
    // только первому worker-у в пайплайне нужно это имплементировать
    throw logic_error("Unimplemented");
  }

protected:
  // реализации должны вызывать PassOn, чтобы передать объект дальше
  // по цепочке обработчиков
  void PassOn(unique_ptr<Email> email) const{
	  if(next.get()!=nullptr){

	  next->Process(move(email));
	  }
  }


  unique_ptr<Worker> next;
public:
  void SetNext(unique_ptr<Worker> n){
	  next=move(n);
  }
};


class Reader : public Worker {
public:
  Reader(istream& s):stream(s){}

  void Run() override{
	 while(stream){
    	  unique_ptr<Email> object=make_unique<Email>();
    	  getline(stream, object->from);
    	 if(stream.eof()){break;}
    	  getline(stream,object->to);
    	  if(stream.eof()){break;}
    	  getline(stream,object->body);

    	  PassOn(move(object));
     }
   }

  void Process(unique_ptr<Email> email){}


protected:
   istream& stream;
};


class Filter : public Worker {
public:
  using Function = function<bool(const Email&)>;

public:

 Filter(function<bool(const Email&)> pred):f(pred){ }

  void Process(unique_ptr<Email> email) override{
   if(f(*email)){
	   PassOn(move(email));
   }
 }

private:
 function<bool(const Email&)> f;
};


class Copier : public Worker {
public:
  Copier(const string& a):adress(a){}

  void Process(unique_ptr<Email> email) override{
	  if(email->to!=adress){
 	   unique_ptr<Email> one=make_unique<Email>(email->from,adress,email->body);

 	   PassOn(move(email));
 	  PassOn(move(one));
 	  return;
    }

	  PassOn(move(email));
  }

private:
  string adress;
};


class Sender : public Worker {
public:

		Sender(ostream& s):stream(s){ }

	void Process(unique_ptr<Email> email) override{
		 	   stream << email->from << "\n" << email->to<< "\n" << email->body << "\n";
		 	   PassOn(move(email));
	  }

protected:
  ostream& stream;
};


// реализуйте класс
class PipelineBuilder {
public:
  // добавляет в качестве первого обработчика Reader
  explicit PipelineBuilder(istream& in){
  result=make_unique<Reader>(in);
  current=result.get();
  }

  // добавляет новый обработчик Filter
  PipelineBuilder& FilterBy(Filter::Function filter){
	  unique_ptr<Filter> object=make_unique<Filter>(filter);
			  Filter* helper=object.get();
	  current->SetNext(move(object));
	  current=helper;
	  return *this;

  }

  // добавляет новый обработчик Copier
  PipelineBuilder& CopyTo(string recipient){
	  unique_ptr<Copier> object=make_unique<Copier>(recipient);
	  Copier* helper=object.get();
	  	  current->SetNext(move(object));
	  	  current=helper;
	  	  return *this;
  }

  // добавляет новый обработчик Sender
  PipelineBuilder& Send(ostream& out){
	  unique_ptr<Sender> object=make_unique<Sender>(out);
	  	  Sender* helper=object.get();
	  	  	  current->SetNext(move(object));
	  	  	  current=helper;
	  	  	  return *this;
  }

  // возвращает готовую цепочку обработчиков
  unique_ptr<Worker> Build(){
	  return move(result);
  }

  unique_ptr<Worker> result;
  Worker* current;
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
  return 0;
}
