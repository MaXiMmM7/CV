#pragma once
#include <iterator>
#include "Int.h"
using namespace std;


template<typename Iterator,typename T>
Iterator my_brute_force(Iterator begin, Iterator end, T object);

template<typename Iterator,typename T>
Iterator my_lower_bound_Int(Iterator begin, Iterator end, T object);

template<typename Iterator>
void my_buble_Int(Iterator begin, Iterator end);

template<typename Iterator>
void my_insert_brute_Int(Iterator begin, Iterator end);

template<typename Iterator>
void my_insert_binary_Int(Iterator begin, Iterator end);




/*
template<typename Iterator,typename T>
Iterator my_brute_force(Iterator begin, Iterator end, T object){

	while(begin!=end&&*begin<object){
		begin++;
	}
	return begin;
}
*/

template<typename Iterator,typename T>
Iterator my_brute_force(Iterator begin, Iterator end, T object){//aka upper bound

	if(end!=begin){end=prev(end);}
		else {return begin;}
	while(prev(begin)!=end&&*end>object){
		end--;
	}
	end++;
	return end;
}
/*
template<typename Iterator,typename T>
Iterator my_brute_force(Iterator begin, Iterator end, T object){//from end

	if(end!=begin){end=prev(end);}
	else {return begin;}
	//end=prev(end);
	while(end!=prev(begin)&&*end>=object){
		end--;
	}
	return begin;
}*/


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


template<typename Iterator>
void onestep_my_buble_Int(Iterator begin, Iterator end){

Int helper;
Iterator It1=begin;
Iterator It2=next(begin);
if(begin<end){
		while(It2!=end){
			if(*It2<*It1){
				helper=*It1;
				*It1=*It2;
				*It2=helper;
			}
			It1++;
			It2++;
		}
	}
}
