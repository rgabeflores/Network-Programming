#ifndef SERVER
#define SERVER

#include <string.h>

#define NUM_NODES 10

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
	newEntry.id = ID;
	newEntry.filename = filename;
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


int max(int x, int y) 
{ 
	if (x > y) 
		return x; 
	else
		return y; 
} 

#endif