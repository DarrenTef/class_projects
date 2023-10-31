#include "mathlib.h"

#include <stdbool.h>
#include <stdio.h>

static int i;

double pi_bbp(void) {
    double total = 0.0;
    double a, b, c, d = 0.0;
    double prev = 0.0;
    double base = 1.0;
    i = 0;
    do {
        a = 4.0 / (8.0 * i + 1);
        b = 2.0 / (8.0 * i + 4);
        c = 1.0 / (8.0 * i + 5);
        d = 1.0 / (8.0 * i + 6);
        prev = total;
        total += base * (a - b - c - d);
        base = base / 16.0;
        i += 1;
    } while (total - prev > EPSILON);
    return total;
}

int pi_bbp_terms(void) {
    return i;
}
