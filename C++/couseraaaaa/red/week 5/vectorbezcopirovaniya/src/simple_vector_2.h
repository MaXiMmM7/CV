#pragma once

#include <algorithm>
#include <utility>
using namespace std;

template <typename T>
class SimpleVector {
public:
  SimpleVector() = default;
  explicit SimpleVector(size_t size);
  ~SimpleVector();

  T& operator[](size_t index);

  T* begin();
  T* end();

  size_t Size() const;
  size_t Capacity() const;
  void PushBack( T value);
  void PushBack( T&& value);

  SimpleVector(const SimpleVector& other) = delete;

 // SimpleVector<T>& operator=(SimpleVector<T>&& other) = delete;

  const T* begin() const {
      return data ;
    }

  const T* end() const {
      return data + size;
    }

   SimpleVector(SimpleVector&& other);
   void operator=(SimpleVector&& other);
private:
  T* data = nullptr;
  size_t size = 0;
  size_t capacity = 0;
};

template <typename T>
SimpleVector<T>::SimpleVector(size_t size)
  : data(new T[size])
  , size(size)
  , capacity(size)
{
}

template <typename T>
SimpleVector<T>::~SimpleVector() {
  delete[] data;
}

template <typename T>
T& SimpleVector<T>::operator[](size_t index) {
  return data[index];
}

template <typename T>
size_t SimpleVector<T>::Size() const {
  return size;
}

template <typename T>
size_t SimpleVector<T>::Capacity() const {
  return capacity;
}


template <typename T>
void SimpleVector<T>::PushBack(T value) {
  if (size >= capacity) {
    auto new_cap = capacity == 0 ? 1 : 2 * capacity;
    auto new_data = new T[new_cap];
    move(begin(), end(), new_data);
    delete[] data;
    data = new_data;
    capacity = new_cap;
  }
  data[size++] = move(value);
}


template <typename T>
void SimpleVector<T>::PushBack(T&& value) {
  if (size >= capacity) {
    auto new_cap = capacity == 0 ? 1 : 2 * capacity;
    auto new_data = new T[new_cap];
    move(begin(), end(), new_data);
    delete[] data;
    data = new_data;
    capacity = new_cap;
  }
  data[size++] = move(value);
}

template <typename T>
T* SimpleVector<T>::begin() {
  return data;
}

template <typename T>
T* SimpleVector<T>::end() {
  return data + size;
}

/*
template <typename T>
SimpleVector<T>& SimpleVector<T>::operator=(SimpleVector<T>&& other){
data=other.data;
size=other.size;
capacity=other.capacity;
	other.data==nullptr;
	other.size = other.capacity = 0;

	return *this;
}*/

template <typename T>
SimpleVector<T>::SimpleVector(SimpleVector<T>&& other):
data(other.data),size(other.size),capacity(other.capacity){
	other.data==nullptr;
	other.size = other.capacity = 0;
}

template <typename T>
void SimpleVector<T>::operator =(SimpleVector<T>&& other){
	delete[] data;
	data=other.data;
	size=other.size;
	capacity=other.capacity;

	other.data=nullptr;
	other.capacity = other.size =0;
}
