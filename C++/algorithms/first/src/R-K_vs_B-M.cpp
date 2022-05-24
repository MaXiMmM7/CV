#include <iostream>
#include <cassert>
#include "Algs_task_first.h"
#include <chrono>
#include <vector>
#include <random>
#include <utility>
#include <fstream>
#include <deque>
#include <iomanip>
#include <algorithm>
using namespace std;
using namespace std::chrono;


char Get(int x){
	if(x==1){return 'A';}
	if(x==2){return 'G';}
	if(x==3){return 'C';}
	if(x==4){return 'T';}
	return '0';
}

pair<vector<char>,vector<char>> CookVectorForFirstTask(int size_v,int size_w){
	//const size_t step=1000;//1250
	//const size_t steps=10;//100


	default_random_engine rand_(steady_clock::now().time_since_epoch().count());
	mt19937 gen(rand_());
	uniform_int_distribution<> dist(1,4);

	vector<char> v(size_v);

	//create word
	vector<char> word(size_w);

	for(auto& x:word){
		x=Get(dist(gen));
	}

	//create array
	for(auto& x:v){
     x=Get(dist(gen));
		}

	//Insert word
	if(size_w<size_v&&size_v!=0){
	default_random_engine rand_1(steady_clock::now().time_since_epoch().count());
		mt19937 gen1(rand_1());
		uniform_int_distribution<> dist1(0,v.size()-1);

		int helper=size_v;
		while(size_v-size_w<helper){
			helper=dist1(gen1);
		}

		int k=0;
		for(int i=helper;i<helper+size_w;i++){
			v[i]=word[k++];
		}

	}


	return move(pair<vector<char>,vector<char>>(move(v),move(word)));
}



struct Data{
	size_t N;
	size_t time;
	Data(size_t n,size_t t):N(n),time(t){}
};

void DoFirstTask(){

	const int steps=100;
	const int step=200000;
	const int w_size=30;


	vector<Data> data_RK;
	vector<Data> data_BM;
	vector<Data> data_BF;

	data_RK.reserve(steps);
	data_BM.reserve(steps);
	data_BF.reserve(steps);

	for(int i=0;i <=steps ;i++){////0

		auto [x,word] = CookVectorForFirstTask(i*step,w_size);
		//////RK
		{
		steady_clock::time_point start = steady_clock::now();
		Rabin_Karp(x.begin(),x.end(),word.begin(),word.end());
		steady_clock::time_point finish = steady_clock::now();
		size_t duration = duration_cast<milliseconds>(finish-start).count();

		data_RK.push_back(Data(i*step,duration));
		//
/*
		cerr <<"RK" <<  endl;
		for(auto&y : x){
			cerr << y << " ";
		}
		cerr << endl;

		for(auto&y : word){
				cerr << y << " ";
			}
			cerr << endl;
			cerr << *It << endl;
*/
		//


		}
						//////BM
						{
							steady_clock::time_point start = steady_clock::now();
							Boyer_Moore(x.begin(),x.end(),word.begin(),word.end());
									steady_clock::time_point finish = steady_clock::now();
									size_t duration = duration_cast<milliseconds>(finish-start).count();

									data_BM.push_back(Data(i*step,duration));
									//
/*
									cerr <<"BM" <<  endl;
									for(auto&y : x){
										cerr << y << " ";
									}
									cerr << endl;

									for(auto&y : word){
											cerr << y << " ";
										}
										cerr << endl;
										cerr << *It << endl;
*/
									//

						}

						//////BM
											{
												steady_clock::time_point start = steady_clock::now();
												Brute_Force(x.begin(),x.end(),word.begin(),word.end());
														steady_clock::time_point finish = steady_clock::now();
														size_t duration = duration_cast<milliseconds>(finish-start).count();

														data_BF.push_back(Data(i*step,duration));
														//
/*
														cerr <<"BF" <<  endl;
														for(auto&y : x){
															cerr << y << " ";
														}
														cerr << endl;

														for(auto&y : word){
																cerr << y << " ";
															}
															cerr << endl;
															cerr << *It << endl;
*/
														//

											}

	}

	/////////////////////////////
	////////////////////////////
	//Write in FIle
	//Write RK
	{const string first_txt_RK="first_part_RK.txt";
	ofstream output(first_txt_RK);
	output << left;
	for (auto& x: data_RK){
		output << setw(14) << x.N<< setw(14) << x.time << "\n";
	}
	}
	//Write BM
	{const string first_txt_BM="first_part_BM.txt";
		ofstream output(first_txt_BM);
		output << left;
		for (auto& x: data_BM){
			output << setw(14) << x.N<< setw(14) << x.time << "\n";
		}
	}
	//Write BF
		{const string first_txt_BF="first_part_BF.txt";
			ofstream output(first_txt_BF);
			output << left;
			for (auto& x: data_BF){
				output << setw(14) << x.N<< setw(14) << x.time << "\n";
			}
		}/////////////////////////////
	/////////////////////////////
	/////
	cerr << "\nFirst task has finished" << endl;
	/////

}


