
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


int CharToInt(char a){
	return (a - 97);
}

//void CountingSort(vector<string>& data, vector<int>& from, vector<int>& to, int i){
void CountingSort(const string& data, vector<int>& from, vector<int>& to, int i){

	/*int pos = static_cast<int>(data.size()) - 1 - i;
	if(pos < 0){
		pos = 0;
	}
	*/
	vector<int> counter(26, 0);

	for(auto x: data){
		counter[CharToInt(x)]++;
	}

	for( int i = 1; i < 26; i++){
		counter[i]+=counter[i - 1];
	}


	/*int helper;
	for( int i = (static_cast<int>(data[0].size())-1); i + 1 > 0; i--){
		helper = CharToInt(data[pos][from[i]]);
		to[counter[helper] - 1] = from[i];
		counter[helper]--;
	}*/
	int helper;
	for( int i = (static_cast<int>(data.size())-1); i + 1 > 0; i--){
		helper = CharToInt(data[from[i]]);
		to[counter[helper] - 1] = from[i];
		counter[helper]--;
	}


}


vector<int> RadixSort(vector<string>& data, int k){

	vector<int> even(data[0].size());
	vector<int> odd(data[0].size());
	//
	//cout << "data[0].size() = " << data[0].size() << endl;
	//
	for( int i = 0; i < static_cast<int>(data[0].size()); i++){
		even[i] = i;
	}

	for( int i = 0; i < k; i++){
		if( i % 2 == 0){
			CountingSort( data[(static_cast<int>(data.size()) - 1 - i)], even, odd, i);
		}else{
			CountingSort( data[(static_cast<int>(data.size()) - 1 - i)], odd, even, i);
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

	vector<string> data(length);
	string helper;

	for(int i = 0; i < length; i++){
			input >> helper;
			data[i].append(helper);
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
