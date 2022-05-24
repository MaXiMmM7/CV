#include <iostream>
#include <cassert>
#include <array>
#include "Algs_task_second.h"
#include "Int.h"
#include <chrono>
#include <vector>
#include <random>
#include <utility>
#include <fstream>
#include <deque>
#include <iomanip>
using namespace std;
using namespace std::chrono;

vector<vector<Int>> CookVectorsForFirstTask(size_t steps,size_t step){
	//const size_t step=1000;//1250
	//const size_t steps=10;//100

	default_random_engine rand_(steady_clock::now().time_since_epoch().count());
	mt19937 gen(rand_());
	uniform_int_distribution<> dist(0,static_cast<int>(10*steps*step));

	vector<vector<Int>> v;
	v.reserve(steps);
	vector<Int> helper;

	for(size_t i=0; i<steps;i++){

        size_t N=step*i;
		helper.reserve(N);

		for(size_t j=0;j<N;j++){
			helper.push_back(dist(gen));
			helper.back().Zero();
		}

		v.push_back(move(helper));
	}

	return move(v);
}

struct Data{
	size_t N;
	size_t time;
	uint64_t copy;
	uint64_t less;
	Data(size_t n,size_t t,uint64_t c,uint64_t l):N(n),time(t),copy(c),less(l){}
};

void DoFirstTask(){
	const size_t steps=100;
	const size_t step=5000;

	vector<vector<Int>> test= CookVectorsForFirstTask(steps,step);
	vector<Data> data_buble;
	vector<Data> data_brute;
	vector<Data> data_binary;
	data_buble.reserve(steps);
	data_brute.reserve(steps);
	data_binary.reserve(steps);

	size_t less=0;
	size_t count=0;

	vector<Int> helper;

	for(auto& x: test){

		//////BUBLE
		{
			helper=x;
			//
			for(auto& z:helper){
						z.Zero();
					}
			//
		steady_clock::time_point start = steady_clock::now();
		my_buble_Int(helper.begin(),helper.end());
		steady_clock::time_point finish = steady_clock::now();
		size_t duration = duration_cast<milliseconds>(finish-start).count();

		    for(const auto& y: helper){
		   	less+=y.GetLess();
		   	}

		    for(const auto& y: helper){
		    count+=y.GetCopy();
		   	}
		  	count=(count)/2;

		  	data_buble.push_back(Data(helper.size(),duration,count,less));
		   	less =0;
		   	count =0;
		   	//
		   /*	for(auto z: helper){
		   		cout << z << " ";
		   	}
		   	cout << endl;*/
		   	//
		}

		//////BRUTE

			{
				helper.clear();

				auto helper=x;
				//
							for(auto& z:helper){
										z.Zero();
									}
							//
			steady_clock::time_point start = steady_clock::now();
			my_insert_brute_Int(helper.begin(),helper.end());
			steady_clock::time_point finish = steady_clock::now();
			size_t duration = duration_cast<milliseconds>(finish-start).count();

			    for(const auto& y: helper){
			   	less+=y.GetLess();
			   	}

			    for(const auto& y: helper){
			    count+=y.GetCopy();
			   	}
			    count=(count)/2;

			  	data_brute.push_back(Data(helper.size(),duration,count,less));
			   	less =0;
			   	count =0;

			   	//
			   		/*	   	for(auto z: helper){
			   			   		cout << z << " ";
			   			   	}
			   			   	cout << endl;*/
			   			   	//
			}

				//////BINARY
						{
							//
										for(auto& z:x){
													z.Zero();
												}
										//
						steady_clock::time_point start = steady_clock::now();
					    my_insert_binary_Int(x.begin(),x.end());
						steady_clock::time_point finish = steady_clock::now();
						size_t duration = duration_cast<milliseconds>(finish-start).count();

						    for(const auto& y: x){
						   	less+=y.GetLess();
						   	}

						    for(const auto& y: x){
						    count+=y.GetCopy();
						   	}
						    count=(count)/2;

						  	data_binary.push_back(Data(x.size(),duration,count,less));
						   	less =0;
						   	count =0;

						   	//
						   		/*	   	for(auto z: x){
						   			   		cout << z << " ";
						   			   	}
						   			   	cout << endl;*/
						   			   	//
						}


	}

	/////////////////////////////
	////////////////////////////
	//Write in FIle
	//Write buble
	{const string first_txt_buble="first_part_buble.txt";
	ofstream output(first_txt_buble);
	output << left;
	for (auto& x: data_buble){
		output << setw(14) << x.N<< setw(14) << x.time<< setw(14)
				<< x.copy << setw(14)<< x.less << "\n";
	}
	}
	//Write brute
	{const string first_txt_brute="first_part_brute.txt";
		ofstream output(first_txt_brute);
		output << left;
		for (auto& x: data_brute){
			output << setw(14) << x.N<< setw(14) << x.time<< setw(14)
					<< x.copy << setw(14)<< x.less << "\n";
		}
	}
	//Write binary
	{	const string first_txt_binary="first_part_binary.txt";
			ofstream output(first_txt_binary);
			output << left;
			for (auto& x: data_binary){
				output << setw(14) << x.N<< setw(14) << x.time<< setw(14)
						<< x.copy << setw(14)<< x.less << "\n";
			}
	}
	/////////////////////////////
	/////////////////////////////

/*
	cout << "BUBLE" << endl;
	for(auto& x: data_buble){
		cout << "N: " << x.N << " Time: " << x.time <<
				" milliseconds Copy:" << x.copy << " Less:" << x.less << endl;
	}
			cout  << endl;

			cout << "BRUTE" << endl;
				for(auto& x: data_brute){
					cout << "N: " << x.N << " Time: " << x.time <<
							" milliseconds Copy:" << x.copy << " Less:" << x.less << endl;
				}
						cout  << endl;

						cout << "BINARY" << endl;
							for(auto& x: data_binary){
								cout << "N: " << x.N << " Time: " << x.time <<
										" milliseconds Copy:" << x.copy << " Less:" << x.less << endl;
							}
									cout  << endl;*/
}



