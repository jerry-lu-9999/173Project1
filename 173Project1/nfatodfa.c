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

    IntHashSet unionSet[36];
    for (int i = 0; i < 36; i++){
    	unionSet[i] = (IntHashSet)malloc(36*sizeof(IntHashSet));
        unionSet[i] = new_IntHashSet(1);
    }
    IntHashSet cur = new_IntHashSet(20);
    IntHashSet newCur = new_IntHashSet(20);
    IntHashSet_insert(cur, 0);

    //put cur in to allstate list and process lsit
    LinkedList_add_at_front(allStates, cur);
    LinkedList_add_at_front(processingStates, cur);

    int currentState = 0;
    int indexCur = 0;
    int destination = 0;

    while (!LinkedList_isEmpty(processingStates))
    {
        printf("LOOP ALLSTATES\n");
        IntHashSet pop = LinkedList_pop(processingStates);
        cur = pop;

        
        IntHashSetIterator curIterator = IntHashSet_iterator(cur);
        while (IntHashSetIterator_hasNext(curIterator))
        {
            printf("LOOP CURR\n");
            currentState = IntHashSetIterator_next(curIterator);

            for (int i = 0; i < 36; i++)
            {
                printf("LOOP INPUT CHARACTERS\n");
                newCur = (IntHashSet)NFA_get_transitions(nfa, currentState, integerToSymbol(i));
                IntHashSet_print(newCur);
                // IntHashSet_print(unionSet[i]);
                // bool b = IntHashSet_equals(unionSet[i], newCur);
                // printf("\nat %d it's equal? %d\n",i, b);
                if (!IntHashSet_equals(unionSet[i], newCur)) //tested that it does not equal
                {
                    printf("innn:\n");
                    IntHashSet_union(unionSet[i], newCur); //THIS IS WHERE EVERYTHING STOPS
                    printf("UNION SET:\n");
                    IntHashSet_print(unionSet[i]);
                    {
                        /* data */
                    }
                }

                // put every transition set we get into a array with 36 elements

                // if (!IntHashSet_isEmpty(newCur))
                // {
                //     printf("\nAt input character %c... \n", integerToSymbol(i));

                //     if (!LinkedList_contains_set(allStates, newCur))
                //     {
                //         // printf("Jumped in here!\n");
                //         LinkedList_add_at_end(allStates, newCur);
                //         LinkedList_add_at_end(processingStates, newCur);
                //     }
                //     printf("This is cur: %s \n", IntHashSet_toString(cur));
                //     printf("This is newCur: %s \n", IntHashSet_toString(newCur));
                //     indexCur = getIndexfromList(allStates, cur);

                //     printf("Index of cur in allStates %d\n", indexCur);
                //     destination = getIndexfromList(allStates, newCur);
                //     printf("Index of destination in allStates %d\n", destination);
                //     printf("At destination %d, this is new cur: \n", destination);
                //     IntHashSet_print(newCur);

                //     DFA_set_transition(newdfa, indexCur, integerToSymbol(i), destination);
                // }
            }
        }
        for (int i = 0; i < 36; i++)
        {
            if (!LinkedList_contains_set(allStates, unionSet[i]))
            {
                LinkedList_add_at_end(allStates, unionSet[i]);
                LinkedList_add_at_end(processingStates, unionSet[i]);
            }
            printf("This is cur: %s \n", IntHashSet_toString(cur));
            printf("This is newCur: %s \n", IntHashSet_toString(unionSet[i]));
            indexCur = getIndexfromList(allStates, cur);
            printf("Index of cur in allStates %d\n", indexCur);
            destination = getIndexfromList(allStates, unionSet[i]);
            printf("Index of destination in allStates %d\n", destination);
            printf("At destination %d, this is new cur: \n", destination);
            IntHashSet_print(unionSet[i]);

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
                printf("DFA accepting state: %d\n", getIndexfromList(allStates, curSet));
            }
            else
            {
                DFA_set_accepting(newdfa, getIndexfromList(allStates, curSet), false);
            }
        }
    }
    return newdfa;
}
