#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <chrono>
#include <random>
using namespace std;


void InsertionSort(vector<uint32_t>& v, uint32_t pos , uint32_t& helper1, uint64_t& sum){
	vector<uint32_t> counter(80000,0);

		for( auto x: v){
			counter[(x - pos*80000)]++;
		}

		//auto It = v.begin();
		for(uint32_t i = 0; i < counter.size(); i++){
			while( counter[i] > 0){
				if(helper1 % 10 == 0){
					sum += i + pos*80000;
					//*It = i + pos*40000;
				}
				helper1++;
				//It++;
				counter[i]--;
			}
		}
}





uint64_t PocketSort(vector<uint32_t>& A, vector<uint32_t>& B){

	vector<vector<uint32_t>> data(20000+1); //40000
	uint32_t index, helper;


	auto start_time = std::chrono::steady_clock::now();

	for( uint32_t i = 0; i < A.size(); i++){
		for( uint32_t j = 0; j < B.size(); j++){
			helper = A[i] * B[j];
			index = helper / 80000; // 40000
			data[index].push_back(helper);
		}
	}

	auto end_time = std::chrono::steady_clock::now();
		auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
		std::cout << "adasdsad time: " << elapsed_ms.count() << "\n";

	uint64_t sum = 0;
	helper = 0;
	for( uint32_t i = 0; i < data.size(); i++){
		InsertionSort(data[i], i, helper, sum);
	}

	//
	/*auto start_time = std::chrono::steady_clock::now();
	//
	uint64_t sum = 0;
	helper = 0;
	for(uint32_t i = 0; i < data.size(); i++){
		for(auto y: data[i]){
			if(helper % 10 == 0){
				sum += y;
			}
			helper++;
		}
	}

	//
	auto end_time = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	std::cout << "Sum time: " << elapsed_ms.count() << "\n";
	*/
	//

	//
	//cout << " Sum^ " << sum << endl;
	//
	return sum;
}







int main() {
	//


	ofstream output_("file.txt");
	output_ << "6000 6000\n";
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, 40000);

	for(int i = 0; i < 6000; i++){
		output_ << dist(gen) << " ";
	}

	output_ << "\n";

	for(int i = 0; i < 6000; i++){
		output_ << dist(gen) << " ";
	}

	//


	auto start_time = std::chrono::steady_clock::now();

	uint32_t n,m;
	//ifstream input("input.txt");
	ifstream input("file.txt");
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

	auto end_time = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	std::cout << "Total time: " << elapsed_ms.count() << "\n";

	return 0;
}
