
#include <iostream>
#include "lists.h"
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include <cassert>
#include <algorithm>
#include <iomanip>
using namespace std;

template<typename T>
uint64_t Less(T& list){
	auto cur=list.GetHead();
	uint64_t res=0;
	while(cur!=nullptr){
		res+=cur->value.Get_Less();
		cur=cur->next;
	}
return res;
}

template<typename T>
void Zero(T& list){
	auto cur=list.GetHead();
	while(cur!=nullptr){
		cur->value.Zero();
		cur=cur->next;
	}
}


void CleanWord(string& word){
	/*while(*word.begin()==','||*word.begin()=='.'||*word.begin()=='?'
			||*word.begin()=='!'||*word.begin()=='"'||*word.begin()=='"'||
			*word.begin()=='('||*word.begin()==')'||
					*word.begin()==':'||
					*word.begin()==';'||
					*word.begin()=='-'
										){
		if(word.begin()!=word.end()){
			break;
		}

		word.erase(word.begin());
	}

	while(word.back()==','||word.back()=='.'||word.back()=='?'
				||word.back()=='!'||word.back()=='"'||word.back()=='"'||
				word.back()==':'||word.back()==';'||word.back()=='-'
						||word.back()=='('||word.back()==')'){
		if(word.begin()!=word.end()){
					break;
				}
		if(word.begin()!=word.end()){word.erase(prev(word.end()));}
		}
*/

	/*for(char& x: word){
		if(ispunct(x))
if(!islower(x)){
	 x=static_cast<char>(tolower(x));
}
	}*/
	/*for(auto It=word.begin();It!=word.end();It++){
		if(!islower(*It)){
			 *It=static_cast<char>(tolower(*It));
		}
		while(It!=end(word)&&ispunct(*It)){
					word.erase(It);
						}
		if(It==end(word)){break;}

	}*/
	auto It=word.begin();
		while(It!=word.end()){
				if(!islower(*It)){
					 *It=static_cast<char>(tolower(*It));
				}
		if(ispunct(*It)){
				while(It!=end(word)&&ispunct(*It)){
							word.erase(It);
								}
		}
		else{
			It++;
		}

				if(It==end(word)){break;}

	}

}



struct Data{
	uint64_t N;
	uint64_t count;
	Data(uint64_t n,uint64_t count):N(n),count(count){}
};


void DoTask(){

	BeginList<MyString> list_b;
	EndList<MyString> list_e;
	ABCList<MyString> list_a;
	FreqList<MyString> list_f;

	ifstream input("text.txt");
	//ifstream input("cat.txt");

	vector<Data> data_Begin;
    vector<Data> data_End;
    vector<Data> data_ABC;
    vector<Data> data_Freq;

    string helper;
    uint64_t res=0;

    size_t prev_size=0;
    uint64_t helper_b=0;
    uint64_t helper_e=0;
    uint64_t helper_a=0;
    uint64_t helper_f=0;

    uint64_t counter=1;

    //while(helper.empty()){
while(input){
	input>>helper;
	CleanWord(helper);
	if(!helper.empty()&&input){

	//	cout << helper << endl;
		{
			Zero(list_b);
			list_b.Insert(helper);
			if(prev_size<list_b.Size()){
			//res=Less(list_b);
			res=(helper_b+Less(list_b))/counter;
			data_Begin.push_back(Data(static_cast<uint64_t>(list_b.Size()),res));
			////
			helper_b=0;
			/////counter=1;
			}
			else{
				helper_b+=Less(list_b);
				counter++;
			}

		}
		{
			Zero(list_e);
					list_e.Insert(helper);
					if(prev_size<list_e.Size()){

					res=(helper_e+Less(list_e))/counter;
					data_End.push_back(Data(static_cast<uint64_t>(list_e.Size()),res));
					helper_e=0;
								}
								else{
									helper_e+=Less(list_e);

								}
					}
		{
			Zero(list_a);
					list_a.Insert(helper);
					if(prev_size<list_a.Size()){

										res=(helper_a+Less(list_a))/counter;
										data_ABC.push_back(Data(static_cast<uint64_t>(list_a.Size()),res));
					helper_a=0;

								}
								else{
									helper_a+=Less(list_a);
								}
		}
		{
			Zero(list_f);
					list_f.Insert(helper);
					if(prev_size<list_f.Size()){

					res=(helper_f+Less(list_f))/counter;

					data_Freq.push_back(Data(static_cast<uint64_t>(list_f.Size()),res));
					helper_f=0;
								counter=1;
								}
								else{
									helper_f+=Less(list_f);
								}

					prev_size=list_f.Size();
		}
	}
}
//}


/////////////////////////////
////////////////////////////
//Write in FIle
//Write begin
{const string first_txt_begin="begin_list.txt";
ofstream output(first_txt_begin);
output << left;
for (auto& x: data_Begin){
	output << setw(14) << x.N<< setw(14) << x.count << "\n";
}
}
//Write end
{const string first_txt_end="end_list.txt";
ofstream output(first_txt_end);
output << left;
for (auto& x: data_End){
	output << setw(14) << x.N<< setw(14) << x.count << "\n";
}
}
//Write ABC
{const string first_txt_ABC="ABC_list.txt";
ofstream output(first_txt_ABC);
output << left;
for (auto& x: data_ABC){
	output << setw(14) << x.N<< setw(14) << x.count << "\n";
}
}
//Write Freq
{const string first_txt_Freq="Freq_list.txt";
ofstream output(first_txt_Freq);
output << left;
for (auto& x: data_Freq){
	output << setw(14) << x.N<< setw(14) << x.count << "\n";
}
}

////////////
cerr << endl << "Completed!" << endl;

}


