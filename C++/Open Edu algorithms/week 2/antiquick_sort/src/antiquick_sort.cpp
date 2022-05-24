
#include <iostream>
#include <fstream>
#include <list>
using namespace std;

list<int> ProduceSequence(int N){
	list<int> lst;
	lst.push_back(1);
	if(N == 1){
		return lst;
	}

	lst.push_back(2);
	if(N == 2){
		return lst;
	}

	auto root = lst.begin();
	int helper;

	for(int i = 3; i < N+1; i++){
		if(i%2 != 0){
			root++;
		}
		helper = *root;
		*root = i;
		lst.push_back(helper);
	}

	return lst;
}


int main() {

	ifstream input("input.txt");
	int N;
	input >> N;

	auto result = ProduceSequence(N);
	ofstream output("output.txt");

	for(auto x: result){
		output << x << " ";
	}

	return 0;
}