vector<vector<Int>> CookVectorsForSecondTask(size_t size_,size_t step){
	//const size_t step=1000;//1250
	//const size_t steps=10;//100

	default_random_engine rand_(steady_clock::now().time_since_epoch().count());
	mt19937 gen(rand_());
	uniform_int_distribution<> dist(0,static_cast<int>(size_*10));

	deque<vector<Int>> v;


	vector<Int> helper;
	//готовим изначальный вектор
	for(size_t j=0;j<size_;j++){
			helper.push_back(dist(gen));
			helper.back().Zero();
		}

	vector<Int> helper_2=helper;//for reversed

	///готовим с чем сравнивать
	vector<Int> helper_1=helper;

	my_insert_binary_Int(helper_1.begin(),helper_1.end());
	vector<Int> right=helper_1;

	my_insert_binary_Int(helper_1.rbegin(),helper_1.rend());
	vector<Int> reversed_right=helper_1;
	///////////////////////////
	//Правильный порядок
	size_t k=step;
	while(helper!=right){
		onestep_my_buble_Int(helper.begin(),helper.end());
	    if(k%step==0){
	    	v.push_front(helper);
	    }
	    k++;
	}
	if(k%step!=0){v.push_front(helper);}

	//обратный порядок
	k=step+1;
	while(helper_2!=reversed_right){
			onestep_my_buble_Int(helper_2.rbegin(),helper_2.rend());
		    if(k%step==0){
		    	v.push_back(helper_2);
		    }
		    k++;
		}
	if(k%step!=0){v.push_back(helper_2);}

    vector<vector<Int>> res= {make_move_iterator(v.begin()),make_move_iterator(v.end())};

	return move(res);
}

