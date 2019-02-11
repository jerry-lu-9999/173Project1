#ifndef _nfatodfa_h
#define _nfatodfa_h

#include <stdbool.h>
#include "LinkedList.h"
#include "IntHashSet.h"
#include "dfa.h"
#include "nfa.h"

extern bool LinkedList_contains_set(LinkedList list, IntHashSet set);
extern LinkedList LinkedList_add_set(LinkedList list, IntHashSet set);
extern int getIndexfromList(LinkedList list, IntHashSet set);
extern DFA nfatodfa (NFA nfa);
#endif