void TestMyString(){
	{
		MyString s;
		assert(s.str==string());

		s=MyString("cat");
		assert(s.str=="cat");
		assert(s.Get_Less()==0);

		bool check=MyString("aa")<s;
		assert(check);

		check=MyString("aa")==s;
		assert(!check);

		assert(s==MyString("cat"));

		assert(s.Get_Less()==1);

		s.Zero();
		assert(s.Get_Less()==0);

		s<MyString("asasa");
		assert(s.Get_Less()==1);
		s.Increase(7);
		assert(s.Get_Less()==8);


	}

	cerr << "TestMyString passed" << endl;
}

void TestBeginList(){
	{
		BeginList<MyString> list;
        assert(list.Size()==0);
        assert(list.Find(MyString("A"))==0);
        assert(Less(list)==0);

        list.Insert(MyString("cat"));
        assert(list.Size()==1);
        assert(list.Find(MyString("A"))==0);
        assert(list.Find(MyString("cat"))==1);
        assert(Less(list)==2);

list.Insert(MyString("B"));
list.Insert(MyString("C"));
list.Insert(MyString("D"));
assert(Less(list)==8);

      assert(list.Size()==4);
      assert(list.Find(MyString("A"))==0);
      assert(list.Find(MyString("cat"))==1);
      assert(list.Find(MyString("C"))==1);
      assert(Less(list)==18);

      list.Insert(MyString("B"));
      assert(list.Size()==4);
      assert(list.Find(MyString("A"))==0);
      assert(list.Find(MyString("cat"))==1);
      assert(list.Find(MyString("C"))==1);
      assert(Less(list)==31);

list.PopFront();
assert(list.Size()==3);
assert(list.Find(MyString("A"))==0);
assert(list.Find(MyString("D"))==0);
assert(list.Find(MyString("C"))==1);

Zero(list);
assert(Less(list)==0);

	}
	cerr << "TestBeginList passed" << endl;
}

void TestEndList(){
	{
	EndList<MyString> list;
    assert(list.Size()==0);
    assert(list.Find(MyString("A"))==0);
    assert(Less(list)==0);

    list.Insert(MyString("cat"));
    assert(list.Size()==1);
    assert(list.Find(MyString("A"))==0);
    assert(list.Find(MyString("cat"))==1);
    assert(Less(list)==2);

list.Insert(MyString("B"));
list.Insert(MyString("C"));
list.Insert(MyString("D"));
assert(Less(list)==8);

  assert(list.Size()==4);
  assert(list.Find(MyString("A"))==0);
  assert(list.Find(MyString("cat"))==1);
  assert(list.Find(MyString("C"))==1);
  assert(Less(list)==16);

  list.Insert(MyString("B"));//2413
  assert(list.Size()==4);
  assert(list.Find(MyString("A"))==0);
  assert(list.Find(MyString("cat"))==1);
  assert(list.Find(MyString("C"))==1);
  assert(Less(list)==26);

list.PopFront();
assert(list.Size()==3);
assert(list.Find(MyString("A"))==0);
assert(list.Find(MyString("cat"))==0);
assert(list.Find(MyString("C"))==1);

Zero(list);
assert(Less(list)==0);

}
cerr << "TestEndList passed" << endl;
}

