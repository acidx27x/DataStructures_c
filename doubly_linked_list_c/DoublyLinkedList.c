#include "DoublyLinkedList.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>



struct Node {
    struct Node *prev;
    struct Node *next;
    void *data;
    int data_count;
};


Node *initNode(const unsigned data_size, const void *new_data,
        const int data_count);
void freeNode(Node *node);
Node *iterateNode(const DLinkedList *dlist, const int index);



//  DList Functions
DLinkedList DLinkedList_Constructor(const unsigned data_size) {
    DLinkedList new_list;
    new_list.head = NULL;
    new_list.tail = NULL;
    new_list.length = 0;
    new_list.data_size = data_size;

    return new_list;
}

void DLinkedList_Destructor(DLinkedList *dlist) {
    Node *cursor_head = dlist->head;
    Node *cursor_tail = dlist->tail;
    Node *tmp_cursor_head = NULL;
    Node *tmp_cursor_tail = NULL;
    int size = dlist->length;
    for (int i = 0; i < size / 2; ++i) {
        tmp_cursor_head = cursor_head;
        cursor_head = cursor_head->next;
        freeNode(tmp_cursor_head);
        tmp_cursor_tail = cursor_tail;
        cursor_tail = cursor_tail->prev;
        freeNode(tmp_cursor_tail);
    }
    if (size & 0b1)
        freeNode(cursor_head);

    dlist->head = NULL;
    dlist->tail = NULL;
    dlist->length = 0;
}


void insert_DLL(DLinkedList *dlist, const int index,
        const void *new_data, const int data_count) {
    Node *node_to_insert = initNode(dlist->data_size, new_data, data_count);

    if (index == 0) {
        node_to_insert->next = dlist->head;
        if (dlist->length == 0) {
            dlist->tail = dlist->head = node_to_insert;
            ++(dlist->length);
            return;
        }
        dlist->head = dlist->head->prev = node_to_insert;
    } else if (index == dlist->length) {
        node_to_insert->prev = dlist->tail;
        dlist->tail = dlist->tail->next = node_to_insert;
    } else {
        Node *cursor = iterateNode(dlist, index - 1);
        node_to_insert->next = cursor->next;
        node_to_insert->prev = cursor;
        node_to_insert->next->prev = cursor->next = node_to_insert;
    }

    ++(dlist->length);
}

void erase_DLL(DLinkedList *dlist, const int index) {
    Node *node_to_erase = NULL;

    if (index == 0) {
        if (dlist->length == 1) {
            freeNode(dlist->head);
            --(dlist->length);
            return;
        }
        node_to_erase = dlist->head;
        dlist->head = node_to_erase->next;
        dlist->head->prev = NULL;
    } else if (index == dlist->length - 1) {
        node_to_erase = dlist->tail;
        dlist->tail = node_to_erase->prev;
        dlist->tail->next = NULL;
    } else {
        Node *cursor = iterateNode(dlist, index - 1);
        node_to_erase = cursor->next;
        node_to_erase->next->prev = cursor;
        cursor->next = node_to_erase->next;
    }

    freeNode(node_to_erase);
    --(dlist->length);
}

void *retrieve_DLL(const DLinkedList *dlist, const int index) {
    return iterateNode(dlist, index)->data;
}


void pushBack_DLL(DLinkedList *dlist,
        const void *new_data, const int data_count) {
    insert_DLL(dlist, dlist->length, new_data, data_count);
}

void pushFront_DLL(DLinkedList *dlist,
        const void *new_data, const int data_count) {
    insert_DLL(dlist, 0, new_data, data_count);
}

void popBack_DLL(DLinkedList *dlist) {
    erase_DLL(dlist, dlist->length - 1);
}

void popFront_DLL(DLinkedList *dlist) {
    erase_DLL(dlist, 0);
}


//  generic print
#define printListF(list_ptr, data_type, format) \
    Node* cursor = (list_ptr)->head; \
    while (cursor != NULL && (list_ptr)->length > 0) { \
        printf(format, data_type(cursor->data)); \
        cursor = cursor->next; \
    } \
    printf("NULL\n"); \