void DoSecondTask(){

	const int steps=300;
	const int step=10000;
	const int v_size=20000000;


	vector<Data> data_RK;
	vector<Data> data_BM;
	vector<Data> data_BF;

	data_RK.reserve(steps);
	data_BM.reserve(steps);
	data_BF.reserve(steps);


	for(int i=0;i <=steps ;i++){////0

		auto [x,word] = CookVectorForFirstTask(v_size,i*step);
		//////RK
		{
		steady_clock::time_point start = steady_clock::now();
	    Rabin_Karp(x.begin(),x.end(),word.begin(),word.end());
		steady_clock::time_point finish = steady_clock::now();
		size_t duration = duration_cast<milliseconds>(finish-start).count();

		data_RK.push_back(Data(i*step,duration));
		//
/*
		cerr <<"RK" <<  endl;
		for(auto&y : x){
			cerr << y << " ";
		}
		cerr << endl;

		for(auto&y : word){
				cerr << y << " ";
			}
			cerr << endl;
			cerr << *It << endl;
*/
		//


		}
						//////BM
						{
							steady_clock::time_point start = steady_clock::now();
							Boyer_Moore(x.begin(),x.end(),word.begin(),word.end());
									steady_clock::time_point finish = steady_clock::now();
									size_t duration = duration_cast<milliseconds>(finish-start).count();

									data_BM.push_back(Data(i*step,duration));
									//
/*
									cerr <<"BM" <<  endl;
									for(auto&y : x){
										cerr << y << " ";
									}
									cerr << endl;

									for(auto&y : word){
											cerr << y << " ";
										}
										cerr << endl;
										cerr << *It << endl;
*/
									//

						}

						//////BF
									{
										steady_clock::time_point start = steady_clock::now();
										Brute_Force(x.begin(),x.end(),word.begin(),word.end());
												steady_clock::time_point finish = steady_clock::now();
												size_t duration = duration_cast<milliseconds>(finish-start).count();

												data_BF.push_back(Data(i*step,duration));
												//
/*
												cerr <<"BF" <<  endl;
												for(auto&y : x){
													cerr << y << " ";
												}
												cerr << endl;

												for(auto&y : word){
														cerr << y << " ";
													}
													cerr << endl;
													cerr << *It << endl;
*/
												//

									}

	}

	/////////////////////////////
	////////////////////////////
	//Write in FIle
	//Write RK
	{const string second_txt_RK="second_part_RK.txt";
	ofstream output(second_txt_RK);
	output << left;
	for (auto& x: data_RK){
		output << setw(14) << x.N<< setw(14) << x.time << "\n";
	}
	}
	//Write BM
	{const string second_txt_BM="second_part_BM.txt";
		ofstream output(second_txt_BM);
		output << left;
		for (auto& x: data_BM){
			output << setw(14) << x.N<< setw(14) << x.time << "\n";
		}
	}
	//Write BF
		{const string second_txt_BF="second_part_BF.txt";
			ofstream output(second_txt_BF);
			output << left;
			for (auto& x: data_BF){
				output << setw(14) << x.N<< setw(14) << x.time << "\n";
			}
		}/////////////////////////////
	/////////////////////////////
	/////
	cerr << "\nSecond task has finished" << endl;
	/////

}


//////////////////////////////
/////////////////////////////////
///////////////////////////////
//TESTS
void TestBruteForce(){
	{
					vector<char> test={'A','G','C','T','C','T','A','G'};

					size_t finded=my_brute_force(test.begin(),test.end(),'A');
					assert(finded==1);

					finded=my_brute_force(test.begin(),test.end(),'G');
					assert(finded==9);//Rebuild project

					finded=my_brute_force(test.begin(),test.end(),'C');
					assert(finded==3);

					finded=my_brute_force(test.begin(),test.end(),'T');
					assert(finded==2);

					try{
					finded=my_brute_force(test.begin(),test.begin(),'T');
					}catch(string& ex){
					assert(ex=="Empty");
					}

	}


	cerr << "TestBruteForce passed" << endl;
}

