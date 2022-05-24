//============================================================================
// Name        : pereborperestanovok.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
template<typename T>
ostream& operator <<(ostream& stream,const vector<T> v){
	size_t N=v.size();
 for(size_t i=0;i<N;i++){
	 stream << v[i];
	 if(i+1!=N){
		 stream << " ";
	 }
 }
 return stream;
}


void Function( int N){
	vector<int> v;
	while(N!=0){
		v.push_back(N);
		N--;
	}
	cout << v << endl;
	while(prev_permutation(v.begin(),v.end())!=false){
		cout << v << endl;
	}

}

int main() {
	int N;
	cin >> N;
	Function(N);
	return 0;
}
