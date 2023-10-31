// Main Test Harness For Code And Will Contain the Main
//
// Synopsis
// 	A collection of comparison-based sorting algorithms
// Usage
// 	./sorting_amd64 [-Hasbhqn:p:r:] [-n length] [-p elements] [-r seed]
// Options
// -H 	Displays program help and usage
// -a 	Enable all sorts
// -s 	Enable Shell sort.
// -b 	Enable batcher sort.
// -h 	enable heap sort.
// -q 	enable Quick sort.
// -n length	Specifiy number of array elements (Default: 100).
// -p elements	specify number of elements to print (default: 100).
// -r seed	specify random seed (default: 13371453).

#include "batcher.h"
#include "heap.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef enum { HEAP, BATCHER, SHELL, QUICK, USAGE, SEED, SIZE, ELEMENTS } set;

#define OPTIONS "Hasbhqn:p:r:"

// create a array
// uint32_t *arr = calloc(sizeof(uint32_t, 1024)
// Then after program is done free(arr).
void new_arr(uint32_t *arr, uint32_t arr_l, uint32_t seed) {
    srandom(seed);
    for (uint32_t i = 0; i < arr_l; i++) {
        uint32_t r = random();
        r &= 0x3FFFFFFF;
        arr[i] = r;
    }
}

void print_loop(uint32_t *arr, uint32_t ele_t_p) {
    for (uint32_t i = 0; i < ele_t_p; i++) {
        if (i == 0) {
            printf("%13d", arr[i]);
            continue;
        }
        if (i % 5 != 0) {
            printf("%13d", arr[i]);
        } else {
            printf("\n%13d", arr[i]);
        }
    }
    printf("\n");
}

int main(int argc, char **argv) {
    // Length of the array, seeding: default 100, elements to print: default 100
    uint32_t arr_len = 100;
    uint32_t seed = 13371453;
    uint32_t elem_to_print = 100;

    Set set = set_empty();
    // Parsing
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'H': set = set_insert(set, USAGE); break;
        case 'a':
            set = set_insert(set, SHELL);
            set = set_insert(set, QUICK);
            set = set_insert(set, BATCHER);
            set = set_insert(set, HEAP);
            break;
        case 's': set = set_insert(set, SHELL); break;
        case 'b': set = set_insert(set, BATCHER); break;
        case 'h': set = set_insert(set, HEAP); break;
        case 'q': set = set_insert(set, QUICK); break;
        case 'n':
            set = set_insert(set, SIZE);
            arr_len = (uint32_t) strtoul(optarg, NULL, 10);
            break;
        case 'p':
            set = set_insert(set, ELEMENTS);
            elem_to_print = (uint32_t) strtoul(optarg, NULL, 10);
            break;
        case 'r':
            set = set_insert(set, SEED);
            seed = (uint32_t) strtoul(optarg, NULL, 10);
            break;
        default: set = set_insert(set, USAGE); break;
        }
    } // End of while Loop for Parsing

    if (arr_len < elem_to_print) {
        elem_to_print = arr_len;
    }

    uint32_t *arr_d = calloc(sizeof(uint32_t), arr_len);
    Stats s;

    if (set_member(set, USAGE)) {
        printf("SYNOPSIS\n A collection of comparison-based sorting algorithms.\n"
               "\n"
               "Usage\n"
               "\n"
               "OPTIONS\n"
               "  -H\t\tDisplay Progam help and usage.\n"
               "  -a\t\tEnable all sorts.\n"
               "  -s\t\tEnable Shell Sort.\n"
               "  -b\t\tEnable Batcher sort.\n"
               "  -h\t\tEnable Heap Sort.\n"
               "  -q\t\tEnable Quick Sort.\n"
               "  -n length\tSpecify number of array elements (default: 100).\n"
               "  -p elements\tSpecify number of elements to print (default: 100).\n"
               "  -r seed\tSpecift random seed (default 13371453).\n");
    } else {
        if (set_member(set, SHELL)) {
            new_arr(arr_d, arr_len, seed);
            shell_sort(&s, arr_d, arr_len);
            printf("Shell Sort, %d elements, %" PRIu64 " moves, %" PRIu64 " compares\n",
                elem_to_print, s.moves, s.compares);
            print_loop(arr_d, elem_to_print);
            reset(&s);
        }
        if (set_member(set, BATCHER)) {
            new_arr(arr_d, arr_len, seed);
            batcher_sort(&s, arr_d, arr_len);
            printf("Batcher Sort, %d elements, %" PRIu64 " moves, %" PRIu64 " compares\n",
                elem_to_print, s.moves, s.compares);
            print_loop(arr_d, elem_to_print);
            reset(&s);
        }
        if (set_member(set, HEAP)) {
            new_arr(arr_d, arr_len, seed);
            heap_sort(&s, arr_d, arr_len);
            printf("Heap Sort, %d elements, %" PRIu64 " moves, %" PRIu64 " compares\n",
                elem_to_print, s.moves, s.compares);
            print_loop(arr_d, elem_to_print);
            reset(&s);
        }
        if (set_member(set, QUICK)) {
            new_arr(arr_d, arr_len, seed);
            quick_sort(&s, arr_d, arr_len);
            printf("Quick Sort, %d elements, %" PRIu64 " moves, %" PRIu64 " compares\n",
                elem_to_print, s.moves, s.compares);
            print_loop(arr_d, elem_to_print);
            reset(&s);
        }
    }

    free(arr_d);
} // End of Main Function Bracket
