#include "Int.h"

	Int::Int(int x):data(x){}

	Int::Int(const Int& object):data(object.data){
		copy_counter++;
			}

	Int& Int::operator=(const Int& object){
			data=object.data;
			copy_counter++;
			return *this;
		}

	bool Int::operator< (const Int& object){
		less_counter++;
		return data<object.data;
	}

	bool Int::operator<= (const Int& object){
			less_counter++;
			return data<=object.data;
		}

	bool Int::operator> (const Int& object){
		less_counter++;
			return data>object.data;

	}

	uint64_t Int::GetLess() const{
		return less_counter;
	}

	uint64_t Int::GetCopy() const{
		return copy_counter;
	}

	void Int::Zero(){
		copy_counter=0;
		less_counter=0;
	}

bool operator == (const Int& l,const Int& r){
	return l.data==r.data;
}

ostream& operator<< (ostream& stream,const Int& object){
	return stream << object.data;
}