void DoSecondTask(){
	const size_t size_=50000;
	const size_t step=500;

	vector<vector<Int>> test= CookVectorsForSecondTask(size_,step);


	vector<Data> data_buble;
		vector<Data> data_brute;
		vector<Data> data_binary;
		data_buble.reserve(test.size());
		data_brute.reserve(test.size());
		data_binary.reserve(test.size());

		size_t less=0;
		size_t count=0;

		vector<Int> helper;

		for(auto& x: test){

			//////BUBLE
			{
				helper=x;
				//
				for(auto& z:helper){
							z.Zero();
						}
				//
			steady_clock::time_point start = steady_clock::now();
			my_buble_Int(helper.begin(),helper.end());
			steady_clock::time_point finish = steady_clock::now();
			size_t duration = duration_cast<milliseconds>(finish-start).count();

			    for(const auto& y: helper){
			   	less+=y.GetLess();
			   	}

			    for(const auto& y: helper){
			    count+=y.GetCopy();
			   	}
			  	count=(count)/2;

			  	data_buble.push_back(Data(helper.size(),duration,count,less));
			   	less =0;
			   	count =0;
			   	//
			   /*	for(auto z: helper){
			   		cout << z << " ";
			   	}
			   	cout << endl;*/
			   	//
			}

			//////BRUTE

				{
					helper.clear();

					auto helper=x;
					//
								for(auto& z:helper){
											z.Zero();
										}
								//
				steady_clock::time_point start = steady_clock::now();
				my_insert_brute_Int(helper.begin(),helper.end());
				steady_clock::time_point finish = steady_clock::now();
				size_t duration = duration_cast<milliseconds>(finish-start).count();

				    for(const auto& y: helper){
				   	less+=y.GetLess();
				   	}

				    for(const auto& y: helper){
				    count+=y.GetCopy();
				   	}
				    count=(count)/2;

				  	data_brute.push_back(Data(helper.size(),duration,count,less));
				   	less =0;
				   	count =0;

				   	//
				   		/*	   	for(auto z: helper){
				   			   		cout << z << " ";
				   			   	}
				   			   	cout << endl;*/
				   			   	//
				}

					//////BINARY
							{
								//
											for(auto& z:x){
														z.Zero();
													}
											//
							steady_clock::time_point start = steady_clock::now();
						    my_insert_binary_Int(x.begin(),x.end());
							steady_clock::time_point finish = steady_clock::now();
							size_t duration = duration_cast<milliseconds>(finish-start).count();

							    for(const auto& y: x){
							   	less+=y.GetLess();
							   	}

							    for(const auto& y: x){
							    count+=y.GetCopy();
							   	}
							    count=(count)/2;

							  	data_binary.push_back(Data(x.size(),duration,count,less));
							   	less =0;
							   	count =0;

							   	//
							   		/*	   	for(auto z: x){
							   			   		cout << z << " ";
							   			   	}
							   			   	cout << endl;*/
							   			   	//
							}


		}

		/////////////////////////////
		////////////////////////////
		//Write in FIle
		//Write buble
		size_t number=0;
		{const string first_txt_buble="second_part_buble.txt";
		ofstream output(first_txt_buble);
		output << left;
		for (auto& x: data_buble){
			output << setw(14) << number++ << setw(14) << x.time<< setw(14)
					<< x.copy << setw(14)<< x.less << "\n";
		}
		}
		//Write brute
		number=0;
		{const string first_txt_brute="second_part_brute.txt";
			ofstream output(first_txt_brute);
			output << left;
			for (auto& x: data_brute){
				output << setw(14) << number++<< setw(14) << x.time<< setw(14)
						<< x.copy << setw(14)<< x.less << "\n";
			}
		}
		//Write binary
		number=0;
		{	const string first_txt_binary="second_part_binary.txt";
				ofstream output(first_txt_binary);
				output << left;
				for (auto& x: data_binary){
					output << setw(14) << number++ << setw(14) << x.time<< setw(14)
							<< x.copy << setw(14)<< x.less << "\n";
				}
		}
		/////////////////////////////
		/////////////////////////////

	}




