/*
 * Darren Lee, dlee181
 * 2023 Winter CSE101 PA2
 * List.c
 * List ADT
 */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "List.h"

// moveFront() has a commented out condition

// structs -------------------------------------------- Done

typedef struct NodeObj *Node;

typedef struct NodeObj {
    int value;
    Node next, prev;
} NodeObj;

typedef struct ListObj {
    Node front, back;
    int size;
    int index;
    Node cursor;
} ListObj;

// Helper --------------------------------------------- Done
Node node_create(int x) {
    Node n = malloc(sizeof(NodeObj));
    if (n == NULL) {
        fprintf(stderr, "Node does not exist in nodeCreate(), Node is be NULL");
        exit(EXIT_FAILURE);
    }
    n->value = x;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

// Constructors - Destructors -------------------------- Done
// Done
List newList(void) {
    List h = malloc(sizeof(ListObj));
    if (h == NULL) {
        fprintf(stderr,
                "List struct does not exist in newList(), List may be NULL");
        exit(EXIT_FAILURE);
    }
    h->front = NULL;
    h->back = NULL;
    h->size = 0;
    h->index = -1;
    h->cursor = NULL;
    return h;
}

// Done
void freeList(List *pL) {
    if (pL != NULL && *pL != NULL) {
        /*
        while (n -> size > 0) {
            deleteFront(*pL);
        }
        */
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}

// Accessors -------------------------------------------
// Done
int length(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error: called: length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->size;
}
// Done
int index(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error: called: index(), L is NULL\n");
        return -1;
    }
    return L->index;
}
// Done
int front(List L) {
    if (length(L) <= 0) {
        fprintf(stderr, "List error: called: front(), length(L) <= 0\n");
        exit(EXIT_FAILURE);
    }
    return L->front->value;
}
// Done
int back(List L) {
    if (length(L) <= 0) {
        fprintf(stderr, "List error: called: back(), length(L) <= 0\n");
        exit(EXIT_FAILURE);
    }
    return L->back->value;
}
// Done
int get(List L) {
    if(L == NULL) {
        fprintf(stderr, "List error: called: get(), length(L) <= 0\n");
    }
    if (length(L) <= 0){
        fprintf(stderr, "List error: called: get(), length(L) <= 0\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        fprintf(stderr, "List error: called: get(), index(L) < 0\n");
        exit(EXIT_FAILURE);
    }
    return L->cursor->value;
}

// Done
bool equals(List A, List B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "List Error, calling equal when A || B  are NULL)");
        exit(EXIT_FAILURE);
    }
    bool equals;

    Node X, Y;

    equals = (A->size == B->size);

    X = A->front;
    Y = B->front;
    while (equals && X != NULL) {
        equals = (X->value == Y->value);
        X = X->next;
        Y = Y->next;
    }
    return equals;
}

// Setters ---------------------------------------------
// Done
void clear(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error, calling clear when L doesn't exist");
        exit(EXIT_FAILURE);
    }
    while (L->size > 0) {
        deleteFront(L);
    }
    L->front = NULL;
    L->back = NULL;
    L->size = 0;
    L->index = -1;
    L->cursor = NULL;
}

// Done
void set(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "List error, calling set when L doesn't exist");
    }
    if (length(L) <= 0 && index(L) < 0) {
        fprintf(stderr, "List error: called: set(), length(L) <= 0 or index(L) < 0\n");
        exit(EXIT_FAILURE);
    }
    L->cursor->value = x;
}

// Done
void moveFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error: called: moveFront(), L is NULL\n");
        exit(EXIT_FAILURE);
    }
    /*
    if (length(L) == 0) {
        fprintf(stderr, "List error: called: moveFront(), L length == 0\n");
        exit(EXIT_FAILURE);
    }
    */
    if (length(L) > 0) {
        L->cursor = L->front;
        L->index = 0;
    }
}

// Done
void moveBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error: called: moveBack(), L is NULL\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) > 0) {
        L->cursor = L->back;
        L->index = L->size - 1;
    }
}
// Check if this is how you make it undefined
void movePrev(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error: called: movePrev(), L is NULL\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor && (L->cursor != L->front)) {
        L->cursor = L->cursor->prev; // Make the cursor one step towards the front
        L->index -= 1;
    }
    else if (L->cursor && (L->cursor == L->front)) {
        L->cursor = NULL;
        L->index = -1;
        // Make Cursor becomes undefined
    }
    // No point if checking if the cursor is undefined
}

void moveNext(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error: called: moveNext(), L is NULL\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor && (L->cursor != L->back)) {
        L->cursor = L->cursor->next; // Make the cursor one step towards the back
        L->index += 1;
    }
    else if (L->cursor && (L->cursor == L->back)) {
        L->cursor = NULL; // Make Cursor becomes undefined
        L->index = -1;
    }
    // No point if checking if the cursor is undefined
}

