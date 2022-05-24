
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

struct Citizen{
	int index;
	double money;
};

bool operator <(const Citizen& l, const Citizen& r){
	return (l.money < r.money);
}

int main() {

	ifstream input("input.txt");
	size_t N;
	input >> N;
	vector<Citizen> people(N);

	for(int i = 0; i < static_cast<int>(N); i++){
		input >> people[i].money;
		people[i].index = i+1;
	}


	/*for (auto x: people){
		cout << x.index << " - " << x.money << endl;
	}
*/
	sort(people.begin(),people.end());

/*	cout << " _____\n";
	for (auto x: people){
		cout << x.index << " - " << x.money << endl;
	}*/

	ofstream output("output.txt");
	output << people[0].index << " " << people[N/2].index << " " <<  people[N-1].index;
	return 0;
}
