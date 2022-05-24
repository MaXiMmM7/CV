
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


vector<int> Build_p(string& str){

	vector<int> p(str.size() + 1, 0);

	int i = 1;
	int j = 0;
	while( i < static_cast<int>(str.size())){

		//
		/*
		cout << " i = " << i << " ||   ";
		for(auto x: p){
			cout << x << " ";
		}
		cout << endl;
		*/
		//
		if( str[i] == str[j]){
			p[++i] = ++j;
		}else{
			if( j > 0){
				j = p[j];
			}else{
				p[++i] = 0;
			}
		}
	}

	return p;
}

void Process( ifstream& input, ofstream& output){
	string str;
	input >> str;

	//
	//cout << str << endl;
	//
	vector<int> p = Build_p(str);

	for(int i = 1; i < static_cast<int>(p.size()); i++){
		output << p[i] << " ";
	}
}

int main() {

	ifstream input("input.txt");
	ofstream output("output.txt");
	Process( input, output);

	return 0;
}
