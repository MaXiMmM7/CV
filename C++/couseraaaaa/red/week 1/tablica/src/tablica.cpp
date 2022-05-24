#include "test_runner.h"
#include <vector>
#include <utility>

using namespace std;



template <typename T>
class Table{
public:

	Table(const size_t& line, const size_t& column){
		if(line==0||column==0){
			return;
		}
		table.resize(line);
						for(auto It=begin(table);It!=end(table);It++){
							It->resize(column);
						}
	}

	void Resize(const size_t& line, const size_t& column){
		if(line==0||column==0){
			table.clear();
					return;
				}
		table.resize(line);
				for(auto It=begin(table);It!=end(table);It++){
					It->resize(column);
				}
	}

	pair<size_t,size_t> Size()const {
		if(!table.empty()){
			return make_pair(table.size(),table[0].size());
		}
		return make_pair(0,0);
	}

	vector<T>& operator[](const size_t& i){
		return table[i];
	}

	const vector<T>& operator[](const size_t& i)const {
			return table[i];
		}
private:
	vector<vector<T>> table;
};
// Реализуйте здесь шаблонный класс Table
/*
 * Вам надо написать шаблонный класс Table для электронной таблицы.
 *  Для простоты будем считать, что все ячейки таблицы имеют один и
 *   тот же тип данных T. Таблица должна уметь менять свой размер п
 *   о требованию пользователя. Вновь созданные ячейки должны заполняться
 *   значениями по умолчанию типа T.

Требования к классу такие:

    Класс должен называться Table.
    У класса должен быть шаблонный параметр T — тип элемента в ячейке.
    У класса должен быть конструктор, получающий на входе два числа типа
     size_t — количество строк и столбцов соответственно.
    У класса должны быть константная и неконстантная версии оператора [],
    возвращающего нечто такое, к чему снова можно было бы применить оператор [].
    То есть, должны работать конструкции вида cout << table[i][j];и table[i][j] = value;.
     Проверять корректность индексов при этом не нужно.
    У класса должна быть функция Resize, получающая на вход два параметра типа size_t и
     меняющая размер таблицы. Старые данные, умещающиеся в новый размер, должны при этом
      сохраниться.
    У класса должна быть константная функция Size, возвращающая pair<size_t, size_t> —
     размер таблицы (в том же порядке, в котором эти аргументы передавались в конструктор).
     При этом, если у таблицы Table один из размеров нулевой, то необходимо считать таковым
     и второй размер таблицы.
 */
void TestTable() {
  {Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
  }
  /*
  {Table<int> t(1, 0);
  ASSERT_EQUAL(t.Size(),make_pair(0u,0u));
  }
  {Table<int> t(0, 1);
  ASSERT_EQUAL(t.Size(),make_pair(0u,0u));
   }
  {Table<int> t(0, 0);
  ASSERT_EQUAL(t.Size(),make_pair(0u,0u));
    }*/
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
