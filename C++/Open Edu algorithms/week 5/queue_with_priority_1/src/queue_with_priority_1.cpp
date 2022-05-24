
#include <iostream>
#include <vector>
#include <fstream>
#include <variant>
#include <string>
using namespace std;

template <typename T>
class Priority_queue{
public:
	Priority_queue(){
	queue.resize(1000000);
	}

	void Add(T val){
	//	queue.resize(++size_);

		//Increase_key(size_ -  1, val);
		Increase_key((++size_ -  1), val);

		//
	/*	cout << "Add: " << val << endl;
		for(size_t i = 0; i < size_; i++){
			cout << queue[i] << " ";
		}
*/
		//cout << endl;
		//

	}

	variant<T,char> ExtractMinimum(){
		if(size_ == 0){
			return '*';
		}
		T result = queue[0];
		if(--size_ > 0){
			queue[0] = queue[size_];
			Heapify(0);
		}
	//	queue.resize(size_);
		//
		/*	cout << "Extract: " << endl;
			for(size_t i = 0; i < size_; i++){
						cout << queue[i] << " ";
					}
			cout << endl;*/
			//
		return result;
	}

	void Change(T key, T new_key){
		size_t pos = 0;
		/*while(queue[pos] != key){
			pos++;
		}*/
		for(;pos < size_; pos++){
			if(queue[pos] == key){
				break;
			}
		}

		//
		if(queue[pos] != key){
					while(size_ > 0){

					}
				}
		//

		Increase_key(pos, new_key);

		//
		/*	cout << "Change:  old " << key << " new: " << new_key << endl;
			for(size_t i = 0; i < size_; i++){
						cout << queue[i] << " ";
					}
			cout << endl;*/
			//
	}

private:
	void Increase_key(size_t pos, T new_key){
		//
		//cout << "size: " << size_ << endl;

		//
		queue[pos] = new_key;
		while(pos > 0 && queue[pos] < queue[(pos - 1)/2]){
			T helper = queue[pos];
			queue[pos] = queue[(pos - 1)/2];
			queue[(pos - 1)/2] = helper;
			pos = (pos - 1)/2;
		}
	}

	void Heapify(size_t pos){
		size_t minimum = pos;
		size_t l = pos*2 + 1;
		size_t r = 2 * (pos + 1);

		if( l < size_ && queue[l] < queue[minimum]){
			minimum = l;
		}

		if( r < size_ && queue[r] < queue[minimum]){
			minimum = r;
		}

		if( minimum != pos){
			T helper = queue[minimum];
			queue[minimum] = queue[pos];
			queue[pos] = helper;
			Heapify(minimum);
		}
	}


	size_t size_ = 0;
	vector<T> queue;
};

void Process(ifstream& input, ofstream& output){
	int n;
	input >> n;
	vector<int> numbers(n+1);
	char helper;
	int value, value2;

	Priority_queue<int> queue;

	//
//	cout << "start  n = " << n  <<  endl;
	//
//	int j = 1;
	for( int i = 0; i < n; i++){// до того, как while на for исправил вообще было не WA, a RE
		//cout << "hey" << endl;
		input >> helper;

		//
	//	cout << " i = " << i << " helper = " << helper << endl;
		//

		if( helper == 'A'){
			input >> value;
			numbers[i + 1] = value;
		//	numbers[j++] = value;

			queue.Add(value);
			//
						//cout << " here" << endl;
					//	break;
						//
		}else if( helper == 'X'){
			auto result =  queue.ExtractMinimum();
			if(holds_alternative<int>(result)){
				output << get<int>(result) << '\n';
			}else{
				output << get<char>(result) << '\n';
			}
		}else if( helper == 'D'){
			input >> value >> value2;
			queue.Change(numbers[value],value2);
		}
	}
}

int main() {

//string s = "A 3";
//cout << "s[0] = " << s[0]  << "s[1] = " << s[1]  << "s[2] = " << s[2] << endl;
	//
	/*ofstream in("input1.txt");
	int i = 0;
	in << 100 << '\n';
	for(; i < 40; i++ ){
		in << "A " << i << '\n';
	}
	int j = -5;
	for(; i < 65; i++ ){
		in << "D  " << (i - 30) << " " << j-- << '\n';
	}
	for(; i < 100; i++){
		in << 'X' << '\n';
	}

*/
	//
	//cout << "Hello" << endl;
	//

	ifstream input("input.txt");
	ofstream output("output.txt");
	Process(input,output);
	return 0;
}
