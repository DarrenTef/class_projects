#include "mathlib.h"

#include <stdbool.h>
#include <stdio.h>

static int e_count;

double e(void) {
    double fact = 0.0;
    double total = 0.0;
    double prev_t = 0.0;
    e_count = 0;
    bool t = true;
    while (e_count == 0 || e_count == 1) {
        fact = 1.0;
        prev_t = total;
        total += 1.0 / fact;
        e_count += 1;
    }
    while (t) {
        fact = fact * e_count;
        prev_t = total;
        total += 1.0 / (fact);
        e_count += 1;
        if (total - prev_t < EPSILON) {
            t = false;
        }
    }
    return total;
}

int e_terms(void) {
    return e_count;
}
