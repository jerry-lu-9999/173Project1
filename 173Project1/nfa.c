/*
 * File: nfa.h
 * Creator: 
 * Created: 
 * Time-stamp: 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "nfa.h"
#include "IntHashSet.h"

struct NFA {
    int NFA_N_STATE;
    IntHashSet **transitionTable;
    int currentState;
    int acceptingState;  
};

/**
 * Allocate and return a new NFA containing the given number of states.
 */
NFA new_NFA(int nstates){
    NFA this = (NFA)malloc(sizeof(struct NFA));
    if (this == NULL) {
        return NULL; // Out of memory...
    }
    this->NFA_N_STATE = nstates;
    this->currentState = 0;
    this->acceptingState = 1;
    this->transitionTable = (IntHashSet**)malloc(nstates*sizeof(IntHashSet*));

    for (int i = 0; i < nstates; i++){
    	 this->transitionTable[i] = (IntHashSet*)malloc(NFA_INPUT*sizeof(IntHashSet));
        for (int j = 0; j < NFA_INPUT; j++){
            this->transitionTable[i][j] = new_IntHashSet(30); //fix this to whatever number

        }
    }
    return this;
}

/**
 * Free the given NFA.
 */
void NFA_free(NFA nfa){
    if (nfa == NULL) {
		return;
	}
	for (int i = 0; i < nfa->NFA_N_STATE; i++){
	    for (int j = 0; j < NFA_INPUT; j++){
	    	IntHashSet_free(nfa->transitionTable[i][j]);
	    }
	}
	free(nfa);
}

//making sym into ASCII value between 0-36
int convertSymbtoInt2(char sym){
    int symb = (int)sym;
    if(symb < 60){ //if symb is a 'number'
        return symb = symb-22;
    }else if(symb >= 60){ //else if symb is a 'char'
        return symb = symb-97;
    }
    return -1;
}

/**
 * Return the number of states in the given NFA.
 */
int NFA_get_size(NFA nfa){
    return nfa -> NFA_N_STATE;
}

/**
 * Return the set of next states specified by the given NFA's transition
 * function from the given state on input symbol sym.
 */
Set NFA_get_transitions(NFA nfa, int state, char sym){
    int input = convertSymbtoInt2(sym);
    printf("\nthis is the current state: %d \n and this is the input: %c", state, sym);
    //****MUST SET STATE TO SET OF STATES INCASE IT'S MULTIPLE STATE*******//
    IntHashSet set = nfa ->transitionTable[state][input];
	printf("\nThis is the state by the iterator: %d", state);
    IntHashSet_print(set);
    return set;
}

/**
 * For the given NFA, add the state dst to the set of next states from
 * state src on input symbol sym.
 */
 void NFA_add_transition(NFA nfa, int src, char sym, int dst){
    //make the sym into a ASCII value
        // printf("we are in set transition");
    int input = convertSymbtoInt2(sym);
	IntHashSet_insert(nfa->transitionTable[src][input], dst);
	nfa->currentState = dst;
 }

/**
 * Add a transition for the given NFA for each symbol in the given str.
 */
 void NFA_add_transition_str(NFA nfa, int src, char *str, int dst){
     //do we need?
 }

/**
 * Add a transition for the given NFA for each input symbol.
 */
void NFA_add_transition_all(NFA nfa, int src, int dst){
    char inputSymb[36] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};  
    for(int i = 0; i < 36; i++){
        int input = convertSymbtoInt2(inputSymb[i]);
	    IntHashSet_insert(nfa->transitionTable[src][input], dst);
    }
    //we have questionable dfa code   
}

/**
 * Set whether the given NFA's state is accepting or not.
 */
void NFA_set_accepting(NFA nfa, int state, bool value){
	if(value == true){
		nfa -> acceptingState = state;
	}
}

/**
 * Return true if the given NFA's state is an accepting state.
 */
bool NFA_get_accepting(NFA nfa, int state){
         if (state == nfa -> acceptingState){
        return true;
    }else{
        return false;
    }
}

