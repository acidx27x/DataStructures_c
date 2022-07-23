#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H


typedef struct Node Node;


typedef struct {
    Node *head;
    Node *tail;
    int length;
    unsigned data_size;
} DLinkedList;


DLinkedList DLinkedList_Constructor(const unsigned data_size);
void DLinkedList_Destructor(DLinkedList *dlist);


void insert_DLL(DLinkedList *dlist, const int index,
        const void *new_data, const int data_count);
void erase_DLL(DLinkedList *dlist, const int index);
void *retrieve_DLL(const DLinkedList *dlist, const int index);

void pushBack_DLL(DLinkedList *dlist,
        const void *new_data, const int data_count);
void pushFront_DLL(DLinkedList *dlist,
        const void *new_data, const int data_count);
void popBack_DLL(DLinkedList *dlist);
void popFront_DLL(DLinkedList *dlist);

void insertionSort_DLL(DLinkedList *dlist,
        int (*compare)(const void *lhs, const void *rhs));
void sortedInsert_DLL(DLinkedList *dlist,
        const void *new_data, const int data_count,
        int (*compare)(const void *lhs, const void *rhs));
int binarySearch_DLL(const DLinkedList *dlist,
        const int left, const int right, const void *data_to_find,
        int (*compare)(const void *lhs, const void *rhs));

void Copy_DLL_F(DLinkedList *dlist_dst,
        const DLinkedList *dlist_src);
void Copy_DLL_B(DLinkedList *dlist_dst,
        const DLinkedList *dlist_src);

void printDListIntF(const DLinkedList *dlist);  //  F - print from head
void printDListIntB(const DLinkedList *dlist);  //  B - print from tail
void printDListStringF(const DLinkedList *dlist);
void printDListStringB(const DLinkedList *dlist);


#endif

