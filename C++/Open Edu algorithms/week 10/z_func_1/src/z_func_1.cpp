
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


vector<int> Z_func( string& str){
	vector<int> z(str.size(), 0);

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
			}
		}
	}

	return z;
}

void Process( ifstream& input, ofstream& output){
	string str;
	input >> str;

	auto z = Z_func(str);

	for( int i = 1; i < static_cast<int>(z.size()); i++){
		output << z[i] << " ";
	}
}

int main() {

	ifstream input("input.txt");
	ofstream output("output.txt");
	Process( input, output);
	return 0;
}
