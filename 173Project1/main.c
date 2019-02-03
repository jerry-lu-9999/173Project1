#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dfa.h"

int main(int argc, char* argv[]){
	char input1[50];
	printf("\nDFA that recognizes exactly \"csc173\"...\n");
	while(strcmp(input1, "quit") != 0){
		printf("Enter an input (\"quit\" to quit):\n");
		scanf("%s", input1);
		printf("Result for input %s:\n", input1);
		dfa1a(input1);
	}
	char input2[50];
	printf("\nDFA that tests strings that starts with characters cat... \n");
	while(strcmp(input2, "quit") != 0){
		printf("Enter an input (\"quit\" to quit):\n");
		scanf("%s", input2);
		printf("Result for input %s:\n", input2);
		dfa1b(input2);
	}
	char input3[50];
	printf("\nDFA that tests binary inputs with even number of 0's... \n");
	while(strcmp(input3, "quit") != 0){
		printf("Enter an input (\"quit\" to quit):\n");
		scanf("%s", input3);
		printf("Result for input %s:\n", input3);
		dfa1c(input3);
	}
	char input4[50];
	printf("\nDFA that tests binary inputs with even number of both 0's and 1's... \n");
	while(strcmp(input4, "quit") != 0){
		printf("Enter an input (\"quit\" to quit):\n");
		scanf("%s", input4);
		printf("\nResult for input %s:\n", input4);
		dfa1d(input4);
	}
	


	
}
