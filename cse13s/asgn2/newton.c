#include "mathlib.h"

static int count;

double sqrt_newton(double x) {
    count = 0;
    double prev = 0.0;
    double z = 0.0;
    double y = 1.0;
    double current = y;
    while (absolute(current - prev) > EPSILON) {
        prev = current;
        z = y;
        y = (z + x / z) / 2;
        current = y;
        count += 1;
    }
    return y;
}

int sqrt_newton_iters(void) {
    return count;
}

// int main(void){
//    sqrt_newton(9);
// }
