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
    IntHashSet acceptingState;
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
    this->acceptingState = new_IntHashSet(20);
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
    IntHashSet set = nfa ->transitionTable[state][input];
    return set;
}

/**
 * For the given NFA, add the state dst to the set of next states from
 * state src on input symbol sym.
 */
void NFA_add_transition(NFA nfa, int src, char sym, int dst){
    int input = convertSymbtoInt2(sym);
    IntHashSet_insert(nfa->transitionTable[src][input], dst);
    nfa->currentState = dst;
}

/**
 * Add a transition for the given NFA for each symbol in the given str.
 */
void NFA_add_transition_str(NFA nfa, int src, char *str, int dst){
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
}

/**
 * Set whether the given NFA's state is accepting or not.
 */
void NFA_set_accepting(NFA nfa, int state, bool value){
    if(value == true){
        IntHashSet_insert(nfa->acceptingState, state);
    }
}

/**
 * Return true if the given NFA's state is an accepting state.
 */
bool NFA_get_accepting(NFA nfa, int state){
    return IntHashSet_lookup(nfa->acceptingState, state);
}

/**
 * Run the given NFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
bool NFA_execute(NFA nfa, char* sym){
    nfa->currentState = 0;
    IntHashSet cur = new_IntHashSet(20);
    IntHashSet newCur = new_IntHashSet(20);
    IntHashSet tempCur = new_IntHashSet(20);
    IntHashSet_insert(cur, nfa->currentState);
    
    for (int i = 0; i < strlen(sym); i++){
        //The iterator here doesn't exact have the iterator's property, these two lines below are to prevent
        IntHashSet temp =new_IntHashSet(20);
        IntHashSet_union(temp, cur);
        
        IntHashSetIterator iterator = IntHashSet_iterator(temp);
        
        while(IntHashSetIterator_hasNext(iterator)){ 
            nfa->currentState = IntHashSetIterator_next(iterator);
            tempCur = NFA_get_transitions(nfa, nfa->currentState, sym[i]);
            IntHashSet_union(newCur, tempCur);
        }
        cur = newCur;
    }
    
    //check if any state in newCur is an accepting states
    IntHashSetIterator iterator2 = IntHashSet_iterator(cur);
    while(IntHashSetIterator_hasNext(iterator2)){
        int nextState = IntHashSetIterator_next(iterator2);
        if(NFA_get_accepting(nfa, nextState)){
            return true;
        }
    }
    return false;
}

/**
 * Print the given NFA to System.out.
 */
void NFA_print(NFA nfa){
    
}

NFA nfa2a(char* input) {
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
    return nfa2a;
}

NFA nfa2b(char* input) {
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
    if(NFA_execute(nfa2b, input)){
        printf("Accept 2b\n");
    } else {
        printf("Fail 2b\n");
    }
    return nfa2b;
}

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
    NFA_set_accepting(nfa2c, 2, true);
    NFA_set_accepting(nfa2c, 4, true);
    NFA_set_accepting(nfa2c, 6, true);
    NFA_set_accepting(nfa2c, 8, true);
    NFA_set_accepting(nfa2c, 11, true);
    NFA_set_accepting(nfa2c, 13, true);
    NFA_set_accepting(nfa2c, 15, true);
    NFA_set_accepting(nfa2c, 17, true);
    NFA_set_accepting(nfa2c, 19, true);
    NFA_set_accepting(nfa2c, 0, false);
    NFA_set_accepting(nfa2c, 1, false);
    NFA_set_accepting(nfa2c, 3, false);
    NFA_set_accepting(nfa2c, 5, false);
    NFA_set_accepting(nfa2c, 7, false);
    NFA_set_accepting(nfa2c, 9, false);
    NFA_set_accepting(nfa2c, 10, false);
    NFA_set_accepting(nfa2c, 12, false);
    NFA_set_accepting(nfa2c, 14, false);
    NFA_set_accepting(nfa2c, 16, false);
    NFA_set_accepting(nfa2c, 18, false);
    if(NFA_execute(nfa2c, input)){
        printf("Accept 2c\n");
    } else {
        printf("Fail 2c\n");
    }
}

void nfa2d(char* input) {
    NFA nfa2d = new_NFA(8);
    NFA_add_transition_all(nfa2d, 0, 0);
    NFA_add_transition(nfa2d, 0, 'e', 1);
    NFA_add_transition(nfa2d, 1, 'l', 2);
    NFA_add_transition(nfa2d, 2, 'b', 5);

    NFA_add_transition(nfa2d, 0, 'b', 3);
    NFA_add_transition(nfa2d, 3, 'e', 4);
    NFA_add_transition(nfa2d, 4, 'l', 5);

    NFA_add_transition(nfa2d, 5, 'o', 6);
    NFA_add_transition(nfa2d, 6, 'w', 7);

    NFA_set_accepting(nfa2d, 0, false);
    NFA_set_accepting(nfa2d, 1, false);
    NFA_set_accepting(nfa2d, 2, false);
    NFA_set_accepting(nfa2d, 3, false);
    NFA_set_accepting(nfa2d, 4, false);
    NFA_set_accepting(nfa2d, 5, false);
    NFA_set_accepting(nfa2d, 6, false);

    NFA_set_accepting(nfa2d, 7, true);

    if(NFA_execute(nfa2d, input)){
        printf("Accept 2d\n");
    } else {
        printf("Fail 2d\n");
    }

}

#ifdef MAIN

int main(int argc, char* argv[]){
    char input[50];
    printf("Type a character: ");
    scanf("%s", input);
    nfa2a(input);
}
#endif
