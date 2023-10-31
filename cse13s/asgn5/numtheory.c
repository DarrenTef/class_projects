#include "numtheory.h"
#include <gmp.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "randstate.h"
#include <stdlib.h>
#include <assert.h>
#include <check.h>

void pow_mod(mpz_t o, mpz_t a, mpz_t d, mpz_t n) {
    mpz_t v, p, d_t;
    mpz_inits(v, p, d_t, NULL);
    mpz_set_ui(v, 1);
    mpz_set(p, a);
    mpz_set(d_t, d);
    while (mpz_cmp_ui(d_t, 0) > 0) {
        if (mpz_odd_p(d_t)) {
            mpz_mul(v, v, p);
            mpz_mod(v, v, n);
        }
        mpz_mul(p, p, p);
        mpz_mod(p, p, n);
        mpz_fdiv_q_ui(d_t, d_t, 2);
    }
    mpz_set(o, v);
    mpz_clears(v, p, d_t, NULL);
}

void gcd(mpz_t d, mpz_t a, mpz_t b) {
    mpz_t a_p, b_p, t;
    mpz_inits(a_p, b_p, t, NULL);
    mpz_set(a_p, a);
    mpz_set(b_p, b);
    while (mpz_cmp_ui(b_p, 0) != 0) {
        mpz_set(t, b_p);
        mpz_mod(b_p, a_p, b_p);
        mpz_set(a_p, t);
    }
    mpz_set(d, a_p);
    mpz_clears(a_p, b_p, t, NULL);
}

bool is_prime(mpz_t n, uint64_t iters) {
    if (mpz_cmp_ui(n, 2) < 0) {
        return false;
    }
    if (mpz_cmp_ui(n, 2) == 0) {
        return true;
    }

    if (mpz_cmp_ui(n, 3) == 0) {
        return true;
    }

    if (mpz_cmp_ui(n, 4) == 0) {
        return false;
    }

    mpz_t r, s, a, y, j, i, n_c, n_f, s_c, t;
    mpz_inits(r, s, a, y, j, i, n_c, n_f, s_c, t, NULL);
    mpz_sub_ui(r, n, 1);
    mpz_sub_ui(n_c, n, 1);
    mpz_set_ui(t, 2);
    mpz_sub_ui(n_f, n, 4);
    while (mpz_even_p(r)) {
        mpz_fdiv_q_ui(r, r, 2);
        mpz_add_ui(s, s, 1);
    }
    mpz_sub_ui(s_c, s, 1);
    for (mpz_set_ui(i, 1); mpz_cmp_ui(i, iters) < 0; mpz_add_ui(i, i, 1)) {
        mpz_urandomm(a, state, n_f);
        mpz_add_ui(a, a, 2);
        pow_mod(y, a, r, n);
        if ((mpz_cmp_ui(y, 1) != 0) && mpz_cmp(y, n_c) != 0) {
            mpz_set_ui(j, 1);
            while ((mpz_cmp(j, s_c) <= 0) && (mpz_cmp(y, n_c) != 0)) {
                pow_mod(y, y, t, n);
                if (mpz_cmp_ui(y, 1) == 0) {
                    return false;
                }
                mpz_add_ui(j, j, 1);
            }
            if (mpz_cmp(y, n_c) != 0) {
                return false;
            }
        }
    }
    return true;
    mpz_clears(r, s, a, y, j, i, n_c, s_c, n_f, t, NULL);
}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    assert(bits > 0);

    mpz_t r;
    mpz_inits(r, NULL);
    do {
        mpz_urandomb(r, state, bits);
        mpz_setbit(r, bits);
    } while (is_prime(r, iters) == false);
    mpz_set(p, r);
    mpz_clears(r, NULL);
}

void mod_inverse(mpz_t o, mpz_t a, mpz_t n) {
    mpz_t r_a, r_p, t_a, t_p, q, tmp;
    mpz_inits(r_a, r_p, t_a, t_p, q, tmp, NULL);
    mpz_set(r_a, n);
    mpz_set(r_p, a);
    mpz_set_ui(t_a, 0);
    mpz_set_ui(t_p, 1);
    while (mpz_cmp_ui(r_p, 0) != 0) {
        mpz_fdiv_q(q, r_a, r_p);
        mpz_set(tmp, r_a);
        mpz_set(r_a, r_p);
        mpz_submul(tmp, q, r_p);
        mpz_set(r_p, tmp);
        mpz_set(tmp, t_a);
        mpz_set(t_a, t_p);
        mpz_submul(tmp, q, t_p);
        mpz_set(t_p, tmp);
    }
    if (mpz_cmp_ui(r_a, 1) > 0) {
        mpz_set_ui(o, 0);
        return;
    }
    if (mpz_cmp_ui(t_a, 0) < 0) {
        mpz_add(t_a, t_a, n);
    }
    mpz_set(o, t_a);
    mpz_clears(r_a, r_p, t_a, t_p, q, tmp);
}
