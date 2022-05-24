#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <array>
#include <future>
//#include <utility>



vector<string> SplitIntoWords(const string& line) {
  istringstream words_input(line);
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
if(k==0){
	k++;
	InvertedIndex new_index;

	  for (string current_document; getline(document_input, current_document); ) {
	    new_index.Add(move(current_document));
	  }

			 auto access = index.GetAccess();
			 //access.ref_to_value = move(new_index);
			 swap(access.ref_to_value,new_index);

			 ////////////
			// futures.resize(6);
			 //////////////
			 return;

}
	futures.push_back(async([&]{

		InvertedIndex new_index;

  for (string current_document; getline(document_input, current_document); ) {
    new_index.Add(move(current_document));
  }

		 auto access = index.GetAccess();
		 //access.ref_to_value = move(new_index);
		 swap(access.ref_to_value,new_index);
	}));
		/*	if(futures.size()>=8){
				for(auto& x:futures){
					x.get();
				}
				futures.clear();
			}*/

	}


void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {

	futures.push_back(async([&]{

	 // access.ref_to_value
//	vector<pair<size_t,size_t>> docid_count(index.GetSize());
	for (string current_query; getline(query_input, current_query); ) {
    const auto words = SplitIntoWords(current_query);

    vector<pair<size_t,size_t>> docid_count;
    { auto access = index.GetAccess();
  docid_count.resize(access.ref_to_value.GetSize());


   for (const auto& word : words) {
  for (const pair<size_t,size_t> docid : access.ref_to_value.Lookup(word)) {
    docid_count[docid.first].first=docid.first;
    docid_count[docid.first].second+=docid.second;
  }
}
    }



size_t N= docid_count.size() < 5 ? docid_count.size() : 5;

partial_sort(
     begin(docid_count),
	 begin(docid_count)+N,
     end(docid_count),
     [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
       int64_t lhs_docid = lhs.first;
       auto lhs_hit_count = lhs.second;
       int64_t rhs_docid = rhs.first;
       auto rhs_hit_count = rhs.second;
       return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
     }
   );


	for(size_t i=0;i<5;i++){
	if(docid_count[i].second==0||N<i){
		N=i;
		break;
	}
}
//cerr << endl;
//

    search_results_output << current_query << ':';
    for (auto [docid, hitcount] : Head(docid_count, N)) {
      search_results_output << " {"
        << "docid: " << docid << ", "
        << "hitcount: " << hitcount << '}';
    }
    search_results_output << endl;
    }
	}));

	if(futures.size()>=6){

			futures.clear();
		}
}


/*
void SearchServer::AddQueriesStream_1(
  istream& query_input, ostream& search_results_output
) {
	 // access.ref_to_value
//	vector<pair<size_t,size_t>> docid_count(index.GetSize());
	for (string current_query; getline(query_input, current_query); ) {
    const auto words = SplitIntoWords(current_query);


    auto access = index.GetAccess();
    vector<pair<size_t,size_t>> docid_count(access.ref_to_value.GetSize());


   for (const auto& word : words) {
  for (const pair<size_t,size_t> docid : access.ref_to_value.Lookup(word)) {
    docid_count[docid.first].first=docid.first;
    docid_count[docid.first].second+=docid.second;
  }
}



size_t N= docid_count.size() < 5 ? docid_count.size() : 5;

partial_sort(
     begin(docid_count),
	 begin(docid_count)+N,
     end(docid_count),
     [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
       int64_t lhs_docid = lhs.first;
       auto lhs_hit_count = lhs.second;
       int64_t rhs_docid = rhs.first;
       auto rhs_hit_count = rhs.second;
       return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
     }
   );


	for(size_t i=0;i<5;i++){
	if(docid_count[i].second==0||N<i){
		N=i;
		break;
	}
}
//cerr << endl;
//

    search_results_output << current_query << ':';
    for (auto [docid, hitcount] : Head(docid_count, N)) {
      search_results_output << " {"
        << "docid: " << docid << ", "
        << "hitcount: " << hitcount << '}';
    }
    search_results_output << endl;
    }
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
	futures.push_back(async(launch::async,&SearchServer::AddQueriesStream_1,this,
			ref(query_input),ref(search_results_output)));

	if(futures.size()>=8){
		for(auto& x:futures){
			x.get();
		}
		futures.clear();
	}

}
*/
void InvertedIndex::Add(const string& document) {
  docs.push_back(document);

  const size_t docid = docs.size() - 1;
  for (const auto& word : SplitIntoWords(document)) {
	  if(index[word].size()==0||prev(index[word].end())->first!=docid){
	  index[word].push_back(make_pair(docid,1));// точно ли лист лучшая идея?
	  }
	  else{
		  prev(index[word].end())->second++;
	  }
  }
}

const vector<pair<size_t,size_t>>& InvertedIndex::Lookup(const string& word) const {
  if (auto it = index.lower_bound(word); it != index.end()&&(*it).first==word) {// для map лучше бинарным поиском же
    return it->second;
  } else {
    return empty_;
  }
}

/*
 * vector<size_t> docid_count(index.GetSize());
	for (string current_query; getline(query_input, current_query); ) {
    const auto words = SplitIntoWords(current_query);

for (const auto& word : words) {
  for (const size_t docid : index.Lookup(word)) {
    docid_count[docid]++;
  }
}

vector<pair<size_t, size_t>> search_results;
vector<pair<size_t, size_t>>::iterator check;
search_results.reserve(5);
size_t k=0;
size_t i=0;
while(k<5&&i<docid_count.size()){
	if(docid_count[i]!=0){
		search_results.push_back(make_pair(i,docid_count[i]));/////////
		//check=*prev(search_results.end());
		if(k==0){check=prev(search_results.end());}/////////////////////
		if(k>0&&docid_count[i]<=(*check).second){check=prev(search_results.end());}
		k++;
	}
docid_count[i]=0;
i++;
  }
for(;i<docid_count.size();i++){
	if(docid_count[i]>(*check).second){
		(*check).first=i;
		(*check).second=docid_count[i];
		check=search_results.begin();
		for(auto IT =++search_results.begin();IT!=search_results.end();IT++){
			if((*IT).second<=(*check).second){check=IT;}
		}
	}
	docid_count[i]=0;
	}

sort(
     begin(search_results),
     end(search_results),
     [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
       int64_t lhs_docid = lhs.first;
       auto lhs_hit_count = lhs.second;
       int64_t rhs_docid = rhs.first;
       auto rhs_hit_count = rhs.second;
       return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
     }
   );


    search_results_output << current_query << ':';
    for (auto [docid, hitcount] : search_results) {
      search_results_output << " {"
        << "docid: " << docid << ", "
        << "hitcount: " << hitcount << '}';
    }
    search_results_output << endl;
  }
 *
 *
 */
