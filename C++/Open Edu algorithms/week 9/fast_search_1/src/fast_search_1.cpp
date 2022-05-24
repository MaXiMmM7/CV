
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int Int(char x){
	return (x - 0);
}

int64_t Hash(string& str, int start, int count, int p , int x){
	int64_t hash_ = 0;
	for( int i = start; i < count; i++){
		hash_ = (hash_ * x + Int(str[i])) % p;
	}

	return hash_;
}

int M_1(int x, int m, int p){
	int res = 1;
	for( int i = 1; i < m; i++){
		res = (res * x) % p;
	}
	return res;
}

vector<int>Find( string& str, string& sub_str){
	int N = static_cast<int>(str.size());
	int M = static_cast<int>(sub_str.size());
	vector<int> res;

	if( M > N ){
		return res;
	}

	int x = 29;
	int p = 10000121;
	int m = M_1(x, M, p);
	int64_t hash_sub = Hash(sub_str, 0, M, p, x);
	int64_t hash_str = Hash(str, 0, M, p, x);

	//
//	cout << hash_sub << " has_str = " << hash_str  << " m = " << m << endl;
	//

	for( int i = 0; i - 1 < N - M ; i++){
		//
		//cout << " i = " << i << " hash_str = " << hash_str << " hash_sub = " << hash_sub << endl;
		//
		if(hash_str == hash_sub){

			bool flag = true;

			for( int j = 0; j < M; j++){
				if( str[i + j] != sub_str[j]){
					flag = false;
					break;
				}
			}

			if(flag){
				res.push_back(i);
			}
		}

		hash_str += p; // это оказалось ултра важным для
		//корректности (так как после взятия остатка может оказаться маленькое число,
		//а из него потом юудет вычитаться большое
		hash_str -=  (Int(str[i]) * m) % p;
		hash_str *= x;
		hash_str += Int(str[ i + M]);
		hash_str %= p;
	}

	return res;
}

void Process(ifstream& input, ofstream& output){

	string str, sub_str;
	input >> sub_str >> str;

	//
//	cout << sub_str<< endl << str<< endl;
	//
	auto res = Find( str, sub_str);

	output << res.size() << '\n';
	for( auto x: res){
		output << (x + 1) << ' ';
	}
}

int main() {

	ifstream input("input.txt");

	ofstream output("output.txt");

	Process(input, output);

	return 0;
}
