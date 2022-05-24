#include <string>
#include <vector>
using namespace std;


#define h(a) variable_##a
#define g(a) h(a)
#define UNIQ_ID g(__LINE__)

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
}
