#pragma once
#include <algorithm>
#include <vector>
#include <set>
using namespace std;


void CountSort(vector<int>& v,vector<int>& y);

void LSDSort (vector<int>& v, int m,int k);




void CountSort(vector<int>& v,vector<int>& y){//
	if(v.empty()){
		return;
	}

	vector<int> t(*max_element(v.begin(),v.end())+1,0);//just natural

	for(auto& x: v){
		t[x]++;//just natural
	}

	for(int i=static_cast<int>(t.size())-2;i>=0;i--){
		t[i]+=t[i+1];
	}


	y.resize(v.size());

	for(int i=0;i<static_cast<int>(v.size());i++){

		y[v.size()-t[v[i]]]=v[i];
		t[v[i]]--;

	}


}

void LSDSort (vector<int>& v, vector<int>& result, int m,int k){//m=10 in 10-scale; k - number of digits

if(v.empty()){
	return;
}

vector<vector<int>> boxes(m);

for(int i=0;i<static_cast<int>(v.size());i++){
boxes[v[i]%10].push_back(i);
}

vector<int> BOX(v.size());

//auto It=BOX.begin();

/*for(auto& box:boxes){
	for(auto& x: box){
		*It++=x;
	}
	box.clear();
}*/
int R=0;
for(int i=0; i<m;i++){
	for(int j=0;j<static_cast<int>(boxes[i].size());j++){
		BOX[R++]=boxes[i][j];
	}
	boxes[i].clear();
}


if(k>1){
   int denumenator=1;
	for(int r=1;r<k;r++){
	denumenator*=10;
	for(int i=0;i<static_cast<int>(BOX.size());i++){
	boxes[v[BOX[i]]/(denumenator)%10].push_back(BOX[i]);
	}

	//It=BOX.begin();

/*	for(auto& box:boxes){
		for(auto& x: box){
			*It++=x;
		}
		box.clear();
	}
	*/
	R=0;
	for(int i=0; i<m;i++){
		for(int j=0;j<static_cast<int>(boxes[i].size());j++){
			BOX[R++]=boxes[i][j];
		}
		boxes[i].clear();
	}

	}
}

//vector<int> result;

result.resize(BOX.size());

/*for(auto& j: BOX){
	result.push_back(v[j]);
}*/
for(int j=0; j<static_cast<int>(BOX.size());j++){
	result[j]=v[BOX[j]];
}


//v=result;

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
