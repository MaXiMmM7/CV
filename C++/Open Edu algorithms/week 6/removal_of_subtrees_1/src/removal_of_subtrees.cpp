
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;



int Count( const vector<int>& left, const vector<int>& right,
		const vector<int>& parent, vector<int>& count, int current){

	int c = 1;

	if( left[current] != 0){
		c += Count(left, right, parent, count, left[current]);
	}

	if( right[current] != 0){
		c += Count(left, right, parent, count, right[current]);
	}

	count[current] = c;

	return c;
}

void FillTheCount( const vector<int>& left, const vector<int>& right,
		const vector<int>& parent,  vector<int>& count, int root){

	int last = root;
	while( right[last] != 0 ){
		last = right[last];
	}

	int first = root;
	while( left[first] != 0 ){
		first = left[first];
	}

	int current = first;
	int c_l = 0;

	while( current != root ){
		c_l += 1;
		if( right[current] != 0){
			c_l += Count(left, right, parent, count, right[current]);
		}
		count[current] = c_l;

		current = parent[current];
	}

	current = last;
	int c_r = 0;
	while( current != root ){
		c_r += 1;
		if( left[current] != 0){
			c_r += Count(left, right, parent, count, left[current]);
		}
		count[current] = c_r;

		//
	//	cout << " key current = " << current <<  " c = " << c_r << endl;
		//
		current = parent[current];
	}

	count[root] = c_l + c_r + 1;
}



int Extract( const vector<int>& keys,  vector<int>& left, vector<int>& right,
		const vector<int>& parent, vector<int>& count, int key, int root){

	//
	//return 0;
	//
	int current = root;

	while( current != 0 && keys[current] != key ){
		if( keys[current] < key){
			current = right[current];
		}
		if(keys[current] > key){
			current = left[current];
		}
	}

	if( current == 0){
		return count[root];
	}

	int c = count[current];
	if(right[parent[current]] == current) {
		right[parent[current]] = 0;
	}else{
		left[parent[current]] = 0;
	}

	current = parent[current];
	while( current != 0){
		count[current] -= c;
		current = parent[current];
	}

	return count[root];
}

int main() {

	ifstream input("input.txt");
	int N;
	input >> N;
	vector<int> keys(N + 1);
	vector<int> left(N + 1);
	vector<int> right(N + 1);
	vector<int> parent(N + 1);
	vector<int> count(N + 1);


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

		/*int last = root;
		while( right[last] != 0 ){
			last = right[last];
		}

		int first = root;
		while( left[first] != 0 ){
			first = left[first];
		}*/

		/*cout << last << endl;

		int current = root;
		while( current != last){

		}*/


	//	int max = 0;

		FillTheCount( left, right, parent, count, root);

		//
		/*
		for( int i = 1; i < N + 1; i++){
				cout <<"key = "<<  keys[i] << " left = " <<  left[i]
			    << " right = " <<  right[i] << " parent = " << parent[i] << " count = " << count[i] << endl;

			}
			*/
//

		ofstream output("output.txt");

		int M;
		int extract;
		input >> M;
		for( int i = 0; i < M; i++){
			input >> extract;
			//
		//	cout << "extract = " << extract << endl;
			//
			output << Extract( keys, left, right, parent, count, extract, root) << '\n';
		}


	//	cout << max << endl;

		//output << max;

	return 0;
}
