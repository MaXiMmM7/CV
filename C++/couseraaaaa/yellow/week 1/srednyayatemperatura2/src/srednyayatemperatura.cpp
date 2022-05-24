//============================================================================
// Name        : srednyayatemperatura.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

vector<unsigned int> UpperMidle(const vector<int> data){
	int64_t Average=0;
	for(int i=0;i<static_cast<int>(data.size());i++){
		Average+=data[i];
	}

	Average /=static_cast<int>(data.size());

	vector<unsigned int> result;
	for(unsigned int i=0;i+1<=static_cast<unsigned int>(data.size());i++){
		if(data[i]>Average){
			result.push_back(i);
		}
	}

	return result;
}

int main() {
	int N;
	cin >> N;
	vector <int> data(N);
	for(size_t i=0; i+1<=data.size();i++){
		cin >> data[i];
	}

	vector<unsigned int> result =UpperMidle(data);
    cout << result.size() << endl;
	for(size_t i=0; i+1<=result.size();i++){
			cout << result[i];
			if(i+1!=result.size()){
				cout << " ";
			}
		}

	return 0;
}
