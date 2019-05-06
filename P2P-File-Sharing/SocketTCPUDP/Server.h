#ifndef SERVER
#define SERVER

#define NUM_NODES 10

struct entry {
	int id;
	char * filename;
};

struct entry entries[NUM_NODES];
int entry_count = 0;

struct entry createEntry(int ID, char * filename){
	struct entry newEntry;
	newEntry.id = ID;
	newEntry.filename = filename;
	return newEntry;
}

int saveEntry(char * filename){
	int x = entry_count;
	entries[entry_count] = createEntry(entry_count, filename);
	entry_count++;
	return x;
}


int max(int x, int y) 
{ 
	if (x > y) 
		return x; 
	else
		return y; 
} 

#endif