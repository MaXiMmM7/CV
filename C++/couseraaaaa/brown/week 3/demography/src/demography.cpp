#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
  {
  }

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

private:
  Iterator first, last;
};

template <typename Collection>
auto Head(Collection& v, size_t top) {
  return IteratorRange{v.begin(), next(v.begin(), min(top, v.size()))};
}

struct Person {
  string name;
  int age, income;
  bool is_male;
};

vector<Person> ReadPeople(istream& input) {
  int count;
  input >> count;

  vector<Person> result(count);
  for (Person& p : result) {
    char gender;
    input >> p.name >> p.age >> p.income >> gender;
    p.is_male = gender == 'M';
  }

  return result;
}

int main() {
  vector<Person> people = ReadPeople(cin);
  string man;
  string woman;

   vector<Person> people_by_age=[&people](){
  sort(begin(people), end(people), [](const Person& lhs, const Person& rhs) {
    return lhs.age < rhs.age;
  });
  return people;
  }();

   vector<Person> people_by_wealthy=[&people](){
  sort(begin(people), end(people), [](const Person& lhs, const Person& rhs) {
    return lhs.income > rhs.income;
  });
  return people;
  }();



  for (string command; cin >> command; ) {
    if (command == "AGE") {
      int adult_age;
      cin >> adult_age;

      auto adult_begin = lower_bound(
        begin(people_by_age), end(people_by_age), adult_age, [](
        		const Person& lhs, int age) {
          return lhs.age < age;
        }
      );

      cout << "There are " << std::distance(adult_begin, end(people_by_age))
           << " adult people for maturity age " << adult_age << '\n';
    }

    ///////////////////////////////////

    else if (command == "WEALTHY") {
      int count;
      cin >> count;

      auto head = Head(people_by_wealthy, count);

      int total_income = accumulate(
        head.begin(), head.end(), 0, [](int cur, Person& p) {
          return cur+=p.income;
        }
      );
      cout << "Top-" << count << " people have total income " << total_income << '\n';

    }

    /////////////////////////////////////////////////////
    else if (command == "POPULAR_NAME") {
      char gender;
      cin >> gender;
     if(gender!='M'&&gender!='W'){
    		 cout << "No people of gender " << gender << '\n';
     }
     else{
    	 if(!man.empty()&&gender=='M'){

    		 cout << "Most popular name among people of gender " << gender << " is "
    		              << man << '\n';
    	 }

    	 else if(!woman.empty()&&gender=='W'){
    	     		 cout << "Most popular name among people of gender " << gender << " is "
    	     		              << woman << '\n';
    	     	 }
    	 else{
      IteratorRange range{
        begin(people),
        partition(begin(people), end(people), [gender](Person& p) {
        	if(gender=='M'){
          return p.is_male == 1;
        	}
        	else {
        		return p.is_male  == 0;
        	}
        })
      };
      if (range.begin() == range.end()) {
        cout << "No people of gender " << gender << '\n';
      } else {
        sort(range.begin(), range.end(), [](const Person& lhs, const Person& rhs) {
          return lhs.name < rhs.name;
        });
        const string* most_popular_name = &range.begin()->name;
        int count = 1;
        for (auto i = range.begin(); i != range.end(); ) {
          auto same_name_end = find_if_not(i, range.end(), [i](const Person& p) {
            return p.name == i->name;
          });
          auto cur_name_count = std::distance(i, same_name_end);
          if (cur_name_count > count) {
            count = cur_name_count;
            most_popular_name = &i->name;
          }
          i = same_name_end;
        }
        cout << "Most popular name among people of gender " << gender << " is "
             << *most_popular_name << '\n';
        if(gender=='M'){man =*most_popular_name ;}
        else{woman = *most_popular_name;}
      }
    	 }
    }
    }
  }
}
