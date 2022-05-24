#include <iostream>
#include <cassert>
#include "Algs_task_fourth.h"
#include <chrono>
#include <vector>
#include <random>
#include <utility>
#include <fstream>
#include <deque>
#include <iomanip>
#include <algorithm>

/////
#include <string>
////
using namespace std;
using namespace std::chrono;


vector<vector<int>> CookVectorsForFirstTask(size_t steps,size_t step){
	//const size_t step=1000;//1250
	//const size_t steps=10;//100

	default_random_engine rand_(steady_clock::now().time_since_epoch().count());
	mt19937 gen(rand_());
	uniform_int_distribution<> dist(0,static_cast<int>(steps*step));// /10000

	vector<vector<int>> v;
	v.reserve(steps);
	vector<int> helper;

	for(size_t i=0; i<steps;i++){

        size_t N=step*i;
		helper.reserve(N);

		for(size_t j=0;j<N;j++){
			helper.push_back(dist(gen));
		}

		v.push_back(move(helper));
	}


	return move(v);
}

struct Data{
	size_t N;
	size_t time;
	Data(size_t n,size_t t):N(n),time(t){}
};

void DoFirstTask(){
	const size_t steps=51;
	const size_t step=300000;

	vector<vector<int>> test= CookVectorsForFirstTask(steps,step);

	/////
	cerr << "\nVector for first task has cooked" << endl;
	/////

	vector<Data> data_count;
	vector<Data> data_LSD;
	data_count.reserve(steps);
	data_LSD.reserve(steps);

	vector<int> helper;

	for(auto& x: test){

		//////Count
		{
			helper=x;

			vector<int> y;
		steady_clock::time_point start = steady_clock::now();
		CountSort(helper,y);
		steady_clock::time_point finish = steady_clock::now();
		size_t duration = duration_cast<milliseconds>(finish-start).count();

		data_count.push_back(Data(helper.size(),duration));
		//
/*
		cerr <<"Count" <<  endl;
		for(auto&x : y){
			cerr << x << " ";
		}
		cerr << endl;
		//*/


		}

						//////LSD
						{

							int k=0;
							if(!x.empty()){
						auto elem=*max_element(x.begin(),x.end());
						while(elem>0){
							elem/=10;
							k++;
						}
							}

							vector<int> y;
						steady_clock::time_point start = steady_clock::now();
					    LSDSort(x,y,10,k);
						steady_clock::time_point finish = steady_clock::now();
						size_t duration = duration_cast<milliseconds>(finish-start).count();

						data_LSD.push_back(Data(x.size(),duration));

						   	//

						//
/*
						cerr <<"LSD" <<  endl;
						for(auto& y : x){
							cerr << y << " ";
						}
						cerr << endl;
						//
						  */




						}


	}

	/////////////////////////////
	////////////////////////////
	//Write in FIle
	//Write heap
	{const string first_txt_count="first_part_count.txt";
	ofstream output(first_txt_count);
	output << left;
	for (auto& x: data_count){
		output << setw(14) << x.N<< setw(14) << x.time << "\n";
	}
	}
	//Write set
	{const string first_txt_LSD="first_part_LSD.txt";
		ofstream output(first_txt_LSD);
		output << left;
		for (auto& x: data_LSD){
			output << setw(14) << x.N<< setw(14) << x.time << "\n";
		}
	}/////////////////////////////

	/////////////////////////////
	/////
	cerr << "First task has finished" << endl;
	/////

}



