#include "dfa.h"
#include "nfa.h"
#include <stdbool.h>
#include "IntHashSet.h"
#include "LinkedList.h"
/*
typedef struct Node* Node;

struct Node
{
    IntHashSet set;
    Node next;
    Node prev;
};

struct LinkedList {
    Node first;
    Node last;
}

LinkedList new_LinkedList() {
	LinkedList this = (LinkedList)malloc(sizeof(struct LinkedList));
	this->first = this->last = NULL;
	return this;
}

static Node new_Node(I) {
	Node this = (Node)malloc(sizeof(struct Node));
	this->data = data;
	this->next = this->prev = NULL;
	return this;
}
*/
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

int main() {
    LinkedList new_LinkedList();
}




