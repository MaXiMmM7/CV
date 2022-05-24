
#include <iostream>
#include <fstream>
using namespace std;

int main() {

	ifstream input("input.txt");
	int64_t a,b,c;
	input >> a >> b;
	c = a + b*b;
	ofstream output("output.txt");
	output << c;
	return 0;
}