vector<vector<int>> CookVectorsForSecondTask(size_t size_,size_t step){
	//const size_t step=1000;//1250
	//const size_t steps=10;//100

	default_random_engine rand_(steady_clock::now().time_since_epoch().count());
	mt19937 gen(rand_());
	uniform_int_distribution<> dist(0,static_cast<int>(size_));///////x*1000

	deque<vector<int>> v;


	vector<int> helper;
	//готовим изначальный вектор
	for(size_t j=0;j<size_;j++){
			helper.push_back(dist(gen));
		}

	vector<int> helper_2=helper;//for reversed

	///готовим с чем сравнивать
	vector<int> helper_1=helper;

	MyHeapSort(helper_1);
	vector<int> right=helper_1;

	reverse(helper_1.begin(),helper_1.end());
	vector<int> reversed_right=helper_1;
	///////////////////////////
	//Правильный порядок
	size_t k=step;
	while(helper!=right){
		OneStepBuble(helper.begin(),helper.end());
	    if(k%step==0){
	    	v.push_front(helper);
	    }
	    k++;
	}
	if(k%step!=0){v.push_front(helper);}

	//обратный порядок
	k=step+1;
	while(helper_2!=reversed_right){
		OneStepBuble(helper_2.rbegin(),helper_2.rend());
		    if(k%step==0){
		    	v.push_back(helper_2);
		    }
		    k++;
		}
	if(k%step!=0){v.push_back(helper_2);}

    vector<vector<int>> res= {make_move_iterator(v.begin()),make_move_iterator(v.end())};

    /////

   /* cerr << "\n\nCOOOOKing\n";
    for(auto& x: res){
for(auto& y : x){
	cerr << y << " ";
}
cerr << endl;
    }
    cerr << "\n\nCOOOOKing\n";
*/
    ///

	return move(res);
}


/*
void DoSecondTask(){
	const size_t size_=450000;
	const size_t step=10000;

	vector<vector<int>> test= CookVectorsForSecondTask(size_,step);
	/////
	cerr << "\nVector for second task has cooked" << endl;
	/////

	vector<Data> data_count;
	vector<Data> data_LSD;
    data_count.reserve(test.size());
	data_LSD.reserve(test.size());

	vector<int> helper;

	for(auto& x: test){

		//////Count
				{
					helper=x;

					vector<int> y;
				steady_clock::time_point start = steady_clock::now();
				CountSort(helper,y);
				steady_clock::time_point finish = steady_clock::now();
				size_t duration = duration_cast<milliseconds>(finish-start).count();

				data_count.push_back(Data(helper.size(),duration));
				//

				cerr <<"Count" <<  endl;
				for(auto&x : y){
					cerr << x << " ";
				}
				cerr << endl;
				//

				}

								//////LSD
								{

									int k=0;
									if(!x.empty()){
								auto elem=*max_element(x.begin(),x.end());
								while(elem>0){
									elem/=10;
									k++;
								}
									}

								steady_clock::time_point start = steady_clock::now();
							    LSDSort(x,10,k);
								steady_clock::time_point finish = steady_clock::now();
								size_t duration = duration_cast<milliseconds>(finish-start).count();

								data_LSD.push_back(Data(x.size(),duration));

								   	//

								//

								cerr <<"LSD" <<  endl;
								for(auto& y : x){
									cerr << y << " ";
								}
								cerr << endl;

								//





								}

	}

	/////////////////////////////
	////////////////////////////
	//Write in FIle
	//Write heap
	size_t N=0;
	{const string first_txt_count="second_part_count.txt";
	ofstream output(first_txt_count);
	output << left;
	for (auto& x: data_count){
		output << setw(14) << N++ << setw(14)<< x.N<< setw(14) << x.time << "\n";
	}
	}

	N=0;
	//Write set
	{const string first_txt_LSD="second_part_LSD.txt";
		ofstream output(first_txt_LSD);
		output << left;
		for (auto& x: data_LSD){
			output << setw(14)<< N++ << setw(14) << x.N<< setw(14) << x.time << "\n";
		}
	}
		/////////////////////////////
	/////////////////////////////

	/////
	cerr << "Second task has finsihed" << endl;
	/////
	}


*/

/////////////////////////////////////
/////////////////////////////////////
//////////////////////////////////////
//TESTS


void TestOneStepBuble(){

		////TEST Cases
		{
			array<int,10> test={int(10),int(9),int(8),int(7),int(6),int(5),int(4),int(3),int(2),int(1)};
			array<int,10> right_result={int(1),int(2),int(3),int(4),int(5),int(6),int(7),int(8),int(9),int(10)};

			while(test!=right_result){
				OneStepBuble(test.begin(),test.end());
			}

			assert(right_result==test);

			array<int,10> right_reversed_result={int(10),int(9),int(8),int(7),int(6),int(5),int(4),int(3),int(2),int(1)};

			while(test!=right_reversed_result){
				OneStepBuble(test.rbegin(),test.rend());
						}
			assert(right_reversed_result==test);

		}

  cerr << "TestOneStepBuble passed" << endl;
}