/////////////////////////////////////
/////////////////////////////////////
//////////////////////////////////////
//TESTS
void TestOneStepBuble(){

		////TEST Cases
		{
			array<Int,10> test={Int(10),Int(9),Int(8),Int(7),Int(6),Int(5),Int(4),Int(3),Int(2),Int(1)};
			array<Int,10> right_result={Int(1),Int(2),Int(3),Int(4),Int(5),Int(6),Int(7),Int(8),Int(9),Int(10)};

			while(test!=right_result){
				onestep_my_buble_Int(test.begin(),test.end());
			}

			assert(right_result==test);

			array<Int,10> right_reversed_result={Int(10),Int(9),Int(8),Int(7),Int(6),Int(5),Int(4),Int(3),Int(2),Int(1)};

			while(test!=right_reversed_result){
							onestep_my_buble_Int(test.rbegin(),test.rend());
						}
			assert(right_reversed_result==test);

		}

  cerr << "TestOneStepBuble passed" << endl;
}

void TestInsertBinary(){
	{
		////TEST Cases
		{
			array<Int,10> test={Int(10),Int(9),Int(8),Int(7),Int(6),Int(5),Int(4),Int(3),Int(2),Int(1)};

			my_insert_binary_Int(test.begin(),test.end());


			array<Int,10> right_result={Int(1),Int(2),Int(3),Int(4),Int(5),Int(6),Int(7),Int(8),Int(9),Int(10)};

			assert(right_result==test);


		     size_t count =0;
		     for(const auto& x: test){
			 count+=x.GetCopy();
		     }
		     assert((10*9/2)==count/2);

		}
		{
			array<Int,5> test={Int(10),Int(9),Int(8),Int(7),Int(6)};

			my_insert_binary_Int(test.begin(),test.end());

			array<Int,5> right_result={Int(6),Int(7),Int(8),Int(9),Int(10)};
				assert(right_result==test);


					     size_t count =0;
					     for(const auto& x: test){
						 count+=x.GetCopy();
					     }
					     assert((5*4/2)==count/2);

		}

		{
				array<Int,3> test={Int(10),Int(9),Int(8)};

				my_insert_binary_Int(test.begin(),test.end());

					array<Int,3> right_result={Int(8),Int(9),Int(10)};
					assert(right_result==test);


						     size_t count =0;
						     for(const auto& x: test){
							 count+=x.GetCopy();
						     }
						     assert((3*2/2)==count/2);

		}

		////////TEST ONE MEMBER CASE
		{
				array<Int,1> test={10};

				my_insert_binary_Int(test.begin(),test.end());

					array<Int,1> right_result={10};
					assert(right_result==test);

									     size_t count =0;
						     for(const auto& x: test){
							 count+=x.GetCopy();
						     }
						    assert(0==count/2);

		}

		/////TEST THE BEST CASE
		{
			array<Int,10> test={Int(1),Int(2),Int(3),Int(4),Int(5),Int(6),Int(7),Int(8),Int(9),Int(10)};

			my_insert_binary_Int(test.begin(),test.end());

					array<Int,10> right_result={Int(1),Int(2),Int(3),Int(4),Int(5),Int(6),Int(7),Int(8),Int(9),Int(10)};

					assert(right_result==test);

							     size_t count =0;
				     for(const auto& x: test){
					 count+=x.GetCopy();
				     }
				     assert(0==count/2);

		}
		////TEST MIDDLE CASE

		{
			array<Int,10> test={5,9,3,10,2,1,7,4,8,6};

			my_insert_binary_Int(test.begin(),test.end());

					array<Int,10> right_result={Int(1),Int(2),Int(3),Int(4),Int(5),Int(6),Int(7),Int(8),Int(9),Int(10)};

					assert(right_result==test);


		}
		{
			array<Int,5> test={5,4,3,2,1};
			my_insert_binary_Int(test.begin(),test.end());
			array<Int,5> right_result={1,2,3,4,5};
			assert(right_result==test);

			     size_t count =0;
					for(const auto& x: test){
					 count+=x.GetCopy();
							     }
							     assert(10==count/2);

		}


	}
	cerr << "TestInsertBinary passed" << endl;
}


