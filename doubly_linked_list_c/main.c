#include "DoublyLinkedList.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int compareInt(const void *lhs, const void *rhs) {
    const int a = *(const int*)lhs;
    const int b = *(const int*)rhs;

    return (a < b) ? 1 : (a > b) ? -1 : 0;
}


int func1(void) {
    DLinkedList dlist_int = DLinkedList_Constructor(sizeof(int));

    srand(time(NULL));

    printf("random numbers\n");
    for (int i = 0; i < 15; ++i) {
        int num = rand() % 228;
        printf("%d ", num);
        pushBack_DLL(&dlist_int, &num, 1);
    }
    putchar('\n');

    printf("numbers in dll after pushback\n");
    printDListIntF(&dlist_int);

    printf("new random numbers\n");
    for (int i = 0; i < 15; ++i) {
        int num = rand() % 228;
        printf("%d ", num);
        pushFront_DLL(&dlist_int, &num, 1);
    }
    putchar('\n');

    printf("numbers in dll after pushfront\n");
    printDListIntF(&dlist_int);
    printf("print dll in reverse\n");
    printDListIntB(&dlist_int);

    printf("sorted dll\n");
    insertionSort_DLL(&dlist_int, compareInt);
    printDListIntF(&dlist_int);
    printDListIntB(&dlist_int);

    printf("insert in 10th pos 1337\n");
    insert_DLL(&dlist_int, 10, &(int){1337}, 1);
    printDListIntF(&dlist_int);
    printDListIntB(&dlist_int);

    printf("erase 10th pos and make 2 pops front and back\n");
    erase_DLL(&dlist_int, 10);
    popFront_DLL(&dlist_int);
    popFront_DLL(&dlist_int);
    popBack_DLL(&dlist_int);
    popBack_DLL(&dlist_int);
    printDListIntF(&dlist_int);
    printDListIntB(&dlist_int);

    DLinkedList_Destructor(&dlist_int);
    return 0;
}


int main() {
    srand(time(NULL));

    DLinkedList frst = DLinkedList_Constructor(sizeof(int));
    for (int i = 0; i < 15; ++i) {
        int num = rand() % 228;
        printf("%d ", num);
        sortedInsert_DLL(&frst, &num, 1, compareInt);
    }
    putchar('\n');

    DLinkedList scnd = DLinkedList_Constructor(sizeof(int));
    Copy_DLL_F(&scnd, &frst);
    erase_DLL(&frst, 3);
    erase_DLL(&frst, 5);

    printDListIntF(&frst);
    printDListIntF(&scnd);

    int find = *(int*)retrieve_DLL(&scnd, 5);
    printf("to find on 5th place ==%d==\n", find);
    printf("length ==%d==\n", scnd.length);
    printf("==%d==\n", binarySearch_DLL(&scnd, 0, scnd.length - 1, &find, compareInt));

    return 0;
}

