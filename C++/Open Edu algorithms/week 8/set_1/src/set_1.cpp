#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <cmath>
using namespace std;

class Hash_table{
public:

	Hash_table(int N):table_(N), size_(N){}

	void Add(int64_t x){
		int index = hash_func(x);
		auto It = Find(x, index);
		if( It == table_[index].end()){
			table_[index].insert(It, x);
		}
	}
	void Delete(int64_t x){
		int index = hash_func(x);
		auto It = Find(x, index);
		if( It != table_[index].end()){
			table_[index].erase(It);
		}
	}

	bool Exist(int64_t x){
		int index = hash_func(x);
		auto It = Find(x, index);

		if( It != table_[index].end()){
			return true;
		}

		return false;
	}
private:

	list<int64_t>::iterator Find(int64_t x, int index){
		auto It = table_[index].begin();
		while(It != table_[index].end() && *It != x){
			It++;
		}
		return It;
	}

	int hash_func(int64_t x){
		return abs(x) % size_;
	}

	vector<list<int64_t>> table_;
	int size_ = 0;
};


void Process( ifstream& input, ofstream& output){
	int N;
	input >> N;
	Hash_table table(N);

	char command;
	int64_t value;

	for( int i = 0; i < N; i++){

		input >> command >> value;

		if( command == 'A'){
			table.Add(value);
		}else if( command == 'D'){
			table.Delete(value);
		}else if( command == '?'){
			if( table.Exist(value)){
				output << "Y\n";
			}else{
				output << "N\n";
			}
		}
	}
}

int main() {

	ifstream input("input.txt");
	ofstream output("output.txt");
	Process( input, output);
	return 0;
}
