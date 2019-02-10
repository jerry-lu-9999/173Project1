#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dfa.h"
#include "nfa.h"
#include "nfatodfa.h"

int main(int argc, char* argv[]){
	int menu;
	printf("Welcome! Type in the number to select which machine you want to test\n");
    printf("Type 1 for DFA\n");
    printf("Type 2 for NFA\n");
    printf("Type 3 for NFA to DFA converter\n");
    scanf("%d", &menu);
    if (menu == 1) {
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
    } else if (menu == 2){
        char input5[50];
		printf("\nNFA that recognizes strings ending in \"code\"...\n");
		while(strcmp(input5, "quit") != 0){
			printf("Enter an input (\"quit\" to quit):\n");
			scanf("%s", input5);
			printf("Result for input %s:\n", input5);
			nfa2a(input5);
			//DFA dfa = nfatodfa(nfa);
			//printf("Printing out DFA from subset construction...\n");
		}
		char input6[50];
		printf("\nNFA that recognizes strings containing \"code\"...\n");
		while(strcmp(input6, "quit") != 0){
			printf("Enter an input (\"quit\" to quit):\n");
			scanf("%s", input6);
			printf("Result for input %s:\n", input6);
			nfa2b(input6);
		}
        char input7[50];
        printf("\nNFA that recognize non-anagram of 'washington'\n");
        while(strcmp(input7, "quit") != 0){
            printf("Enter an input (\"quit\" to quit):\n");
            scanf("%s", input7);
            printf("Result for input %s:\n", input7);
            nfa2c(input7);
        }

	}
        else if (menu == 3){
	 	printf("Subset construction from NFA part 1 to a DFA...\n");
		printf("Enter an input (\"quit\" to quit):\n");
		NFA nfa = nfa2a(input5);
		DFA dfa = nfatodfa(nfa);
		printf("Printing out DFA from subset construction...\n");
		DFA_print(dfa);
            
	 }

	
}
