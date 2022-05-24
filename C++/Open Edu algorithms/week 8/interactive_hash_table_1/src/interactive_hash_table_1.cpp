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

	Hash_table(size_t N):table_(2*N, -1), size_(2*N){
	/*	c1 = 1;
		while( N % c1 == 0){
			c1++;
		}
		c2 = c1++;
		while( N % c2 == 0){
			c2++;
		}*/

	}

	void Add(int64_t x){
		//
	//	cout << "Add start" << endl;

		//
		size_t pos = Find(x);
		table_[pos] = x;
		//
	//	cout << "Add finish" << endl;
		//
	}

	bool Exist( int64_t x){
		//
	/*	cout << table_.size() << endl;
		for(auto x: table_){
						cout << x << " ";
					}
		cout << "Exist start" << endl;
		for(auto x: table_){
					cout << x << " ";
				}
				*/
		//
		size_t pos = Find(x);
		if( table_[pos] == x){
			//
//			cout << "exist true finish" << endl;
			//
			return true;
		}
		//
//		cout << "exist false finish" << endl;
		//
		return false;
	}



private:

	size_t Find( int64_t x ){
		size_t i = 0;
		size_t next = Next(x, i);

		while( table_[next] != x && table_[next] != -1 ){

			next = Next( x, ++i );
		}

		return next;
	}

	size_t Next(int64_t x, size_t i){
		return (hash_func_2(x) + i*hash_func_1(x)) % size_;
	}

	size_t hash_func_2(int64_t key){
		return hash<int64_t>{}(key) ;
	}

	size_t hash_func_1(int64_t key){
		double A = (sqrt(5) - 1 ) / 2;
		double res = key * A;
		res = res - int(res);
		//
	//	cout << res << endl;
		//
		res *= size_;
		//
	//	cout << " size  = " << size_ << " res = " << int(res) << endl;
		//
		return int(res);
	}

	/*
	size_t hash_func_2(int64_t key, size_t i){
		return (hash<int64_t>{}(key) + c1*i + c2 * i * i) ;
	}

	size_t Next(int64_t x, size_t i){
		return (hash_func_1(x) + i * hash_func_2(x, i)) % size_;
	}




	size_t hash_func_2(int64_t key, size_t i){
		return (hash<int64_t>{}(key) + c1*i + c2 * i * i) ;
	}
*/

	vector<int64_t> table_;
	size_t size_ = 0;
	//size_t c1, c2;
	//size_t c1 = 11689;
	//size_t c2 = 79;
};


void Process( ifstream& input, ofstream& output){
	size_t N;
	input >> N;
	Hash_table table(N);

	int64_t X, B, B_c, B_d;
	uint16_t A, A_c, A_d;
	input >> X >> A >> B >> A_c >> B_c >> A_d >> B_d;

	for( size_t i = 0; i < N; i++){


		//
	//	cout << " I  ================ " << i << endl;
	//	cout << "X = " << X << " A = " << A << " B = " << B << endl;
		//
		if( table.Exist(X)){
			//
		//	cout << "TRUE\n";
			//
			A = (A + A_c) % 1000;
			B = (B + B_c) % 1000000000000000;
		}else{
			table.Add(X);
			A = (A + A_d) % 1000;
			B = (B + B_d) % 1000000000000000;
		}

		X = (X * A + B) % 1000000000000000;
	}

	//
		//	cout << "X = " << X << " A = " << A << " B = " << B << endl;
			//

	output << X << " " << A << " " << B;
}

int main() {

	ifstream input("input.txt");
	ofstream output("output.txt");
	Process( input, output);
	return 0;
}
