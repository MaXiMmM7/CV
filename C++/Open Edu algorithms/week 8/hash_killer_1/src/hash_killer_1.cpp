
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


int Hash(string s, int multiple){
	int rv = 0;
	for( int i = 0; i < static_cast<int>(s.size()); i++){
		rv = multiple* rv + int(s[i] - 97);
	}
	return rv;
}


void Process( ifstream& input, ofstream& output){
	int N;
	input >> N;

	string fisrt =
	for( int i = 2 ; i < 100; i++){
		cout << Hash("hello", i) << endl;
	}

}
int main() {
	ifstream input("input.txt");
	ofstream output("output.txt");
	Process( input, output);
	output << "cat";
	return 0;
}
