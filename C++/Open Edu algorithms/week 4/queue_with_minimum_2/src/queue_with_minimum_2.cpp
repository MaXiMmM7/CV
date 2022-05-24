
#include <iostream>
#include <stack>
#include <fstream>
#include <utility>
using namespace std;


int Min(int left, int right){
	if(left >= right){
		return right;
	}
	return left;
}

void Process(ifstream& input, ofstream& output){
	//int size_ = 1000000;
	stack<pair<int,int>> push;
	stack<pair<int,int>> pop;
//
//	cout << pop.empty() << " " << push.empty() << endl;
	//

	int M, min;
    char helper;
    int number;
    input >> M;




	for( int i = 0; i < M; i++){
		input >> helper;

		//
	//	cout << "i = " << i << " helper = " << helper << " push.epmty() = " << push.empty() << " pop.empty() = " <<
		//		pop.empty() << endl;
		//
		if( helper == '+'){
			input >> number;
			if(!push.empty()){
				min = Min(push.top().second,number);
			}else{
				min = number;
			}
			push.push(make_pair(number,min));

		}else if(helper == '-'){

			if(pop.empty()){
				while(!push.empty()){
					number = push.top().first;
					if(pop.empty()){
						min = number;
					}else{
						min = Min(number,pop.top().second);
					}
					pop.push(make_pair(number,min));
					push.pop();
				}
			}


			pop.pop();


		}else{
			if(push.empty()){
				output << pop.top().second << '\n';
			}else if(pop.empty()){
				output << push.top().second << '\n';
			}else{
				output << Min(push.top().second,pop.top().second) << '\n';
			}
		}

	}
}


int main() {

	ifstream input("input.txt");
	ofstream output("output.txt");
	Process(input,output);
	return 0;
}
