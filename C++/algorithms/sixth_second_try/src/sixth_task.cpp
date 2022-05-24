
#include <iostream>
#include "lists.h"
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include <cassert>
#include <algorithm>
#include <iomanip>
using namespace std;


template <typename T>
 vector<pair<string,uint64_t>> Get(T& list){
	vector<pair<string,uint64_t>> res;
	int i=1;
	auto cur=list.GetHead();
	pair<string,uint64_t> max;
    auto MAX=cur;

	while(i<101&&i<=static_cast<int>(list.Size())){
		while(cur!=nullptr){
				if(MAX->count<cur->count){
        	 MAX=cur;
         }
         cur=cur->next;
       }
		res.push_back(make_pair(MAX->value.str,MAX->count));
		MAX->count=0;
		cur=list.GetHead();
		i++;
	}
	return res;
}


void CleanWord(string& word){
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
	//ifstream input("dog.txt");
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

		/*
		MyString().Zero();
		list_b.Insert(helper);
		if(prev_size<list_b.Size()){
			data_Begin.push_back(Data(static_cast<uint64_t>(list_b.Size()),
					list_b.GetHead()->value.Get_Less()));

			MyString().Zero();
			list_e.Insert(helper);
			data_End.push_back(Data(static_cast<uint64_t>(list_e.Size()),
					list_e.GetHead()->value.Get_Less()));
			MyString().Zero();
			list_a.Insert(helper);
			data_ABC.push_back(Data(static_cast<uint64_t>(list_a.Size()),
					list_a.GetHead()->value.Get_Less()));

			MyString().Zero();
			list_f.Insert(helper);
			data_Freq.push_back(Data(static_cast<uint64_t>(list_f.Size()),
					list_f.GetHead()->value.Get_Less()));

			prev_size=list_f.Size();

		}
		else{
			list_e.Insert(helper);
			list_a.Insert(helper);
			list_f.Insert(helper);
		}
*/

			//	cout << helper << endl;
		{
			MyString().Zero();
			//list_b.GetHead()->value.Zero();//Zero(list_b);
			list_b.Insert(helper);
			if(prev_size<list_b.Size()){
			//res=Less(list_b);
			res=(helper_b+list_b.GetHead()->value.Get_Less())/counter;
			data_Begin.push_back(Data(static_cast<uint64_t>(list_b.Size()),res));
			////
			helper_b=0;
			/////counter=1;
			}
			else{
				helper_b+=list_b.GetHead()->value.Get_Less();
				counter++;
			}

		}
		{
			MyString().Zero();
			//Zero(list_e);
					list_e.Insert(helper);
					if(prev_size<list_e.Size()){

					res=(helper_e+list_e.GetHead()->value.Get_Less())/counter;
					data_End.push_back(Data(static_cast<uint64_t>(list_e.Size()),res));
					helper_e=0;
								}
								else{
									helper_e+=list_e.GetHead()->value.Get_Less();

								}
					}
		{
			//Zero(list_a);
			MyString().Zero();
			list_a.Insert(helper);
					if(prev_size<list_a.Size()){

			res=(helper_a+list_a.GetHead()->value.Get_Less())/counter;
			data_ABC.push_back(Data(static_cast<uint64_t>(list_a.Size()),res));
			helper_a=0;

								}
								else{
									helper_a+=list_a.GetHead()->value.Get_Less();
								}
		}
		{
			//Zero(list_f);
					MyString().Zero();

			list_f.Insert(helper);
					if(prev_size<list_f.Size()){

					res=(helper_f+list_f.GetHead()->value.Get_Less())/counter;

					data_Freq.push_back(Data(static_cast<uint64_t>(list_f.Size()),res));
					helper_f=0;
								counter=1;
								}
								else{
									helper_f+=list_f.GetHead()->value.Get_Less();
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


///

vector<pair<string,uint64_t>> res_b;
auto res_e=res_b;
auto res_a=res_b;
auto res_f=res_b;
//
{const string first_txt_begin="begin_list_get.txt";
ofstream output(first_txt_begin);
output << left;
int i=1;
auto res=Get(list_b);
res_b=res;
for (auto& x: res){
	output << setw(5) << i++ << setw(25) << x.first<< setw(14) << x.second << "\n";
}
}
//Write end
{const string first_txt_end="end_list_get.txt";
ofstream output(first_txt_end);
output << left;
int i=1;
auto res=Get(list_e);
res_e=res;
for (auto& x: res){
	output  << setw(5) << i++<< setw(25) << x.first<< setw(14) << x.second << "\n";
}
}
//Write ABC
{const string first_txt_ABC="ABC_list_get.txt";
ofstream output(first_txt_ABC);
output << left;
int i=1;
auto res=Get(list_a);
res_a=res;
for (auto& x: res){
	output  << setw(5) << i++<< setw(25) << x.first<< setw(14) << x.second << "\n";
}
}
//Write Freq
{const string first_txt_Freq="Freq_list_get.txt";
ofstream output(first_txt_Freq);
output << left;
int i=1;
auto res=Get(list_f);
res_f=res;
for (auto& x: res){
	output  << setw(5) << i++<< setw(25) << x.first<< setw(14) << x.second << "\n";
}
}
////////////
/*auto res_b=Get(list_b);
auto res_e=Get(list_e);
auto res_a=Get(list_a);
auto res_f=Get(list_f);*/

/*for(int i=0;i<100;i++){
if(!((res_b[i].first==res_e[i].first)&&(res_b[i].second==res_e[i].second)
		&&(res_e[i].first==res_a[i].first)&&(res_e[i].second==res_a[i].second)
		&&(res_a[i].first==res_f[i].first)&&(res_a[i].second==res_f[i].second))){
	cerr << endl << "NOOOOOO!   "  << i << endl;
}

}
*/

if(res_e==res_a){
	cerr << endl <<"ok!" << endl;
}
else{
	cerr << endl <<"no!" << endl;
}
if(res_b==res_e){
	cerr << endl <<"ok!" << endl;
}
else{
	for(int i=0;i<100;i++){
		if(res_b[i].first!=res_e[i].first||res_b[i].second!=res_e[i].second){
			cerr << res_b[i].first << "-" << res_b[i].second << " "
					<< res_e[i].first << "-" << res_e[i].second <<endl;
		}
	}
	cerr << endl <<"no!" << endl;
}
if(res_a==res_f){
	cerr << endl <<"ok!" << endl;
}
else{
	cerr << endl <<"no!" << endl;
}

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

		assert(s.Get_Less()==3);

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
		MyString().Zero();//clear counter

		BeginList<MyString> list;
        assert(list.Size()==0);
        assert(list.Find(MyString("A"))==0);
        //assert(list.GetHead()->value.Get_Less()==0);

        list.Insert(MyString("cat"));
        assert(list.Size()==1);
        assert(list.Find(MyString("A"))==0);
        assert(list.Find(MyString("cat"))==1);
        //
       // cerr <<list.GetHead()->value.Get_Less() << endl;
        //
        assert(list.GetHead()->value.Get_Less()==2);

list.Insert(MyString("B"));//1
list.Insert(MyString("C"));//2
list.Insert(MyString("D"));//3
assert(list.GetHead()->value.Get_Less()==8);

      assert(list.Size()==4);
      assert(list.Find(MyString("A"))==0);
      assert(list.Find(MyString("cat"))==1);
      assert(list.Find(MyString("C"))==1);
      assert(list.GetHead()->value.Get_Less()==18);

      list.Insert(MyString("B"));
      assert(list.Size()==4);
      assert(list.Find(MyString("A"))==0);
      assert(list.Find(MyString("cat"))==1);
      assert(list.Find(MyString("C"))==1);
      assert(list.GetHead()->value.Get_Less()==31);

list.PopFront();
assert(list.Size()==3);
assert(list.Find(MyString("A"))==0);
assert(list.Find(MyString("D"))==0);
assert(list.Find(MyString("C"))==1);

list.GetHead()->value.Zero();

assert(list.GetHead()->value.Get_Less()==0);

	}
	cerr << "TestBeginList passed" << endl;
}

void TestEndList(){
	{
	EndList<MyString> list;
    assert(list.Size()==0);
    assert(list.Find(MyString("A"))==0);
    assert(list.GetHead()->value.Get_Less()==0);

    list.Insert(MyString("cat"));
    assert(list.Size()==1);
    assert(list.Find(MyString("A"))==0);
    assert(list.Find(MyString("cat"))==1);
    assert(list.GetHead()->value.Get_Less()==2);

list.Insert(MyString("B"));
list.Insert(MyString("C"));
list.Insert(MyString("D"));
assert(list.GetHead()->value.Get_Less()==8);

  assert(list.Size()==4);
  assert(list.Find(MyString("A"))==0);
  assert(list.Find(MyString("cat"))==1);
  assert(list.Find(MyString("C"))==1);
  assert(list.GetHead()->value.Get_Less()==16);

  list.Insert(MyString("B"));//2413
  assert(list.Size()==4);
  assert(list.Find(MyString("A"))==0);
  assert(list.Find(MyString("cat"))==1);
  assert(list.Find(MyString("C"))==1);
  assert(list.GetHead()->value.Get_Less()==26);

list.PopFront();
assert(list.Size()==3);
assert(list.Find(MyString("A"))==0);
assert(list.Find(MyString("cat"))==0);
assert(list.Find(MyString("C"))==1);

list.GetHead()->value.Zero();
assert(list.GetHead()->value.Get_Less()==0);

}
cerr << "TestEndList passed" << endl;
}

void TestABCList(){
	{
	ABCList<MyString> list;
    assert(list.Size()==0);
    assert(list.Find(MyString("A"))==0);
    assert(list.GetHead()->value.Get_Less()==0);


    list.Insert(MyString("cat"));
    assert(list.Size()==1);
    assert(list.Find(MyString("A"))==0);
    assert(list.Find(MyString("cat"))==1);
    assert(list.GetHead()->value.Get_Less()==2);

list.Insert(MyString("D"));//2
assert(list.GetHead()->value.Get_Less()==4);
list.Insert(MyString("B"));//2
assert(list.GetHead()->value.Get_Less()==6);
list.Insert(MyString("C"));//3
assert(list.GetHead()->value.Get_Less()==9);
list.Insert(MyString("E"));//5
assert(list.GetHead()->value.Get_Less()==14);

assert(list.Size()==5);
  assert(list.Find(MyString("A"))==0);//5
  assert(list.GetHead()->value.Get_Less()==19);
  assert(list.Find(MyString("cat"))==1);//5
 //
 // list.Print();
  //cerr << Less(list) << endl;
  //
  assert(list.GetHead()->value.Get_Less()==24);
  assert(list.Find(MyString("C"))==1);//2
  assert(list.GetHead()->value.Get_Less()==26);

  list.Insert(MyString("B"));//2552
  assert(list.Size()==5);
  assert(list.Find(MyString("A"))==0);
  assert(list.Find(MyString("cat"))==1);
  assert(list.Find(MyString("C"))==1);
  assert(list.GetHead()->value.Get_Less()==40);

list.PopFront();
assert(list.Size()==4);
assert(list.Find(MyString("A"))==0);
assert(list.Find(MyString("cat"))==1);
assert(list.Find(MyString("C"))==1);
assert(list.Find(MyString("B"))==0);

list.GetHead()->value.Zero();
assert(list.GetHead()->value.Get_Less()==0);
}
	cerr << "TestABCList passed" << endl;
}

void TestFreqList(){
	{
	FreqList<MyString> list;
    assert(list.Size()==0);
    assert(list.Find(MyString("A"))==0);
    assert(list.GetHead()->value.Get_Less()==0);


    list.Insert(MyString("cat"));
    assert(list.Size()==1);
    assert(list.Find(MyString("A"))==0);
    assert(list.Find(MyString("cat"))==1);
    assert(list.GetHead()->value.Get_Less()==2);

list.Insert(MyString("D"));//2
assert(list.GetHead()->value.Get_Less()==3);
list.Insert(MyString("B"));//4
//
 //list.Print();
  //cerr << Less(list) << endl;
  //
assert(list.GetHead()->value.Get_Less()==5);
list.Insert(MyString("C"));//6
assert(list.GetHead()->value.Get_Less()==8);
list.Insert(MyString("E"));//8
assert(list.GetHead()->value.Get_Less()==12);

assert(list.Size()==5);
  assert(list.Find(MyString("A"))==0);//5
  assert(list.GetHead()->value.Get_Less()==17);
  assert(list.Find(MyString("cat"))==1);//1
 //
  //list.Print();
  //cerr << Less(list) << endl;
  //
  assert(list.GetHead()->value.Get_Less()==18);
  assert(list.Find(MyString("C"))==1);//4
  assert(list.GetHead()->value.Get_Less()==22);

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
  assert(list.GetHead()->value.Get_Less()==36);


  list.Insert(MyString("E"));//5

  list.Insert(MyString("E"));//2

  list.Insert(MyString("B"));//2

  list.Insert(MyString("B"));//2
  list.Insert(MyString("B"));//1
  //
  //  list.Print();
    //cerr << Less(list) << endl;
    //

  assert(list.GetHead()->value.Get_Less()==48);

list.PopFront();
assert(list.Size()==4);
assert(list.Find(MyString("A"))==0);
assert(list.Find(MyString("cat"))==1);
assert(list.Find(MyString("C"))==1);
assert(list.Find(MyString("B"))==0);

list.GetHead()->value.Zero();
assert(list.GetHead()->value.Get_Less()==0);

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
