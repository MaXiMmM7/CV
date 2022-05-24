#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
public:
    virtual void Walk(const string& destination) const = 0;

    string GetName() const {
        return name;
    }
    string GetOccupation() const {
        return occupation;
    }

protected:
    Human(const string& _name, const string& _occupation) : name(_name), occupation(_occupation) {}

    void WalkFirstPart(const string& destination) const {
        cout << occupation << ": " << name << " walks to: " << destination << endl;
    }

    const string name;
    const string occupation;
};


class Student: public Human {
public:

    Student(const string& name, const string& favouriteSong) : Human(name, "Student"), favouriteSong(favouriteSong) {}

    void Learn() const{
        cout << occupation << ": " << name << " learns" << endl;
    }

    void Walk(const string& destination)const override {
        WalkFirstPart(destination);
        SingSong();
    }

    void SingSong() const{
        cout << occupation << ": " << name << " sings a song: " << favouriteSong << endl;
    }

private:
    const string favouriteSong;
};


class Teacher : public Human {
public:

    Teacher(const string& name, const string& subject) : Human(name, "Teacher"), subject(subject) {}

    void Teach() {
        cout << occupation << ": " << name << " teaches: " << subject << endl;
    }

    void Walk(const string& destination) const override {
        WalkFirstPart(destination);
    }

private:
    const string subject;
};


class Policeman: public Human {
public:
    Policeman(const string& name) : Human(name, "Policeman") {}

    void Check(Human& h) const {
        cout << occupation << ": " << name << " checks " << h.GetOccupation() << ". " << h.GetOccupation() << "'s name is: " << h.GetName() << endl;
    }

    void Walk(const string& destination) const override{
        WalkFirstPart(destination);
    }
};



void VisitPlaces(Human& h, const vector<string>& places) {
    for (auto& p : places) {
        h.Walk(p);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, { "Moscow", "London" });
    p.Check(s);
    VisitPlaces(s, { "Moscow", "London" });
    return 0;
}
