
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


int CharToInt(char a){
	return (a - 97);
}

void CountingSort(vector<string>& data, vector<int>& from, vector<int>& to, int i){

	int pos = static_cast<int>(data[0].size()) - 1 - i;
	if(pos < 0){
		pos = 0;
	}
	//
	//cout << "pos = " <<  pos << endl;
	//
	vector<int> counter(26, 0);

	for(auto x: data){
		counter[CharToInt(x[pos])]++;
	}

	for( int i = 1; i < 26; i++){
		counter[i]+=counter[i - 1];
	}


	int helper;
	for( int i = (static_cast<int>(data.size())-1); i + 1 > 0; i--){
		helper = CharToInt(data[from[i]][pos]);
		//
	//	cout << "helper = " << helper << " counter[helper] = " << counter[helper] << endl;
		//
		to[counter[helper] - 1] = from[i];
		counter[helper]--;
	}
}


vector<int> RadixSort(vector<string>& data, int k){

	vector<int> even(data.size());
	vector<int> odd(data.size());
	for( int i = 0; i < static_cast<int>(data.size()); i++){
		even[i] = i;
	}

	for( int i = 0; i < k; i++){
		if( i % 2 == 0){
			CountingSort( data, even, odd, i);
		}else{
			CountingSort( data, odd, even, i);
		}
		//
	/*	cout << "even:\n";
		for( int i = 0; i < static_cast<int>(data.size()); i++){
			cout << even[i] << " ";
		}
		cout << endl;

		cout << "odd:\n";
		for( int i = 0; i < static_cast<int>(data.size()); i++){
			cout << odd[i] << " ";
		}
		cout << endl;*/
		//
	}

	if( k % 2 == 0){
		return even;
	}

	return odd;
}

int main() {

	int count, length, k;

	ifstream input("input.txt");
	//input >> length >> count >> k;
	input >> count >> length >> k;

	vector<string> data(count);
	char helper;

	for(int i = 0; i < length; i++){
		for(int j = 0; j < count; j++){
			input >> helper;
			data[j].push_back(helper);
		}
	}



	//
	/*
	for(auto x: data){
		cout << x << endl;
	}
	*/
	//

	//cout << ('a' < 'b' ) << "  " << ('a' == 'b' ) << "  " << ('a' > 'b' ) << "  " ;

//	cout << endl <<"a - " <<  CharToInt('a') << " z - " << CharToInt('z') <<  endl;

	auto result = RadixSort(data, k);

	ofstream output("output.txt");
	//if( count == 1 && length == 2){
	//	output << "1 2";
	//}else{
	for(auto x: result){
		output << (x + 1) << " ";
	}
	//}
	return 0;
}
