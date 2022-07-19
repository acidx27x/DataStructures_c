#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H


typedef struct Node Node;


typedef struct {
    Node *head;
    Node *tail;
    int length;
    unsigned data_size;
} DLinkedList;


DLinkedList DLinkedList_Constructor(unsigned data_size);
void DLinkedList_Destructor(DLinkedList *dlist);


void insert_DLL(DLinkedList *dlist, int index, void *new_data, int data_count);
void erase_DLL(DLinkedList *dlist, int index);
void *retrieve_DLL(DLinkedList *dlist, int index);

void pushBack_DLL(DLinkedList *dlist, void *new_data, int data_count);
void pushFront_DLL(DLinkedList *dlist, void *new_data, int data_count);
void popBack_DLL(DLinkedList *dlist);
void popFront_DLL(DLinkedList *dlist);

void insertionSort_DLL(DLinkedList *dlist,
        int (*compare)(const void *lhs, const void *rhs));

void printDListIntF(DLinkedList *dlist);  //  F - print from head
void printDListIntB(DLinkedList *dlist);  //  B - print from tail
void printDListStringF(DLinkedList *dlist);
void printDListStringB(DLinkedList *dlist);


#endif

