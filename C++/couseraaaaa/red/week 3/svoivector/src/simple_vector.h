#pragma once

#include <algorithm>
#include <cstdlib>
#include <iostream>

using namespace std;
// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector(){
	  data=nullptr;
	  end_=nullptr;
  }
  explicit SimpleVector(size_t size_){
	  data= new T[size_];
	  end_= data+size_;
	  capacity=size_;
	  size=size_;
  }
  ~SimpleVector(){
	  delete[] data;
  }

  T& operator[](size_t index){
	  return *(data+index);
  }

  T* begin(){return data;}
  T* end(){return end_;}

const  T*  begin() const {return data;}
const T* end() const{return end_;}


  size_t Size() const{
	  return size;
  }
  size_t Capacity() const{
	return capacity;
  }
  void PushBack(const T& value){
	  if(capacity==0){

		  data= new T[1];
		  end_= data+1;
		  capacity++;
		  size++;
		  *data= value;
		  return;
	  }

	  if(size==capacity){

		  T* data_new= new T[2*capacity];
		  copy(data, end_,data_new);
		  delete[] data;
		  data=data_new;
		  end_=data_new+size;
		  capacity*=2;
		  PushBack(value);
		  return;
	  }

	  size++;
	  end_=end_+1;
	  *(end_-1)=value;
  }

private:
T* data;
T* end_;

size_t capacity=0;
size_t size=0;
};
