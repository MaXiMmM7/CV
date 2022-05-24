//============================================================================
// Name        : rabotassrverom.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <exception>
#include <string>
using namespace std;

string AskTimeServer() {
    /* ƒл€ тестировани€ повставл€йте сюда код, реализующий различное поведение этой функии:
       * нормальный возврат строкового значени€
       * выброс исключени€ system_error
       * выброс другого исключени€ с сообщением.
    */
	throw exception();
	return "00:30:45";
}

class TimeServer {
public:

    string GetCurrentTime() {
    	try{
    	last_fetched_time=AskTimeServer();
    	return last_fetched_time;
    	}catch(system_error& ex){
    		 return last_fetched_time;
    		}
    }

private:
    string last_fetched_time = "00:00:00";
};

int main() {
    // ћен€€ реализацию функции AskTimeServer, убедитесь, что это код работает корректно
    TimeServer ts;
    try {
        cout << ts.GetCurrentTime() << endl;
    } catch (exception& e) {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}
