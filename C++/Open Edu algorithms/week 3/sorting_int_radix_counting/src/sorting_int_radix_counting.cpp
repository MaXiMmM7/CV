#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <chrono>
using namespace std;


uint32_t DoSomething(uint32_t x, uint32_t pos){
	while(pos > 0){
		x = x/1000;
	pos--;
	}
	return (x % 1000);
}


void CountingSort(vector<uint32_t>& v, vector<uint32_t>& helper, uint32_t pos ){


	vector<uint32_t> boxes(1000, 0);
	if(pos > 2){
		boxes.resize(10);
	}
	for(auto x: v){
		boxes[DoSomething(x, pos)]++;
	}

	for( uint32_t i = 1; i < boxes.size(); i++){
		boxes[i]+=boxes[i - 1];
	}


	for( uint32_t i = static_cast<uint32_t>(v.size() - 1); i+1 > 0; i--){
		helper[boxes[DoSomething(v[i], pos)] - 1] = v[i];
		boxes[DoSomething(v[i], pos)]--;
	}

}

uint64_t RadixSort(vector<uint32_t>& v){
    uint32_t digits = 4;

    vector<uint32_t> helper(v.size());

    for( uint32_t pos = 0; pos < digits; pos++){
    	if( pos % 2 == 0){
    		CountingSort(v, helper, pos);
    		//
    		/*for(auto x: helper){
    			cout << x << " ";
    		}
    		cout << endl;*/
    		//
    	}else{
    		CountingSort(helper, v, pos);
    		//
    		/*for(auto x: v){
    			cout << x << " ";
    		}
    		cout << endl;*/
    		//
    	}
    }

    uint64_t result = 0;
    for( uint32_t i = 0; i < v.size(); i+=10){
    	result += v[i];
    }

    return result;
}

int main() {
	//

	/*

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


*/
		//




//	auto start_time = std::chrono::steady_clock::now();


	ifstream input("input.txt");
	int N, M;
	input >> N >> M;
	vector<uint32_t> A(N);
	vector<uint32_t> B(M);
	for( int i = 0; i < N; i++){
		input >> A[i];
	}
	for( int j = 0; j < M; j++){
		input >> B[j];
	}

	vector<uint32_t> v;

	for( int i = 0; i < N; i++){
		for( int j = 0; j < M; j++){
			v.push_back(A[i]*B[j]);
		}
	}

	A.clear();
	B.clear();

	auto result = RadixSort(v);

	ofstream output("output.txt");
	output << result;


//	auto end_time = std::chrono::steady_clock::now();
	//auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	//std::cout << "Total time: " << elapsed_ms.count() << "\n";

	return 0;
}

