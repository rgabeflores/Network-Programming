#include "MyExampleInterface_impl.h"
#include <iostream>

using namespace std;

char * MyExampleInterface_impl::send_message(const char * message)
{
	cout << "C++ (omniORB) server: " << message << endl;
	char * server = CORBA::string_alloc(42);
	strncpy(server, "Message from C++ (omniORB) server", 42);
	return server;
}

char * MyExampleInterface_impl::newQuestion(const char * question,const char * answer)
{
	cout << "C++ (omniORB) server: " << "Enter a question" << endl;
	char * server = CORBA::string_alloc(42);
	strncpy(server, question, 42);
	return server;
}

char * MyExampleInterface_impl::askQuestion()
{
	cout << "C++ (omniORB) server: " << "Enter a question" << endl;
	

}

void MyExampleInterface_impl::removeQuestion()
{
	int input = 0;
	displayAllQuestions();
	cout << "Enter the question number of the question to remove" << endl;
	cin>>input;
	input = input - 1;
	questions.erase(input);
	cout << "Question at index: " << input << " deleted."<<endl;
}

void MyExampleInterface_impl::displayAllQuestions()
{
	for(int i = 0; i<questions.size();i++){
		cout << "Question " << i << ": " << questions[i]<< endl;
	}
}

void MyExampleInterface_impl::displayAll()
{
	for(int i = 0; i<questions.size();i++){
		cout << "Question " << i << ": " << questions[i]<< endl;
		cout << "Answer " << i << ": " << answers[i]<< endl;
	}
}

