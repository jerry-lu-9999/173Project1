#include <stdbool.h>
#include <stdio.h>
#include "dfa.h"
#include "nfa.h"
#include "IntHashSet.h"
#include "LinkedList.h"

bool LinkedList_contains_set(LinkedList list, IntHashSet set){
    LinkedListIterator iterate = LinkedList_iterator(list);
    while(LinkedListIterator_hasNext(iterate)){
        if(IntHashSet_equals(set, LinkedListIterator_next(iterate))){
            return true;
        }
    }
    return false;
}

LinkedList LinkedList_add_set(LinkedList list, IntHashSet set){
    if(!LinkedList_contains_set(list, set)){
        LinkedList_add_at_end(list, (void*) set);
    }
    return list;
}

int getIndexfromList(LinkedList list, IntHashSet set){
    LinkedListIterator it1 = LinkedList_iterator(list);
    int index = 0;
    while(LinkedListIterator_hasNext){
        if(IntHashSet_equals(LinkedListIterator_next(it1), set)){
            return index;
        }
        index++;
    }
    return index;
}

char integerToSymbol(int i){
    char inputSymb[36] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    return inputSymb[i];
}

DFA nfatodfa (NFA nfa) {

    DFA newdfa = new_DFA(20);
    LinkedList allStates = new_LinkedList();
    LinkedList processingStates = new_LinkedList();
    IntHashSet cur = new_IntHashSet(20);
    IntHashSet newCur = new_IntHashSet(20);
    IntHashSet_insert(cur,0);

    LinkedList_add_at_front(allStates, cur);
    LinkedList_add_at_front(processingStates, cur);

    int currentState = 0;

    LinkedListIterator iterator = LinkedList_iterator(processingStates);

    while(!LinkedList_isEmpty(processingStates)){
        IntHashSet pop = LinkedList_pop(processingStates);
        cur = pop;

        IntHashSetIterator curIterator = IntHashSet_iterator(cur);
        while(IntHashSetIterator_hasNext(curIterator)){
        currentState = IntHashSetIterator_next(curIterator);
        
        for(int i = 0; i < 36; i++){

            newCur = (IntHashSet) NFA_get_transitions(nfa, currentState, integerToSymbol(i));
            if(!LinkedList_contains_set(allStates, newCur)){
                printf("Jumped in here!\n");
                LinkedList_add_at_end(allStates,newCur);
                LinkedList_add_at_end(processingStates, newCur);
            }
            printf("This is cur: %s \n", IntHashSet_toString(cur));
            printf("This is newCur: %s \n", IntHashSet_toString(newCur));
            printf("Reached this point!\n");
            int indexCur = getIndexfromList(allStates, cur);
            printf("Index of cur in allStates %d\n", indexCur);
            int destination = getIndexfromList(allStates, newCur);
            printf("Index of destination in allStates %d\n", destination);

            DFA_set_transition(newdfa, indexCur, integerToSymbol(i), destination);
        }
        }  


    }
    return newdfa;  
}





