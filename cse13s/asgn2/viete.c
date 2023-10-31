#include "mathlib.h"

#include <stdbool.h>
#include <stdio.h>

static int count;

double pi_viete(void) {
    double total = 0.0;
    double prev = 0.0;
    double num = sqrt_newton(2.0);
    double den = 2.0;
    count = 1;
    do {
        if (count == 1) {
            total += num / den;
            count += 1;
        }
        prev = total;
        num = sqrt_newton(2 + num);
        total *= num / den;
        count += 1;
    } while (absolute(total - prev) > EPSILON);
    return 2 / total;
}

int pi_viete_factors(void) {
    return count;
}
