#pragma once

//#include "test_runner.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <exception>
using namespace std;

template <typename T>
class Deque{
	Deque(){}
	bool Empty() const{
		return pop.empty();
	}

	size_t Size()const {
		return pop.size();
	}

	T& operator[](size_t index){
		return pop[index];
	}

	const T& operator[](size_t index) const{
		return pop[index];
	}

	T& At(size_t index){
		if(index>=pop.size()){
			throw out_of_range("hey");
		}
		return pop[index];
	}

	const T& At(size_t index) const{
			if(index>=pop.size()){
				throw out_of_range("hey");
			}
			return pop[index];
		}

	 T& Front() {
			return *begin(pop);
		}

	 const T& Front() const{
	 		return *end(pop);
	 	}

	 T& Back() {
				return *begin(pop);
			}

		 const T& Back() const{
		 		return *end(pop);
		 	}

		 void PushFront(const T& x){
			 pop.insert(begin(pop),x);
			 push.insert(begin(push),x);
		 }

		 void PushBack(const T& x){
			 pop.push_back(x);
			 push.push_back(x);
		 }
private:
	vector<T> pop;
	vector<T> push;
};
/*
 *    + конструктор по умолчанию;
    +константный метод Empty, возвращающий true, если дек не содержит ни одного элемента;
   + константный метод Size, возвращающий количество элементов в деке;
    +T& operator[](size_t index) и const T& operator[](size_t index) const;
   + константный и неконстантный метод At(size_t index), генерирующий
     стандартное исключение out_of_range, если индекс больше или равен количеству
      элементов в деке;
    константные и неконстантные версии методов Front и Back, возвращающих ссылки
    на первый и последний элемент дека соответственно;
    методы PushFront и PushBack.
 */
