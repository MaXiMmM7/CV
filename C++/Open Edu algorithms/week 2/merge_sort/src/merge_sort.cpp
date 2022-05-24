
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;


/*
vector<int> Merge(vector<int> l,vector<int> r, ofstream& out){
	int N_l = l.size();
	int N_r = r.size();
	int i = 0;
	int j = 0;
	vector<int> res;
	res.reserve(N_l+N_r);
	while (i < N_l || j < N_r){
		if( j == N_r || (i < N_l && l[i] < r[j])){
			res.push_back(l[i]);
			i = i + 1;
		}
		else{
			res.push_back(r[j]);
			j = j + 1;
		}
	}

	return res;
}



vector<int> MergeSort(vector<int> v , ofstream& out){
	int N  = v.size();
	if(N == 1){
		return v;
	}
	auto l = MergeSort({v.begin(),(v.begin()+N/2)},out);
	auto r = MergeSort({(v.begin()+N/2),v.end()},out);
	return Merge(l,r,out);
}
*/

vector<int> MergeSort(vector<int> even, ofstream& out){
	int N = even.size();
	vector<int> odd(N);
	int helper1,helper2,helper0;
	int i = 0;
	int j = 1;
	do{

		j*=2;

		for(int k = 0; k < N; k+=j){
			helper1 = k;
			helper0 = k;
			helper2 = min((k + j/2), N);
			if(i % 2 == 0){
			while( helper1 < min((k + j/2), N) || helper2 < min((k + j), N)){
				if( helper2 == min((k + j), N) || (helper1 < min((k + j/2), N) && even[helper1] < even[helper2])){
					odd[helper0++] = even[helper1++];
				}
				else{
					odd[helper0++] = even[helper2++];
				}
			}
			if((min((k+j),N) - k) > j/2 || j > N ){
			out << (k+1) << " " << min((k+j),N) <<  " " << odd[k] << " " << odd[min((k+j-1),(N-1))] << "\n";
			}
			}else{
				while( helper1 < min((k + j/2), N) || helper2 < min((k + j), N)){
					if( helper2 == min((k + j), N) || (helper1 < min((k + j/2), N) && odd[helper1] < odd[helper2])){
						even[helper0++] = odd[helper1++];
					}
					else{
						even[helper0++] = odd[helper2++];
					}
				}
				if((min((k+j),N) - k) > j/2 || j > N){
				out << (k+1) << " " << min((k+j),N) <<  " " << even[k] << " " << even[min((k+j-1),(N-1))] << "\n";
				}
			}
		}
		i++;

	}while(j < N);

	if(i % 2 == 0){
		return even;
	}
	return odd;
}

int main() {

	int N;
	ifstream input("input.txt");
	input >> N;
	vector<int> data(N);
	for (int i = 0; i < N; i++){
		input >> data[i];
	}

	ofstream output("output.txt");
	auto result = MergeSort(data, output);


	//output << "1 " << result.size() << " " << result[0] << " " << result[(result.size() - 1)] << "\n";
	for(auto x: result){
		output << x << " ";
	}

	return 0;
}
