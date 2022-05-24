
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void Swap(int pos1, int pos2, vector<int>& data){
	int helper = data[pos1];
	data[pos1] = data[pos2];
	data[pos2] = helper;
}

pair<int,int> Split(vector<int>& data,int l, int r,int step){
	int i,j,k;
	i = j = k = l;

	int key = data[(l + step* ((r - l)/(2*step)))];

	for(; j < r+1; j+=step ){
		//
		/*for (auto x: data){
				cout << x << " ";
			}
		cout << " i = " << i << " k = " <<  k << " j = " << j << " daya [j] = " << data[j] << endl << endl;
		*/
		//
		if (data[j] == key){
			if(k != j){
				Swap(k,j,data);
			}
			k+=step;
		}

		if (data[j] < key ){
			if(i != k){
				Swap(i, k, data);
			}
			if(j != k){
				Swap(i, j, data);
			}
			k+=step;
			i+=step;
		}

	}

	return {i,k};
}

void QuickSort(vector<int>& data,int l, int r, int step){

	//
	/*
	for (auto x: data){
		cout << x << " ";
	}
	cout << endl << " l = " << l << " r = " << r << " k1 = " << k1 << " k2 = " << k2 << endl << endl;
	*/
	//

	if(l >= r){
		return;
	}

	auto [i_bound, k_bound] = Split(data, l, r, step);
	QuickSort(data,l, (i_bound - 1), step);
	QuickSort(data, k_bound, r, step);


}


void ScarecrowSort(vector<int>& v, int step ){

	for( int i = 0; i < step; i++){
		QuickSort(v, i, (static_cast<int>(v.size()) - 1 ), step);
	}

}

bool IsSorted(const vector<int>& v){
	int i = 1;
	for(; i < static_cast<int>(v.size()); i++){
		if( v[i - 1] > v[i]){
			break;
		}
	}

	if( i == static_cast<int>(v.size())){
		return true;
	}

	return false;
}

int main() {

	ifstream input("input.txt");
	int N, k;
	input >> N >> k;
	vector<int> data(N);
	for(int i = 0; i < N; i++){
		input >> data[i];
	}

	//
	/*for(auto x: data){
		cout << x << " ";
	}
	cout << endl;
	*/

	//

	ScarecrowSort(data, k);

	ofstream output("output.txt");

	//
	/*	for(auto x: data){
			cout << x << " ";
		}

*/
    //

	if( IsSorted(data)){
		output << "YES";
	}else{
		output << "NO";
	}

	return 0;
}
