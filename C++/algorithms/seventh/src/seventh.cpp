
#include <iostream>
#include "headdd.h"
#include <utility>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <cctype>
#include <cassert>
#include <algorithm>
#include <iomanip>
using namespace std;


using namespace std::chrono;


 vector<pair<string,size_t>> Get(vector<pair<string,size_t>>& list){
	vector<pair<string,size_t>> res;
	int i=1;
	auto cur=list.begin();
	pair<string,size_t> max;
    auto MAX=cur;

	while(i<101&&i<=static_cast<int>(list.size())){
		while(cur!=list.end()){
				if(MAX->second<cur->second){
        	 MAX=cur;
         }
         cur=cur+1;
       }
		res.push_back(make_pair(MAX->first,MAX->second));
		MAX->second=0;
		cur=list.begin();
		i++;
	}
	return res;
}


void CleanWord(string& word){
	auto It=word.begin();
		while(It!=word.end()){
				if(!islower(*It)){
					 *It=static_cast<char>(tolower(*It));
				}
		if(ispunct(*It)){
				while(It!=end(word)&&ispunct(*It)){
							word.erase(It);
								}
		}
		else{
			It++;
		}

				if(It==end(word)){break;}

	}

}



pair<size_t,bool> LinearInsert(vector<pair<string,size_t>>& table,size_t K,const string& word){
	size_t counter=0;
	hash<string> hasher;
	size_t x=hasher(word);
	size_t index=x%K;
    if(table[index].first.empty()){
    	table[index]=make_pair(word,1);
    	return make_pair(counter,true);
    }
    else if(table[index].first==word){
    	table[index].second++;
    	//return make_pair(1,false);
    	return make_pair(0,false);
    }
    size_t i=1;
    size_t h=index;

    do{
   counter++;
    h=(x+i)%K;
    i++;
    }while((!table[h].first.empty())&&(table[h].first!=word)&&h!=index);
    bool res;
    if(h!=index){
    	if(table[h].first==word){
    		table[h].second++;
    	//	counter++;
    		res=false;
    	}
    	else{
    	table[h]=make_pair(word,1);
    	res=true;
    	}
    }

	return make_pair(counter,res);
}

pair<size_t,bool> SquareInsert(vector<pair<string,size_t>>& table,size_t K,const string& word){
	size_t counter=0;
	hash<string> hasher;
	size_t x=hasher(word);
	size_t index=x%K;
    if(table[index].first.empty()){
    	table[index]=make_pair(word,1);
    	return make_pair(counter,true);
    }
    else if(table[index].first==word){
    	table[index].second++;
   // 	return make_pair(1,false);
     	return make_pair(0,false);
    }
    size_t i=1;
    size_t h=index;

    //

   // cerr << 3 << endl;
    //
    do{
   //table[h].second++;
   counter++;
   /*if(h==table.size()){
	   x=x-table.size();
   }*/
    h=(x+i*i)%K;
    i++;
    }while((!table[h].first.empty())&&(table[h].first!=word)&&i<K/2);
    //

       // cerr << 4 << endl;
        //
    bool res;
    if(h!=index){
    	if(table[h].first==word){
    		table[h].second++;
    		//counter++;
    		res=false;
    	}
    	else{
    	table[h]=make_pair(word,1);
    	res=true;
    	}
    }

	return make_pair(counter,res);
}

struct Data{
	size_t N;
	size_t count;
	Data(size_t n,size_t count):N(n),count(count){}
};


