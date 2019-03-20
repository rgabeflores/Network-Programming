#ifndef __MY_EXAMPLE_INTERFACE_IMPL_H__
#define __MY_EXAMPLE_INTERFACE_IMPL_H__

#include "example.hh"
#include <string.h>
#include <vector>


class MyExampleInterface_impl : public POA_ExampleInterface
{
	public:
		vector<string> questions;
		vector<string> answers;
		virtual char * send_message(const char * message);
		virtual char * newQuestion(const char * question,const char * answer);
		virtual void displayAllQuestions();		
		virtual void displayAll();
};

#endif // __MY_EXAMPLE_INTERFACE_IMPL_H__
