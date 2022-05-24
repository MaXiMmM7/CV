#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <cmath>
#include <string>
#include <variant>
#include <functional>
using namespace std;

class Hash_table{
public:

	Hash_table(int N):table_(N), size_(N){ //letters(26),
	/*	for( int i = 0; i < 26; i++){
			letters[i] = char(i + 97);
		}
		*/
	}

	void Add(string key, string x ){

		int index = hash_func(key);
		auto It = Find(key, index);

		if( It == table_[index].end()){

			Key new_key;
			new_key.key = key;
			new_key.value = x;

			if(!prev.empty()){
				new_key.prev = prev;
				auto It_prev = Find(prev, hash_func(prev));
				It_prev->next = key;
			}

			prev = key;
			table_[index].insert(It, new_key);

		}else{
			It->value = x;
		}
	}

	void Delete(string key){
		int index = hash_func(key);
		auto It = Find(key, index);
		if( It != table_[index].end()){
			if(!It -> prev.empty()){
				auto It_prev = Find(It -> prev, hash_func(It -> prev));
				It_prev->next = It->next;
			}
			if(!It -> next.empty()){
				auto It_next = Find(It -> next, hash_func(It -> next));
				It_next->prev = It->prev;
			}
			if(prev == key){
				prev = It->prev;
			}
			table_[index].erase(It);
		}
	}

	variant<string,bool> Get(string key){
		int index = hash_func(key);
		auto It = Find(key, index);

		if( It != table_[index].end()){
	//		return letters[It->value];
			return It->value;
		}

		return false;
	}

	variant<string,bool> Prev(string key){


		int index = hash_func(key);
		auto It = Find(key, index);

		//
		/*
		for(auto y : table_){
			for(auto x: y ){
				cout << x.key << " next = " << x.next << " prev = " << x.prev;
			}
			cout << " / ";
		}
		cout << " \nPREV " << key << " index = " << index << " " << It->key<<   endl;
		cout << (It != table_[index].end()) << endl;
		*/
		//
		if( It != table_[index].end()){
			//
			//cout << "we are inside\n";
			//
			if( !It->prev.empty()){
				auto It_prev = Find(It -> prev, hash_func(It -> prev));
				//return letters[It_prev->value];
				return It_prev->value;
			}
		}

		return false;
	}

	variant<string,bool> Next(string key){
		int index = hash_func(key);
		auto It = Find(key, index);

		if( It != table_[index].end()){
			if( !It->next.empty()){
				auto It_next = Find(It -> next, hash_func(It -> next));
				//return letters[It_next->value];
				return It_next->value;
			}
		}

		return false;
	}

private:

	struct Key{
		string key;
		//int value;
		string value;
		string prev;
		string next;
	};

	list<Key>::iterator Find(string x, int index){
		auto It = table_[index].begin();
		while(It != table_[index].end() && It->key != x){
			It++;
		}
		return It;
	}


	int hash_char(char x){
		return (x - 97);
	}


	/*int hash_func(string key){
		int t = 31;
		int res = 0;
		int s = static_cast<int>(key.size()) - 1;
		int p = 100043;
		for( int i = 0; i < s; i ++ ){
			res += hash_char(key[i]) * pow( t, (s - i));
		}
		res = res % p;
		return abs(res) % size_;
	}
*/
	int hash_func(string key){
		return hash<string>{}(key) % size_;
		}

	vector<list<Key>> table_;
	//vector<char> letters;
	int size_ = 0;
	string prev;
};


void Process( ifstream& input, ofstream& output){
	int N;
	input >> N;
	Hash_table table(N);

	string command, key, value;
	//char value;

	for( int i = 0; i < N; i++){

		input >> command >> key;

		if( command == "put"){
			//
		//	cout << i << " put " << key  << endl;
			//
			input >> value;
			table.Add( key, value);
		}else if( command == "delete"){
			//
		//	cout << i << " delete " << key << endl;
			//
			table.Delete(key);
		}else if( command == "get"){
			//
		//	cout << i << " get " << key << endl;
			//
			auto x = table.Get(key);
			if( holds_alternative<string>(x)){
				output << get<string>(x) <<'\n';
			}else{
				output << "<none>\n";
			}
		}else if( command == "prev"){
			//
		//	cout << i << " prev " << key << endl;
			//
			auto x = table.Prev(key);
			if( holds_alternative<string>(x)){
				output << get<string>(x) <<'\n';
			}else{
				output << "<none>\n";
			}

		}else if( command == "next"){
			//
		//	cout << i << " next " << key << endl;
			//
			auto x = table.Next(key);
			if( holds_alternative<string>(x)){
				output << get<string>(x) <<'\n';
			}else{
				output << "<none>\n";
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