void DoTask(){

	vector<pair<string,size_t>> linear;
	vector<pair<string,size_t>> square;
	//size_t K=23399;
	size_t K=23410;
	linear.resize(K);
	square.resize(K);
	ifstream input("text.txt");
	//ifstream input("dog.txt");
	//ifstream input("cat.txt");
//23326  23399


	vector<Data> data_linear;
    vector<Data> data_square;

    vector<pair<size_t,size_t>> data_l_time;
    vector<pair<size_t,size_t>> data_s_time;

    string helper;
    size_t res_l=0;
    size_t res_s=0;
    size_t time_res_l=0;
    size_t time_res_s=0;
    size_t cur;

    size_t helper_l=0;
    size_t helper_s=0;
    size_t time_helper_l=0;
    size_t time_helper_s=0;

    size_t counter_l=1;
    size_t counter_s=1;
    size_t time_counter_l=1;
    size_t time_counter_s=1;

    size_t M_l=0;
    size_t M_s=0;
    bool logical;

    //while(helper.empty()){
    //
    //cerr << "Hello" << endl;
    //size_t AAA=0;
   // cerr << AAA << endl;
    //

while(input){
	input>>helper;
	CleanWord(helper);
	if(!helper.empty()&&input){

		{
	steady_clock::time_point start = steady_clock::now();
	auto b =LinearInsert(linear,K,helper);
	steady_clock::time_point finish = steady_clock::now();
	size_t duration = duration_cast<microseconds>(finish-start).count();


			logical=b.second;
			cur=b.first;
			if(logical){
				M_l++;
			res_l=(helper_l+cur)/counter_l;
			time_res_l=(time_helper_l+duration)/time_counter_l;
			data_linear.push_back(Data(M_l,res_l));
			data_l_time.push_back(make_pair(M_l,time_res_l));
			////
			helper_l=0;
			time_helper_l=0;
			counter_l=1;
			time_counter_l=1;
			}
			else{
				helper_l+=cur;
				counter_l++;
				time_helper_l+=duration;
				time_counter_l++;
			}

		}

		//
				 //   cerr << "!  " << helper << endl;
		//AAA++;
		//


		{
			steady_clock::time_point start = steady_clock::now();
					auto b =SquareInsert(square,K,helper);
					steady_clock::time_point finish = steady_clock::now();
						size_t duration = duration_cast<microseconds>(finish-start).count();


					logical=b.second;
					cur=b.first;
					if(logical){
						M_s++;
					res_s=(helper_s+cur)/counter_s;
					time_res_s=(time_helper_s+duration)/time_counter_s;
					data_square.push_back(Data(M_s,res_s));
					data_s_time.push_back(make_pair(M_s,time_res_s));
					////
					helper_s=0;
					counter_s=1;
					time_helper_s=0;
					time_counter_s=1;
					}
					else{
						helper_s+=cur;
						counter_s++;
						time_helper_s+=duration;
						time_counter_s++;
					}

				}


}
}

//}

//

//cerr << "Hey" << endl;
//
/////////////////////////////
////////////////////////////
//Write in FIle
//Write linear
{const string first_txt_linear="linear.txt";
ofstream output(first_txt_linear);
output << left;
for (auto& x: data_linear){
	output << setw(14) << x.N<< setw(14) << x.count << "\n";
}
}

//Write square
{const string first_txt_square="square.txt";
ofstream output(first_txt_square);
output << left;
for (auto& x: data_square){
	output << setw(14) << x.N<< setw(14) << x.count << "\n";
}
}

//Write linear_time
{const string first_txt_linear="linear_time.txt";
ofstream output(first_txt_linear);
output << left;
for (auto& x: data_l_time){
	output << setw(14) << x.first<< setw(14) << x.second << "\n";
}
}

//Write square_time
{const string first_txt_square="square_time.txt";
ofstream output(first_txt_square);
output << left;
for (auto& x: data_s_time){
	output << setw(14) << x.first<< setw(14) << x.second << "\n";
}
}

///

vector<pair<string,size_t>> res_ll;
auto res_ss=res_ll;
//
{const string first_txt_linear="linear_get.txt";
ofstream output(first_txt_linear);
output << left;
int i=1;
auto ress=Get(linear);
res_ll=ress;
for (auto& x: res_ll){
	output << setw(5) << i++ << setw(25) << x.first<< setw(14) << x.second << "\n";
}
}
//Write square
{const string first_txt_square="square_get.txt";
ofstream output(first_txt_square);
output << left;
int i=1;
auto ress=Get(square);
res_ss=ress;
for (auto& x: res_ss){
	output  << setw(5) << i++<< setw(25) << x.first<< setw(14) << x.second << "\n";
}
}

cerr << endl << "Completed!" << endl;

}



int main() {


    DoTask();



	return 0;
}