void printDListIntF(const DLinkedList *dlist) {
    printListF(dlist, *(int*), "%d->");
}

void printDListStringF(const DLinkedList *dlist) {
    printListF(dlist, (char*), "%s->");
}


#define printListB(list_ptr, data_type, format) \
    Node* cursor = (list_ptr)->tail; \
    while (cursor != NULL && (list_ptr)->length > 0) { \
        printf(format, data_type(cursor->data)); \
        cursor = cursor->prev; \
    } \
    printf("NULL\n"); \

void printDListIntB(const DLinkedList *dlist) {
    printListB(dlist, *(int*), "%d->");
}

void printDListStringB(const DLinkedList *dlist) {
    printListB(dlist, (char*), "%s->");
}


void swapData(Node *lhs, Node *rhs) {
    void *data_tmp = lhs->data;
    lhs->data = rhs->data;
    rhs->data = data_tmp;
}

void insertionSort_DLL(DLinkedList *dlist,
        int (*compare)(const void *lhs, const void *rhs)) {
    Node *front = dlist->head;
    Node *back = NULL;
    while (front != NULL) {
        back = front->next;

        while (back != NULL && back->prev != NULL &&
                compare(back->data, back->prev->data) > 0) {
            swapData(back, back->prev);
            back = back->prev;
        }
        front = front->next;
    }
}

void sortedInsert_DLL(DLinkedList *dlist,
        const void *new_data, const int data_count,
        int (*compare)(const void *lhs, const void *rhs)) {
    Node *cursor = dlist->head;
    int index = 0;

    while (cursor != NULL) {
        if (compare(new_data, cursor->data) >= 0) {
            insert_DLL(dlist, index, new_data, data_count);
            return;
        }
        cursor = cursor->next;
        ++index;
    }

    pushBack_DLL(dlist, new_data, data_count);
}

int binarySearch_DLL(const DLinkedList *dlist,
        const int left, const int right, const void *data_to_find,
        int (*compare)(const void *lhs, const void *rhs)) {
    if (left <= right) {
        int mid = left + (right - left) / 2;
        void *value_mid = retrieve_DLL(dlist, mid);

        if (compare(value_mid, data_to_find) == 0)
            return mid;

        if (compare(value_mid, data_to_find) < 0)
            return binarySearch_DLL(dlist, left, mid - 1, data_to_find, compare);

        return binarySearch_DLL(dlist, mid + 1, right, data_to_find, compare);
    }
    return -1;
}


void Copy_DLL_F(DLinkedList *dlist_dst,
        const DLinkedList *dlist_src) {
    Node *src_cursor = dlist_src->head;
    while (src_cursor != NULL) {
        pushBack_DLL(dlist_dst, src_cursor->data, src_cursor->data_count);
        src_cursor = src_cursor->next;
    }
}

void Copy_DLL_B(DLinkedList *dlist_dst,
        const DLinkedList *dlist_src) {
    Node *src_cursor = dlist_src->tail;
    while (src_cursor != NULL) {
        pushBack_DLL(dlist_dst, src_cursor->data, src_cursor->data_count);
        src_cursor = src_cursor->prev;
    }
}



//  Node Functions
Node *initNode(const unsigned data_size, const void *new_data,
        const int data_count) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = malloc(data_size * data_count);
    memmove(new_node->data, new_data, data_size * data_count);
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->data_count = data_count;

    return new_node;
}

void freeNode(Node *node) {
    free(node->data);
    free(node);
}

Node *iterateNode(const DLinkedList *dlist, const int index) {
    Node *cursor = NULL;

    if (index < dlist->length / 2) {
        cursor = dlist->head;
        for (int i = 0; i < index; ++i)
            cursor = cursor->next;
    } else {
        cursor = dlist->tail;
        for (int i = 0; i < dlist->length - index - 1; ++i)
            cursor = cursor->prev;
    }

    return cursor;
}

