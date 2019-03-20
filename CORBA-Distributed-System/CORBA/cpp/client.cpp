#include "example.hh"
#include <iostream>
#include <string>
#include <CORBA.h>
#include <Naming.hh>

/** Name is defined in the server.cpp */
#define SERVER_NAME		"MyServerName"
#define NUM_QUESTIONS 3

using namespace std;

int main(int argc, char ** argv)
{
	try {
		//------------------------------------------------------------------------
		// Initialize ORB object.
		//------------------------------------------------------------------------
		CORBA::ORB_ptr orb = CORBA::ORB_init(argc, argv);

		//------------------------------------------------------------------------
		// Resolve service
		//------------------------------------------------------------------------
		ExampleInterface_ptr service_server = 0;

		try {

			//------------------------------------------------------------------------
			// Bind ORB object to name service object.
			// (Reference to Name service root context.)
			//------------------------------------------------------------------------
			CORBA::Object_var ns_obj = orb->resolve_initial_references("NameService");

			if (!CORBA::is_nil(ns_obj)) {
				//------------------------------------------------------------------------
				// Bind ORB object to name service object.
				// (Reference to Name service root context.)
				//------------------------------------------------------------------------
				CosNaming::NamingContext_ptr nc = CosNaming::NamingContext::_narrow(ns_obj);
				
				//------------------------------------------------------------------------
				// The "name text" put forth by CORBA server in name service.
				// This same name ("MyServerName") is used by the CORBA server when
				// binding to the name server (CosNaming::Name).
				//------------------------------------------------------------------------
				CosNaming::Name name;
				name.length(1);
				name[0].id = CORBA::string_dup(SERVER_NAME);
				name[0].kind = CORBA::string_dup("");

				//------------------------------------------------------------------------
				// Resolve "name text" identifier to an object reference.
				//------------------------------------------------------------------------
				CORBA::Object_ptr obj = nc->resolve(name);

				if (!CORBA::is_nil(obj)) {
					service_server = ExampleInterface::_narrow(obj);
				}
			}
		} catch (CosNaming::NamingContext::NotFound &) {
			cerr << "Caught corba not found" << endl;
		} catch (CosNaming::NamingContext::InvalidName &) {
			cerr << "Caught corba invalid name" << endl;
		} catch (CosNaming::NamingContext::CannotProceed &) {
			cerr << "Caught corba cannot proceed" << endl;
		}

		//------------------------------------------------------------------------
		// Do stuff
		//------------------------------------------------------------------------

		if (!CORBA::is_nil(service_server)) {
			string DISPLAY_RESPONSE = "Response from Server:\n";

			// Holds responses from server
			char * server;




			string q, a;
			int i;
			for(i = 0; i < NUM_QUESTIONS; i++){
				
				cout << "Enter a question: " << endl;
				getline(cin, q);
				cout << "Enter the answer: " << endl;
				getline(cin, a);

				const char * question = q.c_str();
				const char * answer = a.c_str();

				server = service_server->newQuestion(question, answer);
				cout << DISPLAY_RESPONSE << server << endl;

			}


			int choice = -1;
			while(!(choice >= 1 && choice <= 3)){
				cout << endl;
				cout << "Please choose from menu items:" << endl;
				cout << "1. Ask me a question" << endl;
				cout << "2. Remove a question" << endl;
				cout << "3. Exit" << endl;
				cin >> choice;
				cin.clear();
				cin.ignore(100, '\n');
			}


			if(choice == 1){
				// Get a question
				server = service_server->getRandomQuestion();
				cout << DISPLAY_RESPONSE << server << endl;

				// Get answer
				string answer;
				cout << "What is your answer?" << endl;
				getline(cin, answer);
				server = service_server->answerQuestion(server, answer.c_str());
				cout << DISPLAY_RESPONSE << server << endl;
			}
			else if (choice == 2){
				int n;

				cout << "Enter the number of the question to remove:" << endl;
				cin >> n;
				
				server = service_server->removeQuestion(n);
				cout << DISPLAY_RESPONSE << server << endl;

			}
			else{
			}

			CORBA::string_free(server);
		}




















		//------------------------------------------------------------------------
		// Destroy OBR
   		//------------------------------------------------------------------------
		orb->destroy();

	} catch (CORBA::UNKNOWN) {
		cerr << "Caught CORBA exception: unknown exception" << endl;
	}
}