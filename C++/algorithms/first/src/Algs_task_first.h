#pragma once
#include <vector>
#include <map>
#include <set>
#include <string>
#include <iterator>
#include <chrono>
#include <exception>
#include <random>
using namespace std;


////////////////////////////////////////////
///////////////КАРП-КАРП
template <typename Iterator>
int Cook(Iterator It,Iterator end_ex){ //AGCT
	int sum=0;

	while(It!=end_ex){
		if(*It=='A'){sum+=7;}
		if(*It=='G'){sum+=79;}
		if(*It=='C'){sum+=211;}
		if(*It=='T'){sum+=907;}
		It++;
	}

return sum;
}

/*
template<typename Iterator>
int Weight(Iterator It){
	if(*It=='A'){return 7;}
		if(*It=='G'){return 79;}
		if(*It=='C'){return 211;}
		if(*It=='T'){return 907;}
		return 0;

}*/

template<typename Iterator>
int64_t Weight(Iterator It){
	if(*It=='A'){return 7;}
		if(*It=='G'){return 11;}
		if(*It=='C'){return 13;}
		if(*It=='T'){return 17;}
		return 0;

}

template<typename Iterator>
int64_t WeightDown(Iterator It,int64_t sum,int64_t X_){
	sum-=Weight(It);
	return sum/=X_;
}

template<typename Iterator>
int64_t WeightUp(Iterator It,int64_t sum,int64_t X){
	sum+=Weight(It)*X;
	return sum;
}

vector<int64_t> DoCoef(int64_t size,int64_t x){
	vector<int64_t> res(size);

	if(size<1){return res;}

	//int R=3571;

	/*default_random_engine rand_(std::chrono::steady_clock::now().time_since_epoch().count());
	mt19937 gen(rand_());
	uniform_int_distribution<> dist(2,R-1);
    int x=dist(gen);*/

    res[0]=1;

    int64_t helper;
    for(int i =1;i<size;i++){
    	helper=x;
    	for(int j=1;j<i;j++){
    		helper*=x;
    	}
    	res[i]=helper;//%R;
    }

    return res;
}

template <typename Iterator>
int64_t Cook_2(Iterator It,Iterator end_ex,const vector<int64_t>& X){ //AGCT
	int64_t sum=0;
for(const auto& x: X){
	sum+=(Weight(It))*x;
	It++;
}
return sum;
}

template <typename Iterator>
Iterator Rabin_Karp(Iterator begin,Iterator end,Iterator begin_ex,Iterator end_ex){

	if(!(distance(begin_ex,end_ex))||!(distance(begin,end))){return end;}

	int64_t xx=3;
	auto X_=DoCoef(static_cast<int64_t>(distance(begin_ex,end_ex)),xx);

	//int weight=Cook(begin_ex,end_ex);
	int64_t weight=Cook_2(begin_ex,end_ex,X_);
	auto It_l=begin;
	auto It_r=begin+distance(begin_ex,end_ex)-1;

	int64_t sum=Cook_2(It_l,It_r+1,X_);

    auto It=begin_ex;
    auto It_=begin;

    while(It_r!=end && It!=end_ex){
    	if(sum==weight){
    	It_=It_l;
    	while(It!=end_ex){
    		if(*It!=*It_){break;}
    		It++; It_++;
    	}
    	if(It!=end_ex){It=begin_ex;}
     }

   	//sum-=Weight(It_l);
    	sum=WeightDown(It_l,sum,xx);
    It_l++;
    It_r++;
    if(It_r!=end){sum=WeightUp(It_r,sum,*prev(X_.end()));}

    }

    if(It!=end_ex){return end;}
    return --It_l;

}






//////////////////////////////////////////////////////////////
/////////////////МУР-МУР


template<typename Iterator,typename T>
size_t my_brute_force(Iterator begin, Iterator end, T object){//aka upper bound

	size_t res=0;
	if(end!=begin){end=prev(end);}
		else {throw string("Empty");}
	while(prev(begin)!=end&&*end!=object){
		end--;
	    res++;
	}

	if(res==0){res=distance(begin,end)+2;}

	return res;
}

template<typename Iterator>
map<char,size_t> Make_table(Iterator begin_ex,Iterator end_ex){
	//AGCT
	map<char,size_t> table;
	try{
	table['A']=my_brute_force(begin_ex,end_ex,'A');
	}catch(string& ex){
		table['A']=0;
	}
	try{
	table['G']=my_brute_force(begin_ex,end_ex,'G');
	}catch(string& ex){
		table['G']=0;
	}
	try{
		table['C']=my_brute_force(begin_ex,end_ex,'C');
	}catch(string& ex){
		table['C']=0;
	}
	try{
		table['T']=my_brute_force(begin_ex,end_ex,'T');
    }catch(string& ex){
	 table['T']=0;
    }

	return table;
}


template<typename Iterator>
Iterator Boyer_Moore(Iterator begin,Iterator end,Iterator begin_ex,Iterator end_ex){

	if(!(distance(begin_ex,end_ex))||!(distance(begin,end))){return end;}

	auto table=Make_table(begin_ex,end_ex);

    size_t M=distance(begin_ex,end_ex)-1;
    auto It=begin+M;
	auto It_=end_ex-1;
	auto It1=It;


	while(It_!=prev(begin_ex)&&It<end){
		It1=It;
		It_=end_ex-1;
		while(It_!=prev(begin_ex)&&*It_==*It1){

			It1--;
			It_--;
		}
		if(table[*It1]==static_cast<size_t>(distance(begin_ex,end_ex)+1)){
			It=It+distance(It1,It)+1;

		}else{
		It+=table[*It1];
		}

	}

	It1++;


	if(It_!=prev(begin_ex)){It1=end;}

	return It1;
}




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//////////////////////////Брут-Брут

template<typename Iterator>
Iterator Brute_Force(Iterator begin,Iterator end,Iterator begin_ex,Iterator end_ex){

	if(!(distance(begin_ex,end_ex))||!(distance(begin,end))){return end;}

	auto It1=begin;
	auto It=begin_ex;

	while(begin!=end&&It!=end_ex){
		It1=begin;
		It=begin_ex;
		while(It1!=end&&It!=end_ex&&*It1==*It){
			It++;
			It1++;
		}
		begin++;
	}

	if(begin!=end){begin--;}
	return begin;
}



