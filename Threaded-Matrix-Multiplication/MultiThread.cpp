#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

using namespace std;

#include "../Utilities/Utils.h"
#include "../Utilities/Scanner.h"
#include "../Utilities/ScanLine.h"

#define NUM_THREADS 9

pthread_t threads[NUM_THREADS];

// Global Matrices
int matrixA[3][3];
int matrixB[3][3];
int result[3][3];

/*
	
	Matrix Multiplication

	a00, a01, a02     b00, b01, b02     (a00b00 + a01b10 + a02b20), (a00b01 + a01b11 + a02b21), (a00b02 + a01b12 + a02b22)
	a10, a11, a12  x  b10, b11, b12  =  (a10b00 + a11b10 + a12b20), (a10b01 + a11b11 + a12b21), (a10b02 + a11b12 + a12b22)
	a20, a21, a22     b20, b21, b22     (a20b00 + a21b10 + a22b20), (a20b01 + a21b11 + a22b21), (a20b02 + a21b12 + a22b22)

*/

struct arg_struct{
	int arg1;
	int arg2;
};

/*
	Computes the value of multiplying two matrices 
*/
void *matrix_mult(void *arguments) {
	int x, y;
	struct arg_struct *args = (struct arg_struct *) arguments;
	
	x = args->arg1;
	y = args->arg2;

	// Initialize value in result
	result[x][y] = 0;

	int i;
	for(i = 0; i < 3; i++){
   		result[x][y] += matrixA[x][i] * matrixB[i][y];
	}

	pthread_exit(NULL);
}

/*
	This function reads the input from files given to fill the values of each matrix.
*/
void *fillMatrices(int argc, char *argv[]){
	
	string inFileName1 = "";
  	string inFileName2 = "";
  	ofstream outStream;
 
	Scanner scanner1;
	Scanner scanner2;  

	string element1 = "";
	string element2 = "";
	int int1;
	int int2;
 
	Utils::CheckArgs(2, argc, argv, "infilename (first matrix) outfilename (second matrix)");
	inFileName1 = static_cast<string>(argv[1]);
	inFileName2 = static_cast<string>(argv[2]);

	scanner1.openFile(inFileName1);
	scanner2.openFile(inFileName2);  
  
	int i;
	int j;

	i = 0;
	j = 0;

	while (scanner1.hasNext() && scanner2.hasNext()) {

		element1 = scanner1.next();
		element2 = scanner2.next();
		int1 = atoi(element1.c_str());
		int2 = atoi(element2.c_str());

		matrixA[i][j] = int1;
		matrixB[i][j] = int2;
		
		// Counters to maintain positions in matrices
		j++;
		if(j >= 3){
			j = 0;
			i++;
		}
	}
}

/*
	Creates the threads for the matrix_mult function.
*/
void *createThreads(){
	// args is an args_struct that is used to pass multiple arguments to 
	// the target function of a thread i.e. (x,y) matrix indices 
	struct arg_struct args;

	int i;
	int j;

	int rc;
	
	// Nested for loop to keep track of indices
	for( i = 0; i < 3; i++ ) {
		for (j = 0; j < 3; j++){

			args.arg1 = i;
			args.arg2 = j;

			rc = pthread_create(&threads[i], NULL, matrix_mult, (void *) &args);

			if (rc) {
				cout << "Error:unable to create thread," << rc << endl;
				exit(-1);
			}
			sleep(1);
		}
	}
}

/*
	Prints the results to standard out.
*/
void *displayResult(){
	int i;
	int j;

    for( i = 0; i < 3; i++ ) {
		for (j = 0; j < 3; j++){

			cout << result[i][j] << " ";
		}
		cout << endl;
	}
}

int main (int argc, char *argv[]) {
	

	fillMatrices(argc, argv);
    
	createThreads();
    	
	displayResult();
    
	pthread_exit(NULL);

	return 0;
}






















