#include "MyExampleInterface_impl.h"
#include <iostream>
#include <string>

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
	// questions.erase(input);
	cout << "Question at index: " << input << " deleted."<<endl;
}

char * MyExampleInterface_impl::displayAllQuestions()
{
	// Sample Questions
	questions.push_back("Hello1");
	questions.push_back("Hello2");
	questions.push_back("Hello3");
	// Sample Answers
	answers.push_back("Hey1");
	answers.push_back("Hey2");
	answers.push_back("Hey3");

	// Initialize response message
	string response = "\n";

	// Iterate through questions/answers vectors and append to response message
	for(int i = 0; i<questions.size();i++){
		response += "Q" + to_string(i) + ": " + questions[i] + "\nA" + to_string(i) + ": " + answers[i] + "\n\n";
	}

	// Construct CORBA friendly return message
	char * server = CORBA::string_alloc(1024);
	// Convert response to (char *) and set to server
	strncpy(server, response.c_str(), 1024); 

	return server;
}

void MyExampleInterface_impl::displayAll()
{
	for(int i = 0; i<questions.size();i++){
		cout << "Question " << i << ": " << questions[i]<< endl;
		cout << "Answer " << i << ": " << answers[i]<< endl;
	}
}

