#include "Common.h"
#include "test_runner.h"
#include <memory>
#include <utility>
#include <string>

#include <sstream>
using namespace std;

class Operation: public Expression{
public:
	explicit Operation(const string& o, unique_ptr<Expression> l,unique_ptr<Expression> r):
	    oper_(o),
		l_(move(l)),
		r_(move(r)){}

	int Evaluate() const {
		if(oper_=="+"){
			  return (l_->Evaluate()+r_->Evaluate());
		}
		  return (l_->Evaluate()*r_->Evaluate());
		  }

		  std::string ToString() const {
			 return "("+l_->ToString()+")"+oper_+"("+r_->ToString()+")";
		 }

private:
		  string oper_;
		  unique_ptr<Expression> l_;
		  unique_ptr<Expression> r_;
};

class Value_: public Expression{
public:
	explicit Value_(int v):value_(v){}
	  int Evaluate() const {
		  return value_;
	  }

	  std::string ToString() const {
		 return to_string(value_);
	 }

private:
	 int value_;
};

ExpressionPtr Value(int value){
	return make_unique<Value_>(value);
}
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right){
	return make_unique<Operation>("+",move(left),move(right));
}

ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right){
	return make_unique<Operation>("*",move(left),move(right));
}


string Print(const Expression* e) {
  if (!e) {
    return "Null expression provided";
  }
  stringstream output;
  output << e->ToString() << " = " << e->Evaluate();
  return output.str();
}

void Test() {
  ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
  ASSERT_EQUAL(Print(e1.get()), "(2)*((3)+(4)) = 14");

  ExpressionPtr e2 = Sum(move(e1), Value(5));
  ASSERT_EQUAL(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19");

  ASSERT_EQUAL(Print(e1.get()), "Null expression provided");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, Test);
  return 0;
}
