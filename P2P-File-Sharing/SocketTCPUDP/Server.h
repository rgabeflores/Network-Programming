#ifndef SERVER
#define SERVER

#include <string.h>

#define NUM_NODES 10

struct request{
	int type;
	char * filename;
};

struct entry {
	int id;
	char * filename;
};

struct entry entries[NUM_NODES];
int entry_count = 0;

/**
	Creates a new entry with the given filename and ID.
*/
struct entry createEntry(int ID, char * filename){
	struct entry newEntry;
	char * s;
	strcpy(s, filename);
	newEntry.id = ID;
	newEntry.filename = s;
	return newEntry;
}

/**
	Saves a new entry with the given filename.
*/
int saveEntry(char * filename){
	int x = entry_count;
	entries[entry_count] = createEntry(entry_count, filename);
	entry_count++;
	return x;
}

/**
	Returns the ID of the node with the filename. Returns -1 if filename not found.
*/
int findEntry(char * filename){
	for(int i = 0; i < entry_count; i++){
		if(strcmp(filename, entries[i].filename) == 0){
			return i;
		}
	}
	return -1;
}

/**
	Parses requests and returns a 0 if it's a registration request and 1 if it's a file request.
*/
int parseRequest(char * message){

	char s[1024];
	char seps[] = ",";
	char* token;
	char* values[2];

	int i = 0;
	strcpy(s, message);

	token = strtok (s, seps);
	while (token != NULL)
	{
		values[i++] = token;
	    token = strtok (NULL, seps);
	}
	
	if(strcmp(values[0], "0") == 0){
		// 0 indicates registration request
		return 0;
	}
	else if (strcmp(values[0], "1") == 0){
		// 1 indicates file request
		return 1;
	}

	// -1 indicates bad request
	return -1;
}

char * getFileRequested(char * message){
	char s[1024];
	char seps[] = ",";
	char* token;
	char* values[2];
	strcpy(s, message);

	int i = 0;
	token = strtok(s, seps);
	while (token != NULL)
	{
		values[i++] = token;
	    token = strtok(NULL, seps);
	}
	return values[1];
}

/**
	Get the max of two integers.
*/
int max(int x, int y) 
{ 
	if (x > y) 
		return x; 
	else
		return y; 
} 

#endif