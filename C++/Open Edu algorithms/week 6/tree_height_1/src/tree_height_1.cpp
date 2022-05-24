
#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
using namespace std;


void Check(const vector<int>& keys, const vector<int>&  left,const vector<int>& right, //const vector<int>& parent,
		int x, int h, int& max){
	if(++h > max){
		max = h;
	}

	if( left[x] != 0){
		Check( keys, left, right, left[x], h, max);
	}

	if( right[x] != 0){
		Check( keys, left, right, right[x], h, max);
	}
}

int main() {

	ifstream input("input.txt");
	int N;
	input >> N;
	vector<int> keys(N + 1);
	vector<int> left(N + 1);
	vector<int> right(N + 1);
	vector<int> parent(N + 1);
	//vector<int> check(N + 1, 0);


	for( int i = 1; i < N + 1; i++){
		input >> keys[i] >> left[i] >> right[i];
		if( left[i] != 0){
			parent[left[i]] = i;
		}
		if( right[i] != 0){
			parent[right[i]] = i;
		}
	}

/*	for( int i = 1; i < N + 1; i++){
		cout <<"key = "<<  keys[i] << " left = " <<  left[i]
	    << " right = " <<  right[i] << " parent = " << parent[i] << endl;

	}
*/
//	int h = 0;

	int root = 1;
	while( parent[root] != 0){
		root++;
	}

//	cout << root << endl;

	int last = root;
	while( right[last] != 0 ){
		last = right[last];
	}

	/*cout << last << endl;

	int current = root;
	while( current != last){

	}*/


	int max = 0;

	if( N != 0){
		Check( keys, left, right, root, 0, max);
	}

//	cout << max << endl;

	ofstream output("output.txt");
	output << max;
	return 0;
}
