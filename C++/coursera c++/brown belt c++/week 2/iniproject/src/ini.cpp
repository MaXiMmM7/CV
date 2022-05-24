#include "ini.h"
#include <exception>


namespace Ini{
  Section& Document::AddSection(string name){
	  Section section;
	  auto [It,b]=sections.insert({name,section});
	  return It->second;
  }
  const Section& Document::GetSection(const string& name) const{
	  if(sections.find(name)==sections.end()){throw out_of_range("sorry");}
	  return sections.find(name)->second;
  }
  size_t Document::SectionCount() const{
	  return sections.size();
  }

Document Load(istream& input){
	Document result;
	string name;
	string number;
	char symbol;
	while(input >> symbol){
		if(symbol=='['){

			getline(input,name,']');
			Section& section = result.AddSection(move(name));

			input.ignore(1);

			if(input.peek()!='['){
		  while(input.peek()!='\n'&&input.peek()!='['&&!input.eof()){
			getline(input,name,'=');
			getline(input,number);

			section.insert({move(name),move(number)});


					}
           }
		}
	}

	return result;
}
}

