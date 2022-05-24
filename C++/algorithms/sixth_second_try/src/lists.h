#pragma once
#include <string>
#include <iostream>
#include <utility>


class MyString{
public:
	std::string str;

	MyString(){};
	MyString(const std::string& s);
	MyString& operator=(const MyString& s);

	bool operator<(const MyString& s);
	bool operator==(const MyString& s);
	uint64_t Get_Less();
	void Increase(const uint64_t& object ){
		less_counter+=object;
	}
	void Zero();
private:
	static uint64_t less_counter;
};


uint64_t MyString::less_counter=0;
////// a    b-1 c-1 d-1 a-1 f  не усреднять(или усреднять) static


MyString& MyString::operator=(const MyString& s){
	str=s.str;
	return *this;
}

MyString::MyString(const std::string& s){
	str=s;
}

bool MyString::operator==(const MyString& s){
	less_counter++;
	return str==s.str;
}

bool MyString::operator<(const MyString& s){
	less_counter++;
	return str<s.str;
}


uint64_t MyString::Get_Less(){
return less_counter;
}


void MyString::Zero(){
	less_counter=0;
}


std::ostream& operator<<(std::ostream& stream,const MyString object){
	return stream<<object.str;
}


////////////////////////////////////////
//BEGIN LIST

template <typename T>
class BeginList {
public:
  struct Node {
    T value;
    size_t count=0;///////////////////
    Node* next = nullptr;
  };

  ~BeginList();

  void Insert(const T& value);
  void PopFront();
  bool Find(const T& s);
  size_t Size();

void Print();
std::string ToString();

  Node* GetHead() { return head; }
  const Node* GetHead() const { return head; }

private:
  Node* head = nullptr;
  size_t size=0;
};

template <typename T>
BeginList<T>::~BeginList() {
  while (head) {
    PopFront();
  }
}

template <typename T>
void BeginList<T>::Insert(const T& value) {
  if(Find(value)==false){
  auto node = new Node{value};
  node->count++;/////////
  node->next = head;
  head = node;
  size++;
  }
}


template <typename T>
void BeginList<T>::PopFront() {
  if (head) {
    Node* new_head = head->next;
    delete head;
    head = new_head;
    size--;
  }
}

template<typename T>
bool BeginList<T>::Find(const T& object){
	auto res= head;
	while(res!=nullptr){
		if(res->value==object){
			res->count++;///////////
			return true;
		}
		res=res->next;
	}
return false;
}

template<typename T>
size_t BeginList<T>::Size(){
	return size;
}

template<typename T>
void BeginList<T>::Print(){
	auto res= head;
		while(res!=nullptr){
			std::cout << res->value << " ";
			res=res->next;
		}
		std::cout << std::endl;
}

////////////////////////////////////////
//END LIST

template <typename T>
class EndList {
public:
  struct Node {
    T value;
    size_t count=0;
    Node* next = nullptr;
  };

  ~EndList();

  void Insert(const T& value);
  void PopFront();
  bool Find(const T& s);
  size_t Size();

void Print();
std::string ToString();

  Node* GetHead() { return head; }
  const Node* GetHead() const { return head; }

private:
  Node* head = nullptr;
  Node* last = nullptr;
  size_t size=0;
};

template <typename T>
EndList<T>::~EndList() {
  while (head) {
    PopFront();
  }
}

template <typename T>
void EndList<T>::Insert(const T& value) {
  if(Find(value)==false){
	  auto node = new Node{value};
	  node->count++;///////////
	  if(head==nullptr){
		  last=head= node;
		  size++;
		  return;
	  }
      last->next = node;
      last = node;
      size++;
  }
}


template <typename T>
void EndList<T>::PopFront() {
  if (head) {
    Node* new_head = head->next;
    delete head;
    head = new_head;
    size--;
  }
}

template<typename T>
bool EndList<T>::Find(const T& object){
	auto res= head;
	while(res!=nullptr){
		if(res->value==object){
			res->count++;
			return true;
		}
		res=res->next;
	}
return false;
}

template<typename T>
size_t EndList<T>::Size(){
	return size;
}

template<typename T>
void EndList<T>::Print(){
	auto res= head;
		while(res!=nullptr){
			std::cout << res->value << " ";
			res=res->next;
		}
		std::cout << std::endl;
}


////////////////////////////////////////
//ABC LIST

template <typename T>
class ABCList {
public:
  struct Node {
    T value;
    size_t count=0;
    Node* next = nullptr;
  };

  ~ABCList();

  void Insert(const T& value);
  void PopFront();
  bool Find(const T& s);
  size_t Size();

void Print();
std::string ToString();

  Node* GetHead() { return head; }
  const Node* GetHead() const { return head; }

private:
  Node* head = nullptr;
  size_t size=0;
};

template <typename T>
ABCList<T>::~ABCList() {
  while (head) {
    PopFront();
  }
}

