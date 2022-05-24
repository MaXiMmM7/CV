#include <iostream>
#include <list>
#include <string>
#include <string_view>
#include <vector>
#include <utility>
#include "test_runner.h"
#include <sstream>
#include <set>
#include <algorithm>
using namespace std;




bool IsThisAdressBad(string_view bad_domain, string_view adress){
	while(true){
		size_t point_bad=bad_domain.find(".");
		size_t point=adress.find(".");

		//

		//cout <<bad_domain.substr(0,point_bad) << "  " << adress.substr(0,point) << endl;
		//
		if( bad_domain.substr(0,point_bad)!=adress.substr(0,point)){
			//
			//cout << "we in this case" << endl;
			//cout << point_bad<< " "<< point << endl;
			//
			return false;
		}

		if(point_bad==bad_domain.npos){
			//
			//cout << "Bad"  << endl;
			//
			return true;
		}
		if(point!=adress.npos){
			//
		//	cout << "We are Here" << endl;
			//
			adress.remove_prefix(point+1);
			bad_domain.remove_prefix(point_bad+1);
			//
		//	cout << bad_domain << "  " << adress <<  endl;
			//
		}
		else{
			//
			//cout << "We gonna break" << endl;
			//
			break;
		}
	}
	return false;
}

class AllBadDomains{
private:
	set<string> bad_domains;

public:
	void AddNewDomain(string s){
		reverse(s.begin(),s.end());
		bad_domains.insert(move(s));
	}
	bool IsThisDomainBad(string word) const{
			reverse(word.begin(),word.end());

			//
			//cout << to_string(char(word[0])) << "  " << to_string(char(word[0]+1)) << endl;
			//cout << string(1,word[0]) << "  " << string(1,char(word[0]+1)) << endl;
			//cout << *bad_domains.lower_bound(to_string(word[0])) << " "  << *bad_domains.lower_bound(to_string(word[0]+1)) << endl;
			//
			for(auto It=bad_domains.lower_bound(string(1,word[0]));
					It!=bad_domains.lower_bound(string(1,char(word[0]+1))); It++){
				//
				//cout << *It << endl;
				//
				if(IsThisAdressBad(*It,word)){
					return true;
				}
			}

			return false;
	}

	const set<string>& Get() const{
		return bad_domains;
	}
};


AllBadDomains CreateADatabase(istream& stream){
	int bad_count;
	stream>> bad_count;
	AllBadDomains bd;
	string helper;
	for(int i =0; i < bad_count; i++){
		stream >> helper;
		bd.AddNewDomain(move(helper));
	}

	return bd;


}

/*vector<string>*/void CheckAreTheseAdressesBadandWrite(istream& stream,const AllBadDomains& bd){
	//vector<string> result;
	int count;
	stream >> count;
	string helper;
	for(int i = 0; i < count; i++){
		stream >> helper;
		if(bd.IsThisDomainBad(helper)){
			cout << "Bad\n";
			//result.push_back("Bad");
		}
		else{
			cout << "Good\n";
			//result.push_back("Good");
		}
	}
	//return result;
}

void Test_CreateADatabase(){
	{
		istringstream stream("3\nru\nmail.ru\nhello.boy\n");
		AllBadDomains bd=CreateADatabase(stream);
		set<string> check{"ur","ur.liam","yob.olleh"};
		ASSERT_EQUAL(bd.Get(),check);
	}
}

void Test_IsThisAdressBad(){
	{
		ASSERT_EQUAL(IsThisAdressBad("ur","ur.xednay"),true);
		ASSERT_EQUAL(IsThisAdressBad("ur.xednay","ur"),false);
		ASSERT_EQUAL(IsThisAdressBad("com.shiit.com","com.shiit"),false);
		ASSERT_EQUAL(IsThisAdressBad("ru.ru","ru.com"),false);
		ASSERT_EQUAL(IsThisAdressBad("ru","ru.ru.ru"),true);
	}
}

/*void Test_CheckAreTheseAdressesBadandWrite(){
	{
		istringstream stream("3\nru\nmail.ru\nhello.boy\n");
		AllBadDomains bd=CreateADatabase(stream);
		set<string> check{"ur","ur.liam","yob.olleh"};
		ASSERT_EQUAL(bd.Get(),check);

		istringstream stream_2("5\nru\nmail.ru\nhello.boy\ncat.ru\nboy.hello");
		vector<string> check_2({"Bad","Bad","Bad","Bad","Good"});
		ASSERT_EQUAL(CheckAreTheseAdressesBadandWrite(stream_2, bd),check_2);
	}
}
*/

int main() {
	//char a='a';
	//char b=a+1;
	//cout << b << endl;

	TestRunner tr;
	RUN_TEST(tr, Test_CreateADatabase);
	RUN_TEST(tr, Test_IsThisAdressBad);
//	RUN_TEST(tr, Test_CheckAreTheseAdressesBadandWrite);

/*	AllBadDomains bd=CreateADatabase(cin);
	for(auto s:CheckAreTheseAdressesBadandWrite(cin,bd)){
		cout << s << "\n";
	}
	*/

	AllBadDomains bd=CreateADatabase(cin);
	CheckAreTheseAdressesBadandWrite(cin,bd);
	/*RUN_TEST(tr, Test_AddNewDomain);
	RUN_TEST(tr, Test_IsThisDomainBad);
	RUN_TEST(tr, Test_CreateABase);
	RUN_TEST(tr, Test_CreateBadDomains_and_CheckAreDomainsBad);
	//RUN_TEST(tr, Test_ManyTries);



	istringstream stream;
	cin>>stream;*/

	return 0;
}
