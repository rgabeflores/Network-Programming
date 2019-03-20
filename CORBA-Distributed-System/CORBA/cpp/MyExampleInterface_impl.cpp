#include "MyExampleInterface_impl.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

// ==================================================================================
// These functions are defined for the server to execute when called by the client.
// ==================================================================================


const int RESPONSE_BUFFER_SIZE = 1024;

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
	const char * response = "There are no questions saved."; // Default response

	// Ensure there are questions saved
	int size = questions.size();
	if(size > 0){
		// Generate random integer for index
		int i = rand() % size;

		// Access item and assign to response
		response = questions[i].c_str();
	}

	// Response message to client
	char * server = CORBA::string_alloc(RESPONSE_BUFFER_SIZE);
	strncpy(server, response, RESPONSE_BUFFER_SIZE);
	return server;
}

/**
	Checks the answer to the question.
*/
char * MyExampleInterface_impl::answerQuestion(const char * question, const char * answer)
{
	string response = "An entry could not be found."; // Default response

	// Loop through each vector to compare to the correct question/answer pair
	string targetQ = string(question), targetA = string(answer);
	int i, size = questions.size();
	for(i = 0; i < size; i++){
		if(questions[i] == targetQ){
			if(answers[i] == targetA){
				response = "Correct!";
			}
			else{
				response = "Incorrect...";
			}
		}
	}

	// Response message to client
	char * server = CORBA::string_alloc(RESPONSE_BUFFER_SIZE);
	strncpy(server, response.c_str(), RESPONSE_BUFFER_SIZE);
	return server;
}

/**
	Removes a specified question.
*/
char * MyExampleInterface_impl::removeQuestion(short index)
{
	string response = "There weren't that many questions..."; // Default response

	if(index < questions.size() && index < answers.size()){
		questions.erase(questions.begin() + index);
		answers.erase(answers.begin() + index);
		response = "Question " + to_string(index) + " removed.";
	}

	// Response message to client
	char * server = CORBA::string_alloc(RESPONSE_BUFFER_SIZE);
	strncpy(server, response.c_str(), RESPONSE_BUFFER_SIZE);
	return server;
}

/**
	Displays the list of questions and answers
*/
char * MyExampleInterface_impl::displayAllQuestions()
{

	// Initialize response message
	string response = "\nAvailable Questions:\n";

	// Check size of questions
	int i, size = questions.size();
	if(size > 0){
		// Iterate through questions/answers vectors and append to response message
		for(i = 0; i < size; i++){
			response += "Q" + to_string(i) + ": " + questions[i] + "\nA" + to_string(i) + ": " + answers[i] + "\n\n";
		}
	}

	// Construct CORBA friendly return message
	char * server = CORBA::string_alloc(RESPONSE_BUFFER_SIZE);
	// Convert response to (char *) and set to server
	strncpy(server, response.c_str(), RESPONSE_BUFFER_SIZE); 

	return server;
}

