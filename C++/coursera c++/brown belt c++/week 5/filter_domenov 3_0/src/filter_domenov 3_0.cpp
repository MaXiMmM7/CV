#include <iostream>
#include <list>
#include <string>
#include <string_view>
#include <vector>
#include "test_runner.h"
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <utility>
using namespace std;




class Unit{
public:

	void InsertNewDomain(string string_){

		string_view s(string_);
		string helper;
		Unit* unit_ptr=this;
		while(true){
			size_t point=s.rfind(".");
			helper=static_cast<string>(s.substr(point+1));
			auto It=unit_ptr->Get().find(helper);  //->find(helper);
			if(It==unit_ptr->Get().end()){
				if(point==s.npos){
					unit_ptr->Get()[helper]=nullptr;
					break;
				}
				unit_ptr->Get()[helper]=make_unique<Unit>();
			}
			else{
				if(point==s.npos){
					It->second=nullptr;
				}
				if(It->second==nullptr){
					break;
				}

			}
			unit_ptr=unit_ptr->Get()[helper].get();
			s.remove_suffix(s.size()-point);
		}
	}


	bool IsThisDomainBad(const string& string_){
		string_view s(string_);
		string helper;
		Unit* unit_ptr=this;
		while(true){
			size_t point=s.rfind(".");
			helper=static_cast<string>(s.substr(point+1));
			auto It=unit_ptr->Get().find(helper);
			if(It==unit_ptr->Get().end()){
				return false;
			}
			unit_ptr=unit_ptr->Get()[helper].get();
			if(unit_ptr==nullptr){
				return true;
			}
			if(point!=s.npos){
				s.remove_suffix(s.size()-point);
			}
			else{
				break;
			}
		}
		return false;
	}

	unordered_map<string,unique_ptr<Unit>>& Get() {
		return unit;
	}
	const unordered_map<string,unique_ptr<Unit>>& Get() const{
			return unit;
		}
private:
	unordered_map<string,unique_ptr<Unit>> unit;

};


vector<string> Process(istream& input){
	vector<string> result;
	Unit root;
	int count;
	input >> count;
	string helper;
	for(int i =0;i < count;i++){
		input >> helper;
		root.InsertNewDomain(move(helper));
	}

	input >> count;
	for(int i =0;i < count;i++){
		input >> helper;
		if(root.IsThisDomainBad(helper)){
			result.push_back("Bad");

		}
		else{
			result.push_back("Good");
		}
	}
	return result;
}


void Test_Process(){
	{
		istringstream s("4\nya.ru\nmaps.me\nm.ya.ru\ncom\n7\nya.ru\nya.com\nm.maps.me\nmoscow.m.ya.ru\nmaps.com\nmaps.ru\nya.ya");
		vector<string> check({"Bad","Bad","Bad","Bad","Bad","Good","Good"});
		ASSERT_EQUAL(Process(s),check);
	}
	{
		istringstream s("10\ncat\ndog\nfrog\nbird\nwild.horse\nyour.man.boss\ncat.cat\nfrog.cat.cat\ncrocodile.dog\na.b.c.frog\n"
				"33\ncat\ndog\nfrog\nbird\nwild.horse\nyour.man.boss\ncat.cat\nfrog.cat.cat\ncrocodile.dog\na.b.c.frog\n"
				"dog.cat\ncat.dog\na.a.b.c.frog\nhave.frog.cat.cat\nman.boss.bird\n"
				"cat.man.boss\nwind.horse\na.b.c.frog.a\nhey\nbro.hey\ngermany\n"
				"cat.com\ndog.com\nfrog.com\nbird.com\nwild.horse.com\nyour.man.boss.com\n"
				"cat.cat.com\nfrog.cat.cat.com\ncrocodile.dog.com\na.b.c.frog.com\nyour.man.     boss   \n");
		vector<string> check({"Bad","Bad","Bad","Bad","Bad","Bad","Bad","Bad","Bad","Bad","Bad","Bad","Bad","Bad","Bad",
			"Good","Good","Good","Good","Good","Good","Good","Good","Good","Good","Good","Good","Good","Good","Good","Good",
			"Good","Good"});
		ASSERT_EQUAL(Process(s),check);
	}
	{
		istringstream s("3\ncom\nya.ru.com\nabc.def\n4\nru.com\ncom\ncom.ru\nutabc.def");
		vector<string> check={"Bad","Bad","Good","Good"};
		ASSERT_EQUAL(Process(s),check);
	}
	{
		istringstream s("0\n4\nru.com\ncom\ncom.ru\nutabc.def");
		vector<string> check={"Good","Good","Good","Good"};
		ASSERT_EQUAL(Process(s),check);
	}
	{
		istringstream s("1\nru\n7\nru\nbot.ru\nru.ru\ncom.ru.ru\nru.com.ru\nru.com\nru.com.com");
		vector<string> check={"Bad","Bad","Bad","Bad","Bad","Good","Good"};
		ASSERT_EQUAL(Process(s),check);
	}
	{
		istringstream s("3\na.ru\nb.ru\nc.ru\n10\nru\nbot.ru\nru.ru\ncom.ru.ru\nru.com.ru\nru.com\nru.com.com\na.ru\nb.ru\nc.ru");
		vector<string> check={"Good","Good","Good","Good","Good","Good","Good","Bad","Bad","Bad"};
		ASSERT_EQUAL(Process(s),check);
		}
}


