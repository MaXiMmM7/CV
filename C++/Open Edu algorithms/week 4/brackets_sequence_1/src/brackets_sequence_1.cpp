
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

template <typename T>
class Stack{
public:
	Stack(size_t size_): data(size_),top(-1){}

	bool Empty() const{
		return (top == -1);
	}

	void Push(T value){
		data[++top] = value;
	}

	T Pop(){
		return data[top--];
	}

	T Top() const{
		return data[top];
	}

	void Clear(){
		top = -1;
	}

	size_t Capacity() const{
		return data.size();
	}
private:
	vector<T> data;
	int top;
};


bool Process(string& data){
	Stack<char> stack(10000);
	//
	//cout << stack.Capacity() << endl;
	//

	for(auto x: data){

		//
	//	cout << x << " ";
		//
		if(stack.Empty()){
			if(x == ')' || x == ']'){
				return false;
			}
			stack.Push(x);
		}else{
			if(x == '(' || x == '['){
				stack.Push(x);
			}else{
				if((stack.Top() == '(' && x == ')') || (stack.Top() == '[' && x == ']')){
					stack.Pop();
				}else{
					return false;
				}
			}
		}
	}


	//
	//cout << endl;
	//
	if(stack.Empty()){
		return true;
	}
	return false;
}

void Check(ifstream& input, ofstream& output){

	int N;
	input >> N;

	string helper;
	for( int i = 0; i < N; i++){
		input >> helper;
		//
		//cout << helper << endl;
		//
		if(Process(helper)){
			output << "YES\n";
		}else{
			output << "NO\n";
		}
	}
}

int main() {

	ifstream input("input.txt");
	ofstream output("output.txt");

	Check(input,output);

	return 0;
}
