
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void Swaper(vector<int>& v, ofstream& out){
	int helper,min;
	for (int i = 0;i < static_cast<int>(v.size()); i++){
		min = i;
		for (int j = i+1; j < static_cast<int>(v.size()); j++){
			if(v[j] < v[min]){
				min = j;
			}
		}
		if(min!=i){
			helper = v[i];
			v[i] = v[min];
			v[min] = helper;
			out << "Swap elements at indices " << (i+1) << " and "<< (min+1) << ".\n";
		}
	}
	out << "No more swaps needed.\n";
}


int main() {

	int N;
	ifstream input("input.txt");
	input >> N;
	vector<int> data(N);

	for( int i = 0; i < N; i++){
		input >> data[i];
	}

	ofstream output("output.txt");
	Swaper(data,output);

	/*for(auto x: data){
		cout << x << " ";
	}
*/

	return 0;
}