// Adds a node into the front of the List
// Change old head
// Change head to new node
// Done - but could be a problem
void prepend(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "List error, in prepend(), List L is NULL");
        exit(EXIT_FAILURE);
    }
    Node n = node_create(x);
    if (L->size == 0) {
        n->next = NULL;
        n->prev = NULL;
        L->front = n;
        L->back = n;
    } else {
        n->next = L->front;
        L->front->prev = n;
        L->front = n;
        n->prev = NULL;
    }
    L->size += 1;
    if (L->cursor) {
        L->index += 1;
    }
}
// insert node at the back of the list
// Done
void append(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "List error, in append(), List L is NULL");
        exit(EXIT_FAILURE);
    }
    Node n = node_create(x);
    if (L->size == 0) {
        n->next = NULL;
        n->prev = NULL;
        L->front = n;
        L->back = n;
    }
    else {
        L->back->next = n;
        n->prev = L->back;
        n->next = NULL;
        L->back = n;
    }
    L->size += 1;
}

// Inserts node before the cursor node.
// Check if len() > 0, ind >= 0:
// Do I need to check if cursor is defined?
// Do I need check if Front and Back are defined?
//
// Inserting between node cursor -> prev and node cursor
//
// Steps:
// set the next of new-node to cursor
// set the prev of new-node to cursor -> prev
// set the prev of cursor to new-node
// set the next of cursor -> prev to new-node
// increment size by 1
void insertBefore(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "List error, in insertBefore(), List L is NULL");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0 || index(L) < 0) {
        fprintf(stderr, "List error, in insertBefore(), length() <= 0 or index() < 0");
        exit(EXIT_FAILURE);
    }

    Node n = node_create(x);
    if (L->cursor) {
        n->prev = L->cursor->prev;
        n->next = L->cursor;
        L->cursor->prev = n;
        if (L->cursor == L->front) {
            L->front = n;
        }
        else {
            n->prev->next = n;
        }
    }
    L->size += 1;
    L->index += 1;
}

void insertAfter(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "List error, in insertAfter(), List L is NULL");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0 || index(L) < 0) {
        fprintf(stderr, "List error, in insertAfter(), length() <= 0 or index() < 0");
        exit(EXIT_FAILURE);
    }
    Node n = node_create(x);
    if(L->cursor == L->back) {
        n->next = L->cursor->next;
        n->prev = L->back;
        L->back->next = n;
        L->back = n;
    }
    else {
        n->next = L->cursor->next;
        L->cursor->next->prev = n;
        L->cursor->next = n;
        n->prev = L->cursor;
    }
    L->size += 1;
}

// deletes the front element
void deleteFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error, in deleteFront(), List L is NULL");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        fprintf(stderr, "List error, in deleteFront(), length() <= 0");
        exit(EXIT_FAILURE);
    }

    Node n = NULL;
    n = L->front;
    if (L -> index == 0) {
        L -> cursor = NULL;
        L -> index = -1;
    }
    else {
        L -> index -= 1;
    }

    if (L->size > 1) {
        L->front = L->front->next;
        L->front->prev = NULL;
    }
    else {
        L->front = NULL;
        L->back = NULL;
    }
    L->size -= 1;
    free(n);
    n = NULL;
}

void deleteBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error, in deleteBack(), List L is NULL");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        fprintf(stderr, "List error, in deleteBack(), length() <= 0");
        exit(EXIT_FAILURE);
    }
    Node n = NULL;
    n = L->back;
    if (L -> index == L -> size - 1) {
        L -> cursor = NULL;
        L -> index = -1;
    }
    if (L->size > 1) {
        L->back = L->back->prev;
        L->back->next = NULL;
    }
    else {
        L->back = NULL;
        L->front = NULL;
    }
    L->size -= 1;
    free(n);
    n = NULL;
}

void delete(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error, in delete(), List L is NULL");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0 || index(L) < 0) {
        fprintf(stderr,
                "List error, in delete(), List length <=0 or index < 0");
        exit(EXIT_FAILURE);
    }
    // modify the stuff before and after
    Node n = L->cursor;
    //n = L->cursor;
    if (L->size > 1) {
        if (L->cursor == L->front) {
            deleteFront(L);
            //L->front = n->next;
        }
        else if (L->cursor == L->back) {
            deleteBack(L);
            //L->back = n->prev;
        }
        else {
            n->prev->next = n->next;
            n->next->prev = n->prev;
            free(n);
            n = NULL;
            L->size -= 1;
        }
        L->cursor = NULL;
        L->index = -1;
    }
    else {
        L->front = NULL;
        L->cursor = NULL;
        L->back = NULL;
        L->index = -1;
        free(n);
        n = NULL;
        L->size -= 1;
    }
}

// Other ----------------------------------------
// prints to *out, a string of L consisiting of a space in between with front on
// the left
void printList(FILE *out, List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error in printList");
        exit(EXIT_FAILURE);
    }
    if (out == NULL) {
        fprintf(stderr, "List error in printList(), file is NULL");
        exit(EXIT_FAILURE);
    }
    Node n = L->front;
    // for (n = L->front; n != NULL; n = n->next) {
    for (int i = 0; i < length(L); i += 1) {
        fprintf(out, " %d", n->value);
        n = n->next;
    }
    fprintf(out, "\n");
}
// Make a new List
// Returns new list with the same integer sequence as L.
// Set the cursor to NULL
//
List copyList(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error in copyList(), List is NULL");
        exit(EXIT_FAILURE);
    }
    List A = newList();
    Node n;
    for (n = L->front; n != NULL; n = n->next) {
        append(A, n->value);
    }
    return A;
}
