#include "test_runner.h"

#include "profile.h"
#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <utility>
#include <list>
#include <array>

using namespace std;

//step 2 ; 1 2 3 4 5 6 7 8 9 10  //1 3 5 7 9 2 6 8 4 10

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {


  list<typename RandomIt::value_type> pool;
  auto It=first;
  while(It!=last){ //N
	  pool.push_back(move(*It));
	  It++;
  }

  auto It1=begin(pool);
  size_t size_;
  while (!pool.empty()) {
    *(first++) = move(*It1);
    pool.erase(It1++);
    size_=pool.size();
    if (size_==0) {
      break;
    }
    if(It1==end(pool)){
        		It1=begin(pool);
        	}

    for(size_t i=1;i<step_size;i++){//3
    	It1++;
    	if(It1==end(pool)){
    		It1=begin(pool);
    	}
    }

  }
}

vector<int> MakeTestVector() {
  vector<int> numbers(10);
  iota(begin(numbers), end(numbers), 0);
  return numbers;
}

void TestIntVector() {
  const vector<int> numbers = MakeTestVector();
  {
    vector<int> numbers_copy = numbers;
    MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
    ASSERT_EQUAL(numbers_copy, numbers);
  }
  {
    vector<int> numbers_copy = numbers;// 0 3 6 9 4 8 5 2 7 1
    MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
    ASSERT_EQUAL(numbers_copy, vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
  }
}

// Это специальный тип, который поможет вам убедиться, что ваша реализация
// функции MakeJosephusPermutation не выполняет копирование объектов.
// Сейчас вы, возможно, не понимаете как он устроен, однако мы расскажем,
// почему он устроен именно так, далее в блоке про move-семантику —
// в видео «Некопируемые типы»

struct NoncopyableInt {
  int value;

  NoncopyableInt(const NoncopyableInt&) = delete;
  NoncopyableInt& operator=(const NoncopyableInt&) = delete;

  NoncopyableInt(NoncopyableInt&&) = default;
  NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

bool operator == (const NoncopyableInt& lhs, const NoncopyableInt& rhs) {
  return lhs.value == rhs.value;
}

ostream& operator << (ostream& os, const NoncopyableInt& v) {
  return os << v.value;
}

void TestAvoidsCopying() {
  vector<NoncopyableInt> numbers;
  numbers.push_back({1});
  numbers.push_back({2});
  numbers.push_back({3});
  numbers.push_back({4});
  numbers.push_back({5});

  MakeJosephusPermutation(begin(numbers), end(numbers), 2);

  vector<NoncopyableInt> expected;
  expected.push_back({1});
  expected.push_back({3});
  expected.push_back({5});
  expected.push_back({4});
  expected.push_back({2});

  ASSERT_EQUAL(numbers, expected);
}

void TimeTest() {
   vector<int> numbers;
  for (int i=0;i<100000;i++){
	  numbers.push_back(i);
  }

  LOG_DURATION("TimeTest");
    MakeJosephusPermutation(begin(numbers), end(numbers), 100);

}

int main() {

  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  RUN_TEST(tr, TestAvoidsCopying);
  RUN_TEST(tr, TimeTest);
  /*
	vector <int> v={0,1,2};
	auto It=v.begin();
    *(++It) = 6;
    cout << v[0] << "  " << *It << endl;*/
  return 0;
}
