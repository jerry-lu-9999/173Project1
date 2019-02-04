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
int convertSymbtoInt(char sym){
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
    int input = convertSymbtoInt(sym);
    printf("\nthis is the current state: %d \n and this is the input: %c", state, sym);
    //****MUST SET STATE TO SET OF STATES INCASE IT'S MULTIPLE STATE*******//
    IntHashSet set = nfa ->transitionTable[state][input];
    // printf("\nthis is the set: \n");
    //         IntHashSet_print(set);

    // IntHashSetIterator iterator = IntHashSet_iterator(set);
    // IntHashSet stateSet = new_IntHashSet(3); //temporary number
    // while(IntHashSetIterator_hasNext(iterator)){
    //     printf("\nint the get transition iterator loop printing stateSet:");
    //     IntHashSet_union(stateSet,set);
    //     IntHashSet_print(stateSet);
    //     printf("\n this is from transition iterator: %d", IntHashSetIterator_next(iterator));
    // }
    //  state is the first element in the set
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
    int input = convertSymbtoInt(sym);
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
        int input = convertSymbtoInt(inputSymb[i]);
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

        for(int i = 0; i < strlen(sym); i++) {
        IntHashSetIterator iterator = IntHashSet_iterator(cur);
        nfa->currentState = IntHashSetIterator_next(iterator); //needs to be the first element of the set
        printf("\nTHIS IS CURRENT STATE:::: %d", nfa->currentState);
        newCur = NFA_get_transitions(nfa, nfa->currentState, sym[i]);

        if(IntHashSetIterator_hasNext(iterator)){
            printf("\n.....at execute HAS NEXT");
            nfa->currentState = IntHashSetIterator_next(iterator);
            printf("\nTHIS IS CURRENT STATE:::: %d", nfa->currentState);
            tempCur = NFA_get_transitions(nfa, nfa->currentState, sym[i]);
            IntHashSet_union(newCur, tempCur);
        }
        printf("\nAT INPUT: %d", sym[i]);
        printf("\nTHIS IS CUR:::: " );
        IntHashSet_print(cur);
        printf("\nTHIS IS NEWCUR:::: " );
        IntHashSet_print(newCur);
        cur = newCur;
        free(newCur);
        }

        IntHashSetIterator iterator = IntHashSet_iterator(cur);
        while(IntHashSetIterator_hasNext(iterator)){
            int nextState = IntHashSetIterator_next(iterator);
            printf("\n.......trying to see if %d is an accepting state", nextState);
            if(NFA_get_accepting(nfa, nextState)){
                printf("\nACCEPTING\n");
            return true;
            }
        }
    return false; //change later to false

 }

/**
 * Print the given NFA to System.out.
 */
 void NFA_print(NFA nfa){

 }

 void nfa1a(char* input) {
    NFA nfa1a = new_NFA(7);
    NFA_add_transition_all(nfa1a, 0, 0);
    NFA_add_transition(nfa1a, 0, 'c', 1);
    NFA_add_transition(nfa1a, 1, 'o', 2);
    NFA_add_transition(nfa1a, 2, 'd', 3);
    NFA_add_transition(nfa1a, 3, 'e', 4);
    NFA_set_accepting(nfa1a, 0, false);
    NFA_set_accepting(nfa1a, 1, false);
    NFA_set_accepting(nfa1a, 2, false);
    NFA_set_accepting(nfa1a, 3, false);
    NFA_set_accepting(nfa1a, 4, true);
    if(NFA_execute(nfa1a, input)){
    	printf("Accept 1a\n");
    } else {
    	printf("Fail 1a\n");
    }
}

int main(int argc, char* argv[]){
	char input[50];
	printf("Type a character: ");
	scanf("%s", input);
    nfa1a(input);
}

//int main(int argc, char* argv[]){
//
//}


/* TERRIBLE MESSED UP EXECUTION CODE
    //put input inti array for list of
    //checking system to see if symbol is on the DFA_SYMBOL list?
    nfa->currentState = 0;
    IntHashSet cur = new_IntHashSet(20); //DUDE IDK BRUH LIKE WHAT NUMBER MAN
    // go through each character of the input
    printf("\nthis is the beginning of NFA execute");
    
    for(int i = 0; i < strlen(sym); i++) {
        int input = convertSymbtoInt(sym[i]);
        // printf("\nThis is the current state:  %d", dfa->currentState);
        // printf("\nThis is the current input: %c   %d", sym[i], input);
        cur = NFA_get_transition(nfa, nfa->currentState, sym[i]);
        // printf("\nTHIS IS CUR: %d", cur);

        IntHashSetIterator iterator = IntHashSet_iterator(cur);
        // nfa->currentState = IntHashSetIterator_next(iterator);
        if(IntHashSetIterator_hasNext(iterator)){
            // for(int j = i; j < strlen(sym); j++) {
            // cur = NFA_get_transition(nfa, nfa->currentState, sym[i]);
            
            // }


        }


        // if(i == (strlen(sym)-1)&&IntHashSetIterator_hasNext(iterator)){
        //     cur = IntHashSetIterator_next(iterator);
        //     i = 0;
        //     //NEED TO ADD TO SET OF STATES
        // }
        // dfa->currentState = cur;
 
        if(nfa->currentState == -1){
            // printf("FAIL\n");
            break;
        }
    }
    if(nfa->currentState != -1 && NFA_get_accepting(nfa, cur)){
        // printf("\nACCEPTING\n");
        return true;
    } 
    return false; //change later to false
        //puts the sets that we get from NFA transitions
        //RYING TO ADD SET INTO INT HASH SET BUT ARGUMENT ONLY TAKES IN INTEGER
        //can you add sets is the problem??
        
        //returns a set so
    //         IntHashSet getTransition = new_IntHashSet(20);
    //         getTransition = NFA_get_transitions(nfa, nfa->currentState, sym[i]);

    //         IntHashSetIterator iterator = IntHashSet_iterator(getTransition);
    //         IntHashSet stateSet = new_IntHashSet(3); //temporary number
    //         while(IntHashSetIterator_hasNext(iterator)){
    //             printf("\nint the EXECUTE transition iterator loop::::::: %d", IntHashSetIterator_next(iterator));
    //             free(iterator);
    //             IntHashSet_insert(cur, IntHashSetIterator_next(iterator)); 
    //             free(iterator);
    //             nfa->currentState = IntHashSetIterator_next(iterator);
    //             printf("\n(inside Iterator:: THIS IS CUR: %d \n", nfa -> currentState);
    //             IntHashSet_print(cur);
    //     }



    //     // nfa->currentState = cur; //WHAT AM I SUPPOSED TO DO WITH THIS
        
    // }       

    
    //     IntHashSetIterator iterator = IntHashSet_iterator(cur);
    //     IntHashSet stateSet = new_IntHashSet(3); //temporary number
    //     while(IntHashSetIterator_hasNext(iterator)){
    //         int nextState = IntHashSetIterator_next(iterator);
    //         printf("\n.......trying to see if %d is an accepting state", nextState);
    //         if(NFA_get_accepting(nfa, nextState)){
    //             printf("\nACCEPTING\n");
    //         return true;
    //         }
    //     }
    // return false; //change later to false



*/