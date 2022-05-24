#include <iostream>
#include <istream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <memory>
#include <iomanip>
using namespace std;

const double pi=3.14;

class Figure{
public:
	Figure(const string& Name):name(Name){}
	virtual string Name() const=0;
	virtual double Perimeter() const=0;
	virtual double Area() const=0;
	virtual ~Figure()=default;
protected:
	const string name;
};

class Triangle:public Figure{
	public:
	Triangle(const string& Name,const double& A,const double& B,const double& C):
		Figure(Name),a(A),b(B),c(C){}
	string Name() const override{ return name;}
	double Perimeter() const override{ return a+b+c;}
	double Area() const override{
		double p=(a+b+c)/2;
		return sqrt(p*(p-a)*(p-b)*(p-c));
	}
	private:
	const double a;
	const double b;
	const double c;
};

class Rect:public Figure{
	public:
	Rect(const string& Name, const double& A,const double& B):Figure(Name),a(A),b(B){}
	string Name() const override{ return name;}
	double Perimeter() const override{ return 2*(a+b);}
	double Area() const override{ return a*b;}
	private:
	const double a;
	const double b;
};

class Circle:public Figure{
	public:
	Circle(const string& Name,const double& R):Figure(Name),r(R){}
	string Name() const override{ return name;}
	double Perimeter() const override{ return 2*pi*r;}
	double Area() const override{ return pi*r*r;}
	private:
	const double r;
};


shared_ptr<Figure> CreateFigure(istringstream& stream){
	shared_ptr<Figure> result;
	string name;
	stream >> name;
	if(name=="RECT"){
		double a,b;
		stream >> a >> b;
		result = make_shared<Rect>(name,a,b);
		return result;
	}
	else if(name=="TRIANGLE"){
		double a,b,c;
		stream>>a>>b>>c;
		result = make_shared<Triangle>(name,a,b,c);
		return result;
	}
	double r;
	stream >> r;
	result=make_shared<Circle>(name,r);
	return result;
}
/*
Triangle, Rect и Circle
ADD RECT 2 3
ADD TRIANGLE 3 4 5
ADD RECT 10 20
ADD CIRCLE 5
PRINT
входного потока создаёт shared_ptr<Rect>, shared_ptr<Triangle> или shared_ptr<Circle>.
*/
int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      // Пропускаем "лишние" ведущие пробелы.
      // Подробнее об std::ws можно узнать здесь:
      // https://en.cppreference.com/w/cpp/io/manip/ws
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
