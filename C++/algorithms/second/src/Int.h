#pragma once

#include <iostream>

using namespace std;



class Int{
public:
	int data;

	Int(int x=0);

	Int(const Int& object);

	Int& operator=(const Int& object);

	bool operator< (const Int& object);

	bool operator<= (const Int& object);

	bool operator> (const Int& object);

	uint64_t GetLess() const;

	uint64_t GetCopy() const;

	void Zero();
private:
	uint64_t less_counter=0;
	uint64_t copy_counter=0;
};

bool operator == (const Int& l,const Int& r);

ostream& operator<< (ostream& stream,const Int& object);
