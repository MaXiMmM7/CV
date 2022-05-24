#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;


void Swap(int pos1, int pos2, vector<int>& data){
	int helper = data[pos1];
	data[pos1] = data[pos2];
	data[pos2] = helper;
}

pair<int,int> Split(vector<int>& data,int l, int r, int k1, int k2){
	int i,j,k;
	i = j = k = l;

	int key = data[((l+r)/2)];

	for(; j < r+1; j++ ){
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
			k++;
		}

		if (data[j] < key ){
			if(i != k){
				Swap(i, k, data);
			}
			if(j != k){
				Swap(i, j, data);
			}
			k++;
			i++;
		}

	}

	return {i,k};
}

void QuickSort(vector<int>& data,int l, int r, int k1, int k2){

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

	auto [i_bound, k_bound] = Split(data,l,r,k1,k2);
	if((k1 <= (i_bound - 1) && (i_bound - 1) <= k2) || (k1 <= l && l <= k2) || (l < k1 && (i_bound - 1) > k2)){
		QuickSort(data,l, (i_bound - 1), k1, k2);
	}
	if((k1 <= r && r <= k2) || (k1 <=  k_bound &&  k_bound <= k2) || ( k_bound < k1 && r > k2)){
		QuickSort(data, k_bound, r, k1, k2);
	}

}



int main() {

	int N,k1,k2,A,B,C,a1,a2;
	ifstream input("input.txt");
	input >> N >> k1 >> k2 >> A >> B >> C >> a1 >> a2 ;

	vector<int> data(N);
	data[0] = a1;
	data[1] = a2;

	for (int i = 2; i < N; i++){
		data[i] = A*data[i-2] + B*data[i-1] + C;
	}

	//
	/*for(auto x: data){
		cout << x << " ";
	}
	cout << endl;
	*/
	/*
	for(auto x: limits){
		cout << x << " ";
	}

	cout << endl << endl;
*/


	ofstream output("output.txt");
	int l = 0;
	int r = N - 1;

	//
	//cout << "N = " << N << " r = " << r << endl;
	//
	QuickSort(data,l,r,(k1 - 1),(k2 - 1));


	for(int i = k1 - 1; i <= k2 - 1; i++){
		output << data[i] << " ";

	//	cout <<  result[i] << " ";
	}

	return 0;
}


/*
 *
 * 5 3 3
12312343 -45345243 -121 -12 21312
 *
 */

