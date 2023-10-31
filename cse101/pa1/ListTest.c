#include "List.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// How do I visually print out each array.
int main(void) {
    // newList();
    List A = newList(); // empty
    List B = newList(); // 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    List C = newList(); // 1, 2, 3, 4, 5
    List D = newList(); // 1, 2, 3, 4, 5, 6, 7, 8, 9, 10

    // append()
    for (int i = 1; i <= 10; i += 1) {
        append(B, i);
        append(D, i);
    }

    // prepend()
    for (int i = 5; i > 0; i -= 1) {
        prepend(C, i);
        prepend(A, i);
    }

    // length()
    printf("\nLength:\n %d\n", length(A));
    printf("%d\n", length(B));
    printf("%d\n", length(C));
    printf("%d\n", length(D));

    // front()
    printf("\nFront:\n");
    // %d\n", front(A));
    printf("%d\n", front(B));
    printf("%d\n", front(C));
    printf("%d\n", front(D));

    // back()
    printf("\nBack\n");
    printf("%d\n", back(B));
    printf("%d\n", back(C));
    printf("%d\n", back(D));

    // moveBack()
    printf("\nMoveBack:\n");
    moveBack(B);
    moveBack(C);
    moveBack(D);
    printf("%d\n", get(B));
    printf("%d\n", get(C));
    printf("%d\n", get(D));

    // movefront()
    printf("\nMoveFront:\n");
    moveFront(B);
    moveFront(C);
    moveFront(D);
    printf("%d\n", get(B));
    printf("%d\n", get(C));
    printf("%d\n", get(D));

    // index()
    printf("\nIndex:\n");
    printf("%d\n", index(B));
    printf("%d\n", index(C));
    printf("%d\n", index(D));
    // assert(index(A) == 0);
    assert(index(B) == 0);
    assert(index(C) == 0);
    assert(index(D) == 0);

    // moveNext()
    printf("\n MoveNext:\n");
    moveNext(B);
    moveNext(C);
    moveNext(D);
    printf("%d\n", index(B));
    printf("%d\n", index(C));
    printf("%d\n", index(D));
    
    // insertAfter()
    printf("\n insertAfter: \n");
    insertAfter(B, 10);
    printList(stdout, B);
    // insertBefore()
    printf("\n insertBefore: \n");
    insertBefore(B, 12);

    printList(stdout, B);
    printf("\n");
    printf("%d\n", get(B));
    printf("%d\n", get(C));
    printf("%d\n", get(D));

    // movePrev()
    printf("\nMovePrev:\n");
    movePrev(B);
    movePrev(C);
    movePrev(D);
    printf("\n");
    printf("%d\n", index(B));
    printf("%d\n", index(C));
    printf("%d\n", index(D));

    // set()
    printf("\nSet: \n");
    for (int i = 0; i < 4; i += 1) {
        moveNext(B);
    }
    set(B, 20);
    printList(stdout, B);
    assert(get(B) == 20);

    // get()
    printf("\nGet: \n");
    printf("%d\n", get(B));
    printf("%d\n", get(C));
    printf("%d\n", get(D));

    // equals()
    printf("\nEquals: \n");
    printf("False\t%d\n", equals(A, B));
    printf("False\t%d\n", equals(B, D));
    printf("False\t%d\n", equals(C, D));
    
    printf("\nPrintList: \n");
    printList(stdout, B);
    printList(stdout, C);
    printList(stdout, D);
    
    // deleteFront(L)
    printf("\ndeleteFront: \n");
    printList(stdout, B);
    deleteFront(B);
    printList(stdout, B);

    // deleteBack(L)
    printf("\ndeleteBack: \n");
    printList(stdout, B);
    deleteBack(B);
    printList(stdout, B);
    
    // delete(L) 
    printf("\ndelete: \n");
    printList(stdout, B);
    delete(B);

    printList(stdout, B);


    // clear()
    printf("\nClear: \n");
    clear(B);
    clear(C);
    clear(D);

    // printList()
    append(A, 1);
    printf("\nPrintList: \n");
    printList(stdout, A);
    printList(stdout, B);
    printList(stdout, C);
    printList(stdout, D);
    

    // freeList()
    freeList(&A);
    freeList(&B);
    freeList(&C);
    freeList(&D);
    return (0);
}
