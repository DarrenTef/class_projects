#include "mathlib.h"

#include <stdio.h>

static int i;

double pi_madhava(void) {
    double total, num, den, prev = 0.0;
    i = 0;
    do {
        if (i == 0) {
            num = 1;
            total = 1;
            i += 1;
            continue;
        }
        num = num / (-3);
        den = 2 * i + 1;
        prev = total;
        total += num / den;
        i += 1;
    } while (absolute(total - prev) > EPSILON);
    return sqrt_newton(12.0) * total;
}

int pi_madhava_terms(void) {
    return i;
}

// int main(void){
//     printf("madhava pi: %6.16f\t, TERMS: %d", pi_madhava(), i);
//     return 0;
// }
