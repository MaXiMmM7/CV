

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;



void WorkWithStack(ifstream& input, ofstream& output){
	vector<int> stack(1000000);
	int top = -1;
	char helper;
	int M;
	input >> M;

	for(int i = 0; i < M; i++){
		input >> helper;

		if( helper == '+'){
			input >> stack[++top];
		}else{
			output << stack[top--] << "\n";
		}
	}
}

int main() {


	ifstream input("input.txt");
	ofstream output("output.txt");
	WorkWithStack(input, output);
	return 0;
}
