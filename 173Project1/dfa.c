/*
 * File: dfa.c
 * Creator: 
 * Created: 
 * Time-stamp: 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "dfa.h"
#include "LinkedList.h"

struct DFA {
    int DFA_N_STATE;
    LinkedList **transitionTable;
    int currentState;
    int acceptingState;
};

/**
 * Allocate and return a new DFA containing the given number of states.
 */
DFA new_DFA(int nstates){
    DFA this = (DFA)malloc(sizeof(struct DFA));
    if (this == NULL) {
        return NULL; // Out of memory...
    }
    this->DFA_N_STATE = nstates;
    this->currentState = 0;
    this->acceptingState = 1;

    this->transitionTable = (LinkedList**)malloc(nstates*sizeof(LinkedList*));

    for (int i = 0; i < nstates; i++){
    	 this->transitionTable[i] = (LinkedList*)malloc(DFA_INPUT*sizeof(LinkedList));
        for (int j = 0; j < DFA_INPUT; j++){
            this->transitionTable[i][j] = new_LinkedList();
        }
    }
    return this;
}


/**
 * Free the given DFA.
 */
void DFA_free(DFA dfa){
	if (dfa == NULL) {
		return;
	}
	for (int i = 0; i < dfa->DFA_N_STATE; i++){
	    for (int j = 0; j < DFA_INPUT; j++){
	    	LinkedList_free(dfa->transitionTable[i][j], true);
	    }
	}
	free(dfa);
}

/**
 * Return the number of states in the given DFA.
 */
int DFA_get_size(DFA dfa){
    return dfa -> DFA_N_STATE;
}

/**
 * Return the state specified by the given DFA's transition function from
 * state src on input symbol sym.
 */
int DFA_get_transition(DFA dfa, int src, char sym){
	int input = (int) sym;
	LinkedList list = dfa ->transitionTable[src][input];
	int state = (int)LinkedList_elementAt(list, 0);
    return state;
}

/**
 * For the given DFA, set the transition from state src on input symbol
 * sym to be the state dst.
 */
void DFA_set_transition(DFA dfa, int src, char sym, int dst){
	LinkedList_add_at_end(dfa->transitionTable[src][(int)sym], &dst);
	dfa->currentState = dst;
}

/**
 * Set the transitions of the given DFA for each symbol in the given str.
 * This is a nice shortcut when you have multiple labels on an edge between
 * two states.
 */
void DFA_set_transition_str(DFA dfa, int src, char *str, int dst) {
	for(int i = 0; i < sizeof(*str); i++){
		DFA_set_transition(dfa, src, str[i], dst);
	}
}

/**
 * Set the transitions of the given DFA for all input symbols.
 * Another shortcut method.
 */
void DFA_set_transition_all(DFA dfa, int src, int dst) {
	for(int i = 0; i < DFA_INPUT; i++){
		//find a way to put all input symbols???????
//		DFA_set_transition(dfa, src, , dst);
	}
}

/**
 * Set whether the given DFA's state is accepting or not.
 */
void DFA_set_accepting(DFA dfa, int state, bool value){
	if(value == true){
		dfa -> acceptingState = state;
	}
}

/**
 * Return true if the given DFA's state is an accepting state.
 */
bool DFA_get_accepting(DFA dfa, int state){
    if (state == dfa -> acceptingState){
        return true;
    }else{
        return false;
    }
}

/**
 * Run the given DFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
bool DFA_execute(DFA dfa, char *input){
	//put input inti array for list of
    //checking system to see if symbol is on the DFA_SYMBOL list?
	//

	// go through each character of the input
	for(int i = 0; i < sizeof(input); i++) {
		int cur = DFA_get_transition(dfa, dfa->currentState, input[i]);
		if(DFA_get_accepting(dfa, cur)){
			return true;
		} else {
			return false;
		}
	}
	return false;
}

/**
 * Print the given DFA to System.out.
 */
//void DFA_print(DFA dfa){
//    for (int i = 0; i < dfa -> DFA_N_STATE; i++){
//        for (int j = 0; j < DFA_INPUT; j++){
//        	LinkedList_print_string_list(dfa->transitionTable[i][j]);
//        }
//    }
//}



int main(int argc, char* argv[]){
//	// Part a
	char* input="";
	printf("Type a character");
	scanf("%s", input);
	DFA dfa1a = new_DFA(7);
	DFA_set_transition(dfa1a, 0, 'c', 1);
	DFA_set_transition(dfa1a, 1, 's', 2);
	DFA_set_transition(dfa1a, 2, 'c', 3);
	DFA_set_transition(dfa1a, 3, '1', 4);
	DFA_set_transition(dfa1a, 4, '7', 5);
	DFA_set_transition(dfa1a, 5, '3', 6);
	DFA_set_accepting(dfa1a, 0, false);
	DFA_set_accepting(dfa1a, 1, false);
	DFA_set_accepting(dfa1a, 2, false);
	DFA_set_accepting(dfa1a, 3, false);
	DFA_set_accepting(dfa1a, 4, false);
	DFA_set_accepting(dfa1a, 5, false);
	DFA_set_accepting(dfa1a, 6, true);
	if(DFA_execute(dfa1a, input)){
		printf("yas");
	} else {
		printf("fail");
	}
	printf("hello");
}