void TestABCList(){
	{
	ABCList<MyString> list;
    assert(list.Size()==0);
    assert(list.Find(MyString("A"))==0);
    assert(Less(list)==0);


    list.Insert(MyString("cat"));
    assert(list.Size()==1);
    assert(list.Find(MyString("A"))==0);
    assert(list.Find(MyString("cat"))==1);
    assert(Less(list)==2);

list.Insert(MyString("D"));//2
assert(Less(list)==4);
list.Insert(MyString("B"));//2
assert(Less(list)==6);
list.Insert(MyString("C"));//3
assert(Less(list)==9);
list.Insert(MyString("E"));//5
assert(Less(list)==14);

assert(list.Size()==5);
  assert(list.Find(MyString("A"))==0);//5
  assert(Less(list)==19);
  assert(list.Find(MyString("cat"))==1);//5
 //
 // list.Print();
  //cerr << Less(list) << endl;
  //
  assert(Less(list)==24);
  assert(list.Find(MyString("C"))==1);//2
  assert(Less(list)==26);

  list.Insert(MyString("B"));//2552
  assert(list.Size()==5);
  assert(list.Find(MyString("A"))==0);
  assert(list.Find(MyString("cat"))==1);
  assert(list.Find(MyString("C"))==1);
  assert(Less(list)==40);

list.PopFront();
assert(list.Size()==4);
assert(list.Find(MyString("A"))==0);
assert(list.Find(MyString("cat"))==1);
assert(list.Find(MyString("C"))==1);
assert(list.Find(MyString("B"))==0);

Zero(list);
assert(Less(list)==0);
}
	cerr << "TestABCList passed" << endl;
}

void TestFreqList(){
	{
	FreqList<MyString> list;
    assert(list.Size()==0);
    assert(list.Find(MyString("A"))==0);
    assert(Less(list)==0);


    list.Insert(MyString("cat"));
    assert(list.Size()==1);
    assert(list.Find(MyString("A"))==0);
    assert(list.Find(MyString("cat"))==1);
    assert(Less(list)==2);

list.Insert(MyString("D"));//2
assert(Less(list)==3);
list.Insert(MyString("B"));//4
//
 //list.Print();
  //cerr << Less(list) << endl;
  //
assert(Less(list)==5);
list.Insert(MyString("C"));//6
assert(Less(list)==8);
list.Insert(MyString("E"));//8
assert(Less(list)==12);

assert(list.Size()==5);
  assert(list.Find(MyString("A"))==0);//5
  assert(Less(list)==17);
  assert(list.Find(MyString("cat"))==1);//1
 //
  //list.Print();
  //cerr << Less(list) << endl;
  //
  assert(Less(list)==18);
  assert(list.Find(MyString("C"))==1);//4
  assert(Less(list)==22);

  list.Insert(MyString("B"));//3
  //
    //list.Print();
    //cerr << Less(list) << endl;
    //

  assert(list.Size()==5);
  assert(list.Find(MyString("A"))==0);//5
  assert(list.Find(MyString("cat"))==1);//2
  assert(list.Find(MyString("C"))==1);//4
  //
//      list.Print();
  //    cerr << Less(list) << endl;
      //
  assert(Less(list)==36);


  list.Insert(MyString("E"));//5

  list.Insert(MyString("E"));//2

  list.Insert(MyString("B"));//2

  list.Insert(MyString("B"));//2
  list.Insert(MyString("B"));//1
  //
  //  list.Print();
    //cerr << Less(list) << endl;
    //

  assert(Less(list)==48);

list.PopFront();
assert(list.Size()==4);
assert(list.Find(MyString("A"))==0);
assert(list.Find(MyString("cat"))==1);
assert(list.Find(MyString("C"))==1);
assert(list.Find(MyString("B"))==0);

Zero(list);
assert(Less(list)==0);

}
	cerr << "TestFreqList passed" << endl;
}

int main() {
	TestMyString();
	TestBeginList();
	TestEndList();
	TestABCList();
	TestFreqList();

    DoTask();



	return 0;
}
