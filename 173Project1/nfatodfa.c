#include "dfa.h"
#include "nfa.h"
#include <stdbool.h>
#include "IntHashSet.h"
#include "LinkedList.h"

LinkedList LinkedList_add_set(LinkedList list, IntHashSet set){
    if(!LinkedList_contains_set(list, set)){
        LinkedList_add_at_end(list, (void*) set);
    }
    return list;
}

bool LinkedList_contains_set(LinkedList list, IntHashSet set){
    LinkedListIterator iterate = LinkedList_iterator(list);
    while(LinkedListIterator_hasNext(iterate)){
        if(IntHashSet_equals(set, (IntHashSet*) LinkedListIterator_next(iterate))){
            return true;
        }
    }
    return false;
}



void nfatodfa (NFA nfa) {
    LinkedList allStates = new_LinkedList();
    LinkedList processingStates = new_LinkedList();
    LinkedList_add_at_front(allStates, 0);
    LinkedList_add_at_front(processingStates, 0);
 
    IntHashSet cur = new_IntHashSet(20);
    IntHashSet newCur = new_IntHashSet(20);
    IntHashSet tempCur = new_IntHashSet(20);

    char inputSymb[36] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};  


    while(!LinkedList_isEmpty(processingStates)){
        IntHashSet_insert(cur, LinkedList_pop(processingStates));

        for(int i = 0; i < 36; i++){
            
            // newCurr = get_transition2(nfa old, curr, c);
            // if(new_curr is not in allStates) {
            //     put new_curr in allStates;
            //     put new_Curr in states to process;
            // }
            
            // i = index of curr in allState
            // destination = index of newCurr in allState 

            // set_transition(dfa new, i, char, destination);

        }

    }


    // LinkedList allSets = new_LinkedList();
    // IntHashSet curStates = new_IntHashSet(20);
    // IntHashSet newCur = new_IntHashSet(20);
    // IntHashSet tempCur = new_IntHashSet(20);
    // LinkedList_add_at_front(allSets, curStates);
    // LinkedListIterator iterate = LinkedList_iterator(allSets);
    // while(LinkedListIterator_hasNext(iterate)){
    //     LinkedListIterator iterate2 = LinkedList_iterator(curStates);
    //     // for loop outside
    //     // get new cur from transition table
    //     // if no duplicates, add new cur to LinkedList
    //     while(LinkedListIterator_hasNext(iterate2)){

    //         for(int i = 0; i < NFA_INPUT; i++){
    //             // get the set of states from cur and all input symbols
    //             // tempCur = nfa->transitionTable[LinkedList_iterator(iterate2)][i];
    //         }
    //         // union temp cur with new cur
            
    //     }
        
    //     // cur = new cur

    //     }
    }


/*

LinkedList allStates, states to be processed;
put state 0 into both;

while (states to be processed is not empty) {

    pop out the first element in the states to process
    cur = popped out element
    
    for (c in Sigma){

        new_curr = get_transition2(nfa old, curr, c);
        if(new_curr is not in allStates) {
            put new_curr in allStates;
            put new_Curr in states to process;
        }
        i = index of curr in allState
        destination = index of newCurr in allState 

        set_transition(dfa new, i, char, destination);
        
    }


}


*/



