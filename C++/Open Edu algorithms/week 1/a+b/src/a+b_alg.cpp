
#include <iostream>
#include <fstream>
using namespace std;

int main() {

	int a = 0;
	int b = 0;
	int res = 0;

	ifstream input("input.txt");

	input >> a >> b;
	res = a + b;
	ofstream output("output.txt");
	output << res;
	return 0;
}
