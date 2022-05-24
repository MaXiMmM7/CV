#pragma once
#include <vector>
#include <set>
using namespace std;

void MakeHeap(vector<int>& v,size_t current,size_t last);

void MyHeapSort(vector<int>& v);

void SetSort(vector<int>& v);




void MakeHeap(vector<int>& v,int i,int last){

	int helper;
	int j=2*i+1;

	if(j<last && v[j]<v[j+1]){
		j++;
	}

	while(j<=last&& v[i]<v[j]){

	helper=v[i];
	v[i]=v[j];
	v[j]=helper;
	//v[i].MinusCopy();

	i=j;
	j=2*j+1;
	if(j<last && v[j]<v[j+1]){
			j++;
		}

	}

}

void MyHeapSort(vector<int>& v){

	if(v.size()>1){
		for(int i=(v.size()/2)-1;i>=0;i--){
		MakeHeap(v,i,static_cast<int>(v.size()-1));

	}
	}

	if(!v.empty()){

		int helper;

		for(int i = v.size()-2;i>=0;i--){
			helper=v[0];
			v[0]=v[i+1];
			v[i+1]=helper;
			//v[i+1].MinusCopy();

	MakeHeap(v,0,static_cast<int>(i));
		}
	}
}


void SetSort(vector<int>& v){
set<int> helper;
	for(auto& x: v){
    helper.insert(x);
}
	auto It=v.begin();
	for(auto&x :helper){
		*It++=x;
	}
}

void SetSortSecond(vector<int>& v){
set<int> helper;
	for(auto& x: v){
    helper.insert(x);
}
	auto It=v.begin();
	while(!helper.empty()){
		*It++=*helper.begin();
	     helper.erase(helper.begin());
	}
}



template<typename Iterator>
void OneStepBuble(Iterator begin, Iterator end){

int helper;
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