/*
void TestSetSortSecond(){

		////TEST Cases
		{
			vector<int> test={int(10),int(9),int(8),int(7),int(6),int(5),int(4),int(3),int(2),int(1)};

			SetSortSecond(test);
			vector<int> right_result={int(1),int(2),int(3),int(4),int(5),int(6),int(7),int(8),int(9),int(10)};



			assert(right_result==test);


		}

		{
			vector<int> test={int(1),int(6),int(7),int(2),int(4),int(10),int(5),int(8),int(3),int(9)};

						SetSortSecond(test);
						vector<int> right_result={int(1),int(2),int(3),int(4),int(5),int(6),int(7),int(8),int(9),int(10)};



						assert(right_result==test);

		}

		{
			vector<int> test={int(2),int(3),int(1)};

						SetSortSecond(test);
						vector<int> right_result={int(1),int(2),int(3)};

						assert(right_result==test);

		}

		////////TEST ONE MEMBER CASE
		{
				vector<int> test={10};

				SetSortSecond(test);

					vector<int> right_result={10};
					assert(right_result==test);

		}

		/////TEST THE BEST CASE
		{
			vector<int> test={int(1),int(2),int(3),int(4),int(5),int(6),int(7),int(8),int(9),int(10)};

			SetSortSecond(test);

					vector<int> right_result={int(1),int(2),int(3),int(4),int(5),int(6),int(7),int(8),int(9),int(10)};

					assert(right_result==test);

		}
		////TEST MIDDLE CASE


	{
	// Many Elements
			vector<int> test;
			test.resize(100);
			int k=0;
			for(int i=99;i>-1;i--){
				test[k]=int(i);
				k++;
			}
			SetSortSecond(test);


			vector<int> right_result;
			right_result.resize(100);
			for(int i=0;i<100;i++){
				right_result[i]=int(i);
			}


			assert(right_result==test);
		}
	{
		//TestEmpty Case
		vector<int> test;
		SetSortSecond(test);
		assert(test==vector<int>());
	}
	cerr << "TestSetSecond passed" << endl;
}
*/

/*
void TestLSDSort(){

		////TEST Cases
		{
			vector<int> test={int(10),int(9),int(8),int(7),int(6),int(5),int(4),int(3),int(2),int(1)};

			LSDSort(test,10,2);
			vector<int> right_result={int(1),int(2),int(3),int(4),int(5),int(6),int(7),int(8),int(9),int(10)};



			assert(right_result==test);


		}

		{
			vector<int> test={int(1),int(6),int(7),int(2),int(4),int(10),int(5),int(8),int(3),int(9)};

			LSDSort(test,10,2);
						vector<int> right_result={int(1),int(2),int(3),int(4),int(5),int(6),int(7),int(8),int(9),int(10)};



						assert(right_result==test);

		}

		{
			vector<int> test={int(2),int(3),int(1)};

			LSDSort(test,10,2);
						vector<int> right_result={int(1),int(2),int(3)};

						assert(right_result==test);

		}

		////////TEST ONE MEMBER CASE
		{
				vector<int> test={10};

				LSDSort(test,10,2);

					vector<int> right_result={10};
					assert(right_result==test);

		}

		/////TEST THE BEST CASE
		{
			vector<int> test={int(1),int(2),int(3),int(4),int(5),int(6),int(7),int(8),int(9),int(10)};

			LSDSort(test,10,2);

					vector<int> right_result={int(1),int(2),int(3),int(4),int(5),int(6),int(7),int(8),int(9),int(10)};

					assert(right_result==test);

		}
		////TEST MIDDLE CASE


	{
	// Many Elements
			vector<int> test;
			test.resize(100);
			int k=0;
			for(int i=99;i>-1;i--){
				test[k]=int(i);
				k++;
			}
			LSDSort(test,10,2);


			vector<int> right_result;
			right_result.resize(100);
			for(int i=0;i<100;i++){
				right_result[i]=int(i);
			}


			assert(right_result==test);
		}
	{
		//TestEmpty Case
		vector<int> test;
		LSDSort(test,10,2);
		assert(test==vector<int>());
	}
	/////EQUAL ELEMENTS CASE
		{
			vector<int> test={2,2,2,7,8,8,7,6,5,10,2,3};

			LSDSort(test,10,2);

			vector<int> right_result={2,2,2,2,3,5,6,7,7,8,8,10};

					assert(right_result==test);

		}
		/////m=3 case
				{
					vector<int> test={523,570,232,562,437,668,978,337,436,545,10,12,333,437};

					LSDSort(test,10,3);

										vector<int> right_result={10,12,232,333,337,436,437,437,523,545,562,570,668,978};

							assert(right_result==test);

				}
	cerr << "TestLSDSort passed" << endl;
}

*/

