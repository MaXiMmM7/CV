
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct PersonType{
	PersonType(const string& type,const string& name):Type(type),Name(name){}
    string DoSomething()const{return Type + ": " + Name; }
	const string Type;
	const string Name;
};

class Person{
public:
	Person(const string& name, const string& type):IndividualPerson(type,name){}
	virtual void Walk(const string& destination) const{
			cout << IndividualPerson.DoSomething()<< " walks to: " << destination << endl;
	};
	string GetName()const {return IndividualPerson.Name;}
	string GetType()const {return IndividualPerson.Type;}
protected:
	const PersonType IndividualPerson;
};

class Student:public Person {
public:

    Student(const string& name, const string& favouriteSong):
    	Person(name,"Student"),FavouriteSong(favouriteSong) {}

    void Learn() const {
        cout << IndividualPerson.DoSomething() << " learns" << endl;
    }

    void Walk(const string& destination)const  override{
        cout << IndividualPerson.DoSomething() << " walks to: " << destination << endl;
        cout << IndividualPerson.DoSomething()<< " sings a song: " << FavouriteSong << endl;
    }

    void SingSong() const{
        cout <<IndividualPerson.DoSomething()<< " sings a song: " << FavouriteSong << endl;
    }

private:
    const string FavouriteSong;
};


class Teacher:public Person {
public:

    Teacher(const string& name, const string& subject):
    	Person(name, "Teacher"),Subject(subject) {}

    void Teach() const{
        cout << IndividualPerson.DoSomething() << " teaches: " << Subject << endl;
    }

private:
    const string Subject;
};


class Policeman:public Person {
public:
    Policeman(const string& name): Person(name, "Policman") {}

    void Check(const Person& person) const{
            cout << IndividualPerson.DoSomething() << " checks " << person.GetType()
            		<<". " << person.GetType() << "'s name is: "
            		<< person.GetName() << endl;
        }

};


void VisitPlaces(const Person& person, const vector<string>& places) {
    for (auto place : places) {
        person.Walk(place);
    }
}




int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
