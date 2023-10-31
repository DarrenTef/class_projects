#include "mathlib.h"
static int i;

double pi_euler(void) {
    double total = 0.0;
    double num = 1.0;
    double prev = 0.0;
    i = 1;
    do {
        prev = total;
        total += num / (i * i);
        i += 1;
    } while ((total - prev) > EPSILON);
    return sqrt_newton(total * 6);
}

int pi_euler_terms(void) {
    return i;
}

// int main(void){
//     pi_euler();
// }
