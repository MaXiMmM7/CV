#include "json.h"
#include "test_runner.h"
//
#include <iostream>
#include <iomanip>
//
using namespace std;

namespace Json {

//
int number1 = 0;
int number2 = 0;
//
  Document::Document(Node root) : root(move(root)) {
  }

  const Node& Document::GetRoot() const {
    return root;
  }

  Node LoadNode(istream& input);

  Node LoadArray(istream& input) {
    vector<Node> result;
    //
    //cout << "Start array_____" << number2++ << endl;
    //

    for (char c; input >> c && c != ']'; ) {
      if (c != ',') {
        input.putback(c);
      }

      result.push_back(LoadNode(input));
    }
    //
//    cout << "End array_____" << --number2 << endl;
    //
    return Node(move(result));
  }

  Node LoadNumberOrBool(istream& input) {
    double result = 0;
    //
//    cout << "Start int_____" << endl;
    //
    if(isalpha(input.peek())){
    	string string_result;
    	while (isalpha(input.peek())){
    		string_result.push_back(input.get());
    	}
    	//
  //  	cout << string_result << endl;
    	//
    	//
    //	    cout << "End int_____" << endl;
    	    //
    	if(string_result=="true"){
    		return Node(true);
    	}else if(string_result == "false"){
    		return Node(false);
    	}
    }
    /*
    while (isdigit(input.peek())) {
      result *= 10;
      result += input.get() - '0';
    }
    if(input.peek()=='.'){
    	input.ignore(1);
    	double degree = 1.;
    	while (isdigit(input.peek())) {
    		degree *= 0.1;
    		result += (input.get() - '0')*degree;
    	}
    	//
    }
    //
    //cout << result << endl;
    //
    //
    //cout << "End int_____" << endl;
    //     */
    input >> result;
    return Node(result);
  }

  Node LoadString(istream& input) {
    string line;
    getline(input, line, '"');
    //
//    cout << "Start string_____" << endl;
    //
    //
  //  cout << line << endl;
    //
    //
   //cout << "End string_____" << endl;
    //
    return Node(move(line));
  }

  Node LoadDict(istream& input) {
    map<string, Node> result;
    //
//    cout << "Start dict_____" << number1++ << endl;
    //

    for (char c; input >> c && c != '}'; ) {
      if (c == ',') {
        input >> c;
      }

      string key = LoadString(input).AsString();
      input >> c;
      result.emplace(move(key), LoadNode(input));
    }
    //
//    cout << "End dict_____" << --number1 << endl;
    //
    return Node(move(result));
  }

  Node LoadNode(istream& input) {
    char c;
    input >> c;

    //
//    cout << "Hello : " << c << endl;
    //
    if (c == '[') {
      return LoadArray(input);
    } else if (c == '{') {
      return LoadDict(input);
    } else if (c == '"') {
      return LoadString(input);
    } else {
      input.putback(c);
      return LoadNumberOrBool(input);
    }
  }

  Document Load(istream& input) {
    return Document{LoadNode(input)};
  }

}


