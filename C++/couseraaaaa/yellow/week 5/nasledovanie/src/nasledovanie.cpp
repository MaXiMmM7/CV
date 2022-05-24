//============================================================================
// Name        : nasledovanie.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
using namespace std;

class Animal {
public:
    // ваш код
Animal(const string& s): Name(s){}
    const string Name;
};


class Dog:public Animal {
public:
   Dog(const string& s): Animal(s){}
    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
