// Pockets + counting_sort in every pocket

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void CountingSort(vector<uint32_t>& v, uint32_t pos, uint32_t& helper, uint64_t& sum ){
	vector<uint32_t> counter(10000,0);

	for( auto x: v){
		counter[x]++;
	}

	auto It = v.begin();
	for(uint32_t i = 0; i < counter.size(); i++){
		while( counter[i] > 0){
			*It = i;
			It++;
			counter[i]--;
			if( helper % 10 == 0){
				sum += (i + pos*10000);
			}
			helper++;
		}
	}

}


uint64_t PocketSort(vector<uint32_t>& A, vector<uint32_t>& B){

	vector<vector<uint32_t>> data(160000+1);
	uint32_t index, helper;
	uint64_t sum = 0;

	for( uint32_t i = 0; i < A.size(); i++){
		for( uint32_t j = 0; j < B.size(); j++){
			helper = A[i] * B[j];
			index = helper / 10000;
			helper -= (index * 10000);
			data[index].push_back(helper);
		}
	}

	helper = 0;
	for( uint32_t i = 0; i < data.size(); i++){
		CountingSort(data[i], i,  helper, sum);
	}

	/*uint64_t sum = 0;
	helper = 0;
	for(uint32_t i = 0; i < data.size(); i++){
		for(auto y: data[i]){
			if(helper % 10 == 0){
				sum += (y + i*10000);
			}
			helper++;
		}
	}
	*/

	return sum;
}


int main() {
	uint32_t n,m;
	ifstream input("input.txt");
	input >> n >> m;
	vector<uint32_t> A(n);
	vector<uint32_t> B(m);

	for(uint32_t i = 0; i < n; i++){
		input >> A[i];
	}

	for(uint32_t i = 0; i < m; i++){
		input >> B[i];
	}

	uint64_t result = PocketSort(A,B);

	ofstream output("output.txt");
	output << result;

	return 0;
}
