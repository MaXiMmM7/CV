#include <iostream>
#include <list>
#include <string>
#include <string_view>
#include <vector>
#include <utility>
#include "test_runner.h"
#include <sstream>
#include <future>
#include "profile.h"
using namespace std;



vector<string> GetVectorOfWordsFromDomainName(const string& data){

	vector<string> result;
	string_view s=data;
	while(true){
		size_t point = s.rfind(".");

		result.push_back(static_cast<string>(s.substr(point+1)));

		if(point==s.npos){
			break;
		}
		else{
			s.remove_suffix(s.size()-point);
		}
	}
	return result;
}



class AllBadDomains{
private:
	using Domain=vector<string>;
	vector<Domain> bad_domains;

public:
	void AddNewDomain(const string& s){
		bad_domains.push_back(GetVectorOfWordsFromDomainName(s));
	}
	bool IsThisDomainBad(const string& word) const{
		vector<string> adress = GetVectorOfWordsFromDomainName(word);
		list<size_t> domains_to_check;
		for(size_t i=0;i<bad_domains.size();i++){
			if(bad_domains[i][0]==adress[0]){

				if(bad_domains[i].size()==1){
					return true;
				}
				domains_to_check.push_back(i);
			}
		}

		if(adress.size()>1){
			return RecursiveCheck(domains_to_check,adress,static_cast<size_t>(1));
		}
		else{
			return false;
		}
	}

	const vector<Domain>& Get() const{
		return bad_domains;
	}
private:
	bool RecursiveCheck(list<size_t> & dmns_nums,const vector<string>& adress,size_t pos) const{
		auto It=dmns_nums.begin();
		while(It!=dmns_nums.end()){
			if(bad_domains[*It][pos]!=adress[pos]){
				It=dmns_nums.erase(It);
				continue;
			}
			if(bad_domains[*It].size()==(pos+1)){
				return true;
			}
			It++;
		}
		if((pos+1)==adress.size()){
			return false;
		}
		return RecursiveCheck(dmns_nums,adress,pos+1);
	}
};

string IsThisWordBadInThisDatabase(const AllBadDomains& dmns,const string& word){
	if(dmns.IsThisDomainBad(word)){
		return "Bad";
	}
	return "Good";
}

AllBadDomains CreateABase(istream& input){
	size_t bad_count;
	input >> bad_count;
	AllBadDomains result;
	string helper;
	for(size_t i=0;i<bad_count;i++){
		input >> helper;
		result.AddNewDomain(helper);
	}
	return result;
}

vector<string> AreTheseDomainsBad(istream& input,const AllBadDomains& db){
	size_t count;
	input >> count;
	vector<string> result;
	string helper;
	for(size_t i=0;i<count;i++){
		input >> helper;
		result.push_back(IsThisWordBadInThisDatabase(db,helper));
	}
	return result;
}



void Test_GetVectorOfWordsFromDomainName() {
	{
		string str="yandex.ru";
		vector<string> v_f=GetVectorOfWordsFromDomainName(str);
		vector<string> v_r={"ru","yandex"};
		ASSERT_EQUAL(v_f, v_r);
		ASSERT_EQUAL(static_cast<int>(v_f.size()),2);

	}
	{
		string str="ru";
		vector<string> v_f=GetVectorOfWordsFromDomainName(str);
		vector<string> v_r={"ru"};
		ASSERT_EQUAL(v_f, v_r);
		ASSERT_EQUAL(static_cast<int>(v_f.size()),1);
	}
}


void Test_AddNewDomain() {
	{
		AllBadDomains database;
		database.AddNewDomain("yandex.ru");
		database.AddNewDomain("mail.ru");
		database.AddNewDomain("physics.msu.ru");

		vector<vector<string>> check={{"ru","yandex"},
		{"ru","mail"},{"ru","msu","physics"}};

		ASSERT_EQUAL(database.Get(), check);
		ASSERT_EQUAL(static_cast<int>(database.Get().size()),3);
	}
}

void Test_IsThisDomainBad(){
	{
		AllBadDomains database;
		database.AddNewDomain("yandex.ru");
		database.AddNewDomain("mail.ru");
		database.AddNewDomain("physics.msu.ru");
		database.AddNewDomain("oh");

		vector<vector<string>> check={{"ru","yandex"},
		{"ru","mail"},{"ru","msu","physics"},{"oh"}};

		ASSERT_EQUAL(database.Get(), check);
		ASSERT_EQUAL(static_cast<int>(database.Get().size()),4);

		ASSERT_EQUAL(database.IsThisDomainBad("ru"),false);
		ASSERT_EQUAL(database.IsThisDomainBad("yandex.ru"),true);
		ASSERT_EQUAL(database.IsThisDomainBad("mail.com"),false);
		ASSERT_EQUAL(database.IsThisDomainBad("physics.msu.com"),false);
		ASSERT_EQUAL(database.IsThisDomainBad("hello.oh"),true);
		ASSERT_EQUAL(database.IsThisDomainBad("physics.msu.ru"),true);
	}
}

void Test_CreateABase(){
	{
		istringstream stream("3\nru\nyandex.ru\nmail.com");
		AllBadDomains database=CreateABase(stream);
		const vector<vector<string>> check({{"ru"},{"ru","yandex"},{"com","mail"}});

		ASSERT_EQUAL(database.Get(),check);

	}
}

void Test_CreateBadDomains_and_CheckAreDomainsBad(){
	{
		istringstream stream("3\nru\nyandex.ru\nmail.com\n5\nyandex.ru\nman.ru\ncat.com\ndog.fm\ncom");
		AllBadDomains bd=CreateABase(stream);
		vector<string> results=AreTheseDomainsBad(stream,bd);
		vector<string> check({"Bad","Bad","Good","Good","Good"});

		ASSERT_EQUAL(results,check);
	}
}

/*
void Test_ManyTries(){
	{
		string s;
		s+="ru";
		for(size_t i=1; i<20;i++){
			s+=".ru";
		}

		stringstream stream;
		stream << 10000 << "\n";
		for(size_t i=0; i<10000;i++){
			stream << s << "\n";
		}
		stream << 10000 << "\n";
		for(size_t i=0; i<10000;i++){
			stream << s << "\n";
		}

		vector<string> check;
		for(size_t i=0; i<10000;i++){
			check.push_back("Good");
		}
		vector<string> results;
		{
			LOG_DURATION("MANY TRIES");
			AllBadDomains bd=CreateABase(stream);
			results=AreTheseDomainsBad(stream,bd);
			//ASSERT_EQUAL(results,right);
		}
		ASSERT_EQUAL(results,check);

	}
}
*/
int main() {
	TestRunner tr;
	RUN_TEST(tr, Test_GetVectorOfWordsFromDomainName);
	RUN_TEST(tr, Test_AddNewDomain);
	RUN_TEST(tr, Test_IsThisDomainBad);
	RUN_TEST(tr, Test_CreateABase);
	RUN_TEST(tr, Test_CreateBadDomains_and_CheckAreDomainsBad);
	//RUN_TEST(tr, Test_ManyTries);


	/*
	istringstream stream;
	cin>>stream;*/
	AllBadDomains db=CreateABase(cin);
	vector<string> result = AreTheseDomainsBad(cin,db);
	for(auto i: result){
		cout <<i << "\n";
	}

	return 0;
}