void TestInsertBrute(){
	{
		////TEST Cases
		{
			array<Int,10> test={Int(10),Int(9),Int(8),Int(7),Int(6),Int(5),Int(4),Int(3),Int(2),Int(1)};

			my_insert_brute_Int(test.begin(),test.end());

			array<Int,10> right_result={Int(1),Int(2),Int(3),Int(4),Int(5),Int(6),Int(7),Int(8),Int(9),Int(10)};



			assert(right_result==test);

			 size_t less =0;
		     for(const auto& x: test){
			 less+=x.GetLess();
		     }

		     assert((10*9/2)==less);

		     size_t count =0;
		     for(const auto& x: test){
			 count+=x.GetCopy();
		     }

		     assert((10*9/2)==count/2);

		}
		{
			array<Int,5> test={Int(10),Int(9),Int(8),Int(7),Int(6)};

			my_insert_brute_Int(test.begin(),test.end());

			array<Int,5> right_result={Int(6),Int(7),Int(8),Int(9),Int(10)};
				assert(right_result==test);

						 size_t less =0;
					     for(const auto& x: test){
						 less+=x.GetLess();
					     }
					     assert((5*4/2)==less);

					     size_t count =0;
					     for(const auto& x: test){
						 count+=x.GetCopy();
					     }
					     assert((5*4/2)==count/2);

		}

		{
				array<Int,3> test={Int(10),Int(9),Int(8)};

				my_insert_brute_Int(test.begin(),test.end());

					array<Int,3> right_result={Int(8),Int(9),Int(10)};
					assert(right_result==test);

							 size_t less =0;
						     for(const auto& x: test){
							 less+=x.GetLess();
						     }
						     assert((3*2/2)==less);

						     size_t count =0;
						     for(const auto& x: test){
							 count+=x.GetCopy();
						     }
						     assert((3*2/2)==count/2);

		}

		////////TEST ONE MEMBER CASE
		{
				array<Int,1> test={10};

				my_insert_brute_Int(test.begin(),test.end());

					array<Int,1> right_result={10};
					assert(right_result==test);

							 size_t less =0;
						     for(const auto& x: test){
							 less+=x.GetLess();
						     }
						     assert(0==less);

						     size_t count =0;
						     for(const auto& x: test){
							 count+=x.GetCopy();
						     }
						    assert(0==count/2);

		}

		/////TEST THE BEST CASE
		{
			array<Int,10> test={Int(1),Int(2),Int(3),Int(4),Int(5),Int(6),Int(7),Int(8),Int(9),Int(10)};

			my_insert_brute_Int(test.begin(),test.end());

					array<Int,10> right_result={Int(1),Int(2),Int(3),Int(4),Int(5),Int(6),Int(7),Int(8),Int(9),Int(10)};

					assert(right_result==test);

					 size_t less =0;
				     for(const auto& x: test){
					 less+=x.GetLess();
				     }
				     assert((10-1)==less);

				     size_t count =0;
				     for(const auto& x: test){
					 count+=x.GetCopy();
				     }
				     assert(0==count/2);

		}
		////TEST MIDDLE CASE

		{
			array<Int,10> test={5,9,3,10,2,1,7,4,8,6};

			my_insert_brute_Int(test.begin(),test.end());

					array<Int,10> right_result={Int(1),Int(2),Int(3),Int(4),Int(5),Int(6),Int(7),Int(8),Int(9),Int(10)};

					assert(right_result==test);


		}
		{
			array<Int,5> test={5,4,3,2,1};
			my_insert_brute_Int(test.begin(),test.end());
			array<Int,5> right_result={1,2,3,4,5};
			assert(right_result==test);

			size_t less =0;
		   for(const auto& x: test){
			   less+=x.GetLess();
							 }
		   assert((10)==less);
			     size_t count =0;
					for(const auto& x: test){
					 count+=x.GetCopy();
							     }
							     assert(10==count/2);

		}


	}

	{
	// Many Elements
			array<Int,100> test;
			int k=0;
			for(int i=99;i>-1;i--){
				test[k]=Int(i);
				test[k].Zero();
				k++;
			}
			my_insert_brute_Int(test.begin(),test.end());


			array<Int,100> right_result;
			for(int i=0;i<100;i++){
				right_result[i]=Int(i);
			}


			assert(right_result==test);

			 size_t less =0;
		     for(const auto& x: test){
			 less+=x.GetLess();
		     }

		     assert((100*99/2)==less);

		     size_t count =0;
		     for(const auto& x: test){
			 count+=x.GetCopy();
		     }

		     assert((100*99/2)==count/2);

		}
	cerr << "TestInsertBrute passed" << endl;
}

