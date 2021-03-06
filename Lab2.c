/* Ho-ren Kang	horenk	21397985
 * Edwin Li		liek	10153998
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int fillArray(FILE *processFile, char *emptyArray[]);
void viewArray(char *filledArray[], int numOfElems);
void convertToInts(char *numberStrs[], int numOfStr, int numberInts[]);
void viewIntArray(int filledArray[], int numOfInts);
void forkSearch(int intArray[], int numOfInts, int targetNum);


int main(int argc, char *argv[]){
	FILE *inputFile;
	int srchTarget;

	inputFile = fopen(argv[1], "r");
	srchTarget = atoi(argv[2]);

	printf("srchTarget: %d\n", srchTarget);

	char *numberStrings[11];
	int numElems;
	int numberIntegers[11];
	numElems = fillArray(inputFile, numberStrings);
	//printf("numElems: %d\n", numElems);
	//viewArray(numberStrings, numElems);
	//---File processing is done at this point

	convertToInts(numberStrings, numElems, numberIntegers);
	//viewIntArray(numberIntegers, numElems);
	//---Conversion to ints finished at this point

	//Fork until single number, compare, then return result
	forkSearch(numberIntegers, numElems, srchTarget);

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
		//printf("String to be converted: %s\n", currentNum);
		numberInts[i] = atoi(currentNum);
		//printf("Conversion success: numberInts[%d]: %d\n", i, numberInts[i]);
	}
}

void viewIntArray(int filledArray[], int numOfInts){
	int i;
	for(i = 0; i < numOfInts; i++){
		printf("\n[%d]: %d", i, filledArray[i]);
	}
	printf("\n");
}

void forkSearch(int intArray[], int numOfInts, int targetNum){
	/*int mid = (numOfInts-1) / 2;
	pid_t processID;
	printf("Parent process ID: %d and current value is %d\n", getpid(), intArray[mid]);
	if(intArray[mid] == targetNum){
		exit(1);
	}
	processID = fork();
	if(processID == 0){
		printf("Child process ID: %d and current value is %d\n", getpid(), intArray[mid+1]);
		if(intArray[mid+1] == targetNum){
			exit(1);
		}
	}*/

	int i, status;
	int exitstatus;
	pid_t childID, wpid;
	printf("Parent process ID: %d ", getpid());
	for(i = 0; i < numOfInts; i++){
		childID = fork();
		if(childID == 0){
			printf("pid: %d, value: %d\n", getpid(), intArray[i]);
			if(targetNum == intArray[i]){
				printf("[i]: %d\n", i);
				exit(i + 2);
			}
			exit(0);
		}
	}
	//index default -1 if not found
	int index = -1;
	do
	{
		wpid = wait(&status);
		exitstatus = WEXITSTATUS(status) - 2;
		if(exitstatus >= 0)
		{
			index = exitstatus;
		}
	}
	while(wpid > 0);
	//printf("This should print after all the child processes are done\n\n");
	//printf("Exit status: %d\n", index);
	printf("Search output: %d\n", index);

}
