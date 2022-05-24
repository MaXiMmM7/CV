#include "test_runner.h"
#include <iterator>
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	size_t N=range_end - range_begin;
	if(N<2){return;}
	vector<typename RandomIt::value_type> v(
			make_move_iterator(range_begin),make_move_iterator(range_end));

	MergeSort(v.begin(),v.begin()+N/3);
	MergeSort(v.begin()+N/3,v.begin()+2*N/3);
	MergeSort(v.begin()+2*N/3,v.end());

	vector<typename RandomIt::value_type> vv;
	merge(make_move_iterator(v.begin()),make_move_iterator(v.begin()+N/3),
			make_move_iterator(v.begin()+N/3),make_move_iterator(v.begin()+2*N/3),
			back_inserter(vv));
	merge(make_move_iterator(vv.begin()),make_move_iterator(vv.end()),
			make_move_iterator(v.begin()+2*N/3),make_move_iterator(v.end()),
			range_begin);
	//move(vvv.begin(),vvv.end(),range_begin);
/*
 * vector<typename RandomIt::value_type> elements(range_begin, range_end);

	MergeSort(elements.begin(),elements.begin()+(elements.end()-elements.begin())/3);
	MergeSort(elements.begin()+(elements.end()-elements.begin())/3,elements.begin()+2*(elements.end()-elements.begin())/3);
	MergeSort(elements.begin()+2*(elements.end()-elements.begin())/3,elements.end());
	vector<typename RandomIt::value_type> helper;
	merge(elements.begin(),elements.begin()+(elements.end()-elements.begin())/3,
			elements.begin()+(elements.end()-elements.begin())/3,elements.begin()+2*(elements.end()-elements.begin())/3,
			back_inserter(helper));
	merge(helper.begin(),helper.end(),elements.begin()+2*(elements.end()-elements.begin())/3,elements.end(),
			range_begin);
 */
  // Напишите реализацию функции,
  // не копируя сортируемые элементы
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
