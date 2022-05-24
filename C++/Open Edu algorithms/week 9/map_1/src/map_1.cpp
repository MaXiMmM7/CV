
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

int Hash_char(char x){
	return ( x - 97);
}


int64_t FindSubstr(string& s){
	int64_t res = 0;
	vector<vector<int>> letters(26);


	for( int i = 0; i < static_cast<int>(s.size()); i++){
		while( s[i] == ' '){
			s.erase(i,1);
		}
		letters[Hash_char(s[i])].push_back(i);
	}


	int counter = 0;
	for( int j = 0; j  < static_cast<int>(letters.size()); j++ ){
		if( static_cast<int>(letters[j].size()) > 0){
			counter++;
		}
	}
	if( counter == 1){
		int64_t N = static_cast<int64_t>(s.size()) ;

		return N*(N - 1)*(N - 2)/2/3;
	}

	for(int i = 0; i < 26; i++){

		if( static_cast<int>(letters[i].size()) > 1 ){

			int64_t helper = 0;
			for( int j = 0; j + 1 < static_cast<int>(letters[i].size()); j++ ){
				for( int k = j + 1; k < static_cast<int>(letters[i].size()); k++ ){
					helper += letters[i][k] - letters[i][j] - 1;
				}
			}

			res += helper;
		}

	}

	return res;
}

void Process( ifstream& input, ofstream& output){
	string s;
	getline(input, s);
	auto res = FindSubstr(s);
	output << res ;
}

int main() {

	//
/*
	ofstream out("input3.txt");
	for(int i = 0; i < 300000; i++ ){
		out << char(97);
	}
*/
	//
	ifstream input("input.txt");

	ofstream output("output.txt");

	Process(input, output);

	return 0;
}
