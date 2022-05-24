#pragma once

#include <stdexcept>
#include <array>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0):size_(a_size){
	  if(size_>capacity_){
		  throw invalid_argument("");}
  }

  T& operator[](size_t index){return vector_[index];}
  const T& operator[](size_t index) const{return vector_[index];}

 auto begin(){return vector_.begin();}
  auto end(){return vector_.begin()+size_;}
  auto begin() const{return vector_.begin();}
  auto end() const{return vector_.begin()+size_;}

  size_t Size() const{return size_;}
  size_t Capacity() const{return capacity_;}

  void PushBack(const T& value){
	if(size_==capacity_){throw overflow_error("");}
	  vector_[size_]=value;
      size_++;
  }
  T PopBack(){
	  if(size_==0){throw underflow_error("");}
	  return vector_[--size_];
  }

private:
 size_t  capacity_=N;
 size_t size_=0;
 array<T,N> vector_;

};

