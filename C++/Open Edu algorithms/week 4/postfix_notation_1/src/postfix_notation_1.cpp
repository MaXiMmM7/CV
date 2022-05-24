
#include <iostream>
#include <stack>
#include <fstream>
#include <utility>
#include <memory>
#include <cctype>
using namespace std;

class Node{
public:
	virtual int Evaluate() const = 0;
	virtual ~Node(){};
private:

};

class Value: public Node{
public:

	Value(int val): value_(val){}

	int Evaluate() const override{
		return value_;
	}

private:
int value_;
};


class Token: public Node{
public:

	Token(unique_ptr<Node> l, unique_ptr<Node> r): left_(move(l)),right_(move(r)){}
	int Evaluate() const final{
		return Process(left_->Evaluate(), right_->Evaluate());
	}
private:
	virtual int Process(int l, int r) const = 0;
	unique_ptr<Node> left_, right_;
};

class Plus: public Token{
public:
	using Token::Token;
private:
	int Process(int l, int r) const final{
		//
		//cout << "Process: ( " << l << " + " << r << " )\n";
		//
		return r + l;
	}
};

class Minus: public Token{
public:
	 using Token::Token;
private:
	int Process( int l, int r) const final{
		//
	//			cout << "Process: ( " << l << " - " << r << " )\n";
				//
		return l - r;
	}
};

class Multiplication: public Token{
public:
	using Token::Token;
private:
	int Process ( int l, int r) const final{
		//
		//		cout << "Process: ( " << l << " * " << r << " )\n";
				//
		return l * r;
	}
};



unique_ptr<Node> Val(int val){
	return make_unique<Value>(val);
}

unique_ptr<Node> Sum(unique_ptr<Node> l, unique_ptr<Node> r ){
	return make_unique<Plus>(move(l), move(r));
}

unique_ptr<Node> Substract(unique_ptr<Node> l, unique_ptr<Node> r ){
	return make_unique<Minus>(move(l), move(r));
}

unique_ptr<Node> Multiply(unique_ptr<Node> l, unique_ptr<Node> r ){
	return make_unique<Multiplication>(move(l), move(r));
}



stack<char> ReadFile(ifstream& input){
	char helper;
	stack<char> result;

	int size_;
	input >> size_;

	for(int i = 0; i < size_; i++){
		input >> helper;
		result.push(helper);
	}

	//cout << result.size() << endl;
	return result;
}


char Pop( stack<char>& data ){
	char helper = data.top();
	data.pop();
	return helper;
}

unique_ptr<Node> CreateExpression( stack<char>& data){
	char helper;

	if(!data.empty()){
		helper = Pop(data);
	}

	//
	/*cout << "helper = " << helper;
	if(!data.empty()){
		cout << " top = " << data.top();
	}
	cout << endl;
	*/
	//

	if(!isdigit(helper)){

		unique_ptr<Node> right_ptr = CreateExpression(data);
		unique_ptr<Node> left_ptr = CreateExpression(data);

		if( helper == '+'){
			return Sum(move(left_ptr), move(right_ptr));
		}
		if( helper == '-'){
			return Substract(move(left_ptr), move(right_ptr));
		}
		if( helper == '*'){
			return Multiply(move(left_ptr), move(right_ptr));
		}
	}

	return Val(helper - '0');

}

int main() {

	ifstream input("input.txt");

	auto data = ReadFile(input);
	auto expr = CreateExpression(data);

	ofstream output("output.txt");
	output << expr->Evaluate();

	return 0;
}
