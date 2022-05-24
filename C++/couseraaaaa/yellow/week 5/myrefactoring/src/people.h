//============================================================================
// Name        : myrefactoring.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>

using namespace std;

class Person{
public:
	Person(const string& name):Name(name){}
	virtual void Walk(const string& destination) const=0;
protected:
	const string Name;
};

class Student:public Person {
public:

    Student(const string& name, const string& favouriteSong):
    	Person(name),FavouriteSong(favouriteSong) {}
    void Learn() const ;
    void Walk(string destination)const  override;
    void SingSong() const;

private:
    string FavouriteSong;
};


class Teacher {
public:
    Teacher(const string& name, const string& subject):
    	Person(name),Subject(subject) {}
    void Teach() const;
    void Walk(string destination)const  override;

private:
    string Subject;
};


class Policeman {
public:
    Policeman(const string& name): Person(name) {}
    void Check(shared_ptr<Person>& person) const;
    void Walk(string destination)const  override;
};


void VisitPlaces(shared_ptr<Person> person, vector<string> places);

