#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;


vector<int> MergeSort(vector<int> even, vector<int>& limits){
	int N = even.size();
	int M = (static_cast<int>(limits.size()) - 1);
	if (M < 2){
		return even;
	}
	vector<int> odd(N);

	int helper1,helper2,helper0;
	int i = 0;
	int j = 1;

	do{
		j*=2;
		for(int k = 0; k < M + 1; k+=j){
			helper1 = limits[k]; //helper1 = k;
			helper0 = limits[k]; //helper0 = k;
			helper2 = limits[min((k + j/2), M)]; //helper2 = min((k + j/2), N);
			if(i % 2 == 0){
			while( helper1 < limits[min((k + j/2), M)] || helper2 < limits[min((k + j), M)]){
				if( helper2 == limits[min((k + j), M)] || (helper1 < limits[min((k + j/2), M)] && even[helper1] < even[helper2])){
					odd[helper0++] = even[helper1++];
				}
				else{
					odd[helper0++] = even[helper2++];
				}
			}
			}else{
				while( helper1 < limits[min((k + j/2), M)] || helper2 < limits[min((k + j), M)]){
					if( helper2 == limits[min((k + j), M)] || (helper1 < limits[min((k + j/2), M)] && odd[helper1] < odd[helper2])){
						even[helper0++] = odd[helper1++];
					}
					else{
						even[helper0++] = odd[helper2++];
					}
				}
			}
		}
		i++;

	}while(j < M + 1);

	//////////

	/*for(auto x: odd){
		cout << x << " ";
	}
	cout << endl;
	for(auto x: even){
		cout << x << " ";
	}
	cout << endl;
*/
	////////
	if(i % 2 == 0){
		return even;
	}
	return odd;
}



int main() {

	int N,k1,k2,A,B,C,a1,a2;
	ifstream input("input.txt");
	input >> N >> k1 >> k2 >> A >> B >> C >> a1 >> a2 ;

	vector<int> data(N);
	vector<int> limits;
	data[0] = a1;
	data[1] = a2;
	limits.push_back(0);
	if(data[1] < data[0]){
		limits.push_back(1);
	}
	for (int i = 2; i < N; i++){
		data[i] = A*data[i-2] + B*data[i-1] + C;
		if(data[i] < data[i-1]){
			limits.push_back(i);
		}
	}
	limits.push_back(N); //(n-1 ??????????????????????????????????????????????//)

	/*for(auto x: data){
		cout << x << " ";
	}
	cout << endl;
	for(auto x: limits){
		cout << x << " ";
	}

	cout << endl << endl;
*/
	ofstream output("output.txt");
	auto result = MergeSort(data, limits);


	for(int i = k1 - 1; i <= k2 - 1; i++){
		output << result[i] << " ";

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

