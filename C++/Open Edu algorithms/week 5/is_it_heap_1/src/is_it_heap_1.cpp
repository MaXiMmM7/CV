
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std;

/*
int left(int i){
	return 2*i+1;
}

int right(int i){
	return 2*(i+1);
}


bool Heapify(vector<int> data, int i){
	int l = left(i);
	int r = right(i);
	int size_ = static_cast<int>(data.size());
	//int largest = i;

	if(l < size_ && data[l] < data[i]){
		return false;
	}

	if(r < size_ && data[r] < data[i]){
		return false;
	}

	return true;
}
*/

bool IsHeap(vector<int>& data){

//	bool flag;
	int size_ = static_cast<int>(data.size());
	int l,r;

	for(int i = (size_ / 2); i + 1 > 0; i--){
		l = 2*i+1;
		if(l < size_ && data[l] < data[i]){
			return false;
		}
		r = 2*(i + 1);
		if(r < size_ && data[r] < data[i]){
			return false;
		}

		/*flag = Heapify(data,i);
		if(!flag){
			return false;
		}*/
	}

	//return flag;
	return true;
}


void Process(ofstream& output, vector<int>& data){
	if(IsHeap(data)){
		output << "YES";
	}else{
		output << "NO";
	}
}

vector<int> ReadFile(ifstream& input){
	int n;
	input >> n;
	vector<int> result(n);
	for( int i = 0; i < n; i++){
		input >> result[i];
	}
	return result;
}

int main() {

	//
	ofstream output1("input2.txt");
	output1 << 1000000 << '\n';

	for( int i = -500000; i < 0; i++){
		output1 << i << " ";
	}
	for( int i = 0; i < 500000; i++){
		output1 << i << " ";
	}

	//
	auto start_time = std::chrono::steady_clock::now();
	//

	ifstream input("input2.txt");
	auto data = ReadFile(input);
	ofstream output("output.txt");
	Process(output, data);

	//
	auto end_time = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	std::cout << "Total time: " << elapsed_ms.count() << "\n";
	//


	return 0;
}