void TestMakeTable(){
	{
		map<char,size_t> excepted={{'A',1},{'G',9},{'C',3},{'T',2}};///zero is size+1
		vector<char> test={'A','G','C','T','C','T','A','G'};

				auto result=Make_table(test.begin(),test.end());
				assert(result==excepted);
	}
	{
		map<char,size_t> excepted={{'A',8},{'G',8},{'C',8},{'T',8}};
		vector<char> test={'B','E','R','V','W','N','S','R'};

			auto result=Make_table(test.begin(),test.end());
			assert(result==excepted);

	}
	{
		map<char,size_t> excepted={{'A',0},{'G',0},{'C',0},{'T',0}};
		vector<char> test;

			auto result=Make_table(test.begin(),test.end());
			assert(result==excepted);

	}

	cerr << "TestMakeTable passed" << endl;
}

void Test_Boyer_Moore(){
	{

		vector<char> test={'A','G','C','T','C','T','A','G'};
        vector<char> word={'C','T','A'};

        auto result=Boyer_Moore(test.begin(),test.end(),word.begin(),word.end());
				assert(*result++=='C');
				assert(*result++=='T');
				assert(*result=='A');

				word={'A','G','C'};
			    result=Boyer_Moore(test.begin(),test.end(),word.begin(),word.end());
				assert(*result++=='A');
				assert(*result++=='G');
				assert(*result=='C');


				word={'T','C'};
				result=Boyer_Moore(test.begin(),test.end(),word.begin(),word.end());
				assert(*result++=='T');
				assert(*result++=='C');
				assert(*result=='T');

				word={'A','G','C','T','C','T','A','G'};
				result=Boyer_Moore(test.begin(),test.end(),word.begin(),word.end());
				assert(*result++=='A');
				assert(*result++=='G');
				assert(*result=='C');

				word={'T','A','G'};
				result=Boyer_Moore(test.begin(),test.end(),word.begin(),word.end());
				assert(*result++=='T');
				assert(*result++=='A');
				assert(*result=='G');

	}

	{
		vector<char> test={'A','A','A','A','A','A','C','A'};
		        vector<char> word={'A','C','A'};

		               auto result=Boyer_Moore(test.begin(),test.end(),word.begin(),word.end());

				       assert(*result++=='A');
						assert(*result++=='C');
						assert(*result=='A');

						word={'A','A','A','C'};
						result=Boyer_Moore(test.begin(),test.end(),word.begin(),word.end());
						assert(*result++=='A');
						assert(*result++=='A');
						assert(*result++=='A');
						assert(*result++=='C');

						word={'C','C'};
						result=Boyer_Moore(test.begin(),test.end(),word.begin(),word.end());
						assert(result==test.end());

						word={};
						result=Boyer_Moore(test.begin(),test.end(),word.begin(),word.end());
						assert(result==test.end());

	}

	{
		vector<char> test;
			        vector<char> word={'A','C','A'};

			               auto result=Boyer_Moore(test.begin(),test.end(),word.begin(),word.end());

					       assert(result==test.end());


	}
	{

	vector<char> test={'T','G', 'T', 'G', 'A', 'A',
			'G', 'G' ,'A','C','T','G','A','T','G','A', 'C', 'C', 'G' ,'G'};
	 vector<char> word={'A','A'};

	 auto result=Boyer_Moore(test.begin(),test.end(),word.begin(),word.end());

	 assert(*result++=='A');
	 assert(*result=='A');

	};
	cerr << "Test_Boyer_Moore passed" << endl;
}

void TestCook(){
	{
		vector<char> test={'A','G','C','T','A','A'}; //7 79 211 907
		int res=Cook(test.begin(),test.end());
		assert(res==1218);
	}
	{
			vector<char> test={'Q','E','W','R','X' ,'Z'}; //7 79 211 907
			int res=Cook(test.begin(),test.end());
			assert(res==0);
	}
	{
			vector<char> test={}; //7 79 211 907
			int res=Cook(test.begin(),test.end());
			assert(res==0);
	}
	cerr << "TestCook passed" << endl;
}

void TestWeight(){
	{
		vector<char> test={'A','G','C','T','N'};
		auto It=test.begin();
		assert(Weight(It++)==7);
		assert(Weight(It++)==79);
		assert(Weight(It++)==211);
		assert(Weight(It++)==907);
		assert(Weight(It++)==0);
	}

	cerr << "TestWeight passed" << endl;
}