void TestBruteForce(){
	{
				array<Int,10> test={Int(1),Int(2),Int(3),Int(4),Int(5),Int(6),Int(7),Int(8),Int(9),Int(10)};

				auto It=my_brute_force(test.begin(),test.end(),Int(9));

				assert(*It==Int(10));


				It=my_brute_force(test.begin(),test.end(),Int(2));

				assert(*It==Int(3));

				It=my_brute_force(test.begin(),test.end(),Int(1));

				assert(*It==Int(2));

		}{
			array<Int,1> test={Int(9)};

			auto It=my_brute_force(test.begin(),test.end(),Int(9));

			assert(It==test.end());

		}

	cerr << "TestBruteForce passed" << endl;

}

void TestLowerBound(){

		{
				array<Int,10> test={Int(1),Int(2),Int(3),Int(4),Int(5),Int(6),Int(7),Int(8),Int(9),Int(10)};

				auto It=my_lower_bound_Int(test.begin(),test.end(),Int(9));

				assert(*It==Int(9));


				It=my_lower_bound_Int(test.begin(),test.end(),Int(2));

				assert(*It==Int(2));

				It=my_lower_bound_Int(test.begin(),test.end(),Int(1));

				assert(*It==Int(1));

		}{
			array<Int,1> test={Int(9)};

			auto It=my_lower_bound_Int(test.begin(),test.end(),Int(9));

			assert(*It==Int(9));

		}

	cerr << "TestLowerBound passed" << endl;
}
void TestBubleInt(){

	////TEST BADE CASE
	{
		array<Int,10> test={Int(10),Int(9),Int(8),Int(7),Int(6),Int(5),Int(4),Int(3),Int(2),Int(1)};

		my_buble_Int(test.begin(),test.end());

		array<Int,10> right_result={Int(1),Int(2),Int(3),Int(4),Int(5),Int(6),Int(7),Int(8),Int(9),Int(10)};

		assert(right_result==test);

		 size_t less =0;
	     for(const auto& x: test){
		 less+=x.GetLess();
	     }
	     assert((10*9/2)==less);

	     size_t count =0;
	     for(const auto& x: test){
		 count+=x.GetCopy();
	     }
	     assert((10*9/2)==count/2);
	}
	{
		array<Int,5> test={Int(10),Int(9),Int(8),Int(7),Int(6)};

			my_buble_Int(test.begin(),test.end());

		array<Int,5> right_result={Int(6),Int(7),Int(8),Int(9),Int(10)};
			assert(right_result==test);

					 size_t less =0;
				     for(const auto& x: test){
					 less+=x.GetLess();
				     }
				     assert((5*4/2)==less);

				     size_t count =0;
				     for(const auto& x: test){
					 count+=x.GetCopy();
				     }
				     assert((5*4/2)==count/2);
	}

	{
			array<Int,3> test={Int(10),Int(9),Int(8)};

				my_buble_Int(test.begin(),test.end());

				array<Int,3> right_result={Int(8),Int(9),Int(10)};
				assert(right_result==test);

						 size_t less =0;
					     for(const auto& x: test){
						 less+=x.GetLess();
					     }
					     assert((3*2/2)==less);

					     size_t count =0;
					     for(const auto& x: test){
						 count+=x.GetCopy();
					     }
					     assert((3*2/2)==count/2);
}

	////////TEST ONE MEMBER CASE
	{
			array<Int,1> test={10};

				my_buble_Int(test.begin(),test.end());

				array<Int,1> right_result={10};
				assert(right_result==test);

						 size_t less =0;
					     for(const auto& x: test){
						 less+=x.GetLess();
					     }
					     assert(0==less);

					     size_t count =0;
					     for(const auto& x: test){
						 count+=x.GetCopy();
					     }
					     assert(0==count/2);
}

	/////TEST THE BEST CASE
	{
		array<Int,10> test={Int(1),Int(2),Int(3),Int(4),Int(5),Int(6),Int(7),Int(8),Int(9),Int(10)};

				my_buble_Int(test.begin(),test.end());

				array<Int,10> right_result={Int(1),Int(2),Int(3),Int(4),Int(5),Int(6),Int(7),Int(8),Int(9),Int(10)};

				assert(right_result==test);

				 size_t less =0;
			     for(const auto& x: test){
				 less+=x.GetLess();
			     }
			     assert((10*9/2)==less);

			     size_t count =0;
			     for(const auto& x: test){
				 count+=x.GetCopy();
			     }
			     assert(0==count/2);

	}

	////TEST MIDDLE CASE
	{
		array<Int,10> test={5,9,3,10,2,1,7,4,8,6};

				my_buble_Int(test.begin(),test.end());

				array<Int,10> right_result={Int(1),Int(2),Int(3),Int(4),Int(5),Int(6),Int(7),Int(8),Int(9),Int(10)};

				assert(right_result==test);

				 size_t less =0;
			     for(const auto& x: test){
				 less+=x.GetLess();
			     }
			     assert((10*9/2)==less);

	}
	{
		// Many Elements
		//
		array<Int,25> test;
				int k=0;
				for(int i=24;i>-1;i--){
					test[k]=Int(i);
					test[k].Zero();
					k++;
				}
				my_buble_Int(test.begin(),test.end());



				array<Int,25> right_result;
				for(int i=0;i<25;i++){
					right_result[i]=Int(i);
				}


				assert(right_result==test);

				 size_t less =0;
			     for(const auto& x: test){
				 less+=x.GetLess();
			     }

			     assert((25*24/2)==less);

			     size_t count =0;
			     for(const auto& x: test){
				 count+=x.GetCopy();
			     }


			     assert((25*24/2)==count/2);

			}

	cerr << "TestBuble passed" << endl;

}

