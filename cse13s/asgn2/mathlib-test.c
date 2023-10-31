// This is the main test harness for implemented math library
#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#define OPTIONS "aebmrvnsh"

int main(int argc, char **argv) {
    // TRUE PI
    // TRUE exp()
    double pi = M_PI;
    double eul = M_E;

    // MY VERSION OF FUNCTIONS: EULER, PIs, and SQRT_NEWTON
    double my_e = e();
    double my_pi_euler = pi_euler();
    double my_pi_bbp = pi_bbp();
    double my_pi_madhava = pi_madhava();
    double my_pi_viete = pi_viete();

    // BOOLS
    bool e = false;
    bool m = false;
    bool r = false;
    bool v = false;
    bool n = false;
    bool b = false;
    bool h = false;
    bool s = false;

    // THE GETOPT()
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            e = true;
            b = true;
            m = true;
            v = true;
            r = true;
            n = true;
            break;
        case 'e': e = true; break;
        case 'b': b = true; break;
        case 'm': m = true; break;
        case 'v': v = true; break;
        case 'r': r = true; break;
        case 'n': n = true; break;
        case 's': s = true; break;
        case 'h': h = true; break;
        default: h = true; break;
        }
    }

    if (h) {
        printf("SYNOPSIS\n\tA test harness for the small numerical "
               "library.\n\nUSAGE\n\n\t./mathlib-test [-aebmrvnsh]\n\nOPTIONS\n   "
               "-a\tRuns all tests.\n   -e\tRuns e test.\n   -b\tRuns BBP pi test.\n  "
               " -m\tRuns Madhava pi test.\n   -r\tRuns Euler pi test.\n   -v\tRuns "
               "Viete pi test.\n   -n\tRuns Newton square root tests.\n   -s\tPrint "
               "verbose statistics.\n   -h\tDisplay program synopsis and usage.\n");
    } else {
        if (e) {
            printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", my_e, eul,
                absolute(eul - my_e));
            if (s) {
                printf("e() terms = %d\n", e_terms());
            }
        }
        if (b) {
            printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", my_pi_bbp, pi,
                absolute(my_pi_bbp - pi));
            if (s) {
                printf("pi_bbp() terms = %d\n", pi_bbp_terms());
            }
        }
        if (m) {
            printf("pi_madhava = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", my_pi_madhava, pi,
                absolute(my_pi_madhava - pi));
            if (s) {
                printf("pi_madhava() terms = %d\n", pi_madhava_terms());
            }
        }
        if (v) {
            printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", my_pi_viete, pi,
                absolute(my_pi_viete - pi));
            if (s) {
                printf("pi_viete() terms = %d\n", pi_viete_factors());
            }
        }
        if (r) {
            printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", my_pi_euler, pi,
                absolute(my_pi_euler - pi));
            if (s) {
                printf("pi_euler() terms = %d\n", pi_euler_terms());
            }
        }
        if (n) {
            for (double i = 0.0; i < 10.05; i += 0.1) {
                printf("sqrt_newton(%16.15lf) = %16.15f, sqrt(%16.15lf) = %16.15lf, "
                       "diff = %16.15lf\n",
                    i, sqrt_newton(i), i, sqrt(i), absolute(sqrt(i) - sqrt_newton(i)));
                if (s) {
                    printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
                }
            }
        } else if (s) {
            printf("SYNOPSIS\n\tA test harness for the small numerical "
                   "library.\n\nUSAGE\n\n\t./mathlib-test-amd64 "
                   "[-aebmrvnsh]\n\nOPTIONS\n   -a\tRuns all tests.\n   -e\tRuns e "
                   "test.\n   -b\tRuns BBP pi test.\n   -m\tRuns Madhava pi test.\n  "
                   " -r\tRuns Euler pi test.\n   -v\tRuns Viete pi test.\n   "
                   "-n\tRuns Newton square root tests.\n   -s\tPrint verbose "
                   "statistics.\n   -h\tDisplay program synopsis and usage.\n");
        }
    }
    return 0;
}