template <typename T>
void ABCList<T>::Insert(const T& value) {//current+ prev=prev+cur+next
	if(head==nullptr){
	 head = new Node{value};
	 head->count++;/////////////
	}
	else{
  auto cur=head;
  auto prev=cur;
  while(cur!=nullptr){
	  if(!(cur->value<value)){
		  if(cur->value==value){
			  cur->count++;////////////
			  return;}
		  else{break;}
	  }
	  prev=cur;
	  cur=cur->next;
  }

      auto node = new Node{value};
      node->count++;//////////////
	  if(cur!=prev){
      prev->next = node;
	  node->next =cur;}
	  else{
		  node->next=cur;
		  head=node;
	  }

	}

      size++;
}


template <typename T>
void ABCList<T>::PopFront() {
  if (head) {
    Node* new_head = head->next;
    delete head;
    head = new_head;
    size--;
  }
}

template<typename T>
bool ABCList<T>::Find(const T& object){
	auto res= head;
	while(res!=nullptr){
		if(res->value==object){
			res->count++;////////
			return true;
		}
		res=res->next;
	}
return false;
}

template<typename T>
size_t ABCList<T>::Size(){
	return size;
}

template<typename T>
void ABCList<T>::Print(){  //current+ prev=prev+cur+next
	auto res= head;
		while(res!=nullptr){
			std::cout << res->value << " ";
			res=res->next;
		}
		std::cout << std::endl;
}


////////////////////////////////////////
//Frequency LIST

template <typename T>
class FreqList {
public:
  struct Node {
    T value;
    size_t count=0;
    Node* next = nullptr;
  };

  ~FreqList();

  void Insert(const T& value);
  void PopFront();
  bool Find(const T& s);
  size_t Size();

void Print();
std::string ToString();

  Node* GetHead() { return head; }
  const Node* GetHead() const { return head; }

private:
  Node* head = nullptr;
  size_t size=0;
};

template <typename T>
FreqList<T>::~FreqList() {
  while (head) {
    PopFront();
  }
}

/*
template <typename T>
void FreqList<T>::Insert(const T& value) {//current+ prev=prev+cur+next
	if(head==nullptr){
	 head = new Node{value};
	 head->count++;
	}
	else{
  auto cur=head;
  auto prev=cur;
  while(cur!=nullptr){
	  if(cur->value==value){
	  cur->count++;
	if(prev->count<cur->count){

		auto helper=cur;
		prev->next=cur->next;
		cur=prev=head;
		uint64_t V=1;
		while(helper->count<cur->count){//добавить тут сравнения в счетчик
			prev=cur;
			cur=cur->next;
			V++;
		}
        helper->value.Increase(V);///////////dsdsdsd

		if(prev!=cur){
		prev->next=helper;
		helper->next=cur;
		}
		else{
			helper->next=cur;
			head=helper;
		}
	}
			  return;
	  }
	  prev=cur;
	  cur=cur->next;
  }


  auto node = new Node{value};
  prev->next=node;
  node->count++;
  }

      size++;
}
*/

template <typename T>
void FreqList<T>::Insert(const T& value) {//current+ prev=prev+cur+next
	if(head==nullptr){
	 head = new Node{value};
	 head->count++;
	}
	else{
  auto cur=head;
  auto prev=cur;
  auto pos=cur;
  while(cur!=nullptr){
	  if(cur->value==value){
	  cur->count++;
	  if(pos->next!=cur&&cur!=head){
      prev->next=cur->next;
      auto helper=pos->next;
      pos->next=cur;
      cur->next=helper;
	  }
	  //
	  //std::cerr << head->value << "  " <<head->next->value << std::endl;
	  //
	  if(head->count<head->next->count){
		  //
		  //std::cerr << "CAR" << std::endl;
		  //
		  auto helper=head->next;
		       head->next=helper->next;
		       helper->next=head;
		       head=helper;

	  }
			  return;
	  }
	  if(!(cur->count==prev->count)){
		  pos=prev;
	  }
	  prev=cur;
	  cur=cur->next;
  }


  auto node = new Node{value};
  prev->next=node;
  node->count++;
  }

      size++;
}


template <typename T>
void FreqList<T>::PopFront() {
  if (head) {
    Node* new_head = head->next;
    delete head;
    head = new_head;
    size--;
  }
}

template<typename T>
bool FreqList<T>::Find(const T& object){
	auto res= head;
	while(res!=nullptr){
		if(res->value==object){
			return true;
		}
		res=res->next;
	}
return false;
}

template<typename T>
size_t FreqList<T>::Size(){
	return size;
}

template<typename T>
void FreqList<T>::Print(){  //current+ prev=prev+cur+next
	auto res= head;
		while(res!=nullptr){
			std::cout << res->value << " ";
			res=res->next;
		}
		std::cout << std::endl;
}
