
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Result{
	int left;
	int right;
};


int Lower_bound(const vector<int>& data,int l, int r, int x){

	int m;

	while( l + 1 < r){
		m = ( l + r ) / 2;
		if( data[m] < x){
			l = m;
		}else{
			r = m;
		}
	}

	if( l + 1 < static_cast<int>(data.size()) && data[l + 1] == x){
		return l + 1;
	}
	return -1;
}

int Upper_bound(const vector<int>& data,int l, int r, int x){

	int m;

	while( l + 1 < r){
		m = ( l + r ) / 2;
		if( data[m] > x){
			r = m;
		}else{
			l = m;
		}
	}

	return r - 1;
}



Result Binary_search(const vector<int>& data, int x){
	Result res;
	res.left = Lower_bound( data, -1, static_cast<int>(data.size()), x);
	if( res.left == -1){
		res.right = -1;
		return res;
	}
	res.right = Upper_bound( data, res.left, static_cast<int>(data.size()), x);
	res.right++;
	res.left++;
	return res;
}

int main() {

	ifstream input("input.txt");
	int n;
	input >> n;
	vector<int> data(n);
	for( int i = 0; i < n; i++){
		input >> data[i];
	}

	ofstream output("output.txt");
	int m,helper;
	input >> m;

	//
	/*for(auto x: data){
		cout << x  << " ";
	}
	cout << endl;
	*/
	//

	for( int i = 0; i < m; i++){
		input >> helper;
		auto res = Binary_search(data, helper);
		output << res.left << " " << res.right << '\n';
	}

	return 0;
}
