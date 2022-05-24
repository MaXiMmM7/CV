
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

void Process(ifstream& input, ofstream& output){
	int size_ = 1000000;
	vector<int> queue(size_);
//
	//cout << queue.size() << endl;
	//
	int head = 0;
	int tail = 0;
	char helper;
	int M, new_tail,min;
	input >> M;

	for( int i = 0; i < M; i++){
		//
		//cout << head << " " << tail << endl;
		//
		input >> helper;
		if( helper == '+'){
			if(tail >= size_){
				tail = 0;
			}

			input >> queue[tail++];
		}else if(helper == '-'){
			if(head >= size_){
				head = 0;
			}
			queue[head++];
		}else{
			//new_head = tail;
			new_tail = tail;
			min = queue[head];
			while(head != tail){
				if(new_tail >= size_){
					new_tail = 0;
				}
				if(head >= size_){
					head = 0;
				}
				if( queue[head] < min){
					min = queue[head];
				}
				queue[new_tail++] = queue[head++];
			}
			tail = new_tail;
			output << min << '\n';
		}

	}
}


int main() {

	ifstream input("input.txt");
	ofstream output("output.txt");
	Process(input,output);
	return 0;
}
