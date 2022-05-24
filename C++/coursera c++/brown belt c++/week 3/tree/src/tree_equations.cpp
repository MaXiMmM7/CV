#include "Common.h"
#include "test_runner.h"

#include <sstream>
#include <memory>
#include <utility>

using namespace std;


class Value_:public Expression {
public:

	Value_(int x):val(x){}
    // Вычисляет значение выражения
  int Evaluate() const override{
	  return val;
  }

  // Форматирует выражение как строку
  // Каждый узел берётся в скобки, независимо от приоритета
  std::string ToString() const override{
	  return to_string(val);
  }

private:
  int val;
};

class Operation:public Expression {
public:
	Operation(ExpressionPtr left,ExpressionPtr right,string o):l(move(left)),r(move(right)),oper(o){}
    // Вычисляет значение выражения
  int Evaluate() const override{
	  if(oper=="+"){
		  return (l->Evaluate())+(r->Evaluate());
	  }
		  return (l->Evaluate())*(r->Evaluate());
  }

  // Форматирует выражение как строку
  // Каждый узел берётся в скобки, независимо от приоритета
  std::string ToString() const override{
	  return "("+(l->ToString())+")"+oper+"("+(r->ToString())+")";
  }
private:
  unique_ptr<Expression> l;
  unique_ptr<Expression> r;
  string oper;

};

ExpressionPtr Value(int value){
	return make_unique<Value_>(value);
}
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right){
	return make_unique<Operation>(move(left),move(right),"+");
}
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right){
	return make_unique<Operation>(move(left),move(right),"*");
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
