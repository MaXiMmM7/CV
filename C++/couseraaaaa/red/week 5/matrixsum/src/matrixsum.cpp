#include "test_runner.h"
#include "profile.h"
#include <algorithm>
#include <cstdint>
#include <vector>
#include <future>
using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
    , size_(distance(first, last))
  {
  }

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

  size_t size() const {
    return size_;
  }

private:
  Iterator first, last;
  size_t size_;
};

template <typename Iterator>
class Paginator {
private:
  vector<IteratorRange<Iterator>> pages;

public:
  Paginator(Iterator begin, Iterator end, size_t page_size) {
    for (size_t left = distance(begin, end); left > 0; ) {
      size_t current_page_size = min(page_size, left);
      Iterator current_page_end = next(begin, current_page_size);
      pages.push_back({begin, current_page_end});

      left -= current_page_size;
      begin = current_page_end;
    }
  }

  auto begin() const {
    return pages.begin();
  }

  auto end() const {
    return pages.end();
  }

  size_t size() const {
    return pages.size();
  }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator(begin(c), end(c), page_size);
}

template <typename ContainerOfVectors>
int64_t SumSingleThread(const ContainerOfVectors& matrix) {
  int64_t sum = 0;
  for (const auto& row : matrix) {
    for (auto item : row) {
      sum += item;
    }
  }
  return sum;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
  vector<future<int64_t>> futures;
  for (auto page : Paginate(matrix, 2000)) {
    futures.push_back(async([=] { return SumSingleThread(page); }));
  }
  int64_t result = 0;
  for (auto& f : futures) {
    result += f.get();
  }
  return result;
}


/*
 * #include "test_runner.h"
#include "profile.h"
//#include <numeric>
#include <vector>
#include <algorithm>
#include <future>
using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
    , size_(distance(first, last))
  {
  }

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

  size_t size() const {
    return size_;
  }

private:
  Iterator first, last;
  size_t size_;
};

template <typename Iterator>
class Paginator {
private:
  vector<IteratorRange<Iterator>> pages;

public:
  Paginator(Iterator begin, Iterator end, size_t page_size) {
    for (size_t left = distance(begin, end); left > 0; ) {
      size_t current_page_size = min(page_size, left);
      Iterator current_page_end = next(begin, current_page_size);
      pages.push_back({begin, current_page_end});

      left -= current_page_size;
      begin = current_page_end;
    }
  }

  auto begin() const {
    return pages.begin();
  }

  auto end() const {
    return pages.end();
  }

  size_t size() const {
    return pages.size();
  }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator(begin(c), end(c), page_size);
}

//////////////////////////////////////////////////
////////////////////////////////////////////////////
//////////////////////////////////////////////////




template <typename T>
int64_t CalculateOneThread(const T& matrix){
	int64_t sum=0;
	for(auto& x: matrix){
		//sum=accumulate(x.begin(),x.end(),sum);
	for(auto c:x){
		sum+=c;
	}
	}
	return sum;
}



int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
	LOG_DURATION("MatrixSum");
	int64_t sum=0;
	vector<future<int64_t>> f;
	for(auto& page: Paginate(matrix,matrix.size()/4)){
		f.push_back(async([page] { return CalculateOneThread(page); } ));
	}
	for(auto& x: f){
				sum+=x.get();
			}
	return sum;
}
*/

//////////////////////////////////
/*
int64_t CalculateMatrixUnarySum(const vector<vector<int>>& matrix) {
	LOG_DURATION("MatrixSum");
	int64_t sum=0;
	for(auto& x: matrix){
		sum = accumulate(x.begin(),x.end(),sum);
	}
	return sum;
  // Реализуйте эту функцию
}
*/




void TestCalculateMatrixSum() {

  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);

}

void TestOneThreadMatrixSum(){
	vector<vector<int>> matrix;
	matrix.resize(9000);
	for(auto& x: matrix){
		x.reserve(9000);
	}

	int64_t check=0;
	for(auto& x: matrix){
	for(int i=0; i<9000;i++){
        x.push_back(i);
     	check+=i;
	}
	}

	//ASSERT_EQUAL(CalculateMatrixUnarySum(matrix), check);//unary
cerr << "next" << endl;
	ASSERT_EQUAL(CalculateMatrixSum(matrix), check);//multi
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
  RUN_TEST(tr, TestOneThreadMatrixSum);
return 0;
}
