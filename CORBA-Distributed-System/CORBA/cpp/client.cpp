#include "example.hh"
#include <iostream>
#include <string>
#include <CORBA.h>
#include <Naming.hh>

/** Name is defined in the server.cpp */
#define SERVER_NAME		"MyServerName"
#define NUM_QUESTIONS 3

using namespace std;


/**
	Displays response from server with formatting.
*/
void displayResponse(const char * message){
	cout << "Response from Server: " << message;
	cout << endl;
}

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

			// Holds responses from server
			char * server;

			// Question Generation
			string question, answer;
			int i;
			for(i = 0; i < NUM_QUESTIONS; i++){
				cout << "Enter a question: " << endl;
				getline(cin, question);
				cout << "Enter the answer: " << endl;
				getline(cin, answer);

				cout << endl;
				cout << "Sending to server..." << endl;
				// Question submission through CORBA/IDL name service
				server = service_server->newQuestion(question.c_str(), answer.c_str());
				displayResponse(server);
				cout << endl;
			}

			// Display user options
			int choice = 1;
			while(choice >= 1 && choice <= 3){
				cout << endl;
				cout << "Please choose from menu items:" << endl;
				cout << "1. Ask me a question" << endl;
				cout << "2. Remove a question" << endl;
				cout << "3. Exit" << endl;
				cin >> choice;

				// Clear cin buffer
				cin.clear();
				cin.ignore(INT_MAX, '\n');

				if(choice == 1){
					// Get a question
					server = service_server->getRandomQuestion();

					// Get answer from user
					string answer;
					cout << endl;
					cout << "Q: " << server << endl;				
					cout << "A: ";
					getline(cin, answer);
				
					// Submit answer through CORBA/IDL name service
					server = service_server->answerQuestion(server, answer.c_str());
					displayResponse(server);
					cout << endl << endl;
				}
				else if (choice == 2){
					
					server = service_server->displayAllQuestions();
					displayResponse(server);
					
					// Get index of question to remove from user
					int n;
					cout << "Enter the number of the question to remove: ";
					cin >> n;

					// Clear cin buffer
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					
					// Request removal of question through CORBA/IDL name service
					server = service_server->removeQuestion(n);
					displayResponse(server);
				}
				else if(choice == 3){
					cout << endl;
					cout << "Exiting..." << endl;
					cout << endl;
					break;
				}
				else{
					cout << endl;
					cout << "Invalid choice..." << endl;
					choice = 1;
				}
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