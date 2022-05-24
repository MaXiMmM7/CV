
//#include "test_runner.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <exception>
#include <sstream>
using namespace std;

template <typename T>
class Deque{
public:
	Deque(){}
	bool Empty() const{
		return pop.empty()&&back.empty();
	}

	size_t Size()const {
		return pop.size()+back.size();
	}

	T& operator[](int index){
		if(index < static_cast<int>(pop.size())){
			return pop[static_cast<int>(pop.size())-index-1];
		}
		return back[index-static_cast<int>(pop.size())];
	}

	const T& operator[](int index) const{
		if(index < static_cast<int>(pop.size())){
					return pop[static_cast<int>(pop.size())-index-1];
				}
				return back[index-static_cast<int>(pop.size())];
	}

	T& At(int index){
		if(index>=static_cast<int>(pop.size()+back.size())){
			ostringstream os;
			os << pop.size()+back.size() << " <= " << index;
			throw out_of_range("hey "+os.str());
		}
		else if(index < static_cast<int>(pop.size())){
							return pop[static_cast<int>(pop.size())-index-1];
						}
						return back[index-static_cast<int>(pop.size())];
	}

	const T& At(int index) const{
			if(index>=static_cast<int>(pop.size()+back.size())){
				ostringstream os;
							os << pop.size()+back.size() << " <= " << index;
							throw out_of_range("hey "+os.str());
			}
			if(index < static_cast<int>(pop.size())){
								return pop[static_cast<int>(pop.size())-index-1];
							}
							return back[index-static_cast<int>(pop.size())];}

	 T& Front() {

		 if(pop.empty()&&back.empty()){throw invalid_argument("soryan");}
		 if(pop.empty()&&!back.empty()){
			 return back.front();
		 }

			return pop.back();

		}

	 const T& Front() const{

		 if(pop.empty()&&back.empty()){throw invalid_argument("soryan");}
		 if(pop.empty()&&!back.empty()){
					 return back.front();
				 }

					return pop.back();

	 	}

	       T& Back() {

	  		 if(pop.empty()&&back.empty()){throw invalid_argument("soryan");}
	    	   if(!pop.empty()&&back.empty()){
	    	  					 return pop.front();
	    	  				 }

	    	  					return back.back();
			}

		 const T& Back() const{
		 if(pop.empty()&&back.empty()){throw invalid_argument("soryan");}
		 if(!pop.empty()&&back.empty()){
				    	  					 return pop.front();
				    	  				 }

				    	  					return back.back();
						}

		 void PushFront(const T& x){
			pop.push_back(x);
		 }

		 void PushBack(const T& x){
			 back.push_back(x);
		 }
private:
	vector<T> pop;
	vector<T> back;
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
/*
void TestAll1(){

		Deque<int> d;
		d.PushBack(3);
		d.PushFront(1);
		ASSERT_EQUAL(d[0],1);
		ASSERT_EQUAL(d[1],3);
		d.PushBack(4);
		d.PushBack(4);
		ASSERT_EQUAL(d[3],4)

		d.PushFront(7);
		ASSERT_EQUAL(d[0],7);
	}

void TestAll2()	{
		Deque<int> d;
				d.PushBack(1);
				d.PushBack(2);
				d.PushBack(3);
				ASSERT_EQUAL(d.Front(),1);
				ASSERT_EQUAL(d.Back(),3);
				ASSERT_EQUAL(d.At(0),1);
				ASSERT_EQUAL(d.At(2),3);
				try{
								    	d.At(-1);
								    }catch(exception& ex){
								    	cerr << ex.what() << "  ohhhhhhhhh"  << endl;
								    }

	}
	void TestAll3(){
			Deque<int> d;
					d.PushFront(1);
					d.PushFront(2);
					d.PushFront(3);
					ASSERT_EQUAL(d.Front(),3);
					ASSERT_EQUAL(d.Back(),1);
					ASSERT_EQUAL(d.At(0),3);
				    ASSERT_EQUAL(d.At(2),1);
				    try{
				    	d.At(-1);
				    }catch(exception& ex){
				    	cerr << ex.what() << "  hmmmmmmmmmmmmm"  << endl;
				    }



		}

*/


int main(){
	/*TestRunner tr;
	RUN_TEST(tr,TestAll1);
	RUN_TEST(tr,TestAll2);
	RUN_TEST(tr,TestAll3);
*/
	return 0;
}
