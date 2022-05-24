//============================================================================
// Name        : otpravkauvedomleniy.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
using namespace std;

void SendSms(const string& number, const string& message) {
  cout << "Send '" << message << "' to number " << number << endl;
}

void SendEmail(const string& email, const string& message) {
  cout << "Send '" << message << "' to e-mail "  << email << endl;
}

/*
 Реализуйте здесь классы INotifier, SmsNotifier, EmailNotifier
 */


class INotifier{
public:
	virtual void Notify(const string& message)=0;
};

class SmsNotifier:public INotifier{
public:
	SmsNotifier(const string& number){
		PhoneNumber=number;
	}
	void Notify(const string& message) override{
		SendSms(PhoneNumber,message);
	}
protected:
	string PhoneNumber;
};

class EmailNotifier:public INotifier{
public:
	EmailNotifier(const string& adress){
		Email=adress;
	}
	void Notify(const string& message) override{
		SendEmail(Email,message);
	}
protected:
	string Email;
};
/*
Send 'I have White belt in C++' to number +7-495-777-77-77
Send 'And want a Yellow one' to e-mail na-derevnyu@dedushke.ru
*/
void Notify(INotifier& notifier, const string& message) {
  notifier.Notify(message);
}


int main() {
  SmsNotifier sms{"+7-495-777-77-77"};
  EmailNotifier email{"na-derevnyu@dedushke.ru"};

  Notify(sms, "I have White belt in C++");
  Notify(email, "And want a Yellow one");
  return 0;
}
