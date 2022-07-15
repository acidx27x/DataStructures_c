#include "LinkedList.h"
#include <stdio.h>
#include <string.h>

#define insertNode(str, pos, data, ...) insertNode(str, pos, data, (1, ##__VA_ARGS__))
#define pushBackNode(str, data, ...) pushBackNode(str, data, (1, ##__VA_ARGS__))
#define pushFrontNode(str, data, ...) pushFrontNode(str, data, (1, ##__VA_ARGS__))



void test1(void) {
    LinkedList list_int = LinkedList_Constructor(sizeof(int));

    printf("length - %d, data_size - %llu\n", list_int.length, list_int.data_size);

    for (int i = 0; i < 10; ++i) {
        insertNode(&list_int, i, (void*)&i);
    }

    printf("print nodes:\n");
    printListInt(&list_int);
    printf("length - %d, data_size - %llu\n", list_int.length, list_int.data_size);

    printf("erase 2 and 3 positions");
    eraseNode(&list_int, 2);
    eraseNode(&list_int, 3);

    printf("print nodes:\n");
    printListInt(&list_int);
    printf("length - %d, data_size - %llu\n", list_int.length, list_int.data_size);

    printf("6th node = %d\n", *(int*)retrieveNode(&list_int, 6));

    LinkedList_Destructor(&list_int);
}

int cmpStr(const void *a, const void *b) {
    const char *str1 = (const char*)a;
    const char *str2 = (const char*)b;

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    return (len1 < len2) ? 1 : (len1 > len2) ? -1 : 0;
}

void test2(void) {
    LinkedList list_str = LinkedList_Constructor(sizeof(char));

    printf("enter 5 words\n");
    for (int i = 0; i < 5; ++i) {
        char str[100];
        fgets(str, 100, stdin);
        str[strcspn(str, "\n")] = '\0';
        pushFrontNode(&list_str, (void*)str, strlen(str) + 1);
    }

    printListString(&list_str);
    printf("pop first node and sort\n");
    popFrontNode(&list_str);
    qsortList(&list_str, 0, list_str.length - 1, cmpStr);
    printListString(&list_str);

    printf("find elem with strlen = 4 via binsearch = %d\n", binarySearchList(&list_str, 0, list_str.length - 1, (void*)"frfr", cmpStr));

    LinkedList_Destructor(&list_str);
}


int main(void) {
    //test1();
    test2();
}

