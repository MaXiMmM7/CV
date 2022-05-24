
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


vector<int> Z_func( string& str, int M){
	vector<int> z(str.size(), 0);
	vector<int> res;

	int L = 0;
	int R = 0;
	int j;
	int N = static_cast<int>(str.size());

	for( int i = 1; i < N; i++){
		if( i >= R){
			j = 0;
			while( i + j < N && str[j] == str[i + j]){
				j++;
			}
			R = i + j;
			L = i;
			z[i] = j;
			if(j == M){
				res.push_back(i - M);
			}
		}else{
			if( z[i - L] < R - i){
				z[i] = z[i - L];
			}else{
				j = R - i;
				while( i + j < N && str[j] == str[i + j]){
					j++;
				}
				R = i + j;
				L = i;
				z[i] = j;
				if(j == M){
					res.push_back(i - M);
				}
			}
		}
	}

	//return z;
	return res;
}

void Process( ifstream& input, ofstream& output){
	string str, sub_str;
	input >> sub_str >> str;
	string s = sub_str + '*' + str;

	int M = static_cast<int>(sub_str.size());

	auto res = Z_func(s, M);



	output << res.size() << '\n';
	for( auto x: res){
		output << x << " ";
	}
}

int main() {

	ifstream input("input.txt");
	ofstream output("output.txt");
	Process( input, output);
	return 0;
}

