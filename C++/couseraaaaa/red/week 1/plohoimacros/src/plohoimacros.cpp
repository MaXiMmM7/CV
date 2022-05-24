#include "test_runner.h"

#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y) out << (x) << endl << (y) << endl

int main() {
  TestRunner tr;
  tr.RunTest([] {
    ostringstream output;
    PRINT_VALUES(output, 5, "red belt");
    ASSERT_EQUAL(output.str(), "5\nred belt\n");
  }, "PRINT_VALUES usage example1");

  tr.RunTest([] {
      ostringstream output;
      PRINT_VALUES(output << "hey", 5, "red belt");
      ASSERT_EQUAL(output.str(), "hey5\nred belt\n");
    }, "PRINT_VALUES usage example2");

  tr.RunTest([] {
        ostringstream output;
        PRINT_VALUES(output, 5+10, "red belt");
        ASSERT_EQUAL(output.str(), "15\nred belt\n");
      }, "PRINT_VALUES usage example3");

  tr.RunTest([] {
          ostringstream output;
          PRINT_VALUES(output, 5+10, "");
          PRINT_VALUES(output, 5+10, "");
          ASSERT_EQUAL(output.str(), "15\n\n15\n\n");
        }, "PRINT_VALUES usage example4");

}
