
#include <iostream>
#include <fstream>
#include <vector>
#include <variant>
using namespace std;

class Priority_queue{
public:
	Priority_queue(){
		heap.resize(1000001);
		data.resize(1000001);
	}

	void Add(int value, int num_str){
		data[num_str].value = value;
		data[num_str].heap_pos = size_;
		heap[size_] = num_str;
		//
		//cout << " Add:  num_str = " << num_str << " value = " << value << " "
		//
		Decrease_key(size_++);
	}

	variant<int,char> ExtractMin() {
		if(size_ == 0){
			return '*';
		}
		int min = data[heap[0]].value;
		heap[0] = heap[--size_];
		data[heap[0]].heap_pos = 0;
		Heapify(0);
		return min;
	}

	void Change(int num_str, int y){
		data[num_str].value = y;
		Decrease_key( data[num_str].heap_pos);
	}
private:

	struct Value{
		int value;
		int heap_pos = -1;
	};


	void Decrease_key(size_t pos){//, int num_str){

//		heap[pos] = num_str;

		while ( pos > 0 && data[heap[pos]].value < data[heap[ (pos - 1) / 2 ]].value ){ //!!!!!!!!!!!!!!!!!!!!!!!
			int helper = heap[pos];
			heap[pos] = heap[ (pos - 1) / 2];
			heap[ (pos - 1) / 2] = helper;
			///////
			data[heap[pos]].heap_pos = pos;
			data[heap[(pos - 1) / 2]].heap_pos = (pos - 1) / 2;
			///////
			pos = ( pos - 1) / 2;
		}

		//data[num_str].heap_pos = 2 * pos + 1;
	}

	void Heapify(size_t pos){

		size_t min = pos;
		size_t l = 2 * pos + 1;
		size_t r = 2 * (pos + 1);

		if( l < size_ && data[heap[l]].value < data[heap[min]].value){
			min = l;
		}

		if( r < size_ && data[heap[r]].value < data[heap[min]].value){
			min = r;
		}

		if( min != pos){
			int helper = heap[pos];
			heap[pos] = heap[min];
			heap[min] = helper;
			//////
			data[heap[pos]].heap_pos = pos;
			data[heap[min]].heap_pos = min;
			/////
			Heapify(min);
		}
	}


	size_t size_ = 0;
	vector<int> heap;
	vector<Value> data;
};

void Process(ifstream& input, ofstream& output){
	int n;
	input >> n;
	//vector<int> numbers(n + 1);
	Priority_queue data;

	char helper;
	int value, str_num;

	for(int i = 0; i < n; i++){

		input >> helper;

		if( helper == 'A' ){
			input >> value;
	//		numbers[i + 1] = value;
			data.Add(value, i + 1);
		}else if( helper == 'X' ){
			auto min = data.ExtractMin();
			if( holds_alternative<int>( min )){
				output << get<int>(min) << '\n';
			}else{
				output << get<char>(min) << '\n';
			}
		}else if( helper == 'D'){
			input >> str_num >> value;
			data.Change(str_num , value);
//			numbers[str_num] = value;
		}
	}
}

int main() {

	ifstream input("input.txt");
	ofstream output("output.txt");
	Process(input, output);



	return 0;
}
