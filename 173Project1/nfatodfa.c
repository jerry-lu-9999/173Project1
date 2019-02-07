#include "dfa.h"
#include "nfa.h"
#include <stdbool.h>
#include "IntHashSet.h"
#include "LinkedList.h"

LinkedList LinkedList_add_set(LinkedList list, IntHashSet set){
    if(!LinkedList_contains_set(list, set)){
        LinkedList_add_at_end(list, set);
    }
    return list;
}

bool LinkedList_contains_set(LinkedList list, IntHashSet set){
    LinkedListIterator iterate = LinkedList_iterator(list);
    while(LinkedListIterator_hasNext(iterate)){
        if(IntHashSet_equals(set, LinkedListIterator_next(iterate))){
            return true;
        }
    }
    return false;
}

void nfatodfa (NFA nfa) {
    LinkedList allSets = new_LinkedList();
    
}





