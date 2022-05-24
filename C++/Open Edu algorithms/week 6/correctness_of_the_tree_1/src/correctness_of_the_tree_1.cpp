
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int Min(const vector<int>& left, int x){
	if (left[x] == 0){
		return x;
	}
	return Min(left, left[x]);
}

int Next(const vector<int>& left, const vector<int>&  right,
		const vector<int>& parent, int x){

	if( right[x] != 0){
		return Min( left, right[x]);
	}
//
	//cout << "hey" << endl;
	//

	int y = parent[x];
	while( y != 0 && x == right[y]){
		x = y;
		y = parent[y];
	}
	return y;

}

bool IsTree( const vector<int>& keys, const vector<int>& left, const vector<int>&  right,
		const vector<int>& parent, int first){

	int next = Next( left, right, parent, first);

	//cout << keys.size() << endl;
	int N = static_cast<int>(keys.size()) - 1;
	for( int i = 0; i + 1 < N; i++){
		next = Next( left, right, parent, first);

		if( next == 0){
			break;
		}
		//
	//	break;
		//
		//
	//	cout << "current = " << keys[first] << " next = " << keys[next] << endl;// << " counter = " << counter<< endl;
		//
		if( keys[next] <= keys[first]){
			return false;
		}
		first = next;


	}


	if( next == 0 && N > 1){
		return false;
	}
	return true;
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

	//
	/*
	for( int i = 1; i < N + 1; i++){
		cout <<"key = "<<  keys[i] << " left = " <<  left[i]
	    << " right = " <<  right[i] << " parent = " << parent[i] << endl;

	}
	*/
	//

	ofstream output("output.txt");
	if( N > 0){
	int root = 1;
	while( parent[root] != 0){
		root++;
	}

//	cout << root << endl;

	/*int last = root;
	while( right[last] != 0 ){
		last = right[last];
	}*/

	int first = root;
	while( left[first] != 0 ){
		first = left[first];
	}

	//cout << "LEFT:  " << keys[first] << endl;

	/*cout << last << endl;

	int current = root;
	while( current != last){

	}*/



//	cout << max << endl;

	//cout <<"hey" <<endl;

	if (IsTree(keys, left, right, parent, first)){
		output << "YES" ;
	}else{
		output << "NO";
	}
	}else{
		output << "YES";
	}

	return 0;
}
