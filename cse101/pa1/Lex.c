#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"

#define MAX_LENGTH 500

int main(int argc, char **argv) {
    FILE *infile = stdin;
    FILE *outfile = stdout;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    infile = fopen(argv[1], "r");
    if (infile == NULL) {
        fprintf(stderr, "Unable to open %s <input> file\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    outfile = fopen(argv[2], "w");
    if (outfile == NULL) {
        fprintf(stderr, "Unable to open %s <outfile> file\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    // Check if argc is greater than two
    if (infile == NULL) {
        fprintf(stderr, "Lex.c Error, could not open infile, NULL");
        exit(EXIT_FAILURE);
    }

    char buf[MAX_LENGTH];
    int lines = 0;
    while (fgets(buf, MAX_LENGTH, infile) != NULL) {
        lines += 1;
    }

    char **str_arr = calloc(lines, sizeof(char*));
    rewind(infile);

    int counter = 0;
    while (fgets(buf, MAX_LENGTH, infile) != NULL) {
        str_arr[counter] = calloc(MAX_LENGTH, sizeof(char));   // +1 to account for NULL terminator
        strcpy(str_arr[counter], buf);
        counter += 1;
    }
    // Test for the strings in array
    /*
    for(int i = 0; i < lines; i+= 1) {
        printf("%s\n", str_arr[i]);
    }
    */

    // Iterate the string then Iterate the List
    // If smaller you need to append or prepend based on such
    List L = newList();
    prepend(L, 0);
    for (int i = 1; i < lines; i += 1) {
        moveBack(L);
        while ((index(L) != -1) && strcmp(str_arr[i], str_arr[get(L)]) <= 0) {
            movePrev(L);
            //printf("L index: %d\tIndexN Null?:%d \n", index(L), get(L) == NULL);
        }
        if (index(L) == -1) {
            prepend(L, i);
        }
        if (index(L) > -1) {
            insertAfter(L, i);
        }
        //printList(stdout, L);
    }

    printList(stdout, L);
    
    // Prints strings to outfile
    moveFront(L);
    for(int i = 0; i < lines; i += 1){
        fprintf(outfile, "%s", str_arr[get(L)]);
        moveNext(L);
    }
    
    // Frees the array's strings
    for(int i = 0; i < lines; i += 1){
        free(str_arr[i]);
    }

    free(str_arr);
    fclose(infile);
    fclose(outfile);
    freeList(L);
    
// You have an array of strings
// Don't sort the array of strings
// Start with an empty List and start with index zero
// THen insert the one
//
// Suppose you have an array A of strings (c a b d)
// We want L = (1 2 0 3)
// starting:
// L() or empty
// then insert the index 0 of the string array
// so : L = (0)
// then insert the index 1 of the string array (insert before or after)
// Then strcmp(A[0] and A[1]
// insert 2:
// Movefront()
// then ask if index 2 belong before index 0
// Then moveNext if this is false
// Two Loops which walks down to
// Inner loop should terminate if the cursor becomes undefined
// Insert 3:
// Does 3 belong to the left of 0, no so move next
// Does 3 belong to the left of 1, no so movenext
// Does 3 belong to the left of 2, no so move next
// Now the cursor is undefined and so the inner loop breaks
// So if it isn't before anything then it must be the largest value so just append it.
// The outer loop that steps through the string array 
// inner loop steps through the List() array.
// pa1 
}
