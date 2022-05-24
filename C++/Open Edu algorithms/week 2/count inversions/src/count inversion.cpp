
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;


int64_t count(0);


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
				if( helper2 == min((k + j), N) || (helper1 < min((k + j/2), N) && even[helper1] <= even[helper2])){
					if(helper0 < helper1){
						::count+= helper1 - helper0;
					//	cout << ::count << "  from position " << helper1 << " to position " << helper0
						//		<< " dist" << (helper1 - helper0) << endl;
					}
					odd[helper0++] = even[helper1++];
				}
				else{
					if(helper0 < helper2 ){
						::count+= helper2 - helper0;
					//	cout << ::count << "  from position " << helper2 << " to position " << helper0
					//			<< " dist" << " " << (helper2 - helper0)<< endl;
					}
					odd[helper0++] = even[helper2++];
				}
			}
			if((min((k+j),N) - k) > j/2 ){
	//		out << (k+1) << " " << min((k+j),N) <<  " " << odd[k] << " " << odd[min((k+j-1),(N-1))] << "\n";
			}
			}else{
				while( helper1 < min((k + j/2), N) || helper2 < min((k + j), N)){
					if( helper2 == min((k + j), N) || (helper1 < min((k + j/2), N) && odd[helper1] <= odd[helper2])){
						if(helper0 < helper1){
							::count+= helper1 - helper0;
									}
						even[helper0++] = odd[helper1++];
					}
					else{
						if(helper0 < helper2){
							::count+= helper2 - helper0;
						}
						even[helper0++] = odd[helper2++];
					}
				}
				if((min((k+j),N) - k) > j/2 ){
	//			out << (k+1) << " " << min((k+j),N) <<  " " << even[k] << " " << even[min((k+j-1),(N-1))] << "\n";
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
	output << ::count << "\n";


	return 0;
}
