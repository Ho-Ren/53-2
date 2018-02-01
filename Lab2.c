#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fillArray(FILE *processFile, char *emptyArray[]);
void viewArray(char *filledArray[], int numOfElems);
void convertToInts(char *numberStrs[], int numOfStr, int numberInts[]);
void viewIntArray(int filledArray[], int numOfInts);

/*
 * Specification Changes/Updates from updated PDF
 * - no mention of returning -1 or error message when array file contains more than 10 numbers
 * - array file will supposedly always be valid (never more than 10 numbers & no characters)
 * - no error messages printed at any point
 * - our error handling now pointless
 */

int main(int argc, char *argv[]){
	FILE *inputFile;
	int srchTarget;

	inputFile = fopen(argv[1], "r");
	srchTarget = atoi(argv[2]);

	char *numberStrings[11];
	int numElems;
	int numberIntegers[11];
	numElems = fillArray(inputFile, numberStrings);
	printf("numElems: %d\n", numElems);

	//---File processing is done at this point
	//Convert to ints next
	//Fork until single number, compare, then return result

	if(numElems < 11){
		//Convert to ints here, viewArray is just for convenience
		viewArray(numberStrings, numElems);
		convertToInts(numberStrings, numElems, numberIntegers);
		viewIntArray(numberIntegers, numElems);
	}else{
		//Print error message and return -1 because array contained >10 numbers
		printf("\nError! File contained more than 10 numbers");
		return -1;
	}

	return 0;
}

/*----- fillArray -----
 * Arguments/Parameters to/of function
 * 	FILE *processFile: file pointer
 * 	char *emptyArray: array of char pointers (strings)
 * Returns:
 * 	int: containing the number of elements in the file/array,
 * 		 used to determine if # of numbers in the array file is >10
 * 	Assumptions:
 * 	1. file to be read contains only a single line
 * 	2. file doesn't start with a white space character
 * 	3. there is no '\n' at the end of the file (no empty second line)
 */
int fillArray(FILE *processFile, char *emptyArray[]){
	int counter = 0;

	//https://piazza.com/class/jc2hy1ofmi0319?cid=242
	//-2,147,483,648 to 2,147,483,647
	//11 characters for largest possible int value (includes the negative sign)
	//11 * 10 numbers + 9 spaces (one space character between each int according to lab2 doc)
	// = 119
	char fileLine[130];	//allow 130 chars just to be safe
	char *numStr;

	fgets(fileLine, 130, processFile);
	//printf("\nfileLine: %s", fileLine);

	numStr = strtok(fileLine, " ");
	//printf("\nnumStr %d: %s", counter, numStr);

	while(numStr != NULL){
		if(counter < 10){
			emptyArray[counter] = strdup(numStr);
		}
		numStr = strtok(NULL, " ");
		counter++;
		//printf("\nnumStr %d: %s", counter, numStr);
	}

	return counter;
}

void viewArray(char *filledArray[], int numOfElems){
	int i;
	for(i = 0; i < numOfElems; i++){
		printf("\n[%d]: %s", i, filledArray[i]);
	}
	printf("\n");
}

void convertToInts(char *numberStrs[], int numOfStr, int numberInts[]){
	int i;
	char *currentNum;
	for(i = 0; i < numOfStr; i++){
		currentNum = strdup(numberStrs[i]);
		printf("String to be converted: %s\n", currentNum);
		numberInts[i] = atoi(currentNum);
		printf("Conversion success: numberInts[%d]: %d\n", i, numberInts[i]);
	}
}

void viewIntArray(int filledArray[], int numOfInts){
	int i;
	for(i = 0; i < numOfInts; i++){
		printf("\n[%d]: %d", i, filledArray[i]);
	}
	printf("\n");
}
