
#include <iostream>
#include <fstream>
#include <vector>
#include <variant>
using namespace std;

class Priority_queue{
public:
	Priority_queue(){
		heap.resize(1000001);
	}

	void Add(int value){
		Decrease_key(size_++, value);
	}

	variant<int,char> ExtractMin() {
		if(size_ == 0){
			return '*';
		}
		int min = heap[0];
		heap[0] = heap[--size_];
		Heapify(0);
		return min;
	}

	void Change(int x, int y){
		size_t pos = 0;
		for( ; pos < size_; pos++){
			if( heap[pos] == x){
				break;
			}
		}

		Decrease_key( pos, y);
	}
private:
	void Decrease_key(size_t pos, int value){

		heap[pos] = value;

		while ( pos > 0 && heap[pos] < heap[ (pos - 1) / 2 ]){
			int helper = heap[pos];
			heap[pos] = heap[ (pos - 1) / 2];
			heap[ (pos - 1) / 2] = helper;
			pos = ( pos - 1) / 2;
		}
	}

	void Heapify(size_t pos){

		size_t min = pos;
		size_t l = 2 * pos + 1;
		size_t r = 2 * (pos + 1);

		if( l < size_ && heap[l] < heap[min]){
			min = l;
		}

		if( r < size_ && heap[r] < heap[min]){
			min = r;
		}

		if( min != pos){
			int helper = heap[pos];
			heap[pos] = heap[min];
			heap[min] = helper;
			Heapify(min);
		}
	}

	size_t size_ = 0;
	vector<int> heap;
};

void Process(ifstream& input, ofstream& output){
	int n;
	input >> n;
	vector<int> numbers(n + 1);
	Priority_queue data;

	char helper;
	int value, str_num;

	for(int i = 0; i < n; i++){

		input >> helper;

		if( helper == 'A' ){
			input >> value;
			numbers[i + 1] = value;
			data.Add(value);
		}else if( helper == 'X' ){
			auto min = data.ExtractMin();
			if( holds_alternative<int>( min )){
				output << get<int>(min) << '\n';
			}else{
				output << get<char>(min) << '\n';
			}
		}else if( helper == 'D'){
			input >> str_num >> value;
			data.Change(numbers[str_num], value);
			numbers[str_num] = value;
		}
	}
}

int main() {

	ifstream input("input.txt");
	ofstream output("output.txt");
	Process(input, output);



	return 0;
}