void TestInt(){
	{
		Int a(3);
		Int b=a;
		assert(a.data==b.data);
		assert(b.GetCopy()== 1);
		assert(a.GetCopy()== 0);
		a<b;
		assert(b.GetLess()== 0);
	    assert(a.GetLess()== 1);
	}
	{
	Int a(1);
	Int b(3);
	Int c(5);

	assert(a.data==1);
	assert(b.data==3);
	assert(c.data==5);

	a=b;
    b=c;
    c=a;
    a=b;
    b=c;
    c=a;

    assert((a.GetCopy()+b.GetCopy()+c.GetCopy())==6);
	}

	cerr << "TestInt passed" << endl;
}
int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

TestInt();
TestBubleInt();
TestLowerBound();
TestBruteForce();
TestInsertBrute();
TestInsertBinary();
TestOneStepBuble();

//TestTime();
DoFirstTask();
DoSecondTask();
return 0;
}





/*
class Int{
public:
	int data;
	Int(int x=0):data(x){}
	Int(const Int& object):data(object.data){
		copy_counter++;
	}
	Int& operator=(const Int& object){
			data=object.data;
			copy_counter++;
			return *this;
		}
	bool operator< (const Int& object){
		less_counter++;
		return data<object.data;
	}
	bool operator<= (const Int& object){
			less_counter++;
			return data<=object.data;
		}
	size_t GetLess() const{
		return less_counter;
	}
	size_t GetCopy() const{
		return copy_counter;
	}
private:
	size_t less_counter=0;
	size_t copy_counter=0;
};

bool operator == (const Int& l,const Int& r){
	return l.data==r.data;
}

ostream& operator<< (ostream& stream,const Int& object){
	return stream << object.data;
}
*/
/*
template<typename Iterator,typename T>
Iterator my_brute_force(Iterator begin, Iterator end, T object){

	while(begin!=end&&*begin<object){
		begin++;
	}
	return begin;
}


template<typename Iterator,typename T>
Iterator my_lower_bound_Int(Iterator begin, Iterator end, T object){

	Iterator It=begin+(end-begin)/2;

while(begin<end){
	if(*It<object){
		begin=It+1;
	}
	else{
		end=It;
	}
	It=begin+(end-begin)/2;
}
return It;
}


template<typename Iterator>
void my_buble_Int(Iterator begin, Iterator end){
	if(begin==end){return ;}

Int helper;
Iterator It1=begin;
Iterator It2=next(begin);

while(begin<end){
		while(It2!=end){
			if(*It2<*It1){
				helper=*It1;
				*It1=*It2;
				*It2=helper;
			}
			It1++;
			It2++;
		}
		It1=begin;
		It2=next(begin);
		end--;
	}
}

template<typename Iterator>
void my_insert_brute_Int(Iterator begin, Iterator end){
Iterator helper1,helper2;
Int helper;
	for(Iterator It=begin;It<end;It++){
		helper1=my_brute_force(begin,It,*It);
		for(helper2=It;helper1<helper2;helper2--){
		helper=*helper2;
		*helper2=*prev(helper2);
		*prev(helper2)=helper;
		}
	}
}


template<typename Iterator>
void my_insert_binary_Int(Iterator begin, Iterator end){
	Iterator helper1,helper2;
	Int helper;
		for(Iterator It=begin;It<end;It++){
			helper1=my_lower_bound_Int(begin,It,*It);
			for(helper2=It;helper1<helper2;helper2--){
			helper=*helper2;
			*helper2=*prev(helper2);
			*prev(helper2)=helper;
			}
		}

}
*/
/*
void TestTime(){
	default_random_engine rand_(steady_clock::now().time_since_epoch().count());
	mt19937 gen(rand_());
	uniform_int_distribution<> dist(0,static_cast<int>(20000));
	cout << dist(gen) << " " << dist(gen) << endl;


	steady_clock::time_point start = steady_clock::now();
	vector<Int> v;
	v.reserve(12500);
	for(int i=12500; i >0; i--){
		v.push_back(dist(gen));
	}
	for(auto& x: v){
		x.Zero();
	}

	my_buble_Int(v.begin(),v.end());

	steady_clock::time_point finish = steady_clock::now();
	auto duration = duration_cast<milliseconds>(finish-start).count();
    cout << duration << endl;
    size_t d=duration;
    cout << d << endl;
    size_t less =0;
    for(const auto& x: v){
   	less+=x.GetLess();
   	   }

     size_t count =0;
     for(const auto& x: v){
      count+=x.GetCopy();
   				     }
   		count=count/2;
   		cout << less << "  " <<  count  << endl;
   		cerr << v[0] <<" " <<  v[1]<< " " << v[10000] << "  " << v.size() << endl;


}*/





