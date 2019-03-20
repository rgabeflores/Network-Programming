#include "Servant.h"
#include <iostream>
#include <string>

using namespace std;

/**
	Servant
	Use this file to carry out service operations and processes on the server.

	* Need to add to makefile
*/


char * Servant::send_message(const char * message)
{
	// Print message from client
	cout << "C++ (omniORB) server: " << message << endl;

	// Send message back to client
	char * server = CORBA::string_alloc(42);
	strncpy(server, "Message from C++ (omniORB) server, test", 42);
	return server;
}
