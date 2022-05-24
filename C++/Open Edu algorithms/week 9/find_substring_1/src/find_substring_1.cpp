
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

/*
uint64_t Hash_char(char x){
	return ( x - 0);
}

uint64_t Hash_string(string s){
	size_t x = 7;
	size_t p = 999983;

	uint64_t hash_ = 0;
	for( size_t i = 0; i < s.size(); i++){
		hash_ = x * hash_ + Hash_char(s[i]);
	}
	hash_ = hash_ % p;

	return hash_;
}

uint64_t m_( size_t x, int M){
	if(M == 0){
		return 1;
	}
	uint64_t res = x;

	for(int i = 1; i < M; i++){
		res *= x;
	}

	return res;
}

vector<size_t> Build( string& s, int M){
	int N = static_cast<int>(s.size());
	vector<size_t> res;
	size_t x = 7;
	size_t p = 999983;

	uint64_t m = m_( x, M);
	//
	//cout << " m = " << m << endl;
	//
	uint64_t hash_ = Hash_string(s.substr(0, M));
	res.push_back(hash_);

	for(int i = 1; i - 1 < N - M; i ++ ){
		//
	//	cout << " i - 1 = " <<  (i - 1) << " i + M - 1 " << (i + M - 1)  << " char = " << Hash_char(s[i + M - 1])<< endl;
		//
		hash_ = (hash_ * x - Hash_char(s[i - 1]) * m + Hash_char(s[i + M - 1])) % p;
		res.push_back(hash_);
	}

	return res;
}

vector<int> FindSubstr(string& sub, string& s){
	vector<int> res;
	int N = static_cast<int>(s.size());
	int M = static_cast<int>(sub.size());

	if(N < M){
		return res;
	}
	uint64_t hash_sub = Hash_string(sub);
	vector<uint64_t> hash_s = Build(s, M);
	//size_t hash_i = Hash_string(s.substr(0, M));
	//
	//cout << N << " " << M << endl;
	//

	for(int i = 0; i - 1 < N - M; i ++ ){
		//
	//	cout << "i = " << i << " " << hash_s[i] << " " << hash_sub << '\n';
		//
		if( hash_s[i] != hash_sub){
			continue;
		}

		bool flag = true;
		for( int j = 0; j < M; j++){
			if( s[i+j] != sub[j]){
				flag = false;
				break;
			}
		}
		if( flag ){
			res.push_back(i);
		}
	}

	return res;
}

*/

vector<int> FindSubstr(string& sub, string& s){
	vector<int> res;
	int N = static_cast<int>(s.size());
	int M = static_cast<int>(sub.size());

	if(N < M){
		return res;
	}

	for(int i = 0; i - 1 < N - M; i ++ ){
		bool flag = true;
		for( int j = 0; j < M; j++){
			if( s[i+j] != sub[j]){
				flag = false;
				break;
			}
		}
		if( flag ){
			res.push_back(i);
		}
	}

	return res;
}

void Process( ifstream& input, ofstream& output){
	string sub,s;
	input >> sub >> s;

	//

	//
	auto res = FindSubstr( sub, s);

	output << res.size() << '\n';
	for(auto x: res){
		output << (x + 1) << " ";
	}
}

int main() {

	ifstream input("input.txt");

	ofstream output("output.txt");

	Process(input, output);

	return 0;
}
