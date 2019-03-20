#ifndef __MY_EXAMPLE_INTERFACE_IMPL_H__
#define __MY_EXAMPLE_INTERFACE_IMPL_H__

#include "example.hh"
#include <string>
#include <vector>

using namespace std;

class MyExampleInterface_impl : public POA_ExampleInterface
{
	public:
		vector<string> questions;
		vector<string> answers;
		virtual char * send_message(const char * message);
		virtual char * newQuestion(const char * question, const char * answer);
		virtual char * getRandomQuestion();
		virtual char * answerQuestion(const char * question, const char * answer);
		virtual char * removeQuestion(short index);
		virtual char * displayAllQuestions();	
};

#endif // __MY_EXAMPLE_INTERFACE_IMPL_H__
