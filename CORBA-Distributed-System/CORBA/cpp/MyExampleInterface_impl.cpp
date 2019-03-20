#include "MyExampleInterface_impl.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

// ============================================================================================
// These functions are defined for the server to execute when called by the client.
// ============================================================================================


/**
	Sends a message
*/
char * MyExampleInterface_impl::send_message(const char * message)
{
	cout << "C++ (omniORB) server: " << message << endl;

	char * server = CORBA::string_alloc(42);
	strncpy(server, "Message from C++ (omniORB) server", 42);
	return server;
}

/**
	Adds a new question
*/
char * MyExampleInterface_impl::newQuestion(const char * question, const char * answer)
{

	cout << "C++ (omniORB) server: " << "Saving a new question and answer..." << endl;
	questions.push_back(string(question)); // Convert question to string and push to vector
	answers.push_back(string(answer)); // Convert answer to string and push to vector
	cout << "C++ (omniORB) server: " << "Done." << endl;

	// Response message to client
	char * server = CORBA::string_alloc(44);
	strncpy(server, "Question and answer were successfully added.", 44);
	return server;
}

/**
	Retrieves a random question
*/
char * MyExampleInterface_impl::getRandomQuestion()
{
	// Generate random integer for index
	int i = rand() % questions.size();

	// Access item and assign to response
	const char * question = questions[i].c_str();

	// Response message to client
	char * server = CORBA::string_alloc(1024);
	strncpy(server, question, 1024);
	return server;
}

char * MyExampleInterface_impl::answerQuestion(const char * answer)
{
	cout << "C++ (omniORB) server: " << "Enter a question" << endl;
}

/**
	
*/
char * MyExampleInterface_impl::removeQuestion(short index)
{
	questions.erase(questions.begin() + index - 1);
	string response = "Question " + to_string(index) + " removed.";

	// Response message to client
	char * server = CORBA::string_alloc(1024);
	strncpy(server, response.c_str(), 1024);
	return server;
}

char * MyExampleInterface_impl::displayAllQuestions()
{

	// Initialize response message
	string response = "\n";

	// Iterate through questions/answers vectors and append to response message
	int i;
	for(i = 0; i < questions.size();i++){
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