void TestCountSort(){

		////TEST Cases
		{
			vector<int> test1={int(10),int(9),int(8),int(7),int(6),int(5),int(4),int(3),int(2),int(1)};

			vector<int> test;
			CountSort(test1,test);
			vector<int> right_result={int(1),int(2),int(3),int(4),int(5),int(6),int(7),int(8),int(9),int(10)};



			assert(right_result==test);

        	}

		{
			vector<int> test1={int(1),int(6),int(7),int(2),int(4),int(10),int(5),int(8),int(3),int(9)};
			vector<int> test;

						CountSort(test1,test);
						vector<int> right_result={int(1),int(2),int(3),int(4),int(5),int(6),int(7),int(8),int(9),int(10)};



						assert(right_result==test);

		}

		{
			vector<int> test1={int(2),int(3),int(1)};

			vector<int> test;

						CountSort(test1,test);
						vector<int> right_result={int(1),int(2),int(3)};

						assert(right_result==test);

		}

		////////TEST ONE MEMBER CASE
		{
				vector<int> test1={10};
				vector<int> test;

							CountSort(test1,test);

					vector<int> right_result={10};
					assert(right_result==test);

		}

		/////TEST THE BEST CASE
		{
			vector<int> test1={int(1),int(2),int(3),int(4),int(5),int(6),int(7),int(8),int(9),int(10)};

			vector<int> test;

						CountSort(test1,test);
					vector<int> right_result={int(1),int(2),int(3),int(4),int(5),int(6),int(7),int(8),int(9),int(10)};

					assert(right_result==test);

		}
		////TEST MIDDLE CASE

	{
	// Many Elements
			vector<int> test1;
			test1.resize(100);
			int k=0;
			for(int i=99;i>-1;i--){
				test1[k]=int(i);
				k++;
			}
			vector<int> test;

						CountSort(test1,test);



			vector<int> right_result;
			right_result.resize(100);
			for(int i=0;i<100;i++){
				right_result[i]=int(i);
			}


			assert(right_result==test);
		}
	{
		//TestEmpty Case
		vector<int> test1;
		vector<int> test;

		CountSort(test1,test);
		assert(test==vector<int>());
	}
	/////EQUAL ELEMENTS CASE
	{
		vector<int> test1={2,2,2,7,8,8,7,6,5,10,2,3};

		vector<int> test;

					CountSort(test1,test);
				vector<int> right_result={2,2,2,2,3,5,6,7,7,8,8,10};

				assert(right_result==test);

	}
	{
					vector<int> test1={523,570,232,562,437,668,978,337,436,545,10,12,333,437};

					vector<int> test;

									CountSort(test1,test);

										vector<int> right_result={10,12,232,333,337,436,437,437,523,545,562,570,668,978};

							assert(right_result==test);

				}

	cerr << "TestCountSort passed" << endl;
}


int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

    TestOneStepBuble();
	TestCountSort();
    //TestLSDSort();



DoFirstTask();
//DoSecondTask();

	return 0;

}