void Test_Rabin_Karp(){
	{//A 7 G 79 C 211 T 907

		vector<char> test={'A','G','C','T','C','T','A','G'};
        vector<char> word={'C','T','A'};

        auto result=Rabin_Karp(test.begin(),test.end(),word.begin(),word.end());

                assert(*result++=='C');
				assert(*result++=='T');
				assert(*result=='A');

				word={'A','G','C'};
			    result=Rabin_Karp(test.begin(),test.end(),word.begin(),word.end());
				assert(*result++=='A');
				assert(*result++=='G');
				assert(*result=='C');


				word={'T','C'};
				result=Rabin_Karp(test.begin(),test.end(),word.begin(),word.end());
				assert(*result++=='T');
				assert(*result++=='C');
				assert(*result=='T');

				word={'A','G','C','T','C','T','A','G'};
				result=Rabin_Karp(test.begin(),test.end(),word.begin(),word.end());
				assert(*result++=='A');
				assert(*result++=='G');
				assert(*result=='C');

				word={'T','A','G'};
				result=Rabin_Karp(test.begin(),test.end(),word.begin(),word.end());
				assert(*result++=='T');
				assert(*result++=='A');
				assert(*result=='G');

	}

	{
		vector<char> test={'A','A','A','A','A','A','C','A'};
		        vector<char> word={'A','C','A'};

		               auto result=Rabin_Karp(test.begin(),test.end(),word.begin(),word.end());

				       assert(*result++=='A');
						assert(*result++=='C');
						assert(*result=='A');

						word={'A','A','A','C'};
						result=Rabin_Karp(test.begin(),test.end(),word.begin(),word.end());
						assert(*result++=='A');
						assert(*result++=='A');
						assert(*result++=='A');
						assert(*result++=='C');
						word={'C','C'};
						result=Rabin_Karp(test.begin(),test.end(),word.begin(),word.end());
						assert(result==test.end());

						word={};
						result=Rabin_Karp(test.begin(),test.end(),word.begin(),word.end());
						assert(result==test.end());

	}

	{
			vector<char> test;
			        vector<char> word={'A','C','A'};

			               auto result=Rabin_Karp(test.begin(),test.end(),word.begin(),word.end());

					       assert(result==test.end());


	}

	cerr << "Test_Rabin_Karp passed" << endl;

}

void TestDoCoef(){
	{
		auto v=DoCoef(3,19);
		vector<int64_t> excepted={1,19,361};
		assert(v==excepted);
	}
	{
	    auto v=DoCoef(0,19);
		vector<int64_t> excepted={};
		assert(v==excepted);

	}
	{
	    auto v=DoCoef(1,19);
		vector<int64_t> excepted={1};
		assert(v==excepted);

	}
	{
			auto v=DoCoef(3,20);
			vector<int64_t> excepted={1,20,400};
			assert(v==excepted);
	}
	cerr << "TestDoCoef passed" << endl;
}

void Test_Brute_Force(){
	{//A 7 G 79 C 211 T 907

		vector<char> test={'A','G','C','T','C','T','A','G'};
        vector<char> word={'C','T','A'};

        auto result=Brute_Force(test.begin(),test.end(),word.begin(),word.end());

                assert(*result++=='C');
				assert(*result++=='T');
				assert(*result=='A');

				word={'A','G','C'};
			    result=Brute_Force(test.begin(),test.end(),word.begin(),word.end());
				assert(*result++=='A');
				assert(*result++=='G');
				assert(*result=='C');


				word={'T','C'};
				result=Brute_Force(test.begin(),test.end(),word.begin(),word.end());
				assert(*result++=='T');
				assert(*result++=='C');
				assert(*result=='T');

				word={'A','G','C','T','C','T','A','G'};
				result=Brute_Force(test.begin(),test.end(),word.begin(),word.end());
				assert(*result++=='A');
				assert(*result++=='G');
				assert(*result=='C');

				word={'T','A','G'};
				result=Brute_Force(test.begin(),test.end(),word.begin(),word.end());
				assert(*result++=='T');
				assert(*result++=='A');
				assert(*result=='G');

	}

	{
		vector<char> test={'A','A','A','A','A','A','C','A'};
		        vector<char> word={'A','C','A'};

		               auto result=Brute_Force(test.begin(),test.end(),word.begin(),word.end());

				       assert(*result++=='A');
						assert(*result++=='C');
						assert(*result=='A');

						word={'A','A','A','C'};
						result=Brute_Force(test.begin(),test.end(),word.begin(),word.end());
						assert(*result++=='A');
						assert(*result++=='A');
						assert(*result++=='A');
						assert(*result++=='C');
						word={'C','C'};
						result=Brute_Force(test.begin(),test.end(),word.begin(),word.end());
						assert(result==test.end());

						word={};
						result=Brute_Force(test.begin(),test.end(),word.begin(),word.end());
						assert(result==test.end());

	}

	{
			vector<char> test;
			        vector<char> word={'A','C','A'};

			               auto result=Brute_Force(test.begin(),test.end(),word.begin(),word.end());

					       assert(result==test.end());


	}

	cerr << "Test_Brute_Force passed" << endl;

}
int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	TestBruteForce();
	TestMakeTable();
	Test_Boyer_Moore();
	//TestCook();
	//TestWeight();
	 TestDoCoef();
	Test_Rabin_Karp();
	Test_Brute_Force();


DoFirstTask();
//DoSecondTask();

return 0;
}
