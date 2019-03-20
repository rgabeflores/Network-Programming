#ifndef __SERVANT_H__
#define __SERVANT_H__

#include "example.hh"
#include <string>

#define NUM_QUESTIONS 3

using namespace std;

class Servant : public POA_Servant
{
	public:
		string questions[NUM_QUESTIONS];
		virtual char * send_message(const char * message);
};

#endif // __SERVANT_H__