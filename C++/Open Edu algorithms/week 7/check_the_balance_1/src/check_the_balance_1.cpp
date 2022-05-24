
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int Height( const vector<int>& keys, const vector<int>& left, const vector<int>& right,
		const vector<int>& parent, vector<int>& balance, int x){

	if( x == 0){
		return -1;
	}

	int h_right = Height( keys, left, right, parent, balance, right[x]);
	int h_left = Height( keys, left, right, parent, balance, left[x]);

	balance[x] = Height( keys, left, right, parent, balance, right[x]) -
			 Height( keys, left, right, parent, balance, left[x]);

	int h = max(h_right, h_left);
	return ++h;
}

int main() {

	ifstream input("input.txt");
	int N;
	input >> N;

	vector<int> keys(N + 1);
	vector<int> left(N + 1);
	vector<int> right(N + 1);
	vector<int> parent(N + 1);
	vector<int> balance(N + 1);


	for( int i = 1; i < N + 1; i++){
		input >> keys[i] >> left[i] >> right[i];
		if( left[i] != 0){
			parent[left[i]] = i;
		}
		if( right[i] != 0){
			parent[right[i]] = i;
		}
	}

	//
	/*
		for( int i = 1; i < N + 1; i++){
			cout <<"key = "<<  keys[i] << " left = " <<  left[i]
		    << " right = " <<  right[i] << " parent = " << parent[i] << endl;

		}
		*/
	//


	int root = 1;
	while( parent[root] != 0){
		root++;
	}

	Height( keys, left, right, parent, balance, root);

	ofstream output("output.txt");
	for( int i = 1; i < static_cast<int>(balance.size()); i++){
		//cout << balance[i] << '\n';
		output << balance[i] << '\n';
	}

	return 0;
}
