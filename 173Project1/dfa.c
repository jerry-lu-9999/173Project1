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
#include "IntHashSet.h"

struct DFA {
    int DFA_N_STATE;
    IntHashSet **transitionTable;
    // char inputSymb[36];
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
    // this->inputSymb = (char*)malloc( sizeof(char)); //RIP LMAO WE DON'T KNWO IF THIS WORKS


    this->transitionTable = (IntHashSet**)malloc(nstates*sizeof(IntHashSet*));

    for (int i = 0; i < nstates; i++){
    	 this->transitionTable[i] = (IntHashSet*)malloc(DFA_INPUT*sizeof(IntHashSet));
        for (int j = 0; j < DFA_INPUT; j++){
            this->transitionTable[i][j] = new_IntHashSet(1);
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
	    	IntHashSet_free(dfa->transitionTable[i][j]);
	    }
	}
	free(dfa);
}

int convertSymbtoInt(char sym){
    int symb = (int)sym;
    if(symb < 60){ //if symb is a 'numb'
        return symb = symb-22;
    }else if(symb >= 60){ //else if symb is a 'char'
        return symb = symb-97;
    }
    return -1;
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

    int input = convertSymbtoInt(sym);
    printf("\nthis is the current state: %d \n and this is the input: %c", src, sym);
    IntHashSet set = dfa ->transitionTable[src][input];

            
            printf("\nthis is the set: \n"); // there is nothing in the set
            IntHashSet_print(set);

    IntHashSetIterator iterator = IntHashSet_iterator(set);
	int state = IntHashSetIterator_next(iterator); // state is the first element in the set
	//printf("\nThis is the state by the iterator: %d", state);
    // IntHashSet_print(set);
    return state;
}

/**
 * For the given DFA, set the transition from state src on input symbol
 * sym to be the state dst.
 */
void DFA_set_transition(DFA dfa, int src, char sym, int dst){
    //must go through array to find sym to numb
    int input = convertSymbtoInt(sym);
	IntHashSet_insert(dfa->transitionTable[src][input], dst);
    //****prints hashstate correctly
    // printf("printing inthashset in DFA_set_transition: \n");
    // IntHashSet_print(dfa->transitionTable[src][input]);
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
bool DFA_execute(DFA dfa, char *sym){
    //put input inti array for list of
    //checking system to see if symbol is on the DFA_SYMBOL list?
    //
    dfa->currentState = 0;
    // go through each character of the input
    printf("\nthis is the beginning of DFA execute");
    
    for(int i = 0; i < strlen(sym); i++) {
        int input = convertSymbtoInt(sym[i]);

        printf("\nThis is the current state:  %d", dfa->currentState);
        printf("\nThis is the current input: %c   %d", sym[i], input);
        
        //BUB YOU THE PROBLEM (DFA_get_transition)
        int cur = DFA_get_transition(dfa, dfa->currentState, sym[i]);
        printf("\nTHIS IS CUR: %d", cur);
        dfa->currentState = cur;
        
        if(DFA_get_accepting(dfa, cur)){
            printf("\nACCEPTING");
            return true;
        }
    }
    printf("SOMETHING AINT WORKING BUB");
    return false; //change later to false
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
	// Part a

	char input[50];
    // char inputSymb[36] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	printf("Type a character: ");
	scanf("%s", input);
	DFA dfa1a = new_DFA(7);
	DFA_set_transition(dfa1a, 0, 'c', 1);
    // printf("current state: %d\n", dfa1a->currentState);
    // printf("current state:::: %d\n", DFA_get_transition(dfa1a, 0, 'c'));
	DFA_set_transition(dfa1a, 1, 's', 2);
	DFA_set_transition(dfa1a, 2, 'c', 3);
    // printf("current state: %d\n", dfa1a->currentState);
	DFA_set_transition(dfa1a, 3, '1', 4);
	DFA_set_transition(dfa1a, 4, '7', 5);
	DFA_set_transition(dfa1a, 5, '3', 6);
    // printf("current state: %d\n", dfa1a->currentState);
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

}
