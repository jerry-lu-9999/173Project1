#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "dfa.h"
#include "nfa.h"
#include "IntHashSet.h"
#include "LinkedList.h"

bool LinkedList_contains_set(LinkedList list, IntHashSet set)
{
    LinkedListIterator iterate = LinkedList_iterator(list);
    while (LinkedListIterator_hasNext(iterate))
    {
        if (IntHashSet_equals(set, LinkedListIterator_next(iterate)))
        {
            return true;
        }
    }
    return false;
}

LinkedList LinkedList_add_set(LinkedList list, IntHashSet set)
{
    if (!LinkedList_contains_set(list, set))
    {
        LinkedList_add_at_end(list, (void *)set);
    }
    return list;
}

int getIndexfromList(LinkedList list, IntHashSet set)
{
    LinkedListIterator it1 = LinkedList_iterator(list);
    int index = 0;
    while (&LinkedListIterator_hasNext)
    {
        if (IntHashSet_equals(LinkedListIterator_next(it1), set))
        {
            return index;
        }
        index++;
    }
    return index;
}

char integerToSymbol(int i)
{
    char inputSymb[36] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    return inputSymb[i];
}

DFA nfatodfa(NFA nfa)
{

    DFA newdfa = new_DFA(20);
    LinkedList allStates = new_LinkedList();
    LinkedList processingStates = new_LinkedList();


    IntHashSet cur = new_IntHashSet(20);
    IntHashSet newCur = new_IntHashSet(20);
    IntHashSet_insert(cur, 0);

    LinkedList_add_at_front(allStates, cur);
    LinkedList_add_at_front(processingStates, cur);

    int currentState = 0;
    int indexCur = 0;
    int destination = 0;

    while (!LinkedList_isEmpty(processingStates))
    {
            IntHashSet unionSet[36];
        for (int i = 0; i < 36; i++){
    	    unionSet[i] = (IntHashSet)malloc(36*sizeof(IntHashSet));
            unionSet[i] = new_IntHashSet(1);
        }
        IntHashSet pop = LinkedList_pop(processingStates);
        cur = pop;
        IntHashSetIterator curIterator = IntHashSet_iterator(cur);
        while (IntHashSetIterator_hasNext(curIterator))
        {
            currentState = IntHashSetIterator_next(curIterator);
            for (int i = 0; i < 36; i++)
            {
                newCur = (IntHashSet)NFA_get_transitions(nfa, currentState, integerToSymbol(i));
                if (!IntHashSet_equals(unionSet[i], newCur)) //tested that it does not equal
                {
                    IntHashSet_union(unionSet[i], newCur); //THIS IS WHERE EVERYTHING STOPS
                }
            }
        }

        for (int i = 0; i < 36; i++)
        {
            if (!LinkedList_contains_set(allStates, unionSet[i]))
            {
                LinkedList_add_at_end(allStates, unionSet[i]);
                LinkedList_add_at_end(processingStates, unionSet[i]);
            }
            indexCur = getIndexfromList(allStates, cur);
            destination = getIndexfromList(allStates, unionSet[i]);

            DFA_set_transition(newdfa, indexCur, integerToSymbol(i), destination);            
        }
    }

    LinkedListIterator itAccept = LinkedList_iterator(allStates);
    while (LinkedListIterator_hasNext(itAccept))
    {
        IntHashSet curSet = LinkedListIterator_next(itAccept);
        IntHashSetIterator itState = IntHashSet_iterator(curSet);
        while (IntHashSetIterator_hasNext(itState))
        {
            int acceptState = IntHashSetIterator_next(itState);
            if (NFA_get_accepting(nfa, acceptState))
            {
                DFA_set_accepting(newdfa, getIndexfromList(allStates, curSet), true);
            }
            else
            {
                DFA_set_accepting(newdfa, getIndexfromList(allStates, curSet), false);
            }
        }
    }
    return newdfa;
}
