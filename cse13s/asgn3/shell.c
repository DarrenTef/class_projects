// This implements Shell Sort
#include "shell.h"

#include "gaps.h"
#include "stats.h"

#include <stdint.h>

// how to access each Gap value  and also how to test this also why I need another "stats argument in main function shell_sort()
void shell_sort(Stats *stats, uint32_t *arr, uint32_t length) {
    for (uint32_t gap_index = 0; gap_index < GAPS; gap_index++) {
        uint32_t gap = gaps[gap_index];
        for (uint32_t i = gap; i < length; i++) {
            uint32_t j = i;
            uint32_t temp = move(stats, arr[i]);
            while (j >= gap && cmp(stats, temp, arr[j - gap]) < 0) {
                arr[j] = move(stats, arr[j - gap]);
                j -= gap;
            }
            arr[j] = move(stats, temp);
        }
    }
}
