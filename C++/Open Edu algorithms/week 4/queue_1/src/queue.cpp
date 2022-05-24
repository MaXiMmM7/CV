
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

void Process(ifstream& input, ofstream& output){
	vector<int> queue(1000000);
	int head = 0;
	int tail = 0;
	char helper;
	int M;
	input >> M;

	for( int i = 0; i < M; i++){
		input >> helper;
		if( helper == '+'){
			input >> queue[tail++];
		}else{
			output << queue[head++] << '\n';
		}

	}
}


int main() {

	ifstream input("input.txt");
	ofstream output("output.txt");
	Process(input,output);
	return 0;
}
