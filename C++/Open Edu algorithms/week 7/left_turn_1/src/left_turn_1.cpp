#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <stack>
#include <memory>
using namespace std;

class TreeAVL{
public:
	TreeAVL(){}

	void Build(vector<int>& keys, vector<int>& left, vector<int>& right, vector<int>& parent, int N_){
		N = N_;
		links.resize(N + 1);

		for( int i = 1; i < N + 1; i++){
			Node helper;
			helper.key = keys[i];
			links[i] = make_shared<Node>(helper);
		}


		for( int i = 1; i < N + 1; i++){
			links[i]->left = links[left[i]];
			links[i]->right = links[right[i]];
			links[i]->parent = links[parent[i]];
		}

		root = links[1];

		Balance();

	}

	void LeftTurn(){ ////
		//
//		cout << "hey1" << endl;
//		cout << root->left->key << endl;
		//
		if( root->right->balance == -1){
			auto C = root->right->left;
			root->right->left = C->right;
			C->right = root->right;
			root->right = C->left;
			C->left = root;
			root = C;
		}else{
			auto B = root->right;
			root->right = B->left;
			B->left = root;
			root = B;
		}

		//
	/*
		cout << "new root = " << root->key <<
				" right = " << root->right->key <<
				" left = " << root->left->key << endl;
		cout << "hey2" << endl;
		*/
		//
	}

	void Output(ofstream& output){

		auto helper = root;
		int counter = 0;
		stack<shared_ptr<Node>> stack_;
		while( helper != nullptr || !stack_.empty()){

			if( helper == nullptr && !stack_.empty()){
				helper = stack_.top();
				stack_.pop();
			}

			helper->index = ++counter;
			links[counter] = helper;
			//
		//		cout <<"key = " <<  helper->key  << " index = " << helper->index << endl;
			//

			if( helper->right != nullptr){
				stack_.push( helper->right);
			}

			helper = helper->left;

		}

		//
	//	cout << links.size() << endl;
		//

		for( int i = 1; i < N + 1; i++){
		//	cout << links[i] -> key << " left = ";
			output << links[i] -> key << " ";
			if(links[i]->left == nullptr){
				output << 0;
			}else{
				output << links[i]->left->index;
			}
			output << " ";
			if(links[i]->right == nullptr){
				output << 0;
			}else{
				output << links[i]->right->index;
			}
		//	if(i < N + 2){
			output << '\n';
			//}
		}
	}

private:


	struct Node{
		int key;
		shared_ptr<Node> left;
		shared_ptr<Node> right;
		shared_ptr<Node> parent;
		int height = 0;
		int balance;
		int index;
	};

	void Balance(){

		for( int i = 1; i < N + 1; i++){
			//	cout << " i = " << i << " key = " << keys[i] << endl;

			if(links[i]->left == nullptr && links[i]->right == nullptr){
				int h = 0;
				auto x = links[i];
				x->height = h;
				auto y = x->parent;
				while( y != nullptr){
					h++;
					if( h > y->height){
						y->height = h;
					}
					//
				//	cout << " y = " << y->key << " h = " << y->height << endl;
					//
					x = y;
					y = y -> parent;
				}
			}
		}

		for( int i = 1;  i < N + 1; i++){

			int l,r;
			if(links[i]->left != nullptr){
				l = links[i]->left->height;
			}else{
				l = -1;
			}

			if(links[i]->right != nullptr){
				r = links[i]->right->height;
			}else{
				r = -1;
			}

			//
		//	cout << "key = " << links[i]->key << " l = " << l << " r = " << r << endl;
			//

			links[i]->balance = r - l;

		}

	}

	shared_ptr<Node> root;
	vector<shared_ptr<Node>> links;
	int N = 0;
};
int main() {

	ifstream input("input.txt");
	int N;
	input >> N;

	vector<int> keys(N + 1);
	vector<int> left(N + 1, 0);
	vector<int> right(N + 1, 0);
	vector<int> parent(N + 1, 0);

	for( int i = 1; i < N + 1; i++){
		input >> keys[i] >> left[i] >> right[i];
		if( left[i] != 0){
			parent[left[i]] = i;
		}
		if( right[i] != 0){
			parent[right[i]] = i;
		}
	}


	TreeAVL tree;
	tree.Build(keys, left, right, parent, N);
	tree.LeftTurn();

	ofstream output("output.txt");
	output << N << '\n';
	tree.Output(output);

	return 0;
}