/**
 * Run the given NFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
bool NFA_execute(NFA nfa, char *sym){
    nfa->currentState = 0;
    IntHashSet cur = new_IntHashSet(20); //DUDE IDK BRUH LIKE WHAT NUMBER MAN
    IntHashSet newCur = new_IntHashSet(20);
    IntHashSet tempCur = new_IntHashSet(20);
    IntHashSet_insert(cur, nfa->currentState);
    for(int i = 0; i < strlen(sym); i++) {//Iterating over the string
            newCur = new_IntHashSet(20);
            IntHashSetIterator iterator = IntHashSet_iterator(cur);
        // nfa->currentState = IntHashSetIterator_next(iterator); //needs to be the first element of the set
        // printf("\nTHIS IS CURRENT STATE:::: %d", nfa->currentState);
        // newCur = NFA_get_transitions(nfa, nfa->currentState, sym[i]);

        while(IntHashSetIterator_hasNext(iterator)){
            nfa->currentState = IntHashSetIterator_next(iterator);
            // printf("\n.....at execute HAS NEXT");
            // printf("\nTHIS IS CURRENT STATE:::: %d", nfa->currentState);
            tempCur = NFA_get_transitions(nfa, nfa->currentState, sym[i]);
            IntHashSet_union(newCur, tempCur);

        }
        // printf("\nAT INPUT: %d", sym[i]);
        // printf("\nTHIS IS CUR:::: " );
        // IntHashSet_print(cur);
        // printf("\nTHIS IS NEWCUR:::: " );
        // IntHashSet_print(newCur);
        cur = newCur;
        free(newCur);
        free(tempCur);
        }
        IntHashSetIterator iterator2 = IntHashSet_iterator(cur);
        while(IntHashSetIterator_hasNext(iterator2)){
            int nextState = IntHashSetIterator_next(iterator2);
            printf("\n.......trying to see if %d is an accepting state", nextState);
            if(NFA_get_accepting(nfa, nextState)){
                printf("\nACCEPTING\n");
            free(cur);
            free(iterator2); 
            return true;
            }
        }
        free(cur);
        free(iterator2);
    return false; 

}

/**
 * Print the given NFA to System.out.
 */
void NFA_print(NFA nfa){

 }

void nfa2a(char* input) {
    NFA nfa2a = new_NFA(5);
    NFA_add_transition_all(nfa2a, 0, 0);
    NFA_add_transition(nfa2a, 0, 'c', 1);
    NFA_add_transition(nfa2a, 1, 'o', 2);
    NFA_add_transition(nfa2a, 2, 'd', 3);
    NFA_add_transition(nfa2a, 3, 'e', 4);
    NFA_set_accepting(nfa2a, 0, false);
    NFA_set_accepting(nfa2a, 1, false);
    NFA_set_accepting(nfa2a, 2, false);
    NFA_set_accepting(nfa2a, 3, false);
    NFA_set_accepting(nfa2a, 4, true);
    if(NFA_execute(nfa2a, input)){
    	printf("Accept 2a\n");
    } else {
    	printf("Fail 2a\n");
    }
    NFA_free(nfa2a);
}

void nfa2b(char* input) {
    NFA nfa2b = new_NFA(5);
    NFA_add_transition_all(nfa2b, 0, 0);
    NFA_add_transition(nfa2b, 0, 'c', 1);
    NFA_add_transition(nfa2b, 1, 'o', 2);
    NFA_add_transition(nfa2b, 2, 'd', 3);
    NFA_add_transition(nfa2b, 3, 'e', 4);
    NFA_add_transition_all(nfa2b, 4, 4);
    NFA_set_accepting(nfa2b, 0, false);
    NFA_set_accepting(nfa2b, 1, false);
    NFA_set_accepting(nfa2b, 2, false);
    NFA_set_accepting(nfa2b, 3, false);
    NFA_set_accepting(nfa2b, 4, true);
}
<<<<<<< HEAD


void nfa2c(char* input){
    NFA nfa2c = new_NFA(20);
    NFA_add_transition_all(nfa2c, 0, 0);
    NFA_add_transition(nfa2c, 0, 'a', 1);
    NFA_add_transition(nfa2c, 1, 'a', 2);
    NFA_add_transition(nfa2c, 0, 'g', 3);
    NFA_add_transition(nfa2c, 3, 'g', 4);
    NFA_add_transition(nfa2c, 0, 'h', 5);
    NFA_add_transition(nfa2c, 5, 'h', 6);
    NFA_add_transition(nfa2c, 0, 'i', 7);
    NFA_add_transition(nfa2c, 7, 'i', 8);
    NFA_add_transition(nfa2c, 0, 'n', 9);
    NFA_add_transition(nfa2c, 9, 'n', 10);
    NFA_add_transition(nfa2c, 10, 'n', 11);
    NFA_add_transition(nfa2c, 0, 'o', 12);
    NFA_add_transition(nfa2c, 12, 'o', 13);
    NFA_add_transition(nfa2c, 0, 's', 14);
    NFA_add_transition(nfa2c, 14, 's', 15);
    NFA_add_transition(nfa2c, 0, 't', 16);
    NFA_add_transition(nfa2c, 16, 't', 17);
    NFA_add_transition(nfa2c, 0, 'w', 18);
    NFA_add_transition(nfa2c, 18, 'w', 19);
    // still have to figure how to do lamda - 'a'
    // accepting: 2, 4, 6, 8, 11, 13, 15, 17, 19
    // not accepting: 0, 1, 3, 5, 7, 9, 10, 12, 14, 16, 18
}

#ifdef MAIN

int main(int argc, char* argv[]){
	char input[50];
	printf("Type a character: ");
	scanf("%s", input);
    nfa2a(input);
}
#endif
=======
>>>>>>> 7f2c4e99874c4ae7a5516a2b6291f1288d3bd129
