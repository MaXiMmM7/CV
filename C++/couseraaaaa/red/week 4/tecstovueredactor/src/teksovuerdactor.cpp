#include <string>
#include <list>
#include "test_runner.h"
using namespace std;

class Editor {
 public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor(){}
  void Left(){
	  if(It!=text.begin()){It--;}
  }
  void Right(){
	  if(It!=text.end()){It++;}
  }
  void Insert(char token){
 	  	  text.emplace(It,token);
	    }
  void Cut(size_t tokens = 1){
	  buffer.clear();
	 	  buffer.reserve(tokens);
	 	  auto helper=It;

	 	  while(helper!=text.end()&&tokens!=0){
	 		  buffer.push_back(*helper);
	 		  tokens--;
              helper++;
	 	  }
	 	  buffer.shrink_to_fit();
	 	  text.erase(It,helper);
		  It=helper;
  }
  void Copy(size_t tokens = 1){
	  buffer.clear();
	  buffer.reserve(tokens);
	  auto helper=It;
	  while(helper!=text.end()&&tokens!=0){
		  buffer.push_back(*helper);
		  tokens--;
		  helper++;
	  }
	  buffer.shrink_to_fit();
  }
  void Paste(){
	  if(buffer.empty()){return;}
	  for(auto x: buffer){
		  text.emplace(It,x);
	  }
  }
  string GetText() const{
	  string result;
	  for(auto x: text){
		  result.push_back(x);
	  }
	  return result;
  }
 private:
  list<char> text;
  string buffer="";
  list<char>::iterator It=text.begin();
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();//v nachale
    }
    editor.Cut(first_part_len);// do world cut
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right(); // v konec
    }
    TypeText(editor, ", "); // zapyatuyu ebnuli
    editor.Paste(); // vstavili gavno
    editor.Left();
    editor.Left();
    editor.Cut(3);

    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}


void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}


int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);

  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);

  return 0;
}
