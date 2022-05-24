#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

void Height( const vector<int>& keys, const vector<int>& left, const vector<int>& right,
		const vector<int>& parent, vector<int>& height_left,vector<int>& height_right,
		vector<int>& balance,int root, int N){

	int y,x;
	for( int i = 1; i < N + 1; i++){
		//
	//	cout << " i = " << i << " key = " << keys[i] << endl;
		//
		if(left[i] == 0 && right[i] == 0){
			int h = 0;
			x = i;
			y = parent[x];
			while( y != 0){
				h++;
				//
										//
				if ( x == left[y]){
					if( height_left[y] < h){
						height_left[y] = h;
					}
				}else{
					if( height_right[y] < h){
						height_right[y] = h;
					}
				}
				x = y;
				y = parent[y];
			}
		}
	}


	for( int i = 1;  i < N + 1; i++){
		balance[i] = height_right[i] - height_left[i];
	}

	//
/*
	cout << N << endl;
	for( int i = 1;  i < N + 1; i++){
		cout << "i = " << i << " key = " << keys[i] << " b = " << balance[i] << endl;
	}
	*/
	//
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
	vector<int> height_left(N + 1,0);
	vector<int> height_right(N + 1,0);


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

	Height( keys, left, right, parent, height_left,height_right, balance, root, N);

	ofstream output("output.txt");
	for( int i = 1; i < static_cast<int>(balance.size()); i++){
		//cout << balance[i] << '\n';
		output << balance[i] << '\n';
	}

	return 0;
}
