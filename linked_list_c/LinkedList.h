#ifndef LINKEDLIST_H
#define LINKEDLIST_H



typedef struct Node Node;


typedef struct {
    Node *head;
    int length;
    unsigned long long data_size;
} LinkedList;


LinkedList LinkedList_Constructor(unsigned long long data_size);
void LinkedList_Destructor(LinkedList *list);


void insertNode(LinkedList *list, int index, void *new_data, int data_count);
void eraseNode(LinkedList *list, int index);
void *retrieveNode(LinkedList *list, int index);

void pushBackNode(LinkedList *list, void *new_data, int data_count);
void pushFrontNode(LinkedList *list, void *new_data, int data_count);
void popBackNode(LinkedList *list);
void popFrontNode(LinkedList *list);

void printListInt(LinkedList *list);
void printListString(LinkedList *list);

void qsortList(LinkedList *list, int left, int right,
        int (*compare)(const void *lhs, const void *rhs));
int binarySearchList(LinkedList *list, int left, int right,
        void *data_to_find, int (*compare)(const void *lhs, const void *rhs));



#endif

