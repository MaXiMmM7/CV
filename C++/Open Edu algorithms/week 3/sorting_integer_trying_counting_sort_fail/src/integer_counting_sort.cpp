
#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <vector>
using namespace std;

struct Unit{
	uint32_t value = 0;
	uint32_t count = 0;
};

bool operator ==  (const Unit& l, const Unit& r){
	return (l.value == r.value);
}

bool operator < (const Unit& l, const Unit& r){
	return (l.value < r.value);
}

uint64_t CountingSort(list<uint32_t>& A, list<uint32_t>& B){
	 uint32_t count_of_boxes = 600*6000; // numeration from zero
	 vector<list<Unit>> boxes(count_of_boxes);
	 uint32_t helper;
	 uint32_t index;
	 Unit unit;

     for(auto It_A = A.begin(); It_A != A.end(); It_A++){
    	 for (auto It_B = B.begin(); It_B != B.end(); It_B++){
    		 helper = (*It_A)*(*It_B);

    		 index = helper % count_of_boxes;
    		 unit.value = helper;
    		 auto It = find(boxes[index].begin(),boxes[index].end(), unit);
    		 if(It == boxes[index].end()){
    			 boxes[index].push_front(unit);
    			 It = boxes[index].begin();
    		 }
    		 It->count++;

    	 }
     }


///////////////////////////

	 uint64_t result = 0;
	 uint32_t counter = 0;
	 //
	 //
	 while(step <= max){

		 index = step % count_of_boxes;
		 auto It = min_element(boxes[index].begin(),boxes[index].end());
		 if(It != boxes[index].end()){
			 while( It->count != 0){
				 if(counter % 10 == 0){
					 result+=It->value;
				 }
				 counter++;
				 It->count--;
			 }
			 boxes[index].erase(It);
		 }
		 step++;

	 }

	 return result;
}





int main() {

	cout << "start" << endl;

	ifstream input("input.txt");
	uint32_t n,m;
	input >> n >> m;
	list<uint32_t> A;
	list<uint32_t> B;
	uint32_t helper;

	for(uint32_t i = 0; i < n; i++){
		input >> helper;
		A.push_back(helper);
	}
	for (uint32_t i = 0; i < m; i++){
		input >> helper;
		B.push_back(helper);
	}


	uint64_t sum= CountingSort(A, B);

	ofstream output("output.txt");
	output << sum;

	cout << "end" << endl;
	return 0;
}



