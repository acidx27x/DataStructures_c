#include "LinkedList.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>



struct Node {
    void *data;
    struct Node *next;
};


Node *initNode(unsigned long long data_size, void *data, int data_count);
void freeNode(Node *node);
Node *iterateNode(LinkedList *list, int index);



// List functions
LinkedList LinkedList_Constructor(unsigned long long data_size) {
    LinkedList new_list;
    new_list.head = NULL;
    new_list.length = 0;
    new_list.data_size = data_size;

    return new_list;
}

void LinkedList_Destructor(LinkedList *list) {
    Node *cursor = list->head;
    Node *tmp_cursor = NULL;
    while (cursor != NULL) {
        tmp_cursor = cursor;
        cursor = cursor->next;
        freeNode(tmp_cursor);
    }
    list->head = NULL;
    list->length = 0;
}


void insertNode(LinkedList *list, int index, void *new_data, int data_count) {
    Node *node_to_insert = initNode(list->data_size, new_data, data_count);

    if (index == 0) {
        node_to_insert->next = list->head;
        list->head = node_to_insert;
        ++(list->length);
        return;
    }

    Node* cursor = iterateNode(list, index - 1);
    node_to_insert->next = cursor->next;
    cursor->next = node_to_insert;
    ++(list->length);
}

void eraseNode(LinkedList *list, int index) {
    if (index == 0) {
        Node *node_to_erase = list->head;
        list->head = node_to_erase->next;
        freeNode(node_to_erase);
        --(list->length);
        return;
    }

    Node *cursor = iterateNode(list, index - 1);
    Node *node_to_erase = cursor->next;
    cursor->next = node_to_erase->next;
    freeNode(node_to_erase);
    --(list->length);
}

void *retrieveNode(LinkedList *list, int index) {
    return iterateNode(list, index)->data;
}


void pushBackNode(LinkedList *list, void *new_data, int data_count) {
    insertNode(list, list->length, new_data, data_count);
}

void pushFrontNode(LinkedList *list, void *new_data, int data_count) {
    insertNode(list, 0, new_data, data_count);
}

void popBackNode(LinkedList *list) {
    eraseNode(list, list->length - 1);
}

void popFrontNode(LinkedList *list) {
    eraseNode(list, 0);
}


//  generic print
#define printList(list_ptr, data_type, format) \
    Node* cursor = (list_ptr)->head; \
    while (cursor != NULL) { \
        printf(format, data_type(cursor->data)); \
        cursor = cursor->next; \
    } \
    printf("NULL\n"); \

void printListInt(LinkedList *list) {
    printList(list, *(int*), "%d->");
}

void printListString(LinkedList *list) {
    printList(list, (char*), "%s->");
}


void swapNode(LinkedList *list, int i, int j) {
    void *tmp_node = retrieveNode(list, i);
    iterateNode(list, i)->data = iterateNode(list, j)->data;
    iterateNode(list, j)->data = tmp_node;
}

void qsortList(LinkedList *list, int left, int right,
        int (*compare)(const void *lhs, const void *rhs)) {
    if (left >= right)
        return;
    swapNode(list, left, (left + right) / 2);
    int last = left;
    void *left_data = retrieveNode(list, left);
    for (int i = left + 1; i <= right; ++i)
        if (compare(retrieveNode(list, i), left_data) > 0)
            swapNode(list, ++last, i);
    swapNode(list, left, last);

    qsortList(list, left, last - 1, compare);
    qsortList(list, last + 1, right, compare);
}

int binarySearchList(LinkedList *list, int left, int right,
        void *data_to_find, int (*compare)(const void *lhs, const void *rhs)) {
    if (right >= left) {
        int mid = left + (right - left) / 2;
        void *value_mid = retrieveNode(list, mid);

        if (compare(value_mid, data_to_find) == 0)
            return mid;

        if (compare(value_mid, data_to_find) < 0)
            return binarySearchList(list, left, mid - 1, data_to_find, compare);

        return binarySearchList(list, mid + 1,right, data_to_find, compare);
    }

    return -1;
}



//  Node functions
Node *initNode(unsigned long long data_size, void *new_data, int data_count) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = malloc(data_size * data_count);
    memmove(new_node->data, new_data, data_size * data_count);
    new_node->next = NULL;

    return new_node;
}

void freeNode(Node *node) {
    free(node->data);
    free(node);
}

Node *iterateNode(LinkedList *list, int index) {
    Node *cursor = list->head;
    for (int i = 0; i < index; ++i)
        cursor = cursor->next;
    return cursor;
}

