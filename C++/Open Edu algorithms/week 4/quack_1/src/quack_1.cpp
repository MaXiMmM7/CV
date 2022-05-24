
#include <iostream>
#include <queue>
//#include <list>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;


int CharToInt(char ch){
	return ch - 97;
}

void Process(ifstream& input, ofstream& output){
	//queue<string> commands;
	vector<string> commands;
	string helper;
	uint32_t res;
	unordered_map<string,int> labels;
//	string last;

	int index = 0;

	while(getline(input, helper)){
		//input >> helper;
		if(helper[0] == ':'){
			labels[helper.substr(1)] = index;
		}
		index++;
		commands.push_back(helper);
	}



	//last = helper;
	//
//	cout << "last = " << last << endl;
/*
	while(!commands.empty()){
		cout << commands.front() << "  ___\n";
		commands.pop();
	}
	*/
	//

	vector<int> registers(26, 0);
	queue<uint32_t> quack;
	//string label;
	int value = 65536;
	int value2 = 256;
	int left, right;

	//auto It = commands.begin();

	index = 0;
	while(index < static_cast<int>(commands.size())){

		helper = commands[index];

		if( isdigit(helper[0])){
			quack.push(stoi(helper));
		}else if(helper == "+"){
			left = quack.front();
			quack.pop();
			right = quack.front();
			quack.pop();
			res = left + right;
			/*if(res < 0){
				res = - res;
			}*/
			quack.push(res % value);
		}else if(helper == "-"){
			if(helper.size() == 1){
				left = quack.front();
				quack.pop();
				right = quack.front();
				quack.pop();
				res = left - right;
				/*if(res < 0){
					res = - res;
				}*/
			//	quack.push((left - right) % value);
				quack.push((res) % value);
			}else{
				quack.push(stoi(helper));
			}
		}else if(helper == "*"){
			left = quack.front();
			quack.pop();
			right = quack.front();
			quack.pop();
			res = left * right;
			/*if(res < 0){
				res = - res;
			}*/
			quack.push(res % value);
		}else if(helper == "/"){
			left = quack.front();
			quack.pop();
			right = quack.front();
			quack.pop();
			if(right == 0){
				quack.push(0);
			}else{
				res = left / right;
			/*	if(res < 0){
					res = - res;
				}*/
				quack.push(res % value);
			}
		}else if(helper == "%"){
			left = quack.front();
			quack.pop();
			right = quack.front();
			quack.pop();
			if(right == 0){
				quack.push(0);
			}else{
				res = left % right;
				/*if(res < 0){
					res = - res;
				}*/
				quack.push(res % value);
			}
		}else if(helper[0] == '>'){
			left = quack.front();
			quack.pop();
			registers[CharToInt(helper[1])] = left;
		}else if(helper[0] == '<'){
			quack.push(registers[CharToInt(helper[1])]);
		}else if(helper[0] == 'P'){
			if(helper.size() == 1){
				output << quack.front() << '\n';
				quack.pop();
			}else{
				output << registers[CharToInt(helper[1])] << '\n';
			}
		}else if(helper[0] == 'C'){ //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			if(helper.size() == 1){
			output << char((quack.front() % value2));// << '\n'; ///////// ПРо пренос строки не говорилось проверь
			quack.pop();
			}else{
				output << char(registers[(CharToInt(helper[1]) % value2)]); // << '\n';///////// ПРо пренос строки не говорилось проверь
			}
		}/*else if(helper[0] == ':'){
			//label = helper.substr(1);
		}*/else if( helper[0] == 'J'){
			index = labels[helper.substr(1)];
			/*label = ":" + helper.substr(1);
			while(*It != label){
				It++;
				if(It == commands.end()){
					It = commands.begin();
				}
			}*/
		}else if( helper[0] == 'Z'){
			if( registers[CharToInt(helper[1])] == 0){
				index = labels[helper.substr(2)];
				/*label = ":" + helper.substr(2);
				while(*It != label){
					It++;
					if(It == commands.end()){
						It = commands.begin();
					}
				}*/
			}
		}else if( helper[0] == 'E'){
			if( registers[CharToInt(helper[1])] == registers[CharToInt(helper[2])]){
				index = labels[helper.substr(3)];
				/*label = ":" + helper.substr(3);
				while(*It != label){
					It++;
					if(It == commands.end()){
						It = commands.begin();
					}
				}*/
			}
		}else if( helper[0] == 'G'){
			if( registers[CharToInt(helper[1])] > registers[CharToInt(helper[2])]){
				index = labels[helper.substr(3)];
/*				label = ":" + helper.substr(3);
				while(*It != label){
					It++;
					if(It == commands.end()){
						It = commands.begin();
					}
				}*/
			}
		}else if( helper[0] == 'Q'){
			return;
		}

		index++;
	}
}


int main() {
	//auto start_time = std::chrono::steady_clock::now();

	ifstream input("input.txt");

	//int v = 90;
	//cout << char(v) << endl;
	//cout << CharToInt('z') << endl;
	ofstream output("output.txt");


	Process(input, output);

	/*auto end_time = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	std::cout << "Total time: " << elapsed_ms.count() << "\n";
*/
	return 0;
}
