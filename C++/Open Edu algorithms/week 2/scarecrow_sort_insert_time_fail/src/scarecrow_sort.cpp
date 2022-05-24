
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void SortInsertion(vector<int>& v, int index, int step){

	int i,helper;

	for( int j = index + step; j < static_cast<int>(v.size()); j += step){
		i = j - step;
		while (i >= 0 && v[i] > v[i+step]){
			helper = v[i];
			v[i] = v[i+step];
			v[i+step] = helper;
			i = i - step;
		}
	}
}

void ScarecrowSort(vector<int>& v, int step ){

	for( int i = 0; i < step; i++){
		SortInsertion(v, i, step);
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