int main() {

	TestRunner tr;
    RUN_TEST(tr, Test_Process);

    for(const auto& s: Process(cin)){
    	cout << s << "\n";
    }

	return 0;
}


/*
 * class Unit{
public:
		void InsertNewDomain(string string_){

		string_view s(string_);
		string helper;
		Unit* unit_ptr=this;
		while(true){
			size_t point=s.rfind(".");
			helper=static_cast<string>(s.substr(point+1));
			auto It=unit_ptr->Get().find(helper);  //->find(helper);
			if(It==unit_ptr->Get().end()){
				if(point==s.npos){
					unit_ptr->Get()[helper]=nullptr;
					break;
				}
			    unit_ptr->Get()[helper]=make_unique<Unit>();
			}
			else{
				if(point==s.npos){
					break;
				}
				if (It->second==nullptr){
					unit_ptr->Get()[helper]=make_unique<Unit>();
					unit_ptr->Get()[helper]->Get()["Okey special case"]=nullptr;//!!!!!!!!!!!!!!!!!!!!!
				}

			}

			unit_ptr=unit_ptr->Get()[helper].get();
			s.remove_suffix(s.size()-point);
		}
	}


	bool IsThisDomainBad(const string& string_){
		string_view s(string_);
		string helper;
		Unit* unit_ptr=this;
		while(true){
			size_t point=s.rfind(".");
			helper=static_cast<string>(s.substr(point+1));
			auto It=unit_ptr->Get().find(helper);  //->find(helper);
			if(unit_ptr->Get().find("Okey special case")!=unit_ptr->Get().end()){
				return true;
			}
			if(It==unit_ptr->Get().end()){
				return false;
			}
			else{
				if(point==s.npos){
					if(It->second==nullptr||(It->second->Get().find("Okey special case")!=It->second->Get().end())){
						return true;
					}
					break;
				}
			}


			unit_ptr=unit_ptr->Get()[helper].get();
			if(unit_ptr==nullptr){
				return true;
			}
			s.remove_suffix(s.size()-point);
		}
		return false;
	}

	unordered_map<string,unique_ptr<Unit>>& Get() {
		return unit;
	}
	const unordered_map<string,unique_ptr<Unit>>& Get() const{
			return unit;
		}
private:
	unordered_map<string,unique_ptr<Unit>> unit;
	};
	*/








/*
void Test_BadDomains(){
	{
		Unit root;
		string s("cat");
		root.InsertNewDomain(s);
		ASSERT_EQUAL((root.Get().find("cat")!=root.Get().end()),true);
		ASSERT_EQUAL((root.Get().find("cat")->second==nullptr),true);
		ASSERT_EQUAL((static_cast<int>(root.Get().size())==1),true);


		root.InsertNewDomain("dog");
		ASSERT_EQUAL((root.Get().find("cat")!=root.Get().end()),true);
		ASSERT_EQUAL((root.Get().find("cat")->second==nullptr),true);
		ASSERT_EQUAL((root.Get().find("dog")!=root.Get().end()),true);
		ASSERT_EQUAL((root.Get().find("dog")->second==nullptr),true);
		ASSERT_EQUAL((static_cast<int>(root.Get().size())==2),true);


		root.InsertNewDomain("cat.dog");
		//
		//cout << root.Get().find("dog")->second.get()->Get().find("cat")->first << endl;
		//
		ASSERT_EQUAL((root.Get().find("cat")!=root.Get().end()),true);
		ASSERT_EQUAL((root.Get().find("cat")->second==nullptr),true);
		ASSERT_EQUAL((root.Get().find("dog")!=root.Get().end()),true);
		ASSERT_EQUAL((root.Get().find("dog")->second!=nullptr),true);
		ASSERT_EQUAL((static_cast<int>(root.Get().size())==2),true);
		ASSERT_EQUAL((root.Get().find("dog")->second.get()->Get().find("cat")!=
				      root.Get().find("dog")->second.get()->Get().end()),true);
		ASSERT_EQUAL((root.Get().find("dog")->second.get()->Get().find("cat")->second==
						      nullptr),true);
		ASSERT_EQUAL((root.Get().find("dog")->second.get()->Get().size()==
								      2),true);
		//ASSERT_EQUAL((root.Get().find("dog")->second.get()->Get().find(" ")->second==
			//			      nullptr),true);

		//
		//cout << "\n\n\n next part \n\n\n"  << endl;
		//
		ASSERT_EQUAL(root.IsThisDomainBad("cat"),true);
		ASSERT_EQUAL(root.IsThisDomainBad("bad.cat"),true);
		ASSERT_EQUAL(root.IsThisDomainBad("dog.cat"),true);
		ASSERT_EQUAL(root.IsThisDomainBad("cat.dog"),true);
		ASSERT_EQUAL(root.IsThisDomainBad("cat.dog.cat"),true);
		ASSERT_EQUAL(root.IsThisDomainBad("dog.cat.dog"),true);
		ASSERT_EQUAL(root.IsThisDomainBad("mail.cat"),true);
		ASSERT_EQUAL(root.IsThisDomainBad("mail.ru"),false);
		ASSERT_EQUAL(root.IsThisDomainBad("mail.cat.ru"),false);


	//	for(auto k:book){
		//	cout << k.first << endl;
		//}
		//ASSERT_EQUAL(static_cast<int>(book.size()),1);
	//	ASSERT_EQUAL((book.find[string("cat")]!=book.end()),true);
	}
}
*/






